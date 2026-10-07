# LEOBOG ONE application disassembly

This is a static analysis of the user-supplied `LEOBOG ONE/OemDrv.exe`, not a
transcript of executed code. The executable's SHA-256 is
`635587cf6334346ab9932479d309cfe5f395c45d77c698b0143d28bf5b661ee0`.
It is a 32-bit native PE. The initial instruction listing and cross-reference
index are in `analysis/oemdrv-635587cf/`, produced by
`tools/software-inspect/inspect_pe.py` with pefile 2024.8.26 and Capstone 5.0.7.
The initial listing is a linear sweep, so an address or apparent function
boundary is a lead until checked by control-flow-aware disassembly.

Ghidra 12.1.3 has now analyzed the same PE as `x86:LE:32:default:windows`.
Its decompiled functions and direct references are in
`analysis/ghidra-oemdrv-635587cf/hid-paths.txt` and the `followup-*` exports.
No PDB was available. Ghidra's inferred variable types, function signatures,
and names beginning `FUN_` require checking against instructions before use.
The class-based export was used because this Ghidra release's source-script
loader failed on this host; the saved project and decompiler output succeeded.

## Confirmed static observations

- The import table includes `HidD_SetFeature`, `HidD_GetFeature`, `ReadFile`,
  `WriteFile`, and HID descriptor APIs. The import thunks for SetFeature and
  GetFeature are at `0x5BD73C` and `0x5BD742` in this image base.
- Numerous direct calls to these thunks appear around `0x48B180` and
  `0x48EF20`–`0x494AD1`. These areas appear to contain multiple transport
  variants. A direct call is static evidence of a path; it does not establish
  that a particular keyboard selects that path.
- At `0x48FF90`–`0x4900EE`, a routine builds a feature buffer with second byte
  `0x82` at `0x490023`, sends it using `HidD_SetFeature` at `0x49005F`, then
  calls `HidD_GetFeature` at `0x490094`; both calls pass `0x208` (520) as the
  Windows buffer length. The routine copies six response bytes at `0x4900B2`–
  `0x4900C4`. The startup capture contains repeated `06 82 ... 06 00` requests
  and six trailing bytes `03 00 00 00 00 9B` in each response. Its direct
  caller at `0x48ECBE` compares all six returned bytes with a six-byte value
  from a candidate device record (`0x48ECD5`–`0x48ECE4`); on mismatch, it
  closes that handle at `0x48EDEE` and continues scanning. The profile loader
  also reads a six-byte `Psd` value. This establishes a code path for six-byte
  matching and agrees with the captured RGB value. The exact record layout,
  all other fingerprint conditions, and any side effects still need tracing.
- At `0x48F696`–`0x48F849`, another routine places `0x84` in the second buffer
  byte at `0x48F76D`, then calls `HidD_SetFeature` at `0x48F79F` and
  `HidD_GetFeature` at `0x48F7D4`, again passing `0x208`. The lighting-page
  capture contains a matching `06 84` SET/GET pair. The following two SET
  requests on page open match the `SetLED` (`0x04`) and `SetLedRgbTab` (`0x0A`)
  builders below; their setting effects remain unverified.
- The profile loader reads literal `Fw` and `Psd` entries through Windows INI
  APIs near `0x410C25` and `0x410C46`. Other profile entries such as `Light`,
  `Speed`, `WheelMode`, and `KnobIndex` also have string references. The
  connected app session selected `Hi75 RGB`, whose profile `Psd` bytes match
  the startup response suffix. The comparing branch is mapped below.

## Hi75-related path recovered with Ghidra

The connected app session executed the `0x82` and `0x84` builders from this
family, as corroborated by captures `003` and `004`. The app calls this family
`CDevG5KB` in its own log strings. Other functions listed here are static paths
of that same class; they have not all been observed on this unit.

