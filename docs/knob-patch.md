# Knob rotation patch (v1)

Stock firmware sends consumer Vol+/Vol− straight from the encoder handler, so
knob rotation cannot be remapped through the configuration protocol. This
patch turns each knob step into a press and release of an unused matrix
position, so rotation follows the keymaps like any other key.

| Direction | Matrix | Stock firmware sent |
| --- | --- | --- |
| Clockwise (bit `0x2F` set) | 75 (column 12, row 3) | Vol+ (`0xE9`) |
| Counter-clockwise | 76 (column 12, row 4) | Vol− (`0xEA`) |

Built by [`patch_knob.py`](../tools/software-inspect/patch_knob.py) from the
stock application image (SHA-256 `31ee5b47…7ad0`); it refuses any other input.
Output: `backup/patched/firmware-knob-v1.bin`, 101 bytes changed.

## Changes

- `0x259F` (knob step, inside the scan timer ISR at `0x1DED`): load matrix 75/76
  by direction and `LCALL 0xACC0` instead of writing the consumer report.
- `0x25C9` (after the existing ~10-tick hold): `LCALL 0xACE2` to release it.
- `0x7F32`, `0x7F68` (encoder decoder): `JZ` → `SJMP`, so steps always take the
  key path even when the lighting-knob flag (`0x0323`, LED byte 26) is set.
- `0xACC0`/`0xACE2` (zero-filled gap after code): press/release routines that
  replay the matrix scan's own sequence (`0x08C0`, `0x02E0`, bit `0x42`,
  `0xA96B`, `0x0F73` press / `0x6040` release). The pressed matrix is kept in
  XRAM `0x0FF0` (above every address the firmware uses; zeroed at boot).

## Emulator verification

[`emu8051.py`](../tools/software-inspect/emu8051.py) boots the image into its
main loop ([`knob_harness.py`](../tools/software-inspect/knob_harness.py)), then
runs the scan ISR body with a knob step pending:

- Stock: clockwise writes consumer `E9` to `0x09B8`.
- Patched, matrix 75/76 holding ordinary keys: key report `0x08B0` gets the
  mapped usage, then is released after the hold.
- Patched, matrix 75/76 holding `02 00 00 E9` / `02 00 00 EA`: the consumer
  report gets `E9` / `EA`, i.e. stock behaviour is reproducible by mapping.

Not covered by the emulator: USB transfer timing, the real encoder ISR and
interaction with macros running at the same time.

## After flashing

Matrix 75/76 are empty on the current keyboard (LEOBOG ONE zeroes them), so
the knob does nothing until mapped. Map them on the configurator's Knob page
(Vol+/Vol− restores stock behaviour). Flashing the application region also
rewrites the configuration sectors from the image, so take a configurator
backup first and restore it afterwards.

## Flash log — 2026-10-07

1. Recovery test: `sinowisp write -d leobog-hi75 --format bin` with the stock
   `firmware.bin` (SHA-256 `31ee5b47…7ad0`): erase, write, read-back verify,
   reboot, exit 0. The user confirmed typing and lighting, and restored their
   configurator backup.
2. Patched `firmware-knob-v1.bin` (SHA-256 `78af3742…2377`) flashed the same
   way: verify OK, exit 0, keyboard answers the `0x82` identity query.
3. User restored their backup, mapped both directions on the Knob page and
   confirmed knob rotation works on the device.

## Detection

The `0x85` macro read computes its flash address as `0xDC00 + 0x200 × chunk` in
16 bits, so chunk 36 returns code `0x2400–0x25FF` and chunk 104 returns
`0xAC00–0xADFF`. The configurator compares the knob-step site (`0x259F`) and the
added routines (`0xACC0`) with the stock and patched bytes on connect
([`knob-patch.js`](../src/protocol/knob-patch.js)), using reads only. Verified on
the device: chunk 36 offset `0x19F` returns the patched `74 4c 30 2f 02 …`.
The same wrap would allow a read-only dump of the whole application image over
WebHID.

## v2 — 2026-10-07

v1 left the gate at `0x258E–0x2593` in place: when XRAM `0x0323` (LED byte 26,
set to 6 whenever the knob press is customised) is non-zero, the ISR skips knob
step handling entirely. The user hit this after customising the press. v2 also
replaces `JNZ 0x25D1` at `0x2592` with two `NOP`s (103 bytes changed in total,
SHA-256 `43976a7d…3c88`). The emulator reproduces the failure on v1 with
`0x0323 = 6` and shows v2 pressing matrix 75 as expected.
Flashed 2026-10-07 after a read-only pre-flash backup
(`backup/config/hi75-prefl-20261007T150945.json`): verify OK, exit 0; reading
code `0x2592` over WebHID's read path returns `00 00`.
