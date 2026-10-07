import { assessCandidate } from "../src/hid/fingerprint.js";
import {
  Hi75Session, KNOB_DEFAULT_WORD, parseBackup, readConfiguration, restoreBlocks,
  setKey, setKeyColorBlock, setKnobPress, setLighting, setMacros,
} from "../src/hid/transport.js";
import { decodeKey, hidName } from "../src/protocol/keycodes.js";
import { EFFECTS, SELF_DEFINE_HW, decodeLighting, keyColor, setKeyColors } from "../src/protocol/lighting.js";
import { MACRO_BUFFER_BYTES, encodeMacros, hidForCode, keyAction, macroKeyWord, parseMacros } from "../src/protocol/macros.js";
import { CATEGORIES, sameWord } from "./catalog.js";
import { KEYS, KNOB, KNOB_TURNS, renderKeyboard } from "./keyboard.js";
import { createDemoDevice } from "./demo.js";
import { detectKnobPatch } from "../src/protocol/knob-patch.js";

const $ = (s) => document.querySelector(s);
const h = (tag, attrs = {}, ...children) => {
  const el = document.createElement(tag);
  for (const [k, v] of Object.entries(attrs)) {
    if (k.startsWith("on")) el.addEventListener(k.slice(2), v);
    else if (k === "class") el.className = v;
    else if (v === true) el.setAttribute(k, "");
    else if (v !== false && v != null) el.setAttribute(k, v);
  }
  el.append(...children.flat(Infinity).filter((c) => c != null && c !== false));
  return el;
};
const hex = (bytes) => Array.from(bytes, (b) => b.toString(16).padStart(2, "0")).join("");
const toCss = (rgb) => `#${rgb.map((v) => v.toString(16).padStart(2, "0")).join("")}`;
const fromCss = (s) => [1, 3, 5].map((i) => Number.parseInt(s.slice(i, i + 2), 16));

const LAYERS = ["Base layer", "Fn layer"];
const PGDN_MATRIX = 88;
const PAGES = { remap: "Remap", lighting: "Lighting", macros: "Macros", knob: "Knob", backup: "Backup & Restore" };

const state = {
  device: null, session: null, config: null, busy: false,
  page: "remap", layer: 0, selected: null, category: "keyboard",
  paint: null, paintColor: "#ff0000",
  macros: [], macrosDirty: false, macroIndex: 0, recording: null,
};

// ---------- device ----------

function pickCandidate(devices) {
  return devices.find((d) => assessCandidate(d).status === "descriptor-layout candidate") ?? null;
}

async function connect(device) {
  await run("Reading keyboard", async () => {
    state.device = device;
    state.session = await Hi75Session.open(device);
    await reload();
    state.knobPatch = device.demo ? "patched" : await detectKnobPatch(state.session).catch(() => "unknown");
  }, null);
}

async function reload() {
  state.config = await readConfiguration(state.session, (step) => setStatus(`Reading ${step}…`, true));
  state.macros = parseMacros(state.config.macros).map((m, i) => ({ ...m, orig: i }));
  state.macrosDirty = false;
  state.paint = state.config.keyColors.slice();
}

function disconnected() {
  state.device = null; state.session = null; state.config = null; state.selected = null; stopRecording();
  render();
}

// One write at a time; every helper verifies by read-back and throws on mismatch.
async function run(label, fn, success = "Saved to keyboard") {
  if (state.busy) return;
  state.busy = true;
  setStatus(`${label}…`, true);
  render();
  try {
    await fn();
    if (success) toast(success);
  } catch (error) {
    toast(`${label} failed: ${error?.message || error}`, true);
  } finally {
    state.busy = false;
    render();
  }
}

// ---------- shell ----------

function setStatus(text, busy = false) {
  const el = $("#status");
  el.textContent = text;
  el.classList.toggle("busy", busy);
}

let toastTimer;
function toast(text, error = false) {
  const el = $("#toast");
  el.textContent = text;
  el.classList.toggle("error", error);
  el.hidden = false;
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => { el.hidden = true; }, error ? 7000 : 2500);
}