- Profile `Fw=24` (`0x18`) selects an enumerator branch that checks matching
  VID/PID, usage page `0xFF00`, usage `1`, and a `0x208` (520-byte) feature
  buffer in `FUN_0048eb70`. This `Fw` value comes from `KB.ini`; the code does
  not prove it is the device's firmware revision. A second branch exists for
  profile `Fw=0x1A` and different usage metadata. The enumerator calls the
  `0x82` six-byte query when the profile candidate has nonzero `Psd` bytes,
  compares all six bytes, logs `Psd unmatch` on failure, closes that handle,
  and continues searching. VID/PID alone cannot pass this branch.
- `FUN_0048ef20` builds 520-byte feature reports with an eight-byte outer
  header followed by up to 512 data bytes. In the `Fw=0x18` branch, the header
  bytes are report ID, command, argument, zero, total chunk count, chunk index,
  and a little-endian chunk length. The code chooses `HidD_SetFeature` for
  operation `1` and SET then GET for operation `2`. The transfer length passed
  to both Windows APIs is always 520, even when fewer bytes carry useful data.
  This is a static description of the app's buffer construction, not permission
  to replay it.
- `FUN_00491840`, logged as `CDevG5KB::ApplySetting`, separates LED, matrix,
  macro, and per-key color updates by dirty flags. For LED settings it obtains
  a 128-byte block through the class's `GetLED` method, changes data in memory,
  then uses `SetLED`; it may also send an RGB table. For key assignments it
  calls `FUN_00490d10` to serialize data, then sends each dirty layer through
  vtable slot `+0x58` and macros through slot `+0x60`. This confirms that
  analyzing the serializers can recover keymap layout without manually
  remapping every key.
- `FUN_00490d10` iterates four layers and up to `0x90` candidate key entries
  per layer. It places 32-bit encoded values at matrix indices and handles
  macro references separately. The layer write sends `matrix length × 4`
  bytes. The encoding routine is reached through vtable slot `+0x94` at
  `0x490260`; its semantics still need tracing before individual assignments
  can be decoded.
- `FUN_00490260` is the matrix serializer's key-record encoder. It reads an
  editor record whose first 32-bit word stores a high-byte category and a
  low-24-bit function ID. Its switch covers ordinary key functions,
  multimedia/system functions, modifier combinations, macros, and several
  special functions. It returns a 32-bit hardware value, or `0xFFFFFFFF` for
  unsupported cases. This recovers much of the app's translation logic without
  manually remapping every key, but the helper calls and inverse decoding still
  need analysis before a complete, round-trippable keymap schema can be claimed.
- `FUN_004786A0` looks up Windows virtual-key codes in a fixed table of 115
  `(HID code, virtual-key code)` byte pairs. A reproducible extraction script
  and the resulting `analysis/ghidra-oemdrv-635587cf/vk-to-hid.json` preserve
  the exact table from the analyzed PE. The table is injective in this app
  version; for example, VK `0x41` maps to HID `0x04` and VK `0x1B` to HID
  `0x29`. This supports app-code interpretation but does not replace a
  captured matrix read.
- `FUN_0048F1A0` builds a `0x83` matrix read with layer in the third report
  byte; it chunks a caller-supplied byte count into pieces of at most 512.
  The app copies response data from report offset 8. `FUN_0048F400` and
  `FUN_0048FCF0` build analogous `0x85` macro and `0x8A` RGB-table reads.
  These paths have not been captured on the connected Hi75.
- The `FUN_0048F1A0` pointer is in the `CDevG5KB` vtable at `0x614FD0`,
  corresponding to a candidate `+0x5C` method slot relative to base
  `0x614F74`. A whole-program scan of Ghidra's analyzed indirect `CALL`
  instructions with scalar displacement `0x5C` or `0x64` found 81 candidates,
  all at `0x4A20E5` or later in framework/library code; it found no such
  callsite in the app-specific `0x48`/`0x49` region. This is bounded negative
  static evidence, not a proof that the read routine is unreachable through
  every possible indirect path. Capture `010` independently observed no HID
  report when the key editor was opened without applying changes. Therefore
  the app's mere presence of a `0x83` builder must not be treated as a live
  read demonstration.
