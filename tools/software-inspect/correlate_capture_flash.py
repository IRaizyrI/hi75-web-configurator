"""Find byte-identical regions between a saved Hi75 capture and flash dump.

Offline only. The tool neither opens the keyboard nor constructs HID traffic.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("capture_json", type=Path)
    parser.add_argument("firmware_dump", type=Path)
    parser.add_argument("--startup-json", type=Path,
                        help="Optional startup capture containing frame 10 identity response")
    args = parser.parse_args()
    capture_bytes = args.capture_json.read_bytes()
    dump = args.firmware_dump.read_bytes()
    packets = json.loads(capture_bytes)["packets"]
    reports = {packet["frame"]: bytes.fromhex(packet["payloadHex"])
               for packet in packets if packet["frame"] in (54, 55, 57)}
    wanted = {54: 128, 55: 128, 57: 512}
    if any(len(reports.get(frame, b"")) < 8 + size for frame, size in wanted.items()):
        raise ValueError("Capture lacks required report payloads for frames 54, 55, 57")
    payloads = {frame: reports[frame][8:8 + size] for frame, size in wanted.items()}
    results = {}
    for frame, payload in payloads.items():
        positions = []
        cursor = 0
        while (position := dump.find(payload, cursor)) != -1:
            positions.append(position)
            cursor = position + 1
        results[str(frame)] = {"dataBytes": len(payload),
                               "dataSha256": sha256(payload),
                               "exactFlashOffsets": positions}
    offset = 0xC600
    results["55"]["differencesFromC600"] = [
        {"dataOffset": index, "backupByte": f"{dump[offset + index]:02x}",
         "reportByte": f"{value:02x}"}
        for index, value in enumerate(payloads[55]) if value != dump[offset + index]
    ]
    identity = None
    if args.startup_json:
        startup_bytes = args.startup_json.read_bytes()
        startup_packets = json.loads(startup_bytes)["packets"]
        response = next(packet for packet in startup_packets if packet["frame"] == 10)
        identity_data = bytes.fromhex(response["payloadHex"])[8:14]
        if len(identity_data) != 6:
            raise ValueError("Startup frame 10 lacks six data bytes")
        positions = []
        cursor = 0
        while (position := dump.find(identity_data, cursor)) != -1:
            positions.append(position)
            cursor = position + 1
        identity = {"sourceCaptureJsonSha256": sha256(startup_bytes),
                    "frame": 10, "dataHex": identity_data.hex(" "),
                    "exactFlashOffsets": positions}
    print(json.dumps({"sourceCaptureJsonSha256": sha256(capture_bytes),
                      "sourceFirmwareDumpSha256": sha256(dump),
                      "analysisOnly": True, "reportDataOffset": 8,
                      "startupIdentity": identity, "results": results}, indent=2))


if __name__ == "__main__":
    main()
