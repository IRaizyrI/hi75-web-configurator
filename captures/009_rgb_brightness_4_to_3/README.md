# Capture 009: LEOBOG ONE brightness 4 → 3

- Raw file: `traffic.pcapng`, 14,293,684 bytes, SHA-256
  `9695156a01bd31e48c7be39118091fceb583de3dad797f89d4ae1e35b705a30a`.
  Wireshark initially saved this as `traffic2.pcapng` inside capture 008's
  folder. The byte-identical copy here is the analyzed reversal file.
- Acquired through visible Wireshark/USBPcap2 on 2026-09-28. The user reported
  changing only RGB brightness from displayed value 4 back to 3, with the
  lighting page already open.
- The raw capture spans `2026-09-28T15:30:27.067059Z` to
  `2026-09-28T15:30:35.909024Z` and contains 9,930 USB packets. The derived
  control-transfer JSON has the matching Hi75 report-ID-6 transfers on bus 2,
  device address 5.
- `0x84` SET frame 6209 leads to GET response frame 6250. `0x04` SET frame
  6341 changes **only data offset 60** in the 128-byte block: `04 → 03`.
  `0x0A` SET frame 6515 follows.
- The full 128-byte `0x84` response data in frame 6250 is byte-identical to
  the first 128 data bytes of capture 008's `0x04` SET frame 32253. This shows
  the previous app write was readable in the next capture. It does not show
  retention after unplugging or power cycling.

Together with capture 008's `03 → 04` change at the same offset, this verifies
the official app's brightness 3↔4 mapping for the attached unit. Other levels,
RGB fields, marker/checksum semantics, and safe browser write behavior remain
unverified. See `docs/protocol.md` for the scoped protocol claim.
