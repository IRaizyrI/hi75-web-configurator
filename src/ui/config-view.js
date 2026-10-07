import {
  Hi75Session, parseBackup, readConfiguration, restoreBlocks, setKey, setKeyColorBlock, setKnobPress, setLighting, setMacros, KNOB_DEFAULT_WORD,
} from "../hid/transport.js";
import { assignmentOptions, decodeLayer } from "../protocol/keycodes.js";
import { HI75_KEYS } from "../protocol/hi75-layout.js";
import { COLOR_NAMES, EFFECTS, decodeLighting, keyColor, setKeyColors } from "../protocol/lighting.js";
import { hidForCode, keyAction, macroKeyWord, parseMacros } from "../protocol/macros.js";

const $ = (id) => document.querySelector(id);
const readButton = $("#read-config");
const backupButton = $("#download-backup");
const backupFile = $("#backup-file");
const restoreButton = $("#restore-backup");
const statusNode = $("#config-status");
const view = $("#config");
const summary = $("#config-summary");
const tabs = $("#layer-tabs");
const board = $("#keyboard");
const selectedNode = $("#selected-key");
const assignmentSelect = $("#assignment");
const applyKey = $("#apply-key");
const knobSelect = $("#knob-press");
const applyKnob = $("#apply-knob");
const effectSelect = $("#effect");
const brightnessSelect = $("#brightness");
const speedSelect = $("#speed");
const colorSelect = $("#color-index");
const slotColor = $("#slot-color");
const applyLighting = $("#apply-lighting");
const macroSlot = $("#macro-slot");
const macroName = $("#macro-name");
const macroRecord = $("#macro-record");
const macroSave = $("#macro-save");
const macroRepeat = $("#macro-repeat");
const macroAssign = $("#macro-assign");
const macroActions = $("#macro-actions");
const paintColor = $("#paint-color");
const paintToggle = $("#paint-toggle");
const paintSave = $("#paint-save");

const OPTIONS = assignmentOptions();
const KNOB_OPTIONS = [["Default (stock Mute)", KNOB_DEFAULT_WORD], ...OPTIONS.filter(([l]) => l !== "None" && l !== "Fn")];
const LAYER_NAMES = ["Base", "Fn", "Layer 2", "Layer 3"];
const W = 680, H = 290;
const hex = (bytes) => Array.from(bytes, (b) => b.toString(16).padStart(2, "0")).join("");
const toHtmlColor = (rgb) => `#${rgb.map((v) => v.toString(16).padStart(2, "0")).join("")}`;
const fromHtmlColor = (s) => [1, 3, 5].map((i) => Number.parseInt(s.slice(i, i + 2), 16));

assignmentSelect.replaceChildren(...OPTIONS.map(([label], i) => new Option(label, String(i))));
knobSelect.replaceChildren(...KNOB_OPTIONS.map(([label], i) => new Option(label, String(i))));
effectSelect.replaceChildren(...EFFECTS.map((e) => new Option(e.name, String(e.hw))));
colorSelect.replaceChildren(...COLOR_NAMES.map((n, i) => new Option(i < 7 ? `${i + 1} (stock ${n})` : n, String(i))));

let candidate = null;
let config = null;
let busy = false;
let currentLayer = 0;
let selected = null;
let backupJson = null;
let macros = [];
let recording = null;
let painting = false;
let paintedColors = null; // working copy of the 0x86 block

const writeControls = () => [readButton, restoreButton, applyKey, applyKnob, applyLighting, macroSave, macroAssign, paintSave];

export function setConfigCandidate(device) {
  candidate = device;
  readButton.disabled = !candidate || busy;
  restoreButton.disabled = !candidate || busy || !backupJson;
  if (!candidate && !config) statusNode.textContent = "Choose the keyboard above first.";
}

function refreshButtons() {
  readButton.disabled = !candidate || busy;
  restoreButton.disabled = !candidate || busy || !backupJson;
  applyKey.disabled = busy || !selected;
  macroAssign.disabled = busy || !selected || !macros[Number(macroSlot.value)];
  for (const b of [applyKnob, applyLighting, macroSave]) b.disabled = busy || !config;
  paintSave.disabled = busy || !config || !paintedColors || paintedColors.every((b, i) => b === config.keyColors[i]);
}

