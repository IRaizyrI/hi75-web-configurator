# Capture 008: LEOBOG ONE brightness 3 → 4

- Raw file: `traffic.pcapng`, 60,710,964 bytes; SHA-256
  `53de1fbcb70796c9df8d8c9ff2cf34e6a066a3d9b2dcd303ffa7fb65b39e9a86`.
- Acquired through visible Wireshark/USBPcap2 on 2026-09-28. The user reported
  changing RGB brightness only, from displayed value 3 to 4.
- The raw capture spans `2026-09-28T15:27:20.306985Z` to
  `2026-09-28T15:27:57.916749Z` and has about 41,000 USB packets, including
  traffic unrelated to the Hi75. `extract_control.py` produced 50 control
  frames and eight HID-report frames in `derived/`.
- Matching interface-1, report-ID-6 packets: `0x84` SET frame 32125, GET
  response frame 32164, `0x04` SET frame 32253, `0x0A` SET frame 32427. All
  use the known 520-byte report buffer on bus 2, device address 5. Do not
  attribute other traffic in this 60 MB file to the Hi75 without checking it.
- Within this capture, the 128-byte data from response frame 32164 and the
  first 128 data bytes of SET frame 32253 differ **only at data offset 60**:
  `03 → 04`. This aligns with the user-reported brightness change and was
  reversed at the same offset in capture `009`. The visible
  capture also included the app's lighting-page read/initialization sequence,
  so do not compare whole captures as if they contained only the user action.
- Against old capture `004`, the new `0x84` response differs at data offsets
  10, 60, 61, and 63. Those between-session differences do not by themselves
  identify settings. The new `0x0A` table differs at data offsets 43 and 44.

No browser-originated report or custom write was sent. Byte meanings beyond
the controlled brightness 3↔4 field are not established. See
`docs/protocol.md` for the scoped confidence assessment.
