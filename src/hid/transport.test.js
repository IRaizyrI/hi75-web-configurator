import assert from "node:assert/strict";
import test from "node:test";
import { readFileSync, existsSync } from "node:fs";
import { Hi75Session, parseBackup, readConfiguration, restoreBlocks, setBrightness, setKey, setKeyColorBlock } from "./transport.js";
import { keyColor, setKeyColors } from "../protocol/lighting.js";

const dumpUrl = new URL("../../backup/dumps/20260919T085231Z/firmware.bin", import.meta.url);
const report = (reportId, reportCount) => ({ reportId, items: [{ reportSize: 8, reportCount }] });
const collection = (usagePage, inputReports, featureReports) => ({
  usagePage, usage: 1, inputReports, featureReports, outputReports: [], children: [],
});

// Simulates the firmware read dispatcher (CODE 0x4E1E) over the saved image.
function emulatedDevice(img) {
  const sent = [];
  const base = { 0x82: () => 0xb3e3, 0x83: (a) => [0xcc00, 0xd000, 0xd400, 0xd800][a], 0x84: () => 0xc600, 0x85: () => 0xdc00, 0x86: () => 0xca00, 0x8a: () => 0xc800 };
  let last;
  return {
    sent,
    vendorId: 0x258a, productId: 0x010c, opened: false,
    collections: [
      collection(0x000c, [report(2, 2)], []),
      collection(0xff00, [report(3, 3)], []),
      collection(0xff00, [], [report(5, 5)]),
      collection(0xff00, [report(6, 7)], [report(6, 519)]),
    ],
    async open() { this.opened = true; },
    async close() { this.opened = false; },
    addEventListener() {}, removeEventListener() {},
    async sendFeatureReport(id, body) {
      sent.push(Array.from(body.slice(0, 7)));
      if (body[0] === 0x04) img.set(body.slice(7, 7 + (body[5] | (body[6] << 8))), 0xc600);
      else if (body[0] === 0x0a) img.set(body.slice(7, 7 + 512), 0xc800);
      else if (body[0] === 0x05) img.set(body.slice(7, 7 + 512), 0xdc00 + 0x200 * body[4]);
      else if (body[0] === 0x06) img.set(body.slice(7, 7 + 378), 0xca00); // firmware keeps the tail
      else if (body[0] === 0x03) img.set(body.slice(7, 7 + 512), [0xcc00, 0xd000, 0xd400, 0xd800][body[1]]);
      else last = body;
    },
    async receiveFeatureReport() {
      const [cmd, arg, , , idx, lo, hi] = last;
      const len = lo | (hi << 8);
      const addr = (base[cmd](arg) + (cmd === 0x82 ? 0 : 0x200 * idx)) & 0xffff;
      const out = new Uint8Array(520);
      out.set([6, ...last.slice(0, 7)]);
      out.set(img.subarray(addr, addr + len), 8);
      return new DataView(out.buffer);
    },
  };
}

test("refuses non-read commands", async () => {
  const s = new Hi75Session({ });
  await assert.rejects(s.read(0x03, 0, 4), /not an allowed read/);
  await assert.rejects(s.read(0x11, 0, 4), /not an allowed read/);
});

test("full read against emulated firmware returns flash contents", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const img = new Uint8Array(readFileSync(dumpUrl));
  const dev = emulatedDevice(img);
  const session = await Hi75Session.open(dev);
  const cfg = await readConfiguration(session);
  await session.close();
  assert.deepEqual(Array.from(cfg.identity), [3, 0, 0, 0, 0, 0x9b]);
  assert.deepEqual(cfg.led, img.subarray(0xc600, 0xc680));
  assert.deepEqual(cfg.layers[1], img.subarray(0xd000, 0xd200));
  assert.ok(dev.sent.every((h) => h[0] & 0x80), "only 0x8x read commands sent");
});

test("brightness write changes only offset 60 and verifies read-back", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const img = new Uint8Array(readFileSync(dumpUrl));
  img[0xc600 + 10] = 2; // effect hw 2, whose brightness entry is offset 60
  const original = img.slice(0xc600, 0xc680);
  const dev = emulatedDevice(img);
  const session = await Hi75Session.open(dev);
  const target = original[60] === 2 ? 1 : 2;
  const result = await setBrightness(session, target);
  assert.equal(result.written, true);
  const after = img.subarray(0xc600, 0xc680);
  assert.deepEqual(Array.from(after).map((b, i) => (b === original[i] ? null : i)).filter((i) => i !== null), [60]);
  assert.deepEqual(dev.sent.map((h) => h[0]), [0x84, 0x84, 0x04, 0x84]);
  await assert.rejects(setBrightness(session, 5), /outside/);
  await assert.rejects(session.write(0x11, 0, new Uint8Array(4)), /not an enabled write/);
});