function render() {
  const connected = !!state.config;
  $("#device-card").classList.toggle("connected", connected);
  $("#device-sub").textContent = connected ? (state.device?.demo ? "Demo mode" : "Connected") : "No keyboard";
  $("#connect").hidden = connected;
  $("#demo").textContent = state.device?.demo ? "Exit demo mode" : "Try demo mode";
  $("#demo").hidden = connected && !state.device?.demo;
  $("#empty-state").hidden = connected;
  $(".board-wrap").hidden = !connected;
  $("#page-title").textContent = PAGES[state.page];
  $("#layer-switch").hidden = !connected || state.page !== "remap";
  document.querySelectorAll("#layer-switch button").forEach((b) => b.classList.toggle("active", Number(b.dataset.layer) === state.layer));
  document.querySelectorAll(".nav button").forEach((b) => b.classList.toggle("active", b.dataset.page === state.page));
  document.querySelectorAll("[data-page-panel]").forEach((p) => { p.hidden = !connected || p.dataset.pagePanel !== state.page; });
  if (!state.busy) setStatus(connected ? "Ready" : "");
  if (!connected) return;
  renderBoard();
  const panel = $(`#page-${state.page}`);
  panel.replaceChildren(...[({ remap: remapPanel, lighting: lightingPanel, macros: macrosPanel, knob: knobPanel, backup: backupPanel })[state.page]()].flat(Infinity).filter(Boolean));
}

// ---------- keyboard view ----------

function wordAt(layer, matrix) {
  return Array.from(state.config.layers[layer].subarray(matrix * 4, matrix * 4 + 4));
}

// Short key-cap text; the full name goes in the panel and tooltip.
const SHORT = {
  "Volume up": "Vol+", "Volume down": "Vol−", "Play/Pause": "Play", "Next track": "Next", "Prev track": "Prev",
  "Screen brighter": "Scr+", "Screen dimmer": "Scr−", "Lights on/off": "LED", "Next effect": "Effect",
  "Brighter": "LED+", "Dimmer": "LED−", "Faster": "Spd+", "Slower": "Spd−", "Print Screen": "PrtSc",
  "Scroll Lock": "ScrLk", "Disabled": "—", "Win lock": "Win lock", "Alt+Tab": "Alt+Tab", "Calculator": "Calc",
  "Media player": "Media", "My computer": "PC", "Browser search": "Search", "Browser home": "Home",
  "Browser back": "Back", "Browser forward": "Fwd", "Browser refresh": "Reload", "Page Up": "PgUp", "Page Down": "PgDn",
};
function capLabel(word) {
  const l = labelForWord(word);
  return SHORT[l] ?? l;
}

function labelForWord(word) {
  if (word[0] === 3) {
    const m = state.macros[word[3]];
    return m ? `▶ ${m.name || `Macro ${word[3] + 1}`}` : `▶ Macro ${word[3] + 1}`;
  }
  for (const c of CATEGORIES) for (const g of c.groups) for (const it of g.items) if (sameWord(it.word, word)) return it.label;
  if (sameWord(word, KNOB_DEFAULT_WORD)) return "Mute";
  if (word[0] === 7) return { 0x01: "Win lock", 0x04: "Reset" }[word[3]] ?? `Fn func ${word[3].toString(16).toUpperCase()}`;
  const d = decodeKey(word).label;
  return d === "—" ? "" : d;
}

function renderBoard() {
  const board = $("#keyboard");
  const hint = $("#board-hint");
  const page = state.page;
  const lighting = decodeLighting(state.config.led, state.config.rgbTable);
  const painting = page === "lighting" && lighting.hw === SELF_DEFINE_HW;
  renderKeyboard(board, {
    labelFor: (key) => {
      if (page === "remap") {
        const word = wordAt(state.layer, key.matrix);
        if (key.knob && state.layer === 0 && sameWord(word, KNOB_DEFAULT_WORD)) return "Mute";
        if (state.layer > 0 && sameWord(word, [0, 0, 0, 0])) return "";
        return capLabel(word) || "—";
      }
      if (page === "knob") return key.knob ? "Knob" : key.name;
      return key.name;
    },
    colorFor: painting && state.paint ? (key) => (key.knob ? null : toCss(keyColor(state.paint, key.matrix))) : null,
    selected: new Set(page === "remap" && state.selected != null ? [state.selected] : page === "knob" ? [KNOB.matrix] : []),
    onClick: (key) => {
      if (page === "remap") { state.selected = key.matrix; render(); }
      else if (painting) { state.paint = setKeyColors(state.paint, [[key.matrix, fromCss(state.paintColor)]]); render(); }
      else if (key.knob) { state.page = "knob"; render(); }
    },
  });
  hint.textContent = page === "remap" ? "Select a key, then choose what it should do"
    : painting ? "Click keys to paint them, then save"
    : page === "lighting" ? "Choose an effect below" : page === "knob" ? "The knob is in the top-right corner" : "";
}

