// Offline extraction of interrupt-IN report bytes from saved USBPcap captures.
// Runs tshark on files only; does not connect to a USB or HID device.
import { spawnSync } from "node:child_process";
import { createHash } from "node:crypto";
import { readFile, writeFile } from "node:fs/promises";

const [tsharkPath, outputPath, ...capturePaths] = process.argv.slice(2);
if (!tsharkPath || !outputPath || capturePaths.length === 0) {
  console.error("Usage: node tools/packet-diff/extract-vendor-input.mjs TSHARK.exe OUTPUT.json CAPTURE.pcapng [...CAPTURE.pcapng]");
  process.exit(2);
}
const filter = "usb.bus_id == 2 && usb.device_address == 5 && usb.transfer_type == 1 && usb.endpoint_address == 0x82 && usbhid.data";
const result = { scope: "saved capture analysis only; bus 2/device 5/endpoint 0x82", displayFilter: filter, captures: [] };
for (const capturePath of capturePaths) {
  const source = await readFile(capturePath);
  const run = spawnSync(tsharkPath, [
    "-r", capturePath, "-Y", filter, "-T", "fields",
    "-e", "frame.number", "-e", "frame.time_epoch", "-e", "usbhid.data",
  ], { encoding: "utf8", maxBuffer: 8 * 1024 * 1024 });
  if (run.error || run.status !== 0) throw new Error(run.error?.message || run.stderr || `tshark exit ${run.status}`);
  const reports = run.stdout.trim().split(/\r?\n/).filter(Boolean).map((line) => {
    const [frame, epochSeconds, hex] = line.split("\t");
    if (!/^\d+$/.test(frame) || !/^[0-9a-f]+$/i.test(hex)) throw new Error(`Unrecognized tshark row: ${line}`);
    return { frame: Number(frame), epochSeconds, reportHex: hex.toLowerCase() };
  });
  result.captures.push({
    path: capturePath,
    sourceSha256: createHash("sha256").update(source).digest("hex"),
    reports,
  });
}
await writeFile(outputPath, `${JSON.stringify(result, null, 2)}\n`);
console.log(`${result.captures.reduce((n, c) => n + c.reports.length, 0)} input reports extracted -> ${outputPath}`);
