# Official application: initial static inspection

Date: 2026-09-19. Source supplied locally by the user at `../../LEOBOG ONE/`.
Inspection was file-only; no application was launched, configuration changed,
or firmware disassembled. This is an initial triage, not recovered protocol code.

## Observations

- `OemDrv.exe` is a 2,656,768-byte PE with machine `0x014C` (x86), optional-header
  magic `0x010B`, and zero CLR-directory RVA. These headers indicate a native
  Windows executable rather than a normal managed .NET assembly.
- Its version resource reports file/product version `1, 0, 0, 0`; do not infer
  the public release version from that generic value. `Cfg.ini` contains
  `Title=LEOBOG ONE`, `Ver=0x200`, and `Appdir=BYCOMBO4`.
- Printable executable strings include `HidD_SetFeature`, `HidD_GetFeature`,
  HID capability/enumeration APIs, `ReadFile`, and `WriteFile`. This triage has
  not resolved their import entries, call sites, or which transport each model
  uses. String presence alone proves neither a call nor its arguments.
- An embedded PDB path is `d:\OEM\Beiying\Src\UI4\Debug\OemDrv.pdb`.
  This is a build-path clue, not evidence that debug symbols are available.
- The supplied directory has model configuration files and UI resources. It is
  useful as an application-analysis input; the directory listing does not make
  it equivalent to a keyboard firmware dump.

## Hi75 profiles

Values below are literal application-file observations. Their protocol meanings
and relevance to the connected unit are not established.

| Field | `Dev/kb/2/KB.ini` | `Dev/kb/RGB/KB.ini` |
| --- | --- | --- |
| Name | `Hi75 Keyboard` | `Hi75 RGB Keyboard` |
| VID / PID | `0x258a / 0x010C` | `0x258a / 0x010C` |
| Fw | `24` | `24` |
| Psd | `3,0,0,0,0,A2` | `3,0,0,0,0,9B` |
| LayerNum | `4` | `4` |
| WheelMode | `;WheelMode=6` (commented) | `6` |
| KnobIndex | `;KnobIndex=81` (commented) | `81` |

The `RGB` profile also contains `[KEY]` and `[FN1]` sections and lighting option
tables. These are leads for tracing UI mappings. They do not prove four hardware
layers, knob index encoding, firmware version 24, or any request/response bytes.
`Psd` is a candidate for investigating model selection; its meaning is unknown.
Other models in the supplied folder also specify `258A:010C`.

## Source fingerprints (SHA-256)

| File beneath `LEOBOG ONE/` | SHA-256 |
| --- | --- |
| `OemDrv.exe` | `635587cf6334346ab9932479d309cfe5f395c45d77c698b0143d28bf5b661ee0` |
| `Dev/kb/2/KB.ini` | `46765cdca3c5a41f63f4d3eaae28d80c53c6da657ca9372d1b8f9350aa7a6631` |
| `Dev/kb/RGB/KB.ini` | `69390fede3fcdd8bdf74a63810d20f689606cf2de5817520e9d37cad867a46df` |
| `Cfg.ini` | `3da376a8445dcd9aa6df7f2a23d269d5376793c17e8aaaa8fc7b1f28c8c45db8` |

## Recommended bounded next phase

1. Trace model-profile selection and HID transport call sites in the application.
   Identify candidate device-info/configuration-read requests and response parsing.
2. Collect official-app startup/idle traffic to identify the actually executed
   branch on the connected unit. Launching the app may itself send writes; record
   initialization rather than presuming it is read-only.
3. Trace one lighting control through packet construction, then validate with
   one-setting brightness captures and a reversal. Automate comparisons.
4. Expand to keymaps/layers, knob, and macros in separate phases. Keep unknown
   fields intact; do not replay candidate commands just because code suggests them.

Application analysis can expose serializers and branches more efficiently than
exhaustively trying UI combinations. Captures establish actual requests,
responses, sequencing, and device behavior. Neither alone guarantees complete
protocol coverage: the app may omit firmware features, and captures cover only
exercised paths. Firmware disassembly remains a fallback.

USBPcap captures Windows USB requests, not a literal physical bus trace; retain
transfer framing when comparing HID payloads. See the
[upstream capture limitations](https://desowin.org/usbpcap/capture_limitations.html)
and [capture procedure](https://desowin.org/usbpcap/tour.html).
