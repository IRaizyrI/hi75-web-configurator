# Windows HID inventory (metadata only)

Run with Windows PowerShell 5.1 or PowerShell 7 on Windows. No Python packages,
SDK, compiler installation, administrator session, or replacement USB driver is
required. PowerShell compiles the adjacent C# helper with `Add-Type`.

## Procedure

1. Keep the stock driver and firmware. Close the LEOBOG app, SignalRGB, and other
   keyboard utilities so their traffic or exclusive handles do not interfere.
2. Record the external model/revision label, OS, connection through a hub or
   direct port, and date. Leave the keyboard connected normally.
3. From the `hi75-web` directory, run the commands below. The first run includes
   all present HID collections and USB PnP nodes; filtering by the reported ID
   is optional and is not exact-model identification.
4. To associate Windows nodes with the physical keyboard, optionally take a
   second snapshot with only the Hi75 unplugged, then reconnect it and take a
   third. Close configuration tools first and use another keyboard/mouse if
   needed. Compare the disappearing/reappearing paths; a replug is a separate
   action and can reset volatile keyboard state. Enumeration itself needs no
   unplugging.
5. Supplement the JSON with USBView descriptors as described below. Retain
   query errors and unknowns. Do not try arbitrary feature requests to fill gaps.

```powershell
# In hi75-web. Use a new name for each run; existing files are never overwritten.
New-Item -ItemType Directory -Path .\captures\inventory -Force | Out-Null
$inventoryStamp = [DateTime]::UtcNow.ToString('yyyyMMddTHHmmssfffZ')
$inventoryPath = ".\captures\inventory\windows-hid-$inventoryStamp.json"
.\tools\hid-inspect\Inspect-Hid.ps1 -OutputPath $inventoryPath
Get-FileHash -Algorithm SHA256 -LiteralPath $inventoryPath
```

Output is UTF-8 JSON, both on standard output and in the optional file. For a
smaller, pasteable candidate inventory, run:

```powershell
.\tools\hid-inspect\Inspect-Hid.ps1 -VendorId 0x258A -ProductId 0x010C
```

This filter uses Windows path/instance ID tokens to avoid opening unrelated HID
collections. Also run unfiltered enumeration initially: a different revision
could use another ID. Empty arrays mean no matches, not proof of disconnection.

