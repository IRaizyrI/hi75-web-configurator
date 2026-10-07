"""Correlate captured USB descriptors with the preserved Hi75 firmware image.

This is file-only analysis. The recovered HID report descriptors are firmware
data candidates, not a fresh GET_DESCRIPTOR result from the connected device.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from collections import defaultdict
from pathlib import Path


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def all_offsets(haystack: bytes, needle: bytes) -> list[int]:
    locations = []
    cursor = 0
    while (index := haystack.find(needle, cursor)) != -1:
        locations.append(index)
        cursor = index + 1
    return locations


def captured_payload(packets: list[dict], frame: int) -> bytes:
    return bytes.fromhex(next(row for row in packets if row["frame"] == frame)["payloadHex"])


def hid_lengths(config: bytes) -> dict[int, int]:
    lengths = {}
    interface = None
    offset = 0
    while offset < len(config):
        size = config[offset]
        if size < 2 or offset + size > len(config):
            raise ValueError(f"Malformed USB descriptor at config offset {offset}")
        descriptor = config[offset:offset + size]
        if descriptor[1] == 4:
            interface = descriptor[2]
        elif descriptor[1] == 0x21 and interface is not None:
            if size < 9 or descriptor[6] != 0x22:
                raise ValueError("Unexpected HID descriptor layout")
            lengths[interface] = int.from_bytes(descriptor[7:9], "little")
        offset += size
    return lengths


def parse_report_descriptor(data: bytes) -> dict:
    globals_ = {"usagePage": 0, "reportSize": 0, "reportCount": 0, "reportId": 0}
    stack = []
    local = {"usages": [], "usageMinimum": None, "usageMaximum": None}
    bits = defaultdict(lambda: defaultdict(int))
    fields = []
    collections = 0
    index = 0
    while index < len(data):
        start = index
        prefix = data[index]
        index += 1
        if prefix == 0xFE:
            if index + 2 > len(data):
                raise ValueError("Truncated long HID item")
            size = data[index]
            index += 2 + size
            if index > len(data):
                raise ValueError("Truncated long HID item payload")
            continue
        size = (prefix & 3) if (prefix & 3) != 3 else 4
        if index + size > len(data):
            raise ValueError("Truncated short HID item")
        value = int.from_bytes(data[index:index + size], "little") if size else 0
        index += size
        kind = (prefix >> 2) & 3
        tag = (prefix >> 4) & 15
        if kind == 1:
            name = {0: "usagePage", 7: "reportSize", 8: "reportId", 9: "reportCount"}.get(tag)
            if name:
                globals_[name] = value
            elif tag == 10:
                stack.append(globals_.copy())
            elif tag == 11:
                if not stack:
                    raise ValueError("Global POP without PUSH")
                globals_ = stack.pop()
        elif kind == 2:
            if tag == 0:
                local["usages"].append(value)
            elif tag == 1:
                local["usageMinimum"] = value
            elif tag == 2:
                local["usageMaximum"] = value
        elif kind == 0:
            if tag in (8, 9, 11):
                report_kind = {8: "input", 9: "output", 11: "feature"}[tag]
                count = globals_["reportCount"]
                width = globals_["reportSize"]
                report_id = globals_["reportId"]
                bit_count = count * width
                bits[report_id][report_kind] += bit_count
                fields.append({"descriptorOffset": start, "reportId": report_id,
                               "kind": report_kind, "usagePage": globals_["usagePage"],
                               "usages": local["usages"],
                               "usageMinimum": local["usageMinimum"],
                               "usageMaximum": local["usageMaximum"],
                               "reportSizeBits": width, "reportCount": count,
                               "fieldBits": bit_count, "flags": value})
            elif tag == 10:
                collections += 1
            elif tag == 12:
                collections -= 1
                if collections < 0:
                    raise ValueError("Unbalanced END_COLLECTION")
            local = {"usages": [], "usageMinimum": None, "usageMaximum": None}
    if collections != 0 or stack:
        raise ValueError("Unbalanced HID descriptor collections/global stack")
    sizes = {}
    for report_id, kinds in sorted(bits.items()):
        sizes[str(report_id)] = {
            kind: {"payloadBits": total, "reportBytesIncludingId":
                   (total + 7) // 8 + (1 if report_id else 0)}
            for kind, total in sorted(kinds.items())
        }
    return {"length": len(data), "sha256": sha(data), "hex": data.hex(),
            "reportSizes": sizes, "fields": fields}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("firmware_dump", type=Path)
    parser.add_argument("startup_capture_json", type=Path)
    args = parser.parse_args()
    firmware = args.firmware_dump.read_bytes()
    captured = json.loads(args.startup_capture_json.read_text(encoding="utf-8"))["packets"]
    device = captured_payload(captured, 2)
    config = captured_payload(captured, 4)
    device_matches = all_offsets(firmware, device)
    config_matches = all_offsets(firmware, config)
    if len(device_matches) != 1 or len(config_matches) != 1:
        raise ValueError("Captured USB descriptors do not match unique firmware offsets")
    lengths = hid_lengths(config)
    if set(lengths) != {0, 1} or config_matches[0] != device_matches[0] + len(device):
        raise ValueError("Unexpected interface descriptors or firmware ordering")
    second_start = device_matches[0] - lengths[1]
    first_start = second_start - lengths[0]
    if first_start < 0:
        raise ValueError("HID descriptors exceed firmware prefix")
    first = firmware[first_start:second_start]
    second = firmware[second_start:device_matches[0]]
    result = {
        "analysisOnly": True,
        "firmwareSha256": sha(firmware),
        "capturedDeviceDescriptor": {"frame": 2, "offset": device_matches[0],
                                     "length": len(device), "sha256": sha(device)},
        "capturedConfigurationDescriptor": {"frame": 4, "offset": config_matches[0],
                                            "length": len(config), "sha256": sha(config)},
        "hidReportDescriptors": {
            "interface0": {"firmwareOffset": first_start, **parse_report_descriptor(first)},
            "interface1": {"firmwareOffset": second_start, **parse_report_descriptor(second)},
        },
    }
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
