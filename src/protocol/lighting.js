// LED block (0x84/0x04, 128 bytes) and per-effect palette (0x8A/0x0A, 512
// bytes). Layout from the app's FUN_00491430 and KB.ini LedOpt rows, checked
// against live reads; see docs/lighting.md.
export const LED_EFFECT_OFFSET = 10;
export const LED_CUSTOM_FLAG_OFFSET = 9; // 1 while Self-define is active
export const SELF_DEFINE_HW = 21;
export const LED_ENTRY_BASE = 0x3a; // 19 two-byte entries: [brightness, speed<<4 | colour]
export const PALETTE_GROUP = 21; // 7 RGB slots per effect, group 0 unused

// [hw code, speed adjustable, brightness adjustable, random colour, colour]
// from KB.ini LedOpt1..19, in entry order. Names follow the official app's
// menu (confirmed by the user): it lists hw 1-14, 17, 18, 21 and hides 15/16.
// Choosing Self-define in the app wrote hw 21 and set LED byte 9 to 1.
const LED_OPT = [
  [1, 0, 1, 1, 1], [2, 1, 1, 1, 1], [3, 1, 1, 0, 0], [4, 1, 1, 1, 1], [5, 1, 1, 1, 1],
  [6, 1, 1, 1, 1], [7, 1, 1, 1, 1], [8, 1, 1, 1, 1], [9, 1, 1, 1, 1], [10, 1, 1, 1, 1],
  [11, 1, 1, 1, 1], [12, 1, 1, 1, 1], [13, 1, 1, 1, 1], [14, 1, 1, 1, 1], [15, 1, 1, 0, 0],
  [16, 1, 1, 0, 0], [17, 1, 1, 0, 0], [18, 1, 1, 1, 1], [21, 0, 0, 0, 0],
];
const NAMES = {
  1: "Fixed on", 2: "Respire", 3: "Rainbow", 4: "Flash away", 5: "Raindrops", 6: "Rainbow wheel",
  7: "Ripples shining", 8: "Stars twinkle", 9: "Retro snake", 10: "Neon stream", 11: "Reaction",
  12: "Sine wave", 13: "Rotating windmill", 14: "Colorful waterfall", 15: "Hidden effect 15",
  16: "Hidden effect 16", 17: "Blossoming", 18: "Off", 21: "Self-define",
};
export const EFFECTS = LED_OPT.map(([hw, speed, light, random, color], index) => ({
  index, hw, name: NAMES[hw],
  speed: !!speed, brightness: !!light, random: !!random, color: !!color,
}));

// Colour index order matches the stock palette and the app's COLORREF map.
export const COLOR_NAMES = ["Red", "Green", "Blue", "Yellow", "Magenta", "Cyan", "White", "Random"];

export function decodeLighting(led, rgb) {
  const effect = EFFECTS.find((e) => e.hw === led[LED_EFFECT_OFFSET]) ?? null;
  const effects = EFFECTS.map((e) => {
    const a = LED_ENTRY_BASE + 2 * e.index;
    const g = PALETTE_GROUP * (e.index + 1);
    const palette = Array.from({ length: 7 }, (_, s) => Array.from(rgb.subarray(g + 3 * s, g + 3 * s + 3)));
    return { ...e, level: led[a], speedLevel: led[a + 1] >> 4, colorIndex: led[a + 1] & 0x0f, palette };
  });
  return { hw: led[LED_EFFECT_OFFSET], effect, effects };
}

// Returns new LED/RGB blocks with only the touched bytes changed.
export function encodeLighting(led, rgb, { hw, level, speedLevel, colorIndex, slotColor }) {
  const effect = EFFECTS.find((e) => e.hw === hw);
  if (!effect) throw new RangeError(`Unknown effect hw ${hw}`);
  const nextLed = led.slice();
  const nextRgb = rgb.slice();
  const a = LED_ENTRY_BASE + 2 * effect.index;
  nextLed[LED_EFFECT_OFFSET] = hw;
  nextLed[LED_CUSTOM_FLAG_OFFSET] = hw === SELF_DEFINE_HW ? 1 : 0;
  if (level !== undefined) {
    if (level < 0 || level > 4) throw new RangeError("Brightness 0-4");
    nextLed[a] = level;
  }
  let speed = nextLed[a + 1] >> 4;
  let color = nextLed[a + 1] & 0x0f;
  if (speedLevel !== undefined) {
    if (speedLevel < 0 || speedLevel > 4) throw new RangeError("Speed 0-4");
    speed = speedLevel;
  }
  if (colorIndex !== undefined) {
    if (colorIndex < 0 || colorIndex > 7) throw new RangeError("Colour index 0-7");
    color = colorIndex;
  }
  nextLed[a + 1] = (speed << 4) | color;
  if (slotColor) {
    if (color > 6) throw new RangeError("Random colour has no palette slot");
    nextRgb.set(slotColor, PALETTE_GROUP * (effect.index + 1) + 3 * color);
  }
  return { led: nextLed, rgb: nextRgb };
}

// Self-define per-key colours: block 0x86/0x06 (flash 0xCA00), three planes
// of 126 bytes (R, G, B) indexed by keymap matrix index. The firmware
// preserves bytes 378-511 itself.
export const KEY_COLOR_PLANE = 126;
export function keyColor(block, matrix) {
  return [0, 1, 2].map((p) => block[p * KEY_COLOR_PLANE + matrix]);
}
export function setKeyColors(block, entries) {
  const next = block.slice();
  for (const [matrix, rgb] of entries) {
    if (matrix < 0 || matrix >= KEY_COLOR_PLANE) throw new RangeError(`Matrix ${matrix} out of range`);
    rgb.forEach((v, p) => { next[p * KEY_COLOR_PLANE + matrix] = v; });
  }
  return next;
}
