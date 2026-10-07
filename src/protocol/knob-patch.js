// Detects the knob firmware patch (tools/software-inspect/patch_knob.py) over
// the normal read path: the 0x85 macro read computes 0xDC00 + 0x200 x chunk
// in 16 bits, so chunk 104 reads code 0xAC00-0xADFF and chunk 36 reads
// 0x2400-0x25FF. Read-only.
const ROUTINES = Uint8Array.from([144, 15, 240, 240, 255, 194, 66, 144, 8, 192, 116, 1, 240, 144, 2, 224, 239, 240, 18, 169, 107, 144, 2, 224, 224, 36, 184, 253, 127, 12, 18, 15, 115, 34, 144, 15, 240, 224, 96, 27, 255, 228, 240, 210, 66, 144, 8, 192, 116, 129, 240, 144, 2, 224, 239, 240, 194, 115, 239, 36, 184, 253, 127, 12, 18, 96, 64, 34]); // at 0xACC0
const STEP_PATCHED = Uint8Array.from([116, 76, 48, 47, 2, 116, 75, 18, 172, 192, 210, 45, 120, 111, 118, 0, 128, 5, 0, 0, 0, 0, 0]); // at 0x259F
const STEP_STOCK = Uint8Array.from([144, 9, 184, 48, 47, 4, 116, 233, 128, 2, 116, 234, 240, 228, 163, 240, 210, 80, 210, 45, 120, 111, 246]);
const chunkFor = (addr) => ((((addr >> 8) - 0xdc) & 0xff) >> 1);

async function codeAt(session, addr, length) {
  const base = addr & ~0x1ff;
  const block = await session.readChunk(0x85, 0, chunkFor(base), 512);
  return block.subarray(addr - base, addr - base + length);
}

const same = (a, b) => a.length === b.length && a.every((x, i) => x === b[i]);

// Returns "patched" (v2), "patched-v1", "stock" or "unknown". v1 skipped knob
// steps while the custom-knob-press flag (LED byte 26) was set.
export async function detectKnobPatch(session) {
  const step = await codeAt(session, 0x259F, STEP_STOCK.length);
  if (same(step, STEP_STOCK)) return "stock";
  if (!same(step, STEP_PATCHED)) return "unknown";
  if (!same(await codeAt(session, 0xACC0, ROUTINES.length), ROUTINES)) return "unknown";
  const gate = await codeAt(session, 0x2592, 2);
  return gate[0] === 0 && gate[1] === 0 ? "patched" : gate[0] === 0x70 ? "patched-v1" : "unknown";
}