test("key write changes one word in one layer and verifies read-back", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const img = new Uint8Array(readFileSync(dumpUrl));
  const original = img.slice(0xc000, 0xdc00);
  const dev = emulatedDevice(img);
  const session = await Hi75Session.open(dev);
  // Fn layer, CapsLock (matrix 3) -> Esc
  const result = await setKey(session, 1, 3, Uint8Array.from([0, 0, 0, 0x29]));
  assert.equal(result.written, true);
  const changed = [];
  img.subarray(0xc000, 0xdc00).forEach((b, i) => { if (b !== original[i]) changed.push(0xc000 + i); });
  assert.deepEqual(changed, [0xd000 + 3 * 4 + 3]);
  assert.deepEqual(dev.sent.map((h) => [h[0], h[1]]), [[0x83, 1], [0x03, 1], [0x83, 1]]);
  await assert.rejects(setKey(session, 4, 3, new Uint8Array(4)), /Layer/);
  await assert.rejects(setKey(session, 0, 127, new Uint8Array(4)), /Matrix/);
});

test("restore writes back only changed blocks and verifies", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const img = new Uint8Array(readFileSync(dumpUrl));
  const dev = emulatedDevice(img);
  const session = await Hi75Session.open(dev);
  const cfg = await readConfiguration(session);
  const hex = (b) => Array.from(b, (x) => x.toString(16).padStart(2, "0")).join("");
  const backup = { schema: "hi75-config-backup/1", readAt: cfg.readAt, identityHex: hex(cfg.identity), ledHex: hex(cfg.led),
    rgbTableHex: hex(cfg.rgbTable), layersHex: cfg.layers.map(hex), macrosHex: hex(cfg.macros) };
  await setKey(session, 2, 10, Uint8Array.from([0, 0, 0, 0x04]));
  await setBrightness(session, cfg.led[60] === 0 ? 1 : 0);
  dev.sent.length = 0;
  const report = await restoreBlocks(session, parseBackup(backup, cfg.identity));
  assert.deepEqual(report.filter((r) => r.written).map((r) => r.name), ["layer 2", "lighting"]);
  assert.deepEqual(img.subarray(0xd400, 0xd600), cfg.layers[2]);
  assert.deepEqual(img.subarray(0xc600, 0xc680), cfg.led);
  assert.throws(() => parseBackup({ ...backup, identityHex: "000000000000" }, cfg.identity), /different device/);
  assert.throws(() => parseBackup({ ...backup, ledHex: "00" }), /lighting/);
});

test("key colour write sets R/G/B planes for one key", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const img = new Uint8Array(readFileSync(dumpUrl));
  const dev = emulatedDevice(img);
  const session = await Hi75Session.open(dev);
  const block = await session.read(0x86, 0, 512);
  const next = setKeyColors(block, [[0, [255, 0, 0]], [12, [0, 255, 0]]]);
  const { report } = await setKeyColorBlock(session, next);
  assert.equal(report[0].written, true);
  const live = img.subarray(0xca00, 0xcc00);
  assert.deepEqual(keyColor(live, 0), [255, 0, 0]);
  assert.deepEqual(keyColor(live, 12), [0, 255, 0]);
  assert.equal(live[0], 255); assert.equal(live[126 + 12], 255);
});

test("macro buffer spans several sectors", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const img = new Uint8Array(readFileSync(dumpUrl));
  const dev = emulatedDevice(img);
  const session = await Hi75Session.open(dev);
  const { setMacros } = await import("./transport.js");
  const big = Array.from({ length: 6 }, (_, i) => ({ name: `M${i}`, actions: Array.from({ length: 60 }, (_, j) => ({ kind: 0, down: j % 2 === 0, delay: 10, code: 4 })) }));
  const { data, report } = await setMacros(session, big);
  assert.equal(report[0].written, true);
  assert.deepEqual(img.subarray(0xdc00, 0xdc00 + data.length), data);
  assert.ok(dev.sent.some((h) => h[0] === 0x05 && h[4] === 3), "fourth sector written");
});

test("knob patch detection reads code through the macro address wrap", { skip: !existsSync(dumpUrl) && "no local dump" }, async () => {
  const { detectKnobPatch } = await import("../protocol/knob-patch.js");
  const stock = new Uint8Array(readFileSync(dumpUrl));
  assert.equal(await detectKnobPatch(await Hi75Session.open(emulatedDevice(stock))), "stock");
  for (const [file, expected] of [["firmware-knob-v1.bin", "patched-v1"], ["firmware-knob-v2.bin", "patched"]]) {
    const url = new URL(`../../backup/patched/${file}`, import.meta.url);
    if (!existsSync(url)) continue;
    assert.equal(await detectKnobPatch(await Hi75Session.open(emulatedDevice(new Uint8Array(readFileSync(url))))), expected);
  }
});
