# 007_topology_probe — failed capture setup

- Date: 2026-09-22, local Windows session.
- Intended action: eight-second USBPcap2 address-5 descriptor-injection probe
  using `tools/capture/Capture-Hi75.ps1`; no keyboard setting change.
- Result: `capture.log` records tshark's invalid-stream error and zero packets.
  `capture-command.json` records the attempted command and nonzero exit code.
  No usable `traffic.pcapng` was produced.
- This does not confirm that address 5 is still the keyboard after reboot.
- No packet bytes or device behavior may be inferred from this attempt.