// ---------- Remap ----------

function remapPanel() {
  if (state.selected == null) {
    return [h("h2", {}, "Remap"), h("p", { class: "muted" }, "Select a key on the keyboard above. Use the layer switch at the top to edit what keys do while Fn is held.")];
  }
  const key = KEYS.find((k) => k.matrix === state.selected) ?? KNOB_TURNS.find((k) => k.matrix === state.selected);
  return [
    h("div", { class: "panel-head" },
      h("h2", {}, key.knob ? "Knob press" : key.name),
      h("span", { class: "muted" }, `${LAYERS[state.layer]} · currently ${currentLabel(key, state.layer)}`),
      h("span", { class: "spacer" }),
      h("button", { type: "button", class: "btn", onclick: () => { state.selected = null; render(); } }, "Done")),
    keyPicker(key, state.layer),
  ];
}

function currentLabel(key, layer) {
  return labelForWord(wordAt(layer, key.matrix)) || (key.knob && layer === 0 ? "Mute" : layer > 0 ? "same as base layer" : "nothing");
}

// Category tabs plus option chips for one key on one layer; applying writes immediately.
function keyPicker(key, layer) {
  const current = wordAt(layer, key.matrix);
  const tabs = [...CATEGORIES.map((c) => [c.id, c.name]), ["macro", "Macro"]];
  const apply = (label, word) => run(`Setting ${key.name} to ${label}`, async () => {
    if (key.knob && layer === 0) {
      const r = await setKnobPress(state.session, Uint8Array.from(word));
      state.config.layers[0] = r.key.after; state.config.led = r.led.after;
    } else {
      state.config.layers[layer] = (await setKey(state.session, layer, key.matrix, Uint8Array.from(word))).after;
    }
  });
  const chip = (label, word) => {
    const shown = layer > 0 && sameWord(word, [0, 0, 0, 0]) ? "Use base key" : label;
    return h("button", { type: "button", class: `chip${sameWord(word, current) ? " current" : ""}`, disabled: state.busy, onclick: () => apply(shown, word) }, shown);
  };
  let body;
  if (state.category === "macro") {
    const blocked = key.matrix === PGDN_MATRIX;
    body = [
      blocked ? h("div", { class: "notice" }, "PgDn can't play macros. The keyboard's firmware ignores macros on this key, even ones set by LEOBOG ONE.") : null,
      state.macros.length
        ? h("div", { class: "chips" }, state.macros.map((m, i) => {
          const b = chip(m.name || `Macro ${i + 1}`, macroKeyWord(i, 1));
          if (blocked) b.disabled = true;
          return b;
        }))
        : h("p", { class: "muted" }, "No macros yet. Create one on the Macros page."),
      state.macrosDirty ? h("div", { class: "notice" }, "You have unsaved macro changes. Save them on the Macros page first.") : null,
    ];
  } else {
    const cat = CATEGORIES.find((c) => c.id === state.category);
    body = [
      key.knob && layer === 0 && cat.id === "special" ? h("div", { class: "chips", style: "margin-bottom:6px" }, chip("Mute (default)", KNOB_DEFAULT_WORD)) : null,
      cat.groups.map((g) => [h("h3", {}, g.name), h("div", { class: "chips" }, g.items.map((it) => chip(it.label, it.word)))]),
    ];
  }
  return [
    h("div", { class: "tabs" }, tabs.map(([id, name]) => h("button", { type: "button", class: state.category === id ? "active" : "", onclick: () => { state.category = id; render(); } }, name))),
    body,
  ];
}