// One HID session per user action; errors stop without retries.
async function withSession(what, fn) {
  if (!candidate || busy) return;
  busy = true;
  writeControls().forEach((b) => { b.disabled = true; });
  let session = null;
  try {
    session = await Hi75Session.open(candidate);
    await fn(session);
  } catch (error) {
    statusNode.textContent = `${what} stopped: ${error?.name || "Error"}: ${error?.message || String(error)}. No retry was sent.`;
  } finally {
    if (session) await session.close().catch(() => {});
    busy = false;
    refreshButtons();
  }
}

function selectKey(key, el) {
  selected = key;
  board.querySelectorAll(".key.selected").forEach((n) => n.classList.remove("selected"));
  el?.classList.add("selected");
  selectedNode.textContent = `${LAYER_NAMES[currentLayer]} · ${key.name}: ${key.label}`;
  const match = OPTIONS.findIndex(([, w]) => w.every((b, i) => b === Number.parseInt(key.raw.split(" ")[i], 16)));
  assignmentSelect.value = String(match === -1 ? 0 : match);
  assignmentSelect.disabled = false;
  refreshButtons();
}

function renderLayer(index) {
  currentLayer = index;
  selected = null;
  assignmentSelect.disabled = true;
  selectedNode.textContent = "Click a key to edit it.";
  tabs.querySelectorAll("button").forEach((b, i) => b.setAttribute("aria-selected", String(i === index)));
  board.replaceChildren();
  const keys = decodeLayer(config.layers[index], HI75_KEYS);
  for (const key of keys) {
    if (key.rect[2] === 0) continue; // knob press has no on-screen box
    const [x1, y1, x2, y2] = key.rect;
    const el = document.createElement("div");
    el.className = `key${key.label === "—" ? " empty" : ""}`;
    Object.assign(el.style, {
      left: `${((x1 - 15) / W) * 100}%`, top: `${((y1 - 18) / H) * 100}%`,
      width: `${((x2 - x1) / W) * 100}%`, height: `${((y2 - y1) / H) * 100}%`,
    });
    el.textContent = key.label;
    el.title = `${key.name} (matrix ${key.matrix}): ${key.raw}`;
    if (painting) {
      const rgb = keyColor(paintedColors, key.matrix);
      el.style.background = toHtmlColor(rgb);
      el.style.color = rgb[0] * 0.3 + rgb[1] * 0.6 + rgb[2] * 0.1 > 128 ? "#101820" : "#e9edf1";
      el.addEventListener("click", () => {
        paintedColors = setKeyColors(paintedColors, [[key.matrix, fromHtmlColor(paintColor.value)]]);
        renderLayer(currentLayer);
      });
    } else {
      el.addEventListener("click", () => selectKey(key, el));
    }
    board.append(el);
  }
  const knob = keys.find((k) => k.rect[2] === 0);
  const lighting = decodeLighting(config.led, config.rgbTable);
  summary.textContent = `${lighting.effect?.name ?? `Effect hw ${lighting.hw}`} · Knob press: ${knob?.label ?? "?"} · ${macros.length} macro${macros.length === 1 ? "" : "s"}`;
  refreshButtons();
}

function showEffect(hw) {
  const e = decodeLighting(config.led, config.rgbTable).effects.find((x) => x.hw === hw);
  if (!e) return;
  effectSelect.value = String(hw);
  brightnessSelect.value = String(e.level);
  speedSelect.value = String(Math.min(4, e.speedLevel));
  speedSelect.disabled = !e.speed;
  colorSelect.value = String(Math.min(7, e.colorIndex));
  colorSelect.disabled = !e.color && !e.random;
  showSlot(e);
}

function showSlot(e = decodeLighting(config.led, config.rgbTable).effects.find((x) => x.hw === Number(effectSelect.value))) {
  const slot = Number(colorSelect.value);
  slotColor.disabled = slot > 6 || !e.color;
  if (slot <= 6) slotColor.value = toHtmlColor(e.palette[slot]);
}

function showMacros() {
  macroSlot.replaceChildren(
    ...macros.map((m, i) => new Option(`${i + 1}: ${m.name || "(unnamed)"}`, String(i))),
    new Option("+ New macro", String(macros.length)),
  );
  showMacro(Math.min(Number(macroSlot.value) || 0, macros.length));
}

