// Assignments offered by the Remap page, grouped like a key picker.
// Words use the layout in docs/keycode-encoding.md.
const key = (label, usage, mods = 0) => ({ label, word: [0, mods, 0, usage] });
const consumer = (label, usage) => ({ label, word: [2, 0, usage >> 8, usage & 0xff] });

const letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".split("").map((c, i) => key(c, 0x04 + i));
const digits = "1234567890".split("").map((c, i) => key(c, 0x1e + i));
const fkeys = Array.from({ length: 12 }, (_, i) => key(`F${i + 1}`, 0x3a + i))
  .concat(Array.from({ length: 12 }, (_, i) => key(`F${i + 13}`, 0x68 + i)));

export const CATEGORIES = [
  {
    id: "keyboard", name: "Keyboard", groups: [
      { name: "Letters", items: letters },
      { name: "Numbers", items: digits },
      { name: "Function keys", items: fkeys },
      { name: "Editing", items: [key("Esc", 0x29), key("Tab", 0x2b), key("Caps Lock", 0x39), key("Enter", 0x28), key("Backspace", 0x2a), key("Space", 0x2c), key("Delete", 0x4c), key("Insert", 0x49), key("Menu", 0x65)] },
      { name: "Navigation", items: [key("Home", 0x4a), key("End", 0x4d), key("Page Up", 0x4b), key("Page Down", 0x4e), key("Up", 0x52), key("Down", 0x51), key("Left", 0x50), key("Right", 0x4f)] },
      { name: "Symbols", items: [key("-", 0x2d), key("=", 0x2e), key("[", 0x2f), key("]", 0x30), key("\\", 0x31), key(";", 0x33), key("'", 0x34), key("`", 0x35), key(",", 0x36), key(".", 0x37), key("/", 0x38), key("ISO \\", 0x64)] },
      { name: "System", items: [key("Print Screen", 0x46), key("Scroll Lock", 0x47), key("Pause", 0x48), key("Num Lock", 0x53)] },
    ],
  },
  {
    id: "modifiers", name: "Modifiers", groups: [
      { name: "Left", items: [key("L-Ctrl", 0, 0x01), key("L-Shift", 0, 0x02), key("L-Alt", 0, 0x04), key("L-Win", 0, 0x08)] },
      { name: "Right", items: [key("R-Ctrl", 0, 0x10), key("R-Shift", 0, 0x20), key("R-Alt", 0, 0x40), key("R-Win", 0, 0x80)] },
      { name: "Shortcuts", items: [key("Copy", 0x06, 0x01), key("Paste", 0x19, 0x01), key("Cut", 0x1b, 0x01), key("Undo", 0x1d, 0x01), key("Alt+Tab", 0x2b, 0x04), key("Win+D", 0x07, 0x08), key("Win+L", 0x0f, 0x08), key("Ctrl+Shift+Esc", 0x29, 0x03)] },
    ],
  },
  {
    id: "media", name: "Media", groups: [
      { name: "Playback", items: [consumer("Play/Pause", 0xcd), consumer("Next track", 0xb5), consumer("Prev track", 0xb6), consumer("Stop", 0xb7)] },
      { name: "Volume", items: [consumer("Volume up", 0xe9), consumer("Volume down", 0xea), consumer("Mute", 0xe2)] },
      { name: "Apps", items: [consumer("Media player", 0x183), consumer("Mail", 0x18a), consumer("Calculator", 0x192), consumer("My computer", 0x194), consumer("Browser search", 0x221), consumer("Browser home", 0x223), consumer("Browser back", 0x224), consumer("Browser forward", 0x225), consumer("Browser refresh", 0x227)] },
      { name: "Screen", items: [consumer("Screen brighter", 0x6f), consumer("Screen dimmer", 0x70)] },
    ],
  },
  {
    id: "lighting", name: "Lighting", groups: [
      { name: "Keyboard lighting", items: [
        { label: "Lights on/off", word: [8, 0, 0, 0] }, { label: "Next effect", word: [8, 2, 0, 0] },
        { label: "Brighter", word: [8, 3, 1, 0] }, { label: "Dimmer", word: [8, 3, 2, 0] },
        { label: "Faster", word: [8, 4, 1, 0] }, { label: "Slower", word: [8, 4, 2, 0] },
      ] },
    ],
  },
  {
    id: "special", name: "Special", groups: [
      { name: "Keyboard", items: [{ label: "Fn", word: [0x0d, 0, 0, 0] }, { label: "Win lock", word: [7, 0, 0, 1] }, { label: "Disabled", word: [0, 0, 0, 0] }] },
    ],
  },
];

export const sameWord = (a, b) => a.length === b.length && a.every((x, i) => x === b[i]);