// ---------- Lighting ----------

function lightingPanel() {
  const l = decodeLighting(state.config.led, state.config.rgbTable);
  const e = l.effects.find((x) => x.hw === l.hw);
  const visible = l.effects.filter((x) => x.hw !== 15 && x.hw !== 16);
  const set = (label, params) => run(label, async () => {
    const r = await setLighting(state.session, { hw: l.hw, ...params });
    state.config.led = r.led; state.config.rgbTable = r.rgb;
  });
  const out = [
    h("h2", {}, "Effect"),
    h("div", { class: "cards" }, visible.map((x) => h("button", {
      type: "button", class: `card${x.hw === l.hw ? " current" : ""}`, disabled: state.busy,
      onclick: () => set(`Switching to ${x.name}`, { hw: x.hw }),
    }, x.name))),
  ];
  if (!e) return out;
  const controls = [];
  if (e.brightness) controls.push(slider("Brightness", e.level, ["Off", "Max"], (v) => set("Setting brightness", { level: v })));
  if (e.speed) controls.push(slider("Speed", Math.min(4, e.speedLevel), ["Slow", "Fast"], (v) => set("Setting speed", { speedLevel: v })));
  if (controls.length) out.push(h("h3", {}, `${e.name} settings`), h("div", { class: "row" }, controls));
  if (e.color || e.random) {
    const slot = e.colorIndex;
    const swatches = [];
    if (e.color) e.palette.forEach((rgb, i) => swatches.push(h("button", { type: "button", class: `swatch${slot === i ? " current" : ""}`, style: `background:${toCss(rgb)}`, title: `Colour ${i + 1}`, disabled: state.busy, onclick: () => set("Setting colour", { colorIndex: i }) })));
    if (e.random) swatches.push(h("button", { type: "button", class: `swatch random${slot === 7 ? " current" : ""}`, title: "Random colours", disabled: state.busy, onclick: () => set("Setting colour", { colorIndex: 7 }) }));
    out.push(h("h3", {}, "Colour"), h("div", { class: "swatches" }, swatches,
      e.color && slot <= 6 ? h("label", { class: "muted", style: "display:flex;gap:8px;align-items:center;margin-left:12px" }, "Edit selected",
        h("input", { type: "color", value: toCss(e.palette[slot]), disabled: state.busy, onchange: (ev) => set("Setting colour", { colorIndex: slot, slotColor: fromCss(ev.target.value) }) })) : null));
  }
  if (l.hw === SELF_DEFINE_HW) out.push(...painterControls());
  return out;
}

function slider(label, value, ends, onCommit) {
  return h("div", { class: "field" },
    h("label", {}, `${label}: ${value}`),
    h("input", { type: "range", min: 0, max: 4, step: 1, value, disabled: state.busy, onchange: (ev) => onCommit(Number(ev.target.value)) }),
    h("div", { class: "range-scale" }, h("span", {}, ends[0]), h("span", {}, ends[1])));
}

function painterControls() {
  const dirty = state.paint && state.paint.some((b, i) => b !== state.config.keyColors[i]);
  const all = (rgb) => { state.paint = setKeyColors(state.paint, KEYS.filter((k) => !k.knob).map((k) => [k.matrix, rgb])); render(); };
  return [
    h("h3", {}, "Key colours"),
    h("div", { class: "swatches" },
      h("label", { class: "muted", style: "display:flex;gap:8px;align-items:center" }, "Paint colour",
        h("input", { type: "color", value: state.paintColor, oninput: (ev) => { state.paintColor = ev.target.value; } })),
      h("button", { type: "button", class: "btn", onclick: () => all(fromCss(state.paintColor)) }, "Fill all keys"),
      h("button", { type: "button", class: "btn", onclick: () => all([0, 0, 0]) }, "Clear all"),
      h("button", { type: "button", class: "btn", disabled: !dirty, onclick: () => { state.paint = state.config.keyColors.slice(); render(); } }, "Discard"),
      h("button", { type: "button", class: "btn btn-accent", disabled: !dirty || state.busy, onclick: () => run("Saving key colours", async () => {
        await setKeyColorBlock(state.session, state.paint);
        state.config.keyColors = await state.session.read(0x86, 0, 512);
        state.paint = state.config.keyColors.slice();
      }) }, "Save key colours")),
    dirty ? h("p", { class: "muted" }, "Unsaved changes: the keyboard shows the new colours after you save.") : null,
  ];
}

