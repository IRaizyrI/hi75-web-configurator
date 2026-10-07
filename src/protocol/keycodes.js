// Decoder for 4-byte key words; layout documented in docs/keycode-encoding.md.
const HID = {};
"ABCDEFGHIJKLMNOPQRSTUVWXYZ".split("").forEach((c, i) => { HID[0x04 + i] = c; });
"1234567890".split("").forEach((c, i) => { HID[0x1e + i] = c; });
Object.assign(HID, {
  0x28: "Enter", 0x29: "Esc", 0x2a: "Backspace", 0x2b: "Tab", 0x2c: "Space", 0x2d: "-", 0x2e: "=",
  0x2f: "[", 0x30: "]", 0x31: "\\", 0x32: "#", 0x33: ";", 0x34: "'", 0x35: "`", 0x36: ",", 0x37: ".",
  0x38: "/", 0x39: "CapsLock", 0x46: "PrtSc", 0x47: "ScrLk", 0x48: "Pause", 0x49: "Insert",
  0x4a: "Home", 0x4b: "PgUp", 0x4c: "Delete", 0x4d: "End", 0x4e: "PgDn", 0x4f: "Right", 0x50: "Left",
  0x51: "Down", 0x52: "Up", 0x53: "NumLk", 0x65: "Menu", 0x64: "ISO \\",
  0xe0: "LCtrl", 0xe1: "LShift", 0xe2: "LAlt", 0xe3: "LWin", 0xe4: "RCtrl", 0xe5: "RShift", 0xe6: "RAlt", 0xe7: "RWin",
});
for (let i = 0; i < 12; i++) HID[0x3a + i] = `F${i + 1}`;
for (let i = 0; i < 12; i++) HID[0x68 + i] = `F${i + 13}`;
for (let i = 0; i < 10; i++) HID[0x59 + i] = `KP${(i + 1) % 10}`;

const CONSUMER = {
  0x006f: "Screen bright+", 0x0070: "Screen bright-", 0x00b5: "Next track", 0x00b6: "Prev track",
  0x00b7: "Stop", 0x00cd: "Play/Pause", 0x00e2: "Mute", 0x00e9: "Vol+", 0x00ea: "Vol-",
  0x0183: "Media player", 0x018a: "Mail", 0x0192: "Calculator", 0x0194: "My computer",
  0x0221: "Search", 0x0223: "Browser home", 0x0224: "Browser back", 0x0225: "Browser fwd",
  0x0226: "Browser stop", 0x0227: "Browser refresh", 0x022a: "Bookmarks",
};

const MODS = ["LCtrl", "LShift", "LAlt", "LWin", "RCtrl", "RShift", "RAlt", "RWin"];

// Names below for types 07/08 are hypotheses from the stock Fn layer.
const KB_FUNC = { 0x01: "Win lock", 0x04: "Factory reset?", 0x18: "Fn+W func", 0x19: "Fn+Q func", 0x1a: "Fn+E func", 0x1b: "Fn+R func", 0x1c: "Fn+Bksp func", 0x1d: "Knob press func" };
const LIGHT = { "0000": "LED on/off", "0200": "Next effect", "0301": "LED bright+", "0302": "LED bright-", "0401": "LED speed+", "0402": "LED speed-" };

export const hidName = (usage) => HID[usage] ?? `HID 0x${usage.toString(16).padStart(2, "0")}`;
const h2 = (n) => n.toString(16).padStart(2, "0");

export function decodeKey(word) {
  const [b0, b1, b2, b3] = word;
  const raw = Array.from(word, h2).join(" ");
  let label;
  switch (b0) {
    case 0x00: {
      if (b1 === 0 && b2 === 0 && b3 === 0) { label = "—"; break; }
      const mods = MODS.filter((_, i) => b1 & (1 << i));
      const keys = [b3, b2].filter(Boolean).map(hidName);
      label = [...mods, ...keys].join("+");
      break;
    }
    case 0x01: label = `Mouse ${raw}`; break;
    case 0x02: { const u = (b2 << 8) | b3; label = CONSUMER[u] ?? `Consumer 0x${u.toString(16)}`; break; }
    case 0x03: label = `Macro ${b3 + 1}${b1 === 1 ? ` ×${b2}` : b1 === 2 ? " (mode 2)" : b1 === 4 ? " (mode 4)" : ""}`; break;
    case 0x05: label = `Layer fn ${h2(b1)}${h2(b3)}`; break;
    case 0x07: label = KB_FUNC[b3] ?? `Func 07/${h2(b3)}`; break;
    case 0x08: label = LIGHT[h2(b1) + h2(b2)] ?? `Light ${h2(b1)}${h2(b2)}`; break;
    case 0x0d: label = b1 ? "Fn2" : "Fn"; break;
    default: label = `Type ${h2(b0)}`;
  }
  return { type: b0, label, raw };
}

export function decodeLayer(bytes, keys) {
  return keys.map((key) => ({ ...key, ...decodeKey(bytes.subarray(key.matrix * 4, key.matrix * 4 + 4)) }));
}

// Assignments offered by the editor: [label, word]. Only types whose byte
// layout is confirmed against saved layers (00 key, 02 consumer, 0D Fn).
export function assignmentOptions() {
  const opts = [["None", [0, 0, 0, 0]], ["Fn", [0x0d, 0, 0, 0]]];
  const usages = Object.keys(HID).map(Number).filter((u) => u < 0xe0).sort((a, b) => a - b);
  for (const u of usages) opts.push([HID[u], [0, 0, 0, u]]);
  MODS.forEach((m, i) => opts.push([m, [0, 1 << i, 0, 0]]));
  for (const [u, name] of Object.entries(CONSUMER)) opts.push([name, [2, 0, Number(u) >> 8, Number(u) & 0xff]]);
  return opts;
}
