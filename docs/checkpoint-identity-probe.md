# Identity-probe checkpoint — 2026-10-07

The browser inspector and narrowly scoped identity probe are implemented,
locally tested and **successfully exercised on the physical keyboard through
WebHID**. Its identity reply and vendor input event match official-app captures.
Configuration reads and writes remain disabled.
The complete protocol specification is still in progress; `protocol.md` remains
the source of truth.

## Completed across the project

| Work | Result and evidence limit |
| --- | --- |
| Repository and safety documentation | `src/hid`, `src/protocol`, `src/ui`, inventory/capture/comparison tools, recovery storage, and protocol templates are present. Unknown revisions cannot enable configuration commands. |
| Windows inventory | Metadata-only tool records VID/PID, strings, interfaces, collections, usage pages/IDs and report capabilities. Attached candidate is `258A:010C`, `BY Tech`, `Gaming Keyboard`, device version attribute `0x0500`; these are not unique model/revision proof. |
| Recovery preservation | Upstream sinowisp 2.1.0 `leobog-hi75` reads preserved application (61,440 bytes), bootloader (4,096 bytes), and full (65,536 bytes), with command logs, validation and SHA-256. Full equals application plus bootloader. No separate EEPROM/configuration read section exists. The authorized upstream firmware-enable side effect is documented. Restore has not been tested. |
| Official application analysis | Ghidra exports identify feature-report framing, command builders, keymap serializers and VK-to-HID lookup. `KB.ini` profiles/layouts provide supporting leads. Static findings are not universal device behavior. |
| USB capture tooling | USBPcap and Wireshark capture support is available. Raw captures and reproducible packet extraction/comparison scripts retain evidence for startup, lighting, brightness and key-editor navigation. |
| Transport | Official app uses report ID 6, a 520-byte Windows request buffer (519 payload bytes plus ID), eight-byte framing and up to 512 data bytes. Saved-image descriptors and the user's WebHID snapshot corroborate the report layout. Live raw HID report-descriptor bytes remain outstanding. |
| Identity | Eight official-app `0x82` queries return identical six data bytes `03 00 00 00 00 9B`. Each exchange coincides with input report `06 0A 05 64 01 00 00 00`. Event meaning and exact revision discrimination remain unknown. |
| Lighting | Controlled official-app brightness `3→4→3` captures verify only data offset 60 in a 128-byte LED block for those two values on this unit. `0x84` reads and `0x04`/`0x0A` writes are observed. Other fields, checksum and power-cycle persistence remain unverified. |
| Firmware correlation | Saved-image identity/LED/color-table data match captures at `0xB3E3`, `0xC600`, `0xC800`. Raw read-dispatch bytes corroborate candidate keymap layer bases `0xCC00`, `0xD000`, `0xD400`, `0xD800`, macro base `0xDC00` and game base `0xCA00`. These latter reads still lack live response evidence. |
| Keymap/layers | Offline ordinary/modifier/Fn entries correlate with app layout and serializers. Opening the key editor produced no HID control report in capture 010. Full action encoding and live layer reads remain unresolved; no per-key capture campaign is needed at this stage. |
| Browser tool | Physical identity SET/GET succeeded after the user granted access. Metadata inspector and descriptor-gated probe preserve raw reply/input event with no automatic retry. Configuration I/O is absent. Knob, macro editing, configuration restore and graphical mapping are not implemented. |

## Work and verification at this checkpoint

- Read-pair audit covers eleven official-app exchanges: eight identity and three
  lighting reads. Unknown input events are extracted separately rather than
  silently treated as configuration or ignored.
- Hash-gated saved-image read-dispatch extraction preserves raw bytes and
  avoids unreliable decompiler switch labels. Firmware evidence suggests the
  identity command bypasses a separate state-changing SET_REPORT branch; it
  does not establish that the command has no side effects.
- The probe sends report ID 6 separately from the exact 519-byte body, waits
  20 ms before receiving the feature reply, preserves raw DataView bytes and
  listens briefly for report-ID-6 input. A mismatched reply is recorded without
  guessing alternate packet formats.
- The descriptor gate requires observed consumer/vendor report IDs and lengths,
  including input and feature ID 6 in the same vendor collection. A successful
  match is still only a candidate; exact model/revision and write permission
  remain false.
- The device cannot be probed again in the same loaded module after a send
  attempt, including transfer failure. The page retains the result/error for
  download and leaves all probe controls disabled afterward.
- Metadata export now uses WebHID's collection `type`, unit-factor exponent
  fields and volatility flag. New snapshots use schema version 2 and record
  browser user agent and metadata/probe mode. Original evidence is untouched.
- `npm test`: **10 tests passed**. Coverage includes captured packet hash,
  wrong-descriptor rejection before opening, report framing, event preservation,
  closure on transfer failure, and refusal to retry. These are mock/offline
  checks. The separate actual browser result below establishes physical exchange.
- HTTP checks: UI and protocol assets return 200; backup, capture and analysis
  paths return 404. The server binds only to `127.0.0.1:8787`.
- Browser check: the page initially had no granted device; the user manually
  granted access. The candidate then passed all layout checks and one identity
  query completed successfully. No configuration report command was sent.

## Actual physical result

Completed at `2026-10-07T09:14:57.456Z` in the in-app browser, reported user agent
`Chrome/154.0.0.0`, Windows. Saved
[snapshot](../captures/inventory/webhid-identity-20261007T091457Z.json) is
8,867 bytes, SHA-256
`e0a5bcb12be7e49f3be5fb680a9fd846d4645bd875e4ccb3515ed268b6a2c094`.

- One feature send: report ID 6, captured 519-byte body.
- One feature receive: 14 bytes `06 82 01 00 01 00 06 00 03 00 00 00 00 9B`.
- Response SHA-256 matches the captured official-app response exactly:
  `6411c6c46db2cb764cb1f5b91279de7bb6bb014af94176c432cc90d63391e281`.
- One vendor input event: report ID 6, body `0A 05 64 01 00 00 00`.
- Parsed Psd `03 00 00 00 00 9B` matches the observed RGB profile.
- No retry, configuration command, firmware flash or erase. Device closed after
  the query. No simultaneous USBPcap trace was recorded for this exchange.

This verifies the identity exchange and observed API byte framing on this unit;
exact revision and absence of persistent effects are not established.

## Next gate

A match alone does not enable writes. The next implementation gate is an audited
lighting `0x84` read with unknown bytes preserved, followed by layer `0x83` reads
once their device-side behavior has been sufficiently established. Complete
keymap, macro, knob and persistence analysis remains subsequent work.

The local server remains at `http://localhost:8787`; use `npm start` from
`hi75-web` if stopped. There is no need to repeat the identity query now.
