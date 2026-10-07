// Offline audit of official-app SET_FEATURE -> GET_FEATURE observations.
// Reads extracted capture JSON only; it never connects to a HID device.
import { createHash } from "node:crypto";
import { readFile, writeFile } from "node:fs/promises";
import path from "node:path";

const [outputPath, ...inputs] = process.argv.slice(2);
if (!outputPath || inputs.length === 0) {
  console.error("Usage: node tools/packet-diff/audit-read-pairs.mjs OUTPUT.json CAPTURE.json [...CAPTURE.json]");
  process.exit(2);
}

const sha256 = (bytes) => createHash("sha256").update(bytes).digest("hex");
const payload = (packet) => Buffer.from(packet.payloadHex ?? "", "hex");
const command = (packet) => payload(packet)[1];
const isSet = (p) => p.stage === 0 && p.setup?.bmRequestType === 0x21 && p.setup?.bRequest === 9 && p.setup?.wValue === 0x0306;
const isGet = (p) => p.stage === 0 && p.setup?.bmRequestType === 0xa1 && p.setup?.bRequest === 1 && p.setup?.wValue === 0x0306;
const targets = new Set([0x82, 0x84]);
const result = { scope: "offline official-app capture audit; no HID access", captures: [] };

for (const input of inputs) {
  const raw = await readFile(input);
  const source = JSON.parse(raw.toString("utf8"));
  const packets = source.packets ?? [];
  const pairs = [];
  for (let i = 0; i < packets.length; i++) {
    const set = packets[i];
    if (!isSet(set) || !targets.has(command(set))) continue;
    const get = packets.slice(i + 1).find((p) => isGet(p) && p.bus === set.bus && p.deviceAddress === set.deviceAddress);
    if (!get) continue;
    const response = packets.find((p) => p.stage === 3 && p.requestFrame === get.frame);
    if (!response) continue;
    const sent = payload(set);
    const received = payload(response);
    const nextSet = packets.slice(i + 1).find((p) => isSet(p) && p.frame > response.frame);
    pairs.push({
      command: `0x${command(set).toString(16)}`,
      setFrame: set.frame,
      getFrame: get.frame,
      responseFrame: response.frame,
      requestBytes: sent.length,
      requestHexPrefix: sent.subarray(0, 8).toString("hex"),
      requestDataAllZero: sent.subarray(8).every((byte) => byte === 0),
      requestSha256: sha256(sent),
      responseBytes: received.length,
      responseHexPrefix: received.subarray(0, 8).toString("hex"),
      responseDataHex: received.subarray(8).toString("hex"),
      responseSha256: sha256(received),
      nextSetFrame: nextSet?.frame ?? null,
      nextSetCommand: nextSet ? `0x${command(nextSet).toString(16)}` : null,
    });
  }
  result.captures.push({
    input: path.normalize(input),
    sourceSha256: source.sourceSha256 ?? null,
    pairCount: pairs.length,
    pairs,
  });
}

await writeFile(outputPath, `${JSON.stringify(result, null, 2)}\n`);
console.log(`${result.captures.reduce((n, c) => n + c.pairCount, 0)} read-shaped pairs audited -> ${outputPath}`);
