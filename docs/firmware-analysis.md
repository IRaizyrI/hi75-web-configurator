# Preserved firmware image: offline analysis

This page records correlations found in the unmodified `sinowisp` application
read at `backup/dumps/20260919T085231Z/firmware.bin` (61,440 bytes, SHA-256
`31ee5b474b06b5bd26f32e15e379ce8c3251913b57dfebc3194a7c4dbdcc7ad0`).
It supplements [`protocol.md`](protocol.md), which remains the source of truth
for protocol claims. No commands were sent to the keyboard during this analysis.

## Reproducible byte correlations

The read-only script `tools/software-inspect/correlate_capture_flash.py` compares
extracted report data (after the eight-byte report header) with the preserved
image. Its output is `analysis/firmware-capture-correlation.json`.

| Evidence | Captured report data | Exact location in saved image |
| --- | --- | --- |
| Startup capture `003`, frame 10 | Six bytes `03 00 00 00 00 9B` | `0xB3E3` (only exact occurrence) |
| Lighting capture `004`, frame 54, `0x84` response | 128 bytes | `0xC600–0xC67F` (only exact occurrence) |
| Lighting capture `004`, frame 57, `0x0A` SET | 512 bytes | `0xC800–0xC9FF` (only exact occurrence) |

Frame 55's first 128 `0x04` data bytes have no exact image match. Against the
`0xC600` block, only data offsets 10 (`03→0B`) and 63 (`27→47`) differ. The
image was read before capture `004`, and the page was opened without an
intentional setting change. These facts do not establish why the app changed
the bytes, whether the device committed them, or which settings they encode.

The `0xC600` block ends in `5A A5` at offsets 126–127. The `0xC800` block
contains `5A A5` at offsets 506–507. The app checks for the first marker in
its `GetLED` path. A checksum algorithm and storage semantics are still unknown.

Run from the workspace root:

```powershell
& 'local-tools/pyghidra-venv/Scripts/python.exe' `
  'hi75-web/tools/software-inspect/correlate_capture_flash.py' `
  'hi75-web/captures/004_lighting_open/derived/control-transfers.json' `
  'hi75-web/backup/dumps/20260919T085231Z/firmware.bin' `
  --startup-json 'hi75-web/captures/003_idle_startup/derived/control-transfers.json'
```

## Keymap candidate regions

`0xB400` starts a 512-byte block containing four-byte entries at
`0xB400 + 4 × matrixIndex`. Comparing it with the official RGB `KB.ini`
`[KEY]` matrix indices and the app's extracted VK→HID lookup gives 73 exact
matches among 80 ordinary category-2 profile keys. For example, Esc at
matrix index 0 is `00 00 00 29` (HID `0x29`); F1 at index 12 is
`00 00 00 3A`. The seven mismatches are left/right modifiers and Win keys;
their bytes are bitmasks such as `00 02 00 00`, so treating them as ordinary
HID entries was the wrong comparison. All seven match the *candidate* standard
HID modifier-bit ordering applied to the profile's named keys (left Ctrl
`01`, left Shift `02`, left Alt `04`, left Win `08`, right Ctrl `10`, right
Shift `20`, right Alt `40` in the second byte). This is strong offline evidence
for those saved values, but a live `0x83` response has not confirmed the
on-wire keymap representation.

`0xB800` has 25 exact four-byte matches among 30 `[FN1]` profile entries
placed at their `[KEY]` matrix indices. The five mismatches are profile zero
values but nonzero saved bytes. `0xB400–0xB5FF` is byte-identical to
`0xCC00–0xCDFF`; the subsequent 512-byte blocks through `0xC3FF` are also
byte-identical to blocks 0x1800 bytes later. Why there are duplicate blocks
is unknown. It would be premature to label one bank active, a backup, or a
particular layer. See `analysis/firmware-keymap-correlation.json` for every
comparison and mismatch.

Run the read-only keymap comparison:

```powershell
& 'local-tools/pyghidra-venv/Scripts/python.exe' `
  'hi75-web/tools/software-inspect/compare_firmware_keymap.py' `
  'hi75-web/backup/dumps/20260919T085231Z/firmware.bin' `
  'LEOBOG ONE/Dev/kb/RGB/KB.ini' `
  'hi75-web/analysis/ghidra-oemdrv-635587cf/vk-to-hid.json'
```

These correlations strongly identify configuration-shaped bytes in the saved
flash image. They do **not** prove which `0x83` layer request returns which
block, whether live WebHID reads are safe, or whether a region is writable.
No configuration extraction or restore feature is enabled.

## 8051 disassembly status and limits