function showMacro(i) {
  macroSlot.value = String(i);
  const m = macros[i];
  macroName.value = m?.name ?? "";
  macroActions.textContent = m
    ? m.actions.map((a) => `${["key", "modifier", "mouse"][a.kind] ?? `kind ${a.kind}`} ${a.down ? "down" : "up  "} 0x${a.code.toString(16).padStart(2, "0")} after ${a.delay} ms`).join("\n") || "(no actions)"
    : "New macro: click Record, type, then Stop.";
  refreshButtons();
}

function render() {
  view.hidden = false;
  paintedColors = config.keyColors.slice();
  macros = parseMacros(config.macros);
  tabs.replaceChildren(...LAYER_NAMES.map((name, i) => {
    const b = document.createElement("button");
    b.type = "button";
    b.role = "tab";
    b.textContent = name;
    b.addEventListener("click", () => renderLayer(i));
    return b;
  }));
  showEffect(config.led[10]);
  showMacros();
  renderLayer(currentLayer);
}

readButton.addEventListener("click", () => withSession("Read", async (session) => {
  config = await readConfiguration(session, (step) => { statusNode.textContent = `Reading ${step}…`; });
  config.inputReports = session.inputReports.map((r) => ({ reportId: r.reportId, dataHex: hex(r.data) }));
  statusNode.textContent = `Read complete at ${config.readAt}. Identity ${hex(config.identity)}.`;
  backupButton.disabled = false;
  render();
}));

backupButton.addEventListener("click", () => {
  if (!config) return;
  const out = {
    schema: "hi75-config-backup/1",
    readAt: config.readAt,
    identityHex: hex(config.identity),
    ledHex: hex(config.led),
    rgbTableHex: hex(config.rgbTable),
    layersHex: config.layers.map(hex),
    macrosHex: hex(config.macros),
    keyColorsHex: hex(config.keyColors),
    inputReports: config.inputReports,
  };
  const url = URL.createObjectURL(new Blob([`${JSON.stringify(out, null, 2)}\n`], { type: "application/json" }));
  const link = document.createElement("a");
  link.href = url;
  link.download = `hi75-backup-${config.readAt.replaceAll(":", "-")}.json`;
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
});

applyKey.addEventListener("click", () => {
  if (!selected) return;
  const [label, word] = OPTIONS[Number(assignmentSelect.value)];
  writeKey(selected, currentLayer, label, word);
});

function writeKey(key, layer, label, word) {
  return withSession("Key change", async (session) => {
    statusNode.textContent = `Writing ${LAYER_NAMES[layer]} ${key.name} = ${label}…`;
    const result = await setKey(session, layer, key.matrix, Uint8Array.from(word));
    config.layers[layer] = result.after;
    statusNode.textContent = result.written
      ? `${LAYER_NAMES[layer]} ${key.name} set to ${label}, verified by read-back.`
      : `${key.name} already ${label}; nothing written.`;
    renderLayer(layer);
  });
}

applyKnob.addEventListener("click", () => {
  const [label, word] = KNOB_OPTIONS[Number(knobSelect.value)];
  withSession("Knob change", async (session) => {
    statusNode.textContent = `Writing knob press = ${label}…`;
    const { key, led } = await setKnobPress(session, Uint8Array.from(word));
    config.layers[0] = key.after;
    config.led = led.after;
    statusNode.textContent = `Knob press set to ${label}, verified by read-back. Press the knob to check it.`;
    renderLayer(currentLayer);
  });
});

effectSelect.addEventListener("change", () => showEffect(Number(effectSelect.value)));
colorSelect.addEventListener("change", () => showSlot());

applyLighting.addEventListener("click", () => {
  const hw = Number(effectSelect.value);
  const e = EFFECTS.find((x) => x.hw === hw);
  const colorIndex = Number(colorSelect.value);
  const params = { hw, level: Number(brightnessSelect.value) };
  if (e.speed) params.speedLevel = Number(speedSelect.value);
  if (e.color || e.random) params.colorIndex = colorIndex;
  if (e.color && colorIndex <= 6) params.slotColor = fromHtmlColor(slotColor.value);
  withSession("Lighting change", async (session) => {
    statusNode.textContent = `Writing ${e.name}…`;
    const result = await setLighting(session, params);
    config.led = result.led;
    config.rgbTable = result.rgb;
    const written = result.report.filter((r) => r.written).map((r) => r.name);
    statusNode.textContent = written.length ? `${e.name} applied (${written.join(" + ")}), verified by read-back.` : "Lighting already matches; nothing written.";
    showEffect(hw);
    renderLayer(currentLayer);
  });
});

