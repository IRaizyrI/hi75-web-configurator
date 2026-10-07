"""File-only PE import/string cross-reference inventory; never executes the target.

Linear sweep and frame-pointer prologues provide leads, not authoritative
function boundaries or proof of execution. Output includes source/tool hashes.
"""
import argparse
import bisect
import hashlib
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent / '.deps'))
import pefile
import capstone


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    if (args.output / 'index.json').exists():
        raise SystemExit('Refusing to overwrite an existing analysis index.')
    raw = args.executable.read_bytes()
    pe = pefile.PE(data=raw)
    if pe.FILE_HEADER.Machine != 0x14c:
        raise SystemExit('This initial tool supports x86 PE only.')
    base = pe.OPTIONAL_HEADER.ImageBase
    imports = {}
    for entry in getattr(pe, 'DIRECTORY_ENTRY_IMPORT', []):
        for item in entry.imports:
            imports[item.address] = entry.dll.decode(errors='replace') + '!' + (
                item.name.decode(errors='replace') if item.name else f'ordinal_{item.ordinal}')
    strings = {}
    wanted = {'Psd', 'Fw', 'LayerNum', 'LedOpt%d', 'Light', 'LightHW', 'Speed',
              'SpeedHW', 'KnobIndex', 'WheelMode', 'KB.ini', 'RGB', 'ShortName',
              'VID', 'PID', 'ApplyNow', 'DefLedIndex', 'LedMask'}
    for encoding, pattern in [('ascii', rb'[\x20-\x7e]{2,}'),
                              ('utf-16le', rb'(?:[\x20-\x7e]\x00){2,}')]:
        for match in re.finditer(pattern, raw):
            value = match.group().decode(encoding)
            if value not in wanted and not ('KB.ini' in value or 'LedOpt' in value):
                continue
            try:
                va = base + pe.get_rva_from_offset(match.start())
            except pefile.PEFormatError:
                continue
            strings[va] = {'value': value, 'encoding': encoding,
                           'fileOffset': match.start()}
    disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    disassembler.skipdata = True
    instructions = []
    sections = []
    for section in pe.sections:
        name = section.Name.rstrip(b'\0').decode(errors='replace')
        sections.append({'name': name, 'va': hex(base + section.VirtualAddress),
                         'virtualSize': section.Misc_VirtualSize,
                         'rawBytes': section.SizeOfRawData,
                         'characteristics': hex(section.Characteristics)})
        if section.Characteristics & 0x20000000:
            instructions.extend(disassembler.disasm_lite(section.get_data(), base + section.VirtualAddress))
    addresses = [row[0] for row in instructions]
    prologues = []
    for index, (_, _, mnemonic, operands) in enumerate(instructions[:-1]):
        if mnemonic == 'push' and operands == 'ebp' and instructions[index+1][2:] == ('mov', 'ebp, esp'):
            prologues.append(index)

    def boundary(index):
        position = bisect.bisect_right(prologues, index) - 1
        return hex(instructions[prologues[position]][0]) if position >= 0 else None

    references = []
    interesting_imports = {va for va, name in imports.items() if any(
        key in name for key in ['HidD_', 'HidP_', 'WriteFile', 'ReadFile',
                                'GetPrivateProfile', 'DeviceIoControl'])}
    target_values = set(strings) | interesting_imports
    with (args.output / 'disassembly.txt').open('w', encoding='utf-8') as listing:
        for index, (va, size, mnemonic, operands) in enumerate(instructions):
            listing.write(f'{va:08x}  {mnemonic:9s} {operands}\n')
            for token in re.findall(r'0x[0-9a-f]+', operands):
                target = int(token, 16)
                if target not in target_values:
                    continue
                references.append({'va': hex(va), 'instruction': f'{mnemonic} {operands}',
                    'target': hex(target), 'kind': 'import' if target in imports else 'string',
                    'label': imports.get(target) or strings[target]['value'],
                    'functionPrologueHint': boundary(index), 'listingLine': index + 1})
    report = {
        'source': str(args.executable.resolve()), 'bytes': len(raw),
        'sha256': hashlib.sha256(raw).hexdigest(),
        'scriptSha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'tools': {'pefile': pefile.__version__, 'capstone': capstone.__version__},
        'imageBase': hex(base), 'entryPoint': hex(base + pe.OPTIONAL_HEADER.AddressOfEntryPoint),
        'sections': sections, 'imports': {hex(k): v for k, v in imports.items()},
        'strings': {hex(k): v for k, v in strings.items()}, 'references': references,
        'limitations': 'Linear-sweep references and nearby prologues are analysis leads only; no target code ran.'}
    (args.output / 'index.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
    with (args.output / 'reference-context.txt').open('w', encoding='utf-8') as output:
        for ref in references:
            index = ref['listingLine'] - 1
            output.write('\n' + json.dumps(ref) + '\n')
            for va, _, mnemonic, operands in instructions[max(0,index-18):index+19]:
                output.write(f'{va:08x}  {mnemonic:9s} {operands}\n')
    print(json.dumps({'output': str(args.output), 'imports': len(imports),
        'stringTargets': len(strings), 'references': len(references),
        'instructions': len(instructions)}, indent=2))


if __name__ == '__main__':
    main()