// ---------- Macros ----------

function macrosPanel() {
  const m = state.macros[state.macroIndex];
  let used = 0;
  try { used = state.macros.length ? encodeMacros(state.macros).findLastIndex((b) => b !== 0) + 1 : 0; } catch { used = MACRO_BUFFER_BYTES + 1; }
  const list = h("div", { class: "macro-list" },
    state.macros.map((x, i) => h("button", { type: "button", class: i === state.macroIndex ? "active" : "", onclick: () => { stopRecording(); state.macroIndex = i; render(); } }, x.name || `Macro ${i + 1}`)),
    h("button", { type: "button", class: "btn", onclick: () => { stopRecording(); state.macros.push({ name: `Macro ${state.macros.length + 1}`, actions: [] }); state.macroIndex = state.macros.length - 1; state.macrosDirty = true; render(); } }, "+ New macro"),
    h("div", { style: "margin-top:12px" }, h("div", { class: "meter" }, h("div", { style: `width:${Math.min(100, (used / MACRO_BUFFER_BYTES) * 100)}%` })),
      h("div", { class: "muted", style: "font-size:12px;margin-top:4px" }, `${used} of ${MACRO_BUFFER_BYTES} bytes used`)),
    h("button", { type: "button", class: "btn btn-accent", style: "margin-top:12px", disabled: !state.macrosDirty || state.busy || used > MACRO_BUFFER_BYTES, onclick: saveMacros }, "Save macros to keyboard"),
  );
  let editor;
  if (!m) {
    editor = h("div", {}, h("h2", {}, "Macros"), h("p", { class: "muted" }, "Create a macro, record it, save it, then assign it to a key on the Remap page under Macro."));
  } else {
    const recording = !!state.recording;
    const steps = m.actions.map((a, i) => h("tr", {},
      h("td", { class: "dir" }, a.down ? "↓" : "↑"),
      h("td", {}, a.kind === 2 ? `Mouse ${a.code}` : hidName(a.code)),
      h("td", {}, "then wait ", h("input", { type: "number", min: 0, max: 32767, value: a.delay, onchange: (ev) => { a.delay = Math.max(0, Math.min(32767, Number(ev.target.value) || 0)); state.macrosDirty = true; render(); } }), " ms"),
      h("td", {}, h("button", { type: "button", class: "btn", onclick: () => { m.actions.splice(i, 1); state.macrosDirty = true; render(); } }, "Remove"))));
    editor = h("div", {},
      h("div", { class: "panel-head" },
        h("input", { type: "text", value: m.name, maxlength: 30, onchange: (ev) => { m.name = ev.target.value; state.macrosDirty = true; render(); } }),
        h("button", { type: "button", class: `btn ${recording ? "rec" : "btn-accent"}`, onclick: () => (recording ? stopRecording() : startRecording(m)) }, recording ? "■ Stop recording" : "● Record"),
        h("button", { type: "button", class: "btn", disabled: !m.actions.length, onclick: () => { m.actions = []; state.macrosDirty = true; render(); } }, "Clear steps"),
        h("span", { class: "spacer" }),
        h("button", { type: "button", class: "btn btn-danger", onclick: () => deleteMacro(state.macroIndex) }, "Delete macro")),
      recording ? h("p", { class: "rec" }, "Recording: type on your keyboard now. Click Stop when done.") : null,
      m.actions.length ? h("table", { class: "steps" }, h("tbody", {}, steps)) : h("p", { class: "muted" }, "No steps yet. Click Record and type."));
  }
  return [h("div", { class: "macro-layout" }, list, editor)];
}

