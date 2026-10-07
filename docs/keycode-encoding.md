# Key and macro encoding (static decode)

Source: Ghidra decompilation of `OemDrv.exe` (`FUN_00490260` key encoder,
`FUN_00490D10` layer/macro builder, `FUN_00490940` macro record serializer),
exports in `analysis/ghidra-oemdrv-635587cf/followup-keycodec`,
`followup-serializers` and `followup-codecs`. Cross-checked against the saved
firmware image (`backup/dumps/20260919T085231Z/firmware.bin`) at `0xB400`
(base layer) and `0xB800` (Fn1 layer), and against `Dev/kb/RGB/KB.ini`.

**Confidence:** byte layouts are *observed* in app code and consistent with
the saved image. Function meanings marked *hypothesis* come from KB.ini key
positions and common LEOBOG Fn layouts, not from a device experiment. No
`0x83` read or `0x03`/`0x05` write has been captured yet.

## Layer buffer (`0x83` read / `0x03` write)

- Four layers. Each layer is `matrixLength × 4` bytes (`matrixLength` comes
  from the profile, at most `0x90` editor keys per layer).
- The word for a key is at `matrixIndex × 4` (matrix index = last field of a
  `[KEY]` line in KB.ini, e.g. Esc `K1=…,0`, F1 `…,12`).
- A profile flag can force the last word of every layer to bytes
  `00 00 5A A5`.
- Unassigned positions are `00 00 00 00`.

## Key word (4 bytes, as stored on the wire and in flash)

`b0` is the type. The rest depends on the type.

| b0 | Layout `b0 b1 b2 b3` | Meaning | Evidence |
| --- | --- | --- | --- |
| `00` | `00 mods k2 k1` | Keyboard key: `b1` = HID modifier bits (`01` LCtrl, `02` LShift, `04` LAlt, `08` LGui, `10`–`80` right-hand), `b3` = HID usage, `b2` = optional second usage | 73/80 base keys match; modifier keys stored as `00 mm 00 00`; Fn F3 `00 04 00 2B` = Alt+Tab |
| `01` | `01 kind val 00…` | Mouse: `0x10101` etc. buttons, `0x32ff0701`/`0x32ff0601` wheel | App encoder only |
| `02` | `02 00 hi lo` | Consumer usage, big-endian in `b2..b3` (e.g. `02 00 00 E9` Vol+, `02 00 00 CD` Play/Pause, `02 00 01 83` Media) | Fn1 layer F7–F12 match |
| `03` | `03 mode count idx` | Macro: `idx` = 0-based macro buffer index; `mode` `01` = repeat `count` times, `02`/`04` = two other playback modes (from app option 1/2) | App encoder + layer builder |
| `05` | `05 05 00 n-1`, `05 01/02/04 00 00` | Layer/profile switching functions (category 8 `0xA6`, `0xA8`–`0xAA`) | App encoder only; *hypothesis* on meaning |
| `07` | `07 00 00 xx` | Keyboard-function keys. Fn layer: Esc `04`, LWin `01`, Q/W/E/R `19`/`18`/`1A`/`1B`, Backspace `1C`, knob press `1D` | Saved Fn1 layer matches KB.ini; *hypothesis*: `01` Win lock, `04` reset, `18`–`1B` mode/OS presets |
| `08` | `08 grp dir 00` | Lighting control: `08 03 01/02` brightness up/down (Up/Down, F6/F5), `08 04 01/02` speed up/down (Right/Left), `08 02 00` next effect (Tab), `08 00 00` LED on/off (`\`) | Saved Fn1 layer; meanings *hypothesis* |
| `0D` | `0D 00 00 00` / `0D 01 00 00` | Fn key / Fn2 key (app VK `0xFA`/`0xFB`) | Base layer has `0D 00 00 00` at one position |
| `0E`, `10` | `0E 00 00 00`, `10 00 00 02/04` | Other functions (category 8 `0xAB`, category 6 `0x64`/`0x65`) | App encoder only |

The app's category-9 "raw" entries in KB.ini (e.g. `0x09,0x01,0x08030100`)
are written in byte order `b0 b1 b2 b3`, which is the order stored in flash.

## Macro buffer (`0x85` read / `0x05` write)

```
header:  N × { u16 LE offset, u16 LE length }   offset counts from buffer start (header included)
record:  u8 nameBytes, UTF-16LE name (≤ 30 chars), then actions × 4 bytes
action:  b0 = 0x80 if release | kind << 4 | delay[19:16]
         b1 = delay[15:8], b2 = delay[7:0]      (the firmware sign-extends b1: keep delay < 0x8000)
         b3 = code
```

Corrected 2026-10-07 from the firmware player (`0x4A2B`–`0x4CFF`, kind
dispatch at `0x4C83`) after a first live test played nothing. The app's
serializer agrees once its switch fall-through is read correctly.

| kind | Firmware handler | `b3` code |
| --- | --- | --- |
| 0 | `0x943A` | Keyboard HID usage |
| 1 | `0xA4F2` | Modifier `E0`–`E7`; low nibble selects the modifier bit |
| 2 | `0xA9C4` | Mouse button bit: `01` L, `02` R, `04` M, `08`/`10` side |
| 3 / 4 | `0x4CAB` / `0x4CC8` | Mouse X / Y move, signed byte |
| 5 / 6 | `0x4CE6` / `0x4CF2` | Wheel / horizontal wheel, signed byte |

Macro key word `03 mode count idx`: the firmware (`0x9B1F`) accepts mode 1
(repeat `count` times on press), 2 and 4; any other mode is ignored.

Macros are numbered in the order keys referencing them are found while
walking layers 0–3. The app stops when it exceeds the device's macro count.

## Still open

- Exact `matrixLength` for this unit and whether the `5A A5` trailer applies.
- Live `0x83`/`0x85` response layout (does it match flash at `0xCC00`/`0xDC00`?).
- Meanings of types `01`, `05`, `07`, `0E`, `10`, and macro modes `02`/`04`.
- Whether the firmware stores writes in flash immediately (persistence).

## Live macro check — 2026-10-07

A macro recorded in LEOBOG ONE ("test": T↓63 E↓78 T↑31 E↑125 S↓94 T↓31 S↑94
T↑0 ms in the app UI) was stored as `00 00 3F 17`, `00 00 4E 08`, `80 00 1F 17`…
i.e. exactly the corrected layout above, with delays in **milliseconds** and
each action's delay taken from the app's per-row value. The key word was
`03 01 01 00` on `/` (matrix 64), identical to what this project writes.
Macros play from `/` whether written by the app or by the web page. Neither
tool can make **PgDn (matrix 88)** play a macro; that is a firmware limitation
for that key, not an encoding problem.