The image also contains exact copies of captured USB device/configuration
descriptors at `0x54E5`/`0x54F7` and two structurally valid HID report
descriptors immediately before them. See [`usb.md`](usb.md#hid-report-descriptors-recovered-from-the-saved-firmware-image)
and `analysis/firmware-usb-descriptors.json`. Interface 1's report ID 6
declares a 519-byte Feature body (520 bytes including ID), corroborating the
official app and Windows HID metadata without any new device request.

Ghidra 12.1.3 imported the raw image using `8051:BE:16:default` at
`CODE:0000`. With no raw-image entry metadata it initially found zero
functions. `tools/software-inspect/SeedFirmwareVectors.java` seeded standard
8051 vector addresses that contain an `LJMP`. The reset vector at `0x0000`
jumps to `0x93A0`; other observed jumps are `0x0003→0x9D49`,
`0x000B→0xAC89`, `0x0013→0xAC8F`, `0x001B→0xAC95`, and
`0x003B→0xA3F1`. Ghidra subsequently identified 124 functions in its
project copy. Exports are in `analysis/firmware-ghidra-seeded/` and
`analysis/firmware-ghidra-functions/`.

Decompiler warnings include unresolved 8051 constructors and flow into
addresses beyond the imported image. Some resulting switch statements are
clearly unreliable, so case labels matching `0x82` or `0x84` alone are **not**
evidence of a HID command dispatcher. The later raw-byte read-dispatcher
finding below does not rely on those decompiler switch labels; its upstream
SET_REPORT handling and persistence effects remain unresolved.

`MarkFirmwareDescriptors.java` imported the same raw image into a separate
Ghidra project (`Hi75FirmwareMarked`) and marked the four descriptor ranges
as data before vector seeding. The project still identified 124 functions and
still emitted p-code warnings in the `0x4F8A` function around `0x50xx`.
Separating the known descriptor bytes therefore did **not** resolve the
problematic control flow or expose a verified HID command handler. The
original and marked Ghidra projects are retained as analysis artifacts;
neither modifies the recovery image.

A later raw-byte review found a candidate low-level USB path in
`FUN_CODE_0200`: code near `0x0475–0x0494` uses internal RAM byte `0x77`
to index eight three-byte jumps at `0x0495–0x04AC`. A selector value of `6`
lands at `0x0505`. The same function handles a `0x09` state in external RAM
`0x0F40` and copies incoming data before this dispatch. This may be the
report-ID-6 setup path, but the meaning of byte `0x77` and the later
application-command dispatch are not fully verified. In particular, this
does **not** by itself establish that vendor commands `0x82` or `0x84` avoid
persistent writes. The more specific command-path evidence below supports a
single gated browser identity probe; configuration reads remain disabled.

## Candidate firmware read dispatcher

The file-only extractor
[`extract_read_dispatch.mjs`](../tools/software-inspect/extract_read_dispatch.mjs)
requires the exact preserved-image SHA-256 and records the selector and nine
three-byte jump-table entries from `0x4E1E–0x4E53` in
[`analysis/firmware-read-dispatch.json`](../analysis/firmware-read-dispatch.json)
(SHA-256 `377f0cbd620ffe008f9ad3892cfbbe6fa351e6837faa06927002227bbb1139b8`).
Manual 8051 instruction decoding of those bytes shows the selector adding
`0x7E` to a command byte before indexing the table, so bytes `0x82–0x8A`
map to the following branches. These are **saved-image code observations**;
only `0x82` and `0x84` have matching attached-unit GET responses.

| Command byte | Branch | Candidate read source selected by branch | Corroboration / limit |
| --- | --- | --- | --- |
| `0x82` | `0x4E54` | With additional argument `1`, pointer `0xB3E3`; otherwise `0xB3FC` | `0xB3E3` contains captured six-byte `Psd` response; branch also sets bit address `0x5A`, whose full effect is unresolved |
| `0x83` | `0x4E74` | Additional argument `0–3` selects `0xCC00`, `0xD000`, `0xD400`, or `0xD800`, plus `0x200 ×` chunk index | These are the image's four mirrored keymap candidate regions; no live `0x83` capture |
| `0x84` | `0x4ECC` | `0xC600 + 0x200 ×` chunk index | Captured 128-byte response matches image `0xC600–0xC67F` |
| `0x85` | `0x4EDD` | `0xDC00 + 0x200 ×` chunk index | No live response; app names this `GetMacro` |
| `0x86` | `0x4EED` | `0xCA00 + 0x200 ×` chunk index | No live response; app names this `GetGame` |
| `0x8A` | `0x4F51` | `0xC800 + 0x200 ×` chunk index | Captured `0x0A` write data matches image `0xC800–0xC9FF`; no live `0x8A` response |

Other table entries `0x87–0x89` are retained in the extraction JSON without
asserted semantics. The common path near `0x4F6B` copies the requested length
from two RAM bytes, schedules a control transfer, and returns. The visible
`0x82` branch sets bit address `0x5A`; raw-image references also test and
clear that bit at `0x3CC8–0x3CCB` and `0x64BF–0x64C4`. Those paths are not
fully resolved. The read dispatcher itself contains no obvious flash program
or erase sequence. This is narrower than a whole-device side-effect proof.

Further review of `FUN_CODE_0200` at `0x044B–0x0470` found that a command
byte equal to `0x08` or with high nibble `0x80` jumps past the block that
sets bit `0x3A`, prepares a pointer in external RAM `0x098E–0x098F`, and
calls `FUN_CODE_0056`. The subsequent eight-entry dispatch covers values
`0x03–0x0A`, not `0x82`. This is strong static evidence that the captured
`0x82` SET_REPORT request bypasses this separate state-changing path; the
exact downstream purpose of that skipped path is not fully established.
It is not proof that every firmware path is free of persistent effects. The
matching GET_REPORT branch still sets bit `0x5A`, and the official-app
capture has one vendor interrupt report per identity exchange; see
[`protocol.md`](protocol.md#offline-audit-of-read-shaped-transfers). On this
bounded evidence, the browser exposes only one exact `0x82` identity query
behind the descriptor-layout gate; no `0x84` or `0x83` browser query is
available yet.

Reproduce from `hi75-web`:

```powershell
node tools/software-inspect/extract_read_dispatch.mjs `
  backup/dumps/20260919T085231Z/firmware.bin `
  analysis/firmware-read-dispatch.json
```

## Firmware write path (SET_REPORT `0x03`–`0x0A`) — 2026-10-07

Decoded by hand with [`dis8051.py`](../tools/software-inspect/dis8051.py)
(`python tools/software-inspect/dis8051.py backup/dumps/20260919T085231Z/firmware.bin 0x0340 0x05e9`).
Static code observation; no device write was sent.

**Receive.** IRAM `0x77–0x7D` holds the 8-byte header after the report ID:
`0x77` command, `0x78` argument (→ XRAM `0x0389`), `0x7A` chunk count
(→ `0x02E2`), `0x7B` chunk index (→ `0x0D0F`), `0x7C–0x7D` length. Data bytes
are copied into XRAM `0x09BA` (up to 512 bytes). Command `0x08` instead copies
up to `0x17A` (378) bytes into XRAM `0x0152`, which matches the SignalRGB
streaming header `06 08 00 00 01 00 7A 01`.

**Dispatch** (jump table `0x0495`, index = command − 3):

| Cmd | Handler | Flash target | Notes |
| --- | --- | --- | --- |
| `0x03` | `0x04AD` | arg 0–3 → `0xCC00`/`0xD000`/`0xD400`/`0xD800` | chunk index not added: one 512-byte sector (128 keys) per layer |
| `0x04` | `0x04DF` → `0xABD3` | `0xC600` | also sets bit `0x62` (apply lighting) |
| `0x05` | `0x04E5` | `0xDC00 + 0x200 × chunk` | macros |
| `0x06` | `0x0505` | `0xCA00 + 0x200 × chunk` | "game" block; refills buffer bytes `0x17A–0x1FF` from current flash so the sector tail is preserved |
| `0x07`, `0x09` | `0x05E9` | none | ignored |
| `0x08` | `0x056E` | none (RAM only) | live RGB streaming; sets bits `0x52`/`0x53` |
| `0x0A` | `0x0584` | `0xC800 + 0x200 × chunk` | per-key RGB table; sets bits `0x51`, `0x21` |
| `0xAA` | `0x05A8` | none | stores cmd/arg at `0x08BC`, sets bit `0x3C` |

**Save.** Every flash-target command ends in `0xA252(addr, sector)`: interrupts
off, `0xAAEE` (unlock), `0xA62F` (erase the 512-byte sector), `0x0181` (program
512 bytes from XRAM `0x09BA`), `0xAA97` (lock), interrupts restored. So writes
are **persistent immediately** and always rewrite a whole 512-byte sector,
including any stale buffer bytes past the sent length (e.g. LED writes send 128
bytes but reprogram `0xC600–0xC7FF`). A driver should send full, read-back
sectors and avoid rapid repeated writes (flash wear).

**Defaults vs. user copy.** `0xB400`/`0xB800`/`0xBC00`/`0xC000` are
byte-identical to `0xCC00`/`0xD000`/`0xD400`/`0xD800` in the saved image. The
`0x03` path only writes the latter, so the `0xB400` banks are very likely the
factory-default keymap (probably what `0x11` ResetDevice restores) and the
`0xCC00` banks the live user keymap.

## Knob (rotary encoder) — 2026-10-07

Static reading with `dis8051.py`; not yet device-tested.

- **Turn** is decoded from port P0 at `0x7EEB` (quadrature state in XRAM
  `0x0F5E–0x0F60`). In normal mode (XRAM `0x0323` = 0) a step sets bits `0x2E`
  and `0x2F` (direction), and the main loop at `0x2594` sends the consumer usage
  **`0xE9` Vol+ / `0xEA` Vol−** directly. No keymap or config table is consulted,
  so **knob turn cannot be remapped on stock firmware**.
- In the alternate mode (`0x0323` ≠ 0, toggled at `0x81AE` by a knob-press
  combination) a step instead moves a 0–4 level in `0x0D14`, which is
  copied into lighting state, which suggests the knob adjusts brightness in that mode.
- **Press** (bit `0x2C`) sends hard-coded **`0xE2` Mute** at `0x2FE8` in normal
  mode, unless bit `0x4D` is set (from a flag byte at XRAM `0x0319`), in which
  case the built-in action is skipped. The official app sets LED block byte
  `0x1A` to the profile's `WheelMode` (6) whenever the knob key (keymap matrix
  84, stock word `07 00 00 1D`) differs from its default. That LED flag is
  the likely source of bit `0x4D`, and the matrix-84 word the custom action.