function startRecording(macro) {
  stopRecording();
  macro.actions = [];
  const rec = { macro, last: null, held: new Set() };
  rec.handler = (event) => {
    if (event.target instanceof HTMLInputElement) return;
    const code = hidForCode(event.code);
    if (!code || event.repeat) return;
    event.preventDefault();
    const down = event.type === "keydown";
    if (down === rec.held.has(code)) return;
    down ? rec.held.add(code) : rec.held.delete(code);
    const now = performance.now();
    // Each step's delay is the wait after it, as in LEOBOG ONE.
    const prev = macro.actions[macro.actions.length - 1];
    if (prev) prev.delay = Math.max(1, Math.min(32767, Math.round(now - rec.last)));
    macro.actions.push(keyAction(code, down, 0));
    rec.last = now;
    state.macrosDirty = true;
    render();
  };
  window.addEventListener("keydown", rec.handler, true);
  window.addEventListener("keyup", rec.handler, true);
  state.recording = rec;
  render();
}

function stopRecording() {
  const rec = state.recording;
  if (!rec) return;
  window.removeEventListener("keydown", rec.handler, true);
  window.removeEventListener("keyup", rec.handler, true);
  for (const code of rec.held) rec.macro.actions.push(keyAction(code, false, 0)); // never leave keys held
  state.recording = null;
  render();
}

function deleteMacro(index) {
  const users = [0, 1, 2, 3].reduce((n, L) => n + countKeysUsing(L, state.macros[index].orig), 0);
  if (users && !confirm(`${users} key(s) play this macro. They will be cleared when you save. Delete it?`)) return;
  stopRecording();
  state.macros.splice(index, 1);
  state.macroIndex = Math.max(0, index - 1);
  state.macrosDirty = true;
  render();
}

function countKeysUsing(layer, orig) {
  if (orig == null) return 0;
  const l = state.config.layers[layer];
  let n = 0;
  for (let m = 0; m < 127; m++) if (l[m * 4] === 3 && l[m * 4 + 3] === orig) n++;
  return n;
}

// Key words reference macros by position, so after deletions the keymap is
// updated to the new positions (or cleared for deleted macros).
function saveMacros() {
  stopRecording();
  run("Saving macros", async () => {
    const { data } = await setMacros(state.session, state.macros);
    state.config.macros = data;
    const moved = new Map(state.macros.map((m, i) => [m.orig, i]).filter(([o]) => o != null));
    for (let L = 0; L < 4; L++) {
      const layer = state.config.layers[L];
      for (let m = 0; m < 127; m++) {
        if (layer[m * 4] !== 3) continue;
        const idx = layer[m * 4 + 3];
        const next = moved.get(idx);
        if (next === idx) continue;
        const word = next == null ? [0, 0, 0, 0] : [3, layer[m * 4 + 1], layer[m * 4 + 2], next];
        state.config.layers[L] = (await setKey(state.session, L, m, Uint8Array.from(word))).after;
      }
    }
    state.macros = parseMacros(data).map((x, i) => ({ ...x, orig: i }));
    state.macrosDirty = false;
  });
}

// ---------- Knob ----------

function knobPanel() {
  const patched = state.knobPatch === "patched" || state.knobPatch === "patched-v1";
  const targets = [["press", "Press", KNOB], ...(patched ? [["cw", "Turn clockwise", KNOB_TURNS[0]], ["ccw", "Turn counter-clockwise", KNOB_TURNS[1]]] : [])];
  if (!targets.some(([id]) => id === state.knobTarget)) state.knobTarget = "press";
  const [, , key] = targets.find(([id]) => id === state.knobTarget);
  const layer = state.knobLayer ?? 0;
  const seg = (items, active, onPick) => h("div", { class: "layer-switch", style: "display:inline-flex" },
    items.map(([id, label]) => h("button", { type: "button", class: id === active ? "active" : "", onclick: () => onPick(id) }, label)));
  return [
    h("div", { class: "panel-head" }, h("h2", {}, "Knob"),
      h("span", { class: "muted" }, state.knobPatch === "patched-v1" ? "Knob patch v1 detected: turning stops working while the press is customised. Update to v2."
        : patched ? "Knob patch detected: turning works like a key."
        : state.knobPatch === "stock" ? "Stock firmware: turning always changes the volume. The knob patch makes it mappable."
        : "Couldn't identify the firmware, so only the press can be changed.")),
    h("div", { class: "row", style: "margin:14px 0 4px;align-items:center" },
      seg(targets.map(([id, label]) => [id, label]), state.knobTarget, (id) => { state.knobTarget = id; render(); }),
      seg([[0, "Base layer"], [1, "Fn layer"]], layer, (id) => { state.knobLayer = id; render(); })),
    h("p", { class: "muted" }, `${targets.find(([id]) => id === state.knobTarget)[1]} on the ${LAYERS[layer].toLowerCase()}: currently ${currentLabel(key, layer)}`),
    keyPicker(key, layer),

  ];
}

