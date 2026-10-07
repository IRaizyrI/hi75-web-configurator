import { assessCandidate } from "./fingerprint.js";
import { REPORT_ID, MAX_CHUNK, buildBody, parseReply } from "../protocol/frame.js";
import { EFFECTS, LED_EFFECT_OFFSET, LED_ENTRY_BASE, encodeLighting } from "../protocol/lighting.js";
import { MACRO_BUFFER_BYTES, encodeMacros } from "../protocol/macros.js";

// Read commands only. The firmware read dispatcher (CODE 0x4E1E) serves these
// from flash; none reaches the erase/program routine at 0xA252.
const READ_COMMANDS = new Set([0x82, 0x83, 0x84, 0x85, 0x86, 0x8a]);
const WRITE_COMMANDS = new Set([0x03, 0x04, 0x05, 0x06, 0x0a]);
const GET_DELAY_MS = 20;
const WRITE_SETTLE_MS = 100;
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
const bytesOf = (view) => new Uint8Array(view.buffer, view.byteOffset, view.byteLength).slice();

export class Hi75Session {
  constructor(device) {
    this.device = device;
    this.inputReports = [];
    this.onInput = (e) => this.inputReports.push({ reportId: e.reportId, data: bytesOf(e.data) });
  }

  static async open(device) {
    if (assessCandidate(device).status !== "descriptor-layout candidate") {
      throw new Error("Browser-visible HID layout does not match the Hi75 vendor interface");
    }
    const session = new Hi75Session(device);
    if (!device.opened) await device.open();
    device.addEventListener("inputreport", session.onInput);
    return session;
  }

  async close() {
    this.device.removeEventListener("inputreport", this.onInput);
    if (this.device.opened) await this.device.close();
  }

  // Writes go through firmware 0xA252, which erases and reprograms a 512-byte
  // flash sector immediately. Enabled: layers 0x03, LED 0x04, macros 0x05, key colours 0x06, palette 0x0A.
  // Only macros (0x05) span several sectors: the firmware writes chunk i to
  // 0xDC00 + 0x200 x i.
  async write(command, arg, data) {
    if (!WRITE_COMMANDS.has(command)) throw new Error(`0x${command.toString(16)} is not an enabled write command`);
    if (data.length > MAX_CHUNK && command !== 0x05) throw new RangeError("Multi-chunk writes are only enabled for macros");
    const chunkCount = Math.max(1, Math.ceil(data.length / MAX_CHUNK));
    for (let i = 0; i < chunkCount; i++) {
      const chunk = data.subarray(i * MAX_CHUNK, (i + 1) * MAX_CHUNK);
      await this.device.sendFeatureReport(REPORT_ID, buildBody({ command, arg, chunkCount, chunkIndex: i, data: chunk }));
      await sleep(WRITE_SETTLE_MS);
    }
  }

  // One SET/GET for a single chunk index (used to read code via the 16-bit
  // address wrap in the read dispatcher; see protocol/knob-patch.js).
  async readChunk(command, arg, chunkIndex, length) {
    if (!READ_COMMANDS.has(command)) throw new Error(`0x${command.toString(16)} is not an allowed read command`);
    await this.device.sendFeatureReport(REPORT_ID, buildBody({ command, arg, chunkCount: 1, chunkIndex, length }));
    await sleep(GET_DELAY_MS);
    const reply = parseReply(bytesOf(await this.device.receiveFeatureReport(REPORT_ID)));
    if (reply.command !== command || reply.chunkIndex !== chunkIndex || reply.data.length < length) throw new Error("Unexpected reply to chunk read");
    return reply.data.subarray(0, length);
  }

  // One SET/GET pair per chunk, no retries. Returns concatenated data.
  async read(command, arg, totalLength) {
    if (!READ_COMMANDS.has(command)) throw new Error(`0x${command.toString(16)} is not an allowed read command`);
    const chunkCount = Math.max(1, Math.ceil(totalLength / MAX_CHUNK));
    const out = new Uint8Array(totalLength);
    for (let i = 0; i < chunkCount; i++) {
      const length = Math.min(MAX_CHUNK, totalLength - i * MAX_CHUNK);
      await this.device.sendFeatureReport(REPORT_ID, buildBody({ command, arg, chunkCount, chunkIndex: i, length }));
      await sleep(GET_DELAY_MS);
      const reply = parseReply(bytesOf(await this.device.receiveFeatureReport(REPORT_ID)));
      if (reply.command !== command || reply.chunkIndex !== i) {
        throw new Error(`Unexpected reply header for 0x${command.toString(16)} chunk ${i}: cmd 0x${reply.command.toString(16)} chunk ${reply.chunkIndex}`);
      }
      if (reply.data.length < length) throw new Error(`Short reply for 0x${command.toString(16)} chunk ${i}: ${reply.data.length}/${length} bytes`);
      out.set(reply.data.subarray(0, length), i * MAX_CHUNK);
    }
    return out;
  }
}

