// Macro buffer (0x85/0x05); format from the app's FUN_00490D10/FUN_00490940
// and the firmware player at CODE 0x4A2B. See docs/keycode-encoding.md.
//   header: N x {u16 LE offset, u16 LE length}, offsets from buffer start
//   record: u8 nameBytes, UTF-16LE name, then 4-byte actions
//   action: b0 = 0x80 release | kind<<4 | delay[19:16], b1-b2 delay, b3 code
// Kinds per the firmware player (CODE 0x4C83): 0 key (HID usage), 1 modifier
// (E0-E7; low nibble is the bit), 2 mouse button, 3/4 mouse X/Y, 5 wheel.
// The player sign-extends b1, so delays are kept below 0x8000.
export const MACRO_BUFFER_BYTES = 2048; // 4 flash sectors at 0xDC00; the region is empty up to 0xF000
export const MAX_DELAY = 0x7fff;
export const KIND = { key: 0, modifier: 1, mouse: 2 };

export function parseMacros(buf) {
  const firstOffset = buf[0] | (buf[1] << 8);
  if (firstOffset === 0 || firstOffset % 4 || firstOffset > buf.length) return [];
  const macros = [];
  for (let i = 0; i < firstOffset / 4; i++) {
    const off = buf[i * 4] | (buf[i * 4 + 1] << 8);
    const len = buf[i * 4 + 2] | (buf[i * 4 + 3] << 8);
    if (!len || off + len > buf.length) break;
    const rec = buf.subarray(off, off + len);
    const nameBytes = rec[0];
    let name = "";
    for (let j = 0; j + 1 < nameBytes; j += 2) name += String.fromCharCode(rec[1 + j] | (rec[2 + j] << 8));
    const actions = [];
    for (let p = 1 + nameBytes; p + 4 <= rec.length; p += 4) {
      const [b0, b1, b2, b3] = rec.subarray(p, p + 4);
      actions.push({ kind: (b0 >> 4) & 0x7, down: !(b0 & 0x80), delay: ((b0 & 0x0f) << 16) | (b1 << 8) | b2, code: b3 });
    }
    macros.push({ name, actions });
  }
  return macros;
}

export function encodeMacros(macros) {
  const records = macros.map(({ name, actions }) => {
    const chars = Array.from(name.slice(0, 30));
    const out = [chars.length * 2];
    for (const c of chars) { const u = c.charCodeAt(0); out.push(u & 0xff, u >> 8); }
    for (const a of actions) {
      if (![KIND.key, KIND.modifier, KIND.mouse].includes(a.kind)) throw new RangeError(`Unsupported action kind ${a.kind}`);
      const delay = Math.max(0, Math.min(MAX_DELAY, Math.round(a.delay)));
      out.push((a.down ? 0 : 0x80) | (a.kind << 4), (delay >> 8) & 0xff, delay & 0xff, a.code);
    }
    return out;
  });
  const header = records.length * 4;
  const total = header + records.reduce((n, r) => n + r.length, 0);
  if (total > MACRO_BUFFER_BYTES) throw new RangeError(`Macros need ${total} bytes; limit is ${MACRO_BUFFER_BYTES}`);
  const buf = new Uint8Array(MACRO_BUFFER_BYTES);
  let off = header;
  records.forEach((r, i) => {
    buf.set([off & 0xff, off >> 8, r.length & 0xff, r.length >> 8], i * 4);
    buf.set(r, off);
    off += r.length;
  });
  return buf;
}

// Key word that plays macro `index` (0-based) `count` times (mode 1).
export const macroKeyWord = (index, count = 1) => [0x03, 0x01, Math.max(1, Math.min(255, count)), index];

// KeyboardEvent.code -> HID usage, for recording.
const CODE_TO_HID = {
  Enter: 0x28, Escape: 0x29, Backspace: 0x2a, Tab: 0x2b, Space: 0x2c, Minus: 0x2d, Equal: 0x2e,
  BracketLeft: 0x2f, BracketRight: 0x30, Backslash: 0x31, Semicolon: 0x33, Quote: 0x34, Backquote: 0x35,
  Comma: 0x36, Period: 0x37, Slash: 0x38, CapsLock: 0x39, PrintScreen: 0x46, ScrollLock: 0x47, Pause: 0x48,
  Insert: 0x49, Home: 0x4a, PageUp: 0x4b, Delete: 0x4c, End: 0x4d, PageDown: 0x4e, ArrowRight: 0x4f,
  ArrowLeft: 0x50, ArrowDown: 0x51, ArrowUp: 0x52, ContextMenu: 0x65,
  ControlLeft: 0xe0, ShiftLeft: 0xe1, AltLeft: 0xe2, MetaLeft: 0xe3, ControlRight: 0xe4, ShiftRight: 0xe5, AltRight: 0xe6, MetaRight: 0xe7,
};
for (let i = 0; i < 26; i++) CODE_TO_HID[`Key${String.fromCharCode(65 + i)}`] = 0x04 + i;
for (let i = 1; i <= 9; i++) CODE_TO_HID[`Digit${i}`] = 0x1d + i;
CODE_TO_HID.Digit0 = 0x27;
for (let i = 1; i <= 12; i++) CODE_TO_HID[`F${i}`] = 0x39 + i;
export const hidForCode = (code) => CODE_TO_HID[code];
export const keyAction = (usage, down, delay) => ({ kind: usage >= 0xe0 && usage <= 0xe7 ? KIND.modifier : KIND.key, down, delay, code: usage });
