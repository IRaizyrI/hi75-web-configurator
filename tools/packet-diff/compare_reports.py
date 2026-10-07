"""Compare two captured HID report payloads from extract_control.py output.

This reads a saved JSON file only. It never opens a HID device.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("capture", type=Path, help="derived/control-transfers.json")
    parser.add_argument("first_frame", type=int)
    parser.add_argument("second_frame", type=int)
    parser.add_argument("--other-capture", type=Path,
                        help="JSON containing second_frame; defaults to capture")
    parser.add_argument("--data-offset", type=int, default=0,
                        help="start offset in each complete report, including report ID")
    parser.add_argument("--length", type=int, default=None,
                        help="bytes to compare from data-offset; default: shortest remainder")
    args = parser.parse_args()

    if args.data_offset < 0 or (args.length is not None and args.length < 0):
        parser.error("offset and length must be nonnegative")

    first_packets = json.loads(args.capture.read_text(encoding="utf-8"))["packets"]
    second_packets = (json.loads(args.other_capture.read_text(encoding="utf-8"))["packets"]
                      if args.other_capture else first_packets)
    selected = []
    for packets, frame in ((first_packets, args.first_frame),
                           (second_packets, args.second_frame)):
        matches = [packet for packet in packets if packet["frame"] == frame]
        if len(matches) != 1 or not matches[0].get("payloadHex"):
            parser.error(f"frame {frame} has no unique nonempty report payload")
        selected.append(bytes.fromhex(matches[0]["payloadHex"]))

    first, second = selected
    available = min(len(first), len(second)) - args.data_offset
    if available < 0:
        parser.error("offset exceeds the shorter report")
    length = available if args.length is None else args.length
    if length > available:
        parser.error(f"requested {length} bytes, only {available} available in both reports")

    print(f"frames {args.first_frame} ({len(first)} bytes) and "
          f"{args.second_frame} ({len(second)} bytes)")
    if args.other_capture:
        print(f"sources: {args.capture} and {args.other_capture}")
    print(f"comparing {length} bytes from whole-report offset {args.data_offset}")
    differences = 0
    for relative in range(length):
        absolute = args.data_offset + relative
        if first[absolute] != second[absolute]:
            print(f"data offset {relative:3d}, report offset {absolute:3d}: "
                  f"{first[absolute]:02X} -> {second[absolute]:02X}")
            differences += 1
    print(f"{differences} differing byte(s)")


if __name__ == "__main__":
    main()