// ---------- Backup ----------

function backupPanel() {
  const download = () => run("Reading keyboard", async () => {
    await reload();
    const c = state.config;
    const out = {
      schema: "hi75-config-backup/1", readAt: c.readAt, identityHex: hex(c.identity), ledHex: hex(c.led),
      rgbTableHex: hex(c.rgbTable), layersHex: c.layers.map(hex), macrosHex: hex(c.macros), keyColorsHex: hex(c.keyColors),
    };
    const url = URL.createObjectURL(new Blob([`${JSON.stringify(out, null, 2)}\n`], { type: "application/json" }));
    const a = h("a", { href: url, download: `hi75-backup-${c.readAt.replaceAll(":", "-")}.json` });
    a.click();
    setTimeout(() => URL.revokeObjectURL(url), 1000);
  }, "Backup downloaded");
  const restore = async (file) => {
    let json;
    try { json = JSON.parse(await file.text()); parseBackup(json); } catch (e) { toast(`Not a valid backup: ${e.message}`, true); return; }
    if (!confirm(`Restore the backup from ${json.readAt}? Everything that differs will be overwritten on the keyboard.`)) return;
    run("Restoring backup", async () => {
      const identity = await state.session.read(0x82, 1, 6);
      await restoreBlocks(state.session, parseBackup(json, identity), (name) => setStatus(`Restoring ${name}…`, true));
      await reload();
    }, "Backup restored and verified");
  };
  return [
    h("h2", {}, "Backup & Restore"),
    h("p", { class: "muted" }, "A backup holds every keymap layer, lighting settings, colours and macros. Restoring writes back only what differs and checks each part."),
    h("div", { class: "row", style: "margin-top:14px" },
      h("button", { type: "button", class: "btn btn-accent", disabled: state.busy, onclick: download }, "Download backup"),
      h("label", { class: "btn" }, "Restore from file…", h("input", { type: "file", accept: ".json,application/json", hidden: true, onchange: (ev) => ev.target.files[0] && restore(ev.target.files[0]) })),
      h("button", { type: "button", class: "btn", disabled: state.busy, onclick: () => run("Reading keyboard", reload, "Reloaded from keyboard") }, "Reload from keyboard")),
  ];
}

// ---------- wiring ----------

document.querySelectorAll(".nav button").forEach((b) => b.addEventListener("click", () => { stopRecording(); state.page = b.dataset.page; render(); }));
document.querySelectorAll("#layer-switch button").forEach((b) => b.addEventListener("click", () => { state.layer = Number(b.dataset.layer); render(); }));

$("#connect").addEventListener("click", async () => {
  try {
    const devices = await navigator.hid.requestDevice({ filters: [{ vendorId: 0x258a, productId: 0x010c }] });
    const device = pickCandidate(devices) ?? pickCandidate(await navigator.hid.getDevices());
    if (!device) { if (devices.length) toast("That device doesn't look like a Hi75 configuration interface.", true); return; }
    await connect(device);
  } catch (error) {
    toast(`Couldn't connect: ${error.message}`, true);
  }
});

$("#demo").addEventListener("click", () => {
  if (state.device?.demo) { disconnected(); return; }
  connect(createDemoDevice());
});

window.addEventListener("beforeunload", (e) => { if (state.macrosDirty) e.preventDefault(); });

if (!("hid" in navigator)) {
  $("#empty-state").querySelector("p").textContent = "This browser doesn't support WebHID. Please open this page in Chrome or Edge.";
  $("#connect").disabled = true;
} else {
  navigator.hid.addEventListener("disconnect", (e) => { if (e.device === state.device) { disconnected(); toast("Keyboard disconnected", true); } });
  navigator.hid.getDevices().then((devices) => { const d = pickCandidate(devices); if (d) connect(d); });
}
render();