If local execution policy blocks the reviewed script, run it in a separate
process with a process-scoped override, without changing machine policy:

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\tools\hid-inspect\Inspect-Hid.ps1 -VendorId 0x258A -ProductId 0x010C
```

Organization-enforced restrictions may still block it. Share the error rather
than changing drivers or broadening device access.

To copy an existing inventory verbatim:

```powershell
Get-Content -Raw -LiteralPath $inventoryPath | Set-Clipboard
```

Review serial strings, device paths, parent IDs, and other hardware inventory
before public sharing. Private JSON/TXT snapshots under `captures/inventory/`
are ignored by Git; deliberately curate evidence before committing it. Preserve
the original locally if you make a redacted copy.

## What is collected

| Requested information | JSON location / method |
| --- | --- |
| VID / PID | `hidCollections[].vid` / `.pid`, from `HidD_GetAttributes` |
| Manufacturer / product / serial | `manufacturerString`, `productString`, `serialNumberString`, from HID string getters |
| Device version | `hidDeviceVersionNumber`; not assumed to be a firmware version |
| USB interface association | `pnp.parentInstanceIds`, `usbInterfaceNumberHint`, and separate `usbPnpNodes` |
| Top-level HID collections | One `hidCollections` entry per enumerated Windows HID path |
| Nested collections | `capabilities.linkCollections`, including parent/child indices |
| Usage pages / usage IDs | `capabilities.usagePage` / `usageId`, link nodes, button/value usages or ranges |
| Input / output / feature sizes | `capabilities.reports.<type>.maxWindowsReportBytesIncludingIdSlot` |
| Report IDs | `capabilities.reports.<type>.reportIdsFromCapabilities` |
| Control details | Button/value capability records; value bit sizes/counts, ranges, units, flags |
| Reproducibility | Timestamp, OS, PowerShell, process architecture, script/helper hashes, query errors |

Registry manufacturer/friendly names are recorded separately from HID strings.
Missing/failed values are `null` with query errors where available. A successfully
returned empty string remains `""`. Optional PnP properties commonly produce
Win32 error 13 when unavailable. Do not silently treat errors as observed values.

## Report sizes and descriptor limits

Windows reports a **maximum buffer length per report type and top-level
collection**, including one report-ID slot. Unnumbered reports use zero in that
slot. These numbers are not endpoint packet sizes and are not automatically
WebHID payload lengths. [Microsoft: HIDP_CAPS](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/hidpi/ns-hidpi-_hidp_caps)

IDs are taken from button/value capabilities; constant/padding-only reports may
not be represented there. An empty ID list is not permission to assume ID zero.
Exact wire lengths per ID remain `null`; the tool does not add up usage fields
and guess padding. [Microsoft: value capabilities](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/hidpi/ns-hidpi-_hidp_value_caps)

`nativeCapabilityHex` and `nativeHidpCapsHex` are Windows API structures, **not raw
HID report descriptors**. Button ReportCount occupies formerly reserved bytes
on newer HID API versions, so this tool preserves those bytes without interpreting
that field across Windows versions. [Microsoft: button capabilities](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/hidpi/ns-hidpi-_hidp_button_caps)

Windows exposes a device object for each top-level collection. Several entries
can therefore share one USB interface. `MI_XX` values are PnP association hints,
not a substitute for `bInterfaceNumber` in the USB configuration descriptor.
[Microsoft: top-level collections](https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/top-level-collections)

This is a userspace inventory of the listed public API metadata, not every
possible Windows property or a complete raw USB descriptor dump.

## USBView supplement

Use Microsoft's **USBView**, available with Debugging Tools for Windows in the
Windows SDK. In its connection tree, select the candidate USB device and copy
the right-hand descriptor text into a separately named evidence file. Collect
device/configuration/interface/endpoint descriptors, strings, `bcdUSB`,
`bcdDevice`, interface class/subclass/protocol, alternate settings, endpoint
addresses, types, maximum packet sizes, and intervals. Record the tool version.
Use viewing/copying only; do not disable/reset devices or replace drivers.
[Microsoft: USBView setup and capabilities](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/usbview)

USBView is supplementary and may not expose every descriptor detail. In
particular, a HID descriptor advertising a report-descriptor length is not the
report descriptor itself. Preserve raw HID report descriptors from an available
descriptor export or a later USB enumeration capture; leave them unknown until
obtained. This tool does not reconstruct descriptors from undocumented Windows
preparsed-data layouts.

An optional built-in PnP cross-check (no HID report I/O):

```powershell
Get-PnpDevice -PresentOnly |
    Where-Object { $_.InstanceId -match '^(USB|HID)\\VID_258A&PID_010C' } |
    Select-Object Status, Class, FriendlyName, InstanceId |
    Format-List
```

## Safety implementation

The helper uses SetupAPI/Configuration Manager enumeration and opens HID paths
with `CreateFileW` desired access **zero**. Sharing flags let existing applications
retain their handles; they do not grant this tool write access. It retrieves
attributes, strings, and preparsed capability metadata. String getters can cause
standard descriptor queries; this is not a promise of zero USB bus traffic.
[Microsoft: CreateFileW access semantics](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew)

There are no imports or calls for `WriteFile`, `ReadFile`, `HidD_SetFeature`,
`HidD_SetOutputReport`, `HidD_GetFeature`, `HidD_GetInputReport`, or generic
`DeviceIoControl`. It does not collect keystrokes, query current configuration,
flash firmware, or enable writes. The only file writes are the requested JSON
output and runtime-managed compilation artifacts.

## Validation

```powershell
.\tools\hid-inspect\Test-Decoders.ps1
```

Synthetic fixtures check capability offsets, signed fields, single/range usages,
link-node layouts, and truncated-record handling. They never access hardware.
Source guards detect accidental report-I/O imports and changes to zero-access
device opening. Live inventory is a separate check; successful enumeration is
not experimental verification of the Hi75 configuration protocol.

Local validation on 2026-09-19 passed with Windows PowerShell 5.1.26100.9444
and PowerShell 7.6.5 (64-bit). The full PowerShell 7 inventory opened and parsed
22 collections; the PowerShell 5.1 candidate-filtered run opened and parsed
eight. Empty-filter output and refusal to overwrite existing evidence also
passed. Live 32-bit execution was not tested; link-node fixtures cover both
native structure widths.