// Full read-only snapshot. Layer/RGB/macro reads request whole 512-byte
// sectors because the firmware writes whole sectors.
export async function readConfiguration(session, onStep = () => {}) {
  const result = { readAt: new Date().toISOString() };
  onStep("identity");
  result.identity = await session.read(0x82, 1, 6);
  onStep("lighting");
  result.led = await session.read(0x84, 0, 128);
  onStep("rgb table");
  result.rgbTable = await session.read(0x8a, 0, 512);
  result.layers = [];
  for (let layer = 0; layer < 4; layer++) {
    onStep(`layer ${layer}`);
    result.layers.push(await session.read(0x83, layer, 512));
  }
  onStep("macros");
  result.macros = await session.read(0x85, 0, MACRO_BUFFER_BYTES);
  onStep("key colours");
  result.keyColors = await session.read(0x86, 0, 512);
  return result;
}

export const LED_BRIGHTNESS_OFFSET = 60;
export const LED_BRIGHTNESS_LEVELS = [0, 1, 2, 3, 4]; // KB.ini LightHW

// Read-modify-write of the 128-byte LED block, changing only the given
// bytes, then read back.
export async function setLedBytes(session, changes) {
  const before = await session.read(0x84, 0, 128);
  if (before[126] !== 0x5a || before[127] !== 0xa5) throw new Error("LED block marker 5A A5 missing; refusing to write");
  const block = before.slice();
  for (const [offset, value] of Object.entries(changes)) block[Number(offset)] = value;
  if (block.every((b, i) => b === before[i])) return { before, after: before, written: false };
  await session.write(0x04, 0, block);
  const after = await session.read(0x84, 0, 128);
  const mismatch = after.findIndex((b, i) => b !== block[i]);
  if (mismatch !== -1) throw new Error(`Read-back differs at LED offset ${mismatch}`);
  return { before, after, written: true };
}

// Brightness of the current effect: entry 0x3A + 2 x effect index. Offset 60
// (effect hw 2) was verified by captures 008/009 and the live test.
export async function setBrightness(session, level) {
  if (!LED_BRIGHTNESS_LEVELS.includes(level)) throw new RangeError(`Brightness ${level} outside 0-4`);
  const led = await session.read(0x84, 0, 128);
  const effect = EFFECTS.find((e) => e.hw === led[LED_EFFECT_OFFSET]);
  const offset = effect ? LED_ENTRY_BASE + 2 * effect.index : LED_BRIGHTNESS_OFFSET;
  return setLedBytes(session, { [offset]: level });
}

// Knob press is keymap matrix 84. The official app (FUN_00491430) sets LED
// byte 0x1A to the profile's WheelMode (6) whenever the knob key differs from
// its default, which the firmware appears to use to bypass its built-in
// Mute-on-press. Experimental until confirmed on the device.
export const KNOB_MATRIX = 84;
export const KNOB_DEFAULT_WORD = [0x07, 0x00, 0x00, 0x1d];
export const KNOB_MODE_OFFSET = 0x1a;
export async function setKnobPress(session, word) {
  const isDefault = word.every((b, i) => b === KNOB_DEFAULT_WORD[i]);
  const key = await setKey(session, 0, KNOB_MATRIX, word);
  const led = await setLedBytes(session, { [KNOB_MODE_OFFSET]: isDefault ? 0 : 6 });
  return { key, led };
}

// Read-modify-write of one 512-byte keymap layer sector, changing one 4-byte
// key word, then read back. Layout: docs/keycode-encoding.md.
export async function setKey(session, layer, matrix, word) {
  if (![0, 1, 2, 3].includes(layer)) throw new RangeError(`Layer ${layer} outside 0-3`);
  if (!Number.isInteger(matrix) || matrix < 0 || matrix * 4 + 4 > 508) throw new RangeError(`Matrix index ${matrix} out of range`);
  if (word.length !== 4) throw new RangeError("Key word must be 4 bytes");
  const before = await session.read(0x83, layer, 512);
  if (before[510] !== 0x5a || before[511] !== 0xa5) throw new Error("Layer trailer 5A A5 missing; refusing to write");
  const block = before.slice();
  block.set(word, matrix * 4);
  if (block.every((b, i) => b === before[i])) return { before, after: before, written: false };
  await session.write(0x03, layer, block);
  const after = await session.read(0x83, layer, 512);
  const mismatch = after.findIndex((b, i) => b !== block[i]);
  if (mismatch !== -1) throw new Error(`Read-back differs at layer offset ${mismatch}`);
  return { before, after, written: true };
}

