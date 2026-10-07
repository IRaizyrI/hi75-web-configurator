// Extract exact raw evidence for the candidate 8051 GET_REPORT dispatcher.
// This verifies byte locations in one preserved image; it does not execute code.
import { createHash } from "node:crypto";
import { readFile, writeFile } from "node:fs/promises";

const [inputPath, outputPath] = process.argv.slice(2);
if (!inputPath || !outputPath) {
  console.error("Usage: node tools/software-inspect/extract_read_dispatch.mjs FIRMWARE.bin OUTPUT.json");
  process.exit(2);
}
const firmware = await readFile(inputPath);
const hash = createHash("sha256").update(firmware).digest("hex");
const expectedHash = "31ee5b474b06b5bd26f32e15e379ce8c3251913b57dfebc3194a7c4dbdcc7ad0";
if (hash !== expectedHash) throw new Error(`Unexpected firmware SHA-256: ${hash}`);
const selectorAddress = 0x4e1e;
const selectorHex = "7877e6247eb409004003024f6b904e3975f003a4c58325f0c58373";
if (firmware.subarray(selectorAddress, selectorAddress + selectorHex.length / 2).toString("hex") !== selectorHex) {
  throw new Error("Dispatcher selector bytes changed");
}
const tableAddress = 0x4e39;
const cases = [];
for (let i = 0; i < 9; i++) {
  const at = tableAddress + i * 3;
  if (firmware[at] !== 0x02) throw new Error(`Expected LJMP at 0x${at.toString(16)}`);
  const target = (firmware[at + 1] << 8) | firmware[at + 2];
  cases.push({ commandByte: `0x${(0x82 + i).toString(16)}`, tableOffset: `0x${at.toString(16)}`, target: `0x${target.toString(16)}` });
}
const result = {
  scope: "raw saved-image extraction only; jump table interpretation remains a static-analysis claim",
  firmwareSha256: hash,
  selectorAddress: `0x${selectorAddress.toString(16)}`,
  selectorHex,
  tableAddress: `0x${tableAddress.toString(16)}`,
  cases,
  command82BranchHex: firmware.subarray(0x4e54, 0x4e74).toString("hex"),
  command83BranchHex: firmware.subarray(0x4e74, 0x4ecc).toString("hex"),
  command84BranchHex: firmware.subarray(0x4ecc, 0x4edd).toString("hex"),
  command85BranchHex: firmware.subarray(0x4edd, 0x4eed).toString("hex"),
  command86BranchHex: firmware.subarray(0x4eed, 0x4efd).toString("hex"),
  command8aBranchHex: firmware.subarray(0x4f51, 0x4f6b).toString("hex"),
  commonReadSetupHex: firmware.subarray(0x4f6b, 0x4f86).toString("hex"),
  identityDataAtB3e3Hex: firmware.subarray(0xb3e3, 0xb3e9).toString("hex"),
};
await writeFile(outputPath, `${JSON.stringify(result, null, 2)}\n`);
console.log(`Extracted ${cases.length} dispatch entries from ${inputPath} -> ${outputPath}`);
