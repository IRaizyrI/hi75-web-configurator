# Saved-capture report comparison

`extract_control.py` turns a USBPcap/Wireshark capture into
`derived/control-transfers.json`. `compare_reports.py` compares the complete
report bytes of two frames in that JSON without connecting to any device.
`audit-read-pairs.mjs` summarizes captured `0x82`/`0x84` SET_FEATURE →
GET_FEATURE pairs, including zero-filled request bodies and subsequent SETs.
It also reads saved JSON only; it never opens the keyboard.
`extract-vendor-input.mjs` uses `tshark` on saved PCAPNG files to extract
interrupt-IN reports on the captured candidate's bus/address/endpoint.

From `hi75-web`, reproduce the read-sequence audit with:

```powershell
node tools/packet-diff/audit-read-pairs.mjs `
  analysis/read-sequence-audit.json `
  captures/003_idle_startup/derived/control-transfers.json `
  captures/004_lighting_open/derived/control-transfers.json `
  captures/008_rgb_brightness_one_step/derived/control-transfers.json `
  captures/009_rgb_brightness_4_to_3/derived/control-transfers.json
```

To reproduce the startup vendor-input observation from `hi75-web`:

```powershell
node tools/packet-diff/extract-vendor-input.mjs `
  'C:\Program Files\Wireshark\tshark.exe' `
  analysis/vendor-input-reports.json `
  captures/003_idle_startup/traffic.pcapng `
  captures/004_lighting_open/traffic.pcapng `
  captures/008_rgb_brightness_one_step/traffic.pcapng `
  captures/009_rgb_brightness_4_to_3/traffic.pcapng
```

For the 128-byte LED data read and sent by LEOBOG ONE in capture `004`:

```powershell
& 'local-tools/pyghidra-venv/Scripts/python.exe' `
  'hi75-web/tools/packet-diff/compare_reports.py' `
  'hi75-web/captures/004_lighting_open/derived/control-transfers.json' `
  54 55 --data-offset 8 --length 128
```

The paths above are relative to the workspace root. The reported *data offset*
is relative to `--data-offset`, and *report offset* includes the report ID and
eight-byte header. Different report lengths are printed; bytes beyond the
requested/common range are not compared.

For two different capture JSON files, add `--other-capture` for the second
frame. For example, to check that capture 008's brightness-4 write exactly
matches capture 009's subsequent read:

```powershell
& 'local-tools/pyghidra-venv/Scripts/python.exe' `
  'hi75-web/tools/packet-diff/compare_reports.py' `
  'hi75-web/captures/008_rgb_brightness_one_step/derived/control-transfers.json' `
  32253 6250 `
  --other-capture 'hi75-web/captures/009_rgb_brightness_4_to_3/derived/control-transfers.json' `
  --data-offset 8 --length 128
```
