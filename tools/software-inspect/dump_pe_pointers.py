"""Dump little-endian 32-bit pointers at a PE virtual address without executing it."""

import argparse
import json
import struct
from pathlib import Path


def read_u16(data, offset):
    return struct.unpack_from('<H', data, offset)[0]


def read_u32(data, offset):
    return struct.unpack_from('<I', data, offset)[0]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('pe', type=Path)
    parser.add_argument('virtual_address', type=lambda value: int(value, 0))
    parser.add_argument('--count', type=int, default=32)
    args = parser.parse_args()
    data = args.pe.read_bytes()
    pe_offset = read_u32(data, 0x3c)
    if data[pe_offset:pe_offset + 4] != b'PE\0\0':
        raise SystemExit('Not a PE file')
    section_count = read_u16(data, pe_offset + 6)
    optional_size = read_u16(data, pe_offset + 20)
    optional = pe_offset + 24
    if read_u16(data, optional) != 0x10b:
        raise SystemExit('Requires a 32-bit PE')
    image_base = read_u32(data, optional + 28)
    address_rva = args.virtual_address - image_base
    section_base = optional + optional_size
    match = None
    for index in range(section_count):
        offset = section_base + index * 40
        name = data[offset:offset + 8].rstrip(b'\0').decode('ascii', errors='replace')
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from('<IIII', data, offset + 8)
        if virtual_address <= address_rva < virtual_address + min(virtual_size, raw_size):
            match = (name, raw_pointer + address_rva - virtual_address)
            break
    if match is None:
        raise SystemExit('Address does not map to raw section data')
    name, file_offset = match
    if file_offset + 4 * args.count > len(data):
        raise SystemExit('Requested pointer range exceeds the file')
    print(json.dumps({
        'source': str(args.pe),
        'section': name,
        'virtualAddress': f'0x{args.virtual_address:08x}',
        'fileOffset': f'0x{file_offset:x}',
        'pointers': [
            {'slot': f'0x{args.virtual_address + 4 * i:08x}',
             'value': f'0x{read_u32(data, file_offset + 4 * i):08x}'}
            for i in range(args.count)
        ],
    }, indent=2))


if __name__ == '__main__':
    main()
