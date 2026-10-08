# Hi75 Web Configurator

An open-source, browser-based configurator for the **LEOBOG × EPOMAKER Hi75**
(original wired model) running its **stock firmware**. It replaces the
Windows-only LEOBOG ONE app: no install, no account, nothing leaves your
computer. It talks to the keyboard directly from Chrome or Edge using WebHID.

**Open it:** <https://iraizyri.github.io/hi75-web-configurator/>

> Unofficial project, not affiliated with LEOBOG or EPOMAKER. Settings are
> written to the keyboard's flash; use at your own risk and download a backup
> before big changes.

## What it can do

| Page | Features |
| --- | --- |
| **Remap** | Change any key on the base layer and the Fn layer: letters, modifiers, shortcuts, media keys, lighting controls, Fn, Win lock, macros. Empty Fn-layer keys fall through to the base key. |
| **Lighting** | All stock effects with brightness, speed and colour; edit each effect's 7-colour palette; paint individual keys for the **Self-define** effect. |
| **Macros** | Record key sequences in the browser, edit per-step delays, name and save up to 2 KB of macros, assign them to keys. |
| **Knob** | Remap the knob press. With the optional [knob patch](#optional-knob-rotation-patch), remap clockwise and counter-clockwise rotation too. |
| **Backup & Restore** | Download the whole configuration as JSON and restore it later. Restore only rewrites what differs and verifies each block. |

Every change is saved to the keyboard immediately and checked by reading it
back. Settings persist across unplugging. A **demo mode** lets you explore the
interface without a keyboard.

## Requirements

- A **LEOBOG Hi75 (wired, USB `258A:010C`)** on stock firmware. Other SinoWealth
  boards that share this VID/PID are rejected unless their HID layout matches.
- **Chrome, Edge or another Chromium browser** on desktop (WebHID support).
  Firefox and Safari don't support WebHID.
- **LEOBOG ONE closed**, because it holds the keyboard's configuration interface.
- Linux only: a udev rule giving your user access to the hidraw device, e.g.
  `KERNEL=="hidraw*", ATTRS{idVendor}=="258a", ATTRS{idProduct}=="010c", MODE="0660", TAG+="uaccess"`.

## Getting started

1. Open the [configurator](https://iraizyri.github.io/hi75-web-configurator/).
2. Click **Connect keyboard** and pick the Hi75 in the browser prompt.
3. Go to **Backup & Restore → Download backup** and keep the file.
4. Change things. Each click is applied and verified straight away.

The browser remembers permission, so next time the keyboard connects
automatically when the page opens.

### Run it locally

No build step and no dependencies beyond [Node.js](https://nodejs.org/) 18+:

```bash
git clone https://github.com/IRaizyrI/hi75-web-configurator.git
cd hi75-web-configurator
npm start          # http://localhost:8787
npm test           # offline tests
```

`localhost` counts as a secure context, so WebHID works there too. The page is
plain HTML and ES modules, so any static file server works as well.

## Known limitations

- **PgDn can't play macros.** The firmware ignores macros on that key (also in LEOBOG ONE).
- **Knob rotation is fixed to volume** on stock firmware; see the patch below.
- Hardware effects 9 and 14 do nothing and are hidden.
- The Mac-mode keymap and the "game" lighting table aren't editable.
- Saving from LEOBOG ONE afterwards may overwrite or clear settings made here
  (notably the knob-rotation slots). Re-apply them in the configurator.

## Optional: knob rotation patch

Stock firmware sends Volume Up/Down directly from the encoder. A small firmware
patch (103 bytes, bootloader untouched) turns each knob step into a key press
of two spare keymap slots, so rotation becomes remappable on the **Knob** page.
The configurator detects whether the patch is installed.

This requires flashing firmware with [sinowisp](https://github.com/carlossless/sinowisp)
and is **not** needed for anything else. Firmware images are not distributed in
this repo: you build the patch from your own dump. Full procedure, recovery steps
and emulator verification: [`docs/knob-patch.md`](docs/knob-patch.md).

## How it works

The Hi75 exposes a vendor HID collection (usage page `0xFF00`) with a 520-byte
feature report (ID 6). Commands `0x8x` read and `0x0x` write 512-byte flash
sectors for keymap layers, lighting, palette, per-key colours and macros. The
protocol was reverse-engineered from the official app, the firmware image and
USB captures, then verified on hardware.

| Document | Contents |
| --- | --- |
| [`docs/protocol.md`](docs/protocol.md) | Transport, commands and the evidence log |
| [`docs/keycode-encoding.md`](docs/keycode-encoding.md) | Key word and macro formats |
| [`docs/lighting.md`](docs/lighting.md) | Lighting block, palette, Self-define colours, effect list |
| [`docs/firmware-analysis.md`](docs/firmware-analysis.md) | Firmware read/write handlers, flash layout, knob |
| [`docs/knob-patch.md`](docs/knob-patch.md) | Knob rotation patch |

## Repository layout

```
index.html        configurator (served at /)
app/              configurator UI, demo mode
src/hid/          WebHID transport: guarded reads, verified writes, backup/restore
src/protocol/     report framing, key/lighting/macro encoders, patch detection
research/         original stock-firmware research inspector (/research/)
docs/             protocol and firmware documentation
tools/            8051 disassembler/emulator, patch builder, HID and capture tools
analysis/, captures/, backup/   research evidence (firmware dumps and raw captures are not committed)
```

Pushes to `main` run the tests and publish `index.html`, `app/`, `src/` and
`research/` to GitHub Pages ([workflow](.github/workflows/pages.yml)).

## Safety notes

- Only reads and writes whose behaviour was traced in the firmware are enabled;
  anything else is refused in code.
- Writes rewrite whole 512-byte flash sectors, so the configurator always
  reads first and writes back everything it didn't change.
- Avoid hammering sliders: each applied change is a flash write.
- If something goes wrong, restore your backup. If the keyboard ever fails to
  start, the bootloader is never touched and the firmware can be re-flashed
  with sinowisp (see `docs/knob-patch.md`).
