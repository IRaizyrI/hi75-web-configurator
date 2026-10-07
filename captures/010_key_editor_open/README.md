# Capture 010: open the official app's key editor

- Raw file: `traffic3.pcapng`, 20,531,700 bytes; SHA-256
  `825a4412ff25c36ece3ee73c844724a9cb0be9ca4a46bac9b65120c1fc49997a`.
- Acquired through visible Wireshark/USBPcap2 on 2026-09-28. The user opened
  LEOBOG ONE's key assignment/customize editor once from the lighting page,
  waited about three seconds, and made **no** remap or apply action.
- The raw file spans `2026-09-28T15:36:42.218398Z` to
  `2026-09-28T15:36:54.926490Z` with about 14,000 USB packets overall.
- `extract_control.py` found 42 control-transfer frames but **zero HID report
  transfers**. Filtering the raw capture for bus 2, device address 5 produced
  only six control-stage packets and no interrupt transfer. This capture
  therefore contains no `0x83` keymap read or other Hi75 configuration report.

Opening this page may use app-cached or profile data, or the relevant read
may occur under a different action. This negative capture does not prove the
stock device lacks a keymap read operation. No custom command was sent.
