# 006_topology_probe — failed capture setup

- Date: 2026-09-22, local Windows session.
- Intended action: six-second USBPcap2 all-device descriptor-injection probe to
  re-check the keyboard address after reboot; no keyboard setting change.
- Result: tshark reported `File type is neither a supported pcap nor pcapng
  format (magic = 0x00000000)` and captured zero packets. No usable raw capture
  was produced in this directory.
- A later direct USBPcapCMD attempt also failed to produce a file and was
  stopped. It appears to have requested elevation without a visible UAC prompt.
- No packet bytes or device behavior may be inferred from this attempt.
