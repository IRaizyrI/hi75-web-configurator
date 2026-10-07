"""Extract OemDrv.exe's static Windows-VK to HID-keycode lookup table.

The VA and entry count are evidence from Ghidra function 0x4786A0 in the
analyzed executable, not a generic format shared by other app versions.
The executable is only read as bytes; it is never run.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


def u16(data: bytes, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def va_to_file_offset(data: bytes, va: int) -> int:
    pe_offset = u32(data, 0x3C)
    if data[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise ValueError("not a PE file")
    optional = pe_offset + 24
    if u16(data, optional) != 0x10B:
        raise ValueError("requires a 32-bit PE")
    rva = va - u32(data, optional + 28)
    section_table = optional + u16(data, pe_offset + 20)
    for index in range(u16(data, pe_offset + 6)):
        section = section_table + index * 40
        virtual_size, section_rva, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, section + 8
        )
        if section_rva <= rva < section_rva + min(virtual_size, raw_size):
            return raw_pointer + rva - section_rva
    raise ValueError(f"VA 0x{va:08X} is not mapped to raw PE data")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    executable = args.executable.read_bytes()
    expected_hash = "635587cf6334346ab9932479d309cfe5f395c45d77c698b0143d28bf5b661ee0"
    actual_hash = hashlib.sha256(executable).hexdigest()
    if actual_hash != expected_hash:
        parser.error(f"unrecognized OemDrv.exe SHA-256: {actual_hash}")

    address, count = 0x60B7C0, 0x73
    offset = va_to_file_offset(executable, address)
    raw = executable[offset:offset + count * 2]
    if len(raw) != count * 2:
        parser.error("lookup table extends beyond the file")
    entries = [{"virtualKey": raw[i * 2 + 1], "hidCode": raw[i * 2]}
               for i in range(count)]
    if len({entry["virtualKey"] for entry in entries}) != count:
        parser.error("duplicate VK values; table layout needs rechecking")

    output = {
        "source": str(args.executable),
        "sourceSha256": actual_hash,
        "evidenceFunction": "0x004786A0",
        "tableVirtualAddress": f"0x{address:08X}",
        "entryCount": count,
        "entryLayout": "two bytes: HID code, then Windows virtual-key code",
        "confidence": "static application lookup; mapping to this Hi75 not captured",
        "entries": entries,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    if args.output.exists():
        parser.error(f"refusing to overwrite {args.output}")
    args.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {len(entries)} entries to {args.output}")


if __name__ == "__main__":
    main()