const fromHex = (h) => Uint8Array.from(h.match(/../g) ?? [], (x) => Number.parseInt(x, 16));

// Validates a backup JSON and returns the blocks to restore, in write order.
export function parseBackup(json, liveIdentity) {
  if (json?.schema !== "hi75-config-backup/1") throw new Error("Not a hi75-config-backup/1 file");
  const blocks = [
    ...json.layersHex.map((h, layer) => ({ name: `layer ${layer}`, read: 0x83, write: 0x03, arg: layer, data: fromHex(h), size: 512 })),
    { name: "lighting", read: 0x84, write: 0x04, arg: 0, data: fromHex(json.ledHex), size: 128 },
    { name: "RGB table", read: 0x8a, write: 0x0a, arg: 0, data: fromHex(json.rgbTableHex), size: 512 },
    { name: "macros", read: 0x85, write: 0x05, arg: 0, data: fromHex(json.macrosHex), size: fromHex(json.macrosHex).length },
    ...(json.keyColorsHex ? [{ name: "key colours", read: 0x86, write: 0x06, arg: 0, data: fromHex(json.keyColorsHex), size: 512, compare: 378 }] : []),
  ];
  if (json.layersHex.length !== 4) throw new Error("Backup must contain 4 layers");
  const macros = blocks.find((b) => b.name === "macros");
  if (![512, MACRO_BUFFER_BYTES].includes(macros.size)) throw new Error(`Backup macros are ${macros.size} bytes`);
  for (const b of blocks) if (b.data.length !== b.size) throw new Error(`Backup ${b.name} is ${b.data.length} bytes, expected ${b.size}`);
  if (liveIdentity && json.identityHex !== Array.from(liveIdentity, (x) => x.toString(16).padStart(2, "0")).join("")) {
    throw new Error(`Backup is from a different device identity (${json.identityHex})`);
  }
  return blocks;
}

// Writes each block that differs from the keyboard, verifying by read-back.
export async function restoreBlocks(session, blocks, onStep = () => {}) {
  const report = [];
  for (const b of blocks) {
    const n = b.compare ?? b.size; // bytes the firmware actually stores from us
    const before = await session.read(b.read, b.arg, b.size);
    if (before.subarray(0, n).every((x, i) => x === b.data[i])) { report.push({ name: b.name, written: false }); continue; }
    onStep(b.name);
    await session.write(b.write, b.arg, b.data);
    const after = await session.read(b.read, b.arg, b.size);
    const mismatch = after.subarray(0, n).findIndex((x, i) => x !== b.data[i]);
    if (mismatch !== -1) throw new Error(`Read-back of ${b.name} differs at offset ${mismatch}; stopped`);
    report.push({ name: b.name, written: true });
  }
  return report;
}

// Effect, brightness, speed, colour and palette slot for one effect.
export async function setLighting(session, params) {
  const led = await session.read(0x84, 0, 128);
  const rgb = await session.read(0x8a, 0, 512);
  if (led[126] !== 0x5a || led[127] !== 0xa5) throw new Error("LED block marker 5A A5 missing; refusing to write");
  const next = encodeLighting(led, rgb, params);
  const report = await restoreBlocks(session, [
    { name: "lighting", read: 0x84, write: 0x04, arg: 0, data: next.led, size: 128 },
    { name: "palette", read: 0x8a, write: 0x0a, arg: 0, data: next.rgb, size: 512 },
  ]);
  return { led: next.led, rgb: next.rgb, report };
}

// Replaces the whole macro buffer (MACRO_BUFFER_BYTES, several sectors).
export async function setMacros(session, macros) {
  const data = encodeMacros(macros);
  const report = await restoreBlocks(session, [{ name: "macros", read: 0x85, write: 0x05, arg: 0, data, size: data.length }]);
  return { data, report };
}

// Self-define per-key colours (3 x 126-byte planes; see lighting.js).
export async function setKeyColorBlock(session, data) {
  const report = await restoreBlocks(session, [{ name: "key colours", read: 0x86, write: 0x06, arg: 0, data, size: 512, compare: 378 }]);
  return { data, report };
}