- The macro serializer `FUN_00490940` writes a UTF-16LE name and packed
  four-byte actions. `FUN_00490D10` adds a four-byte-per-macro offset/length
  table ahead of the records and links keymap references to assigned macro
  IDs. Exact bytes and device limits still require a corresponding capture.
- The LED branch of `FUN_00491840` reads 128 bytes using `GetLED`, checks for
  trailing bytes `5A A5`, calls one of two profile-dependent conversion
  routines (`FUN_00491250` or `FUN_00491430`), and sends the block through
  `SetLED`. A separate path builds an RGB table and calls `SetLedRgbTab`. In
  capture `004`, the read LED data and immediately following write data differ
  at two byte positions despite no intentional setting change. The exact
  offsets and raw evidence are in `docs/protocol.md`; neither byte has a
  verified setting meaning.
- The RGB-table builder in `FUN_00491840` places nineteen groups of seven
  three-byte color values after an initial 21-byte zero group, forming a
  420-byte working table. A profile branch pads this to a 512-byte write with
  a `5A A5` marker at data offsets 506–507. The captured `0x0A` data follows
  that shape. Group identities and color-setting effects are not verified.

| Second report byte | Builder / routine | App evidence | Device evidence |
| --- | --- | --- | --- |
| `0x82` | `0x48FF90` | Six-byte candidate identity query | Captured at startup (`003`) |
| `0x83` | `0x48F1A0` | Matrix read candidate, paired with matrix write slot | No capture yet |
| `0x03` | `0x48F160` → `0x48EF20` | Matrix write through `ApplySetting` slot `+0x58` | No capture yet |
| `0x84` | `0x48F650` | `GetLED` log string; reads requested data in 512-byte chunks | Captured on lighting-page open (`004`) |
| `0x04` | `0x48F600` → `0x48EF20` | `SetLED` log string | Captured on lighting-page open (`004`) |
| `0x85` / `0x05` | `0x48F400` / `0x48F3B0` | `GetMacro` / `SetMacro` log strings | No capture yet |
| `0x86` / `0x06` | `0x48F8B0` / `0x48F850` | `GetGame` / `SetGame` log strings | No capture yet |
| `0x8A` / `0x0A` | `0x48FCF0` / `0x48FCA0` | `GetLedRgbTab` / `SetLedRgbTab` log strings | `0x0A` captured on lighting-page open (`004`) |
| `0x11` | `0x48FEF0` | `ResetDevice` log string | No capture; do not invoke |
| `0x88` | `0x48FAC0` | `GetRealData` log string | No capture; purpose unknown |
| `0x08` / `0x0E` | `0x490120` / `0x490150` | Generic write wrappers; payload length supplied by caller | No capture; `0x08` has an external RGB-streaming lead, purpose unverified here |
| `0x0B` / `0x0C` / `0x0D` | `0x48FF40` / `0x492490` / `0x492830` | Screen parameter / page / GIF parameter code paths | No capture; applicability to Hi75 RGB unknown |

The executable also contains a separate report-ID-9 transport with an additive
checksum. That path has not been tied to the attached Hi75, so its checksum
must not be applied to the observed report-ID-6 packets.

## Next trace targets

1. Determine whether the `0x83` matrix reader is reachable through any
   supported app action. Opening the key editor did not call it. If no app
   trigger exists, firmware analysis or another verified read source is needed
   before testing the app-derived four-byte encoding against a live response.
2. Trace profile dispatch and the LED block conversion in `FUN_00491250` / `FUN_00491430` and the
   RGB-table construction, preserving every unknown byte.
3. Map the remaining macro, knob, and persistence paths through class callers.
4. Compare recovered code paths with raw captures. Treat any app-only branch
   as unverified on this Hi75 until the dispatch conditions are known.

`docs/protocol.md` remains the source of truth for actual on-device protocol
observations and confidence levels. No browser request should be sent merely
because a code path exists in the executable.