macroSlot.addEventListener("change", () => showMacro(Number(macroSlot.value)));

macroRecord.addEventListener("click", () => {
  if (recording) {
    window.removeEventListener("keydown", recording.handler, true);
    window.removeEventListener("keyup", recording.handler, true);
    const i = Number(macroSlot.value);
    macros[i] = { name: macroName.value || `Macro ${i + 1}`, actions: recording.actions };
    recording = null;
    macroRecord.textContent = "Record";
    showMacros();
    showMacro(i);
    statusNode.textContent = "Recorded. Click Save macros to write them to the keyboard.";
    return;
  }
  recording = { actions: [], last: performance.now(), held: new Set() };
  recording.handler = (event) => {
    if (event.target === macroName) return;
    const code = hidForCode(event.code);
    if (!code || event.repeat) return;
    event.preventDefault();
    const down = event.type === "keydown";
    if (down === recording.held.has(code)) return;
    down ? recording.held.add(code) : recording.held.delete(code);
    const now = performance.now();
    recording.actions.push(keyAction(code, down, Math.max(10, Math.round(now - recording.last))));
    recording.last = now;
    macroActions.textContent = `Recording… ${recording.actions.length} events`;
  };
  window.addEventListener("keydown", recording.handler, true);
  window.addEventListener("keyup", recording.handler, true);
  macroRecord.textContent = "Stop";
  macroActions.textContent = "Recording… type your macro now.";
});

macroName.addEventListener("change", () => {
  const m = macros[Number(macroSlot.value)];
  if (m) m.name = macroName.value;
});

macroSave.addEventListener("click", () => withSession("Macro save", async (session) => {
  statusNode.textContent = "Writing macros…";
  const result = await setMacros(session, macros);
  config.macros = result.data;
  macros = parseMacros(result.data);
  showMacros();
  statusNode.textContent = result.report[0].written ? `${macros.length} macro(s) saved and verified.` : "Macros already match; nothing written.";
}));

macroAssign.addEventListener("click", () => {
  const i = Number(macroSlot.value);
  if (!selected || !macros[i]) return;
  writeKey(selected, currentLayer, `Macro ${i + 1}`, macroKeyWord(i, Number(macroRepeat.value) || 1));
});

backupFile.addEventListener("change", async () => {
  backupJson = null;
  refreshButtons();
  const file = backupFile.files?.[0];
  if (!file) return;
  try {
    backupJson = JSON.parse(await file.text());
    parseBackup(backupJson); // shape check only; identity is checked on restore
    statusNode.textContent = `Loaded backup from ${backupJson.readAt}. Ready to restore.`;
  } catch (error) {
    backupJson = null;
    statusNode.textContent = `Backup rejected: ${error.message}`;
  }
  refreshButtons();
});

restoreButton.addEventListener("click", () => withSession("Restore", async (session) => {
  statusNode.textContent = "Checking identity…";
  const identity = await session.read(0x82, 1, 6);
  const blocks = parseBackup(backupJson, identity);
  const report = await restoreBlocks(session, blocks, (name) => { statusNode.textContent = `Restoring ${name}…`; });
  config = await readConfiguration(session);
  config.inputReports = [];
  render();
  const written = report.filter((r) => r.written).map((r) => r.name);
  statusNode.textContent = written.length
    ? `Restored and verified: ${written.join(", ")}. Everything else already matched.`
    : "Keyboard already matches the backup; nothing written.";
}));

paintToggle.addEventListener("click", () => {
  if (!config) return;
  painting = !painting;
  paintToggle.textContent = painting ? "Stop painting" : "Paint keys";
  renderLayer(currentLayer);
});

paintSave.addEventListener("click", () => withSession("Key colour save", async (session) => {
  statusNode.textContent = "Writing key colours…";
  const { report } = await setKeyColorBlock(session, paintedColors);
  config.keyColors = await session.read(0x86, 0, 512);
  paintedColors = config.keyColors.slice();
  statusNode.textContent = report[0].written ? "Key colours saved and verified. Select Self-define to see them." : "Key colours already match; nothing written.";
  renderLayer(currentLayer);
}));
