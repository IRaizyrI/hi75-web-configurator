"""Find UTF-16LE PE strings and their immediate references in a text disassembly.

The disassembly is a linear sweep and references are leads until a CFG analyzer
confirms the instruction. The target PE is never executed.
"""

import argparse
import json
import re
import struct
from pathlib import Path


def u16(data, offset):
    return struct.unpack_from('<H', data, offset)[0]


def u32(data, offset):
    return struct.unpack_from('<I', data, offset)[0]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('pe', type=Path)
    parser.add_argument('disassembly', type=Path)
    parser.add_argument('terms', nargs='+')
    args = parser.parse_args()
    data = args.pe.read_bytes()
    pe = u32(data, 0x3c)
    if data[pe:pe + 4] != b'PE\0\0' or u16(data, pe + 24) != 0x10b:
        raise SystemExit('Requires a 32-bit PE')
    image_base = u32(data, pe + 52)
    section_count = u16(data, pe + 6)
    section_start = pe + 24 + u16(data, pe + 20)
    sections = []
    for index in range(section_count):
        entry = section_start + index * 40
        virtual_size, rva, raw_size, raw = struct.unpack_from('<IIII', data, entry + 8)
        sections.append((raw, raw + min(raw_size, virtual_size), image_base + rva))

    targets = {}
    for match in re.finditer(rb'(?:[\x20-\x7e]\x00){4,}', data):
        value = match.group().decode('utf-16le')
        if not any(term.lower() in value.lower() for term in args.terms):
            continue
        for start, end, va in sections:
            if start <= match.start() < end:
                address = va + match.start() - start
                targets[address] = {'address': f'0x{address:08x}', 'text': value, 'references': []}
                break

    pattern = re.compile(r'0x([0-9a-f]+)')
    with args.disassembly.open(encoding='utf-8') as listing:
        for line in listing:
            for token in pattern.findall(line):
                address = int(token, 16)
                if address in targets:
                    targets[address]['references'].append(line.rstrip())
    print(json.dumps(sorted(targets.values(), key=lambda item: item['address']), indent=2))


if __name__ == '__main__':
    main()
