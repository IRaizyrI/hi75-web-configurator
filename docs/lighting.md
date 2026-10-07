# Lighting block and palette

Sources: app `FUN_00491430` (LED converter), KB.ini `LedOpt1..19`, live read
`backup/config/hi75-backup-2026-10-07T09-52-28.785Z.json`.

## LED block (`0x84` read / `0x04` write, 128 bytes)

| Offset | Meaning | Confidence |
| --- | --- | --- |
| 10 | Current effect, hardware code (`LedOpt` column 1: 1–18, 21) | Live read 2 matches the effect whose brightness entry changed in captures 008/009 |
| 26 (`0x1A`) | Custom knob-press flag (0, or `WheelMode` 6) | Verified live (knob press remap) |
| 56–57 | `FF FF` | App writes constant |
| 58 + 2i | Brightness 0–4 of effect entry i (entry order = `LedOpt` order) | Verified for entry 1 (offset 60) |
| 59 + 2i | High nibble speed 0–4, low nibble colour index 0–7 | App code; live values `0x47` = speed 4, colour 7 |
| 126–127 | `5A A5` marker | Observed in every read |

Other bytes (0–9, 11–25, 27–55, 96–125) are preserved verbatim.

Colour index: 0–6 select a palette slot (stock red, green, blue, yellow,
magenta, cyan, white, matching the app's COLORREF mapping), 7 = random.

## Palette (`0x8A` read / `0x0A` write, 512 bytes)

Twenty 21-byte groups; group 0 is zero, group i+1 holds seven RGB triples for
effect entry i (channel order R,G,B per `RGBIndex=0,1,2`). Bytes 420–505 are
zero, 506–507 `5A A5`. The live read differs from the dump only in group 2
slot 0, i.e. the current effect's selected colour, which supports this layout.

## Effects

`LedOpt` rows give: hardware code, an app-internal index, and flags for speed,
brightness, direction, random colour and colour. The official app's menu
(screenshot from the user) lists hardware codes 1–14 in order as Fixed_on,
Respire, Rainbow, Flash_away, Raindrops, Rainbow_wheel, Ripples_shining,
Stars_twinkle, Retro_snake, Neon_stream, Reaction, Sine_wave, Rotating windmill,
Colorful waterfall, then 17 Blossoming, 18 Self-define, 21 OFF. Codes 15 and 16
are not offered by the app. The user confirmed code 17 is Blossoming.

## Self-define per-key colours (`0x86` read / `0x06` write) — 2026-10-07

Found by painting Esc red and F1 green in LEOBOG ONE (WASD and arrows were
already white) and diffing a read-only dump (`tools/hid-inspect/Read-Hi75Config.ps1`):

- The block at flash `0xCA00` (the app's "game" commands) holds three planes of
  126 bytes, **R at 0, G at 126, B at 252**, each indexed by keymap matrix
  index. Esc (matrix 0) appeared only in R, F1 (matrix 12) only in G, WASD
  (9, 14, 15, 21) and arrows (77, 82, 83, 89) in all three.
- Bytes 378–511 are kept from flash by the firmware's `0x06` handler.
- Selecting Self-define wrote LED byte 10 = **21** and LED byte 9 = 1. So
  hardware 21 is Self-define, not Off; hardware 18 is Off (confirmed live by the user, as is the Self-define painter round trip).

## Effect names corrected — 2026-10-07

Live testing showed hardware 9 displays nothing and the names after it were
shifted by one. Corrected mapping: 1 Fixed on, 2 Respire, 3 Rainbow, 4 Flash
away, 5 Raindrops, 6 Rainbow wheel, 7 Ripples shining, 8 Stars twinkle,
10 Retro snake, 11 Neon stream, 12 Reaction, 13 Sine wave, 14 Rotating
windmill, 15 Colorful waterfall, 17 Blossoming, 18 Off, 21 Self-define.
Hardware 9 and 16 are hidden in the configurator. 15 Colorful waterfall is
inferred from the shift (it has no colour option, like the app's waterfall).

Second correction: hardware 14 also shows nothing, 15 is Rotating windmill
(confirmed), 16 Colorful waterfall and 17 Blossoming (confirmed by the user).
Hidden: 9 and 14.
