"""Compare preserved flash bytes with the official app's Hi75 RGB key profile.

Offline only: reads files, never opens a HID device or modifies a dump.
Candidate offsets are analysis inputs, not a claim about live HID behavior.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


def profile_keys(path: Path) -> list[dict[str, int | str]]:
    section = ""
    keys = []
    for line in path.read_text(encoding="utf-8-sig").splitlines():
        line = line.strip()
        if line.startswith("[") and line.endswith("]"):
            section = line[1:-1].upper()
        match = re.fullmatch(r"(K\d+)\s*=\s*(.+)", line) if section == "KEY" else None
        if not match:
            continue
        fields = [int(field.strip(), 0) for field in match.group(2).split(",")]
        if len(fields) >= 8:
            keys.append({"name": match.group(1), "category": fields[4],
                         "virtualKey": fields[5], "matrixIndex": fields[7]})
    return keys


def fn1_values(path: Path) -> dict[str, int]:
    section = ""
    values = {}
    for line in path.read_text(encoding="utf-8-sig").splitlines():
        line = line.strip()
        if line.startswith("[") and line.endswith("]"):
            section = line[1:-1].upper()
        match = re.fullmatch(r"(K\d+)\s*=\s*(.+)", line) if section == "FN1" else None
        if match:
            fields = [int(field.strip(), 0) for field in match.group(2).split(",")]
            if len(fields) >= 3:
                values[match.group(1)] = fields[2]
    return values


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dump", type=Path)
    parser.add_argument("profile", type=Path)
    parser.add_argument("lookup", type=Path)
    parser.add_argument("--offset", type=lambda value: int(value, 0), default=0xB400)
    args = parser.parse_args()
    image = args.dump.read_bytes()
    lookup = {entry["virtualKey"]: entry["hidCode"]
              for entry in json.loads(args.lookup.read_text(encoding="utf-8"))["entries"]}
    comparable = [key for key in profile_keys(args.profile)
                  if key["category"] == 2 and key["virtualKey"] in lookup]
    results = []
    for key in comparable:
        position = args.offset + 4 * key["matrixIndex"]
        actual = image[position:position + 4]
        expected = bytes((0, 0, 0, lookup[key["virtualKey"]]))
        results.append({**key, "flashOffset": position, "actual": actual.hex(" "),
                        "expected": expected.hex(" "), "matches": actual == expected})
    # The seven non-ordinary values resemble the standard HID modifier-bit
    # ordering. Report this as a candidate pattern, separate from direct
    # VK-to-HID-code matches; it is not a captured 0x83 schema.
    modifier_masks = {0xA2: 0x01, 0xA0: 0x02, 0xA4: 0x04, 0x5B: 0x08,
                      0xA3: 0x10, 0xA1: 0x20, 0xA5: 0x40, 0x5C: 0x80}
    modifiers = []
    for key in comparable:
        if key["virtualKey"] not in modifier_masks:
            continue
        position = args.offset + 4 * key["matrixIndex"]
        actual = image[position:position + 4]
        expected = bytes((0, modifier_masks[key["virtualKey"]], 0, 0))
        modifiers.append({**key, "flashOffset": position, "actual": actual.hex(" "),
                          "candidateExpected": expected.hex(" "),
                          "matchesCandidate": actual == expected})
    fn1 = fn1_values(args.profile)
    positions = {key["name"]: key["matrixIndex"] for key in profile_keys(args.profile)}
    fn_results = []
    for name, value in fn1.items():
        if name not in positions:
            continue
        position = args.offset + 0x400 + 4 * positions[name]
        actual = image[position:position + 4]
        expected = value.to_bytes(4, "big")
        fn_results.append({"name": name, "matrixIndex": positions[name],
                           "flashOffset": position, "actual": actual.hex(" "),
                           "expected": expected.hex(" "), "matches": actual == expected})
    print(json.dumps({"candidateOffset": args.offset, "imageBytes": len(image),
                      "profileNormalKeyCount": len(comparable),
                      "matchCount": sum(result["matches"] for result in results),
                      "mismatches": [result for result in results if not result["matches"]],
                      "examples": results[:5], "modifierBitmaskHypothesis": modifiers,
                      "fn1ProfileCount": len(fn_results),
                      "fn1MatchCount": sum(result["matches"] for result in fn_results),
                      "fn1Mismatches": [result for result in fn_results if not result["matches"]],
                      "fn1Examples": fn_results[:5]}, indent=2))


if __name__ == "__main__":
    main()
