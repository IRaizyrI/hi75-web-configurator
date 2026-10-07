# Stock firmware protocol — source of truth

## Status

The [2026-10-07 checkpoint](checkpoint-identity-probe.md) records implementation
and verification limits. The one-query identity probe passes ten local tests
and succeeded against the physical keyboard after the user manually granted
access. Its 14-byte reply and vendor input event match official-app captures.
The probe now
requires input/feature ID 6 in the same vendor collection, refuses a repeated
send attempt in the same loaded module, and exports schema-v2 metadata/results.

Official LEOBOG ONE traffic has now been captured on the attached Hi75 RGB unit.
The transfer shape and literal report bytes below are **observed**. A controlled
brightness `3→4→3` sequence experimentally verifies data offset 60 in the
128-byte `0x04` LED block **for those two displayed levels on this unit**.
Other setting meanings, checksum behavior, retention after power cycling, and
safe browser-originated writes remain unknown. The app's disassembly provides
code-path leads, not proof that every branch runs on this device. Do not infer
a field from another keyboard.

Record every discovered command here, including unknown bytes and unresolved
questions. Source code must not claim stronger knowledge than this document.

## Confidence vocabulary

- **Unknown:** no supporting evidence.
- **Hypothesis:** an interpretation of observations, not experimentally confirmed.
- **Observed:** directly visible in identified evidence; causality/meaning may
  still be unknown.
- **Experimentally verified:** a stated interpretation passed documented,
  repeatable controlled experiments on a specified fingerprint/revision.

Confidence applies to each claim or field, not automatically to the entire
packet. Verification on one revision does not establish another's compatibility.

## Coverage and implementation gate

| Area | Current evidence | Remaining evidence before a revision-safe web driver |
| --- | --- | --- |
| USB transport | Captured interface-1 feature transfers, report ID 6, 520-byte request buffers; saved firmware declares 519-byte feature data plus ID; browser metadata and successful identity SET/GET corroborate the layout | Live raw report-descriptor-byte confirmation and configuration exchange validation |
| Identity | Captured six-byte `Psd`; firmware `0x82` branch selects its saved address; physical WebHID probe returns the identical reply and vendor input event | Establish an accepted revision fingerprint; identity bytes alone are insufficient |
| LED state | Captured `0x84` read and `0x04` write; brightness `3↔4` verified at 128-byte data offset 60; first read exactly matches saved flash image | More levels, other fields, power-cycle persistence, checksum/marker semantics, and WebHID safety |
| RGB colors | Captured `0x0A` table write exactly matches saved flash image; external `0x08` streaming lead | Controlled color capture and exact command/byte semantics |
| Keymap and Fn layers | App has four-layer 32-bit-word serializer and `0x83` read builder; saved flash entries correlate with RGB profile; firmware branch selects four candidate layer bases | Capture actual reads; decode words and unknown indices; round-trip without loss |
| Knob | App profile and conversion code contain wheel-related fields | Identify exact input/output behavior and validate with capture |
| Macros | App serializer and `0x85` read builder recovered | Capture format, limits, IDs, and persistence |
| Configuration backup/restore | Firmware recovery dumps exist; no configuration export verified | Establish complete coverage and safe, versioned restore path |

The browser inspector (`index.html`) lists WebHID collections and report
layouts without opening a connection or sending any report. A snapshot
from 2026-09-28, preserved in
[`captures/inventory/webhid-20260928T160337Z.json`](../captures/inventory/webhid-20260928T160337Z.json)
(SHA-256 `520ed0acecb1ebb003c86a68a256e0614d8bd53fcf746aff478b0d28e2a878e3`),
shows vendor usage `FF00/0001`, feature ID `5` with five payload bytes, and
feature ID `6` with 519 payload bytes. These agree with the saved-image
descriptor parse and 520-byte Windows report buffer. This is **observed
browser metadata**, not exact-model/revision verification. A separate,
user-triggered `0x82` identity probe is now implemented behind a match to
the observed report IDs, usage pages, and sizes. It sends exactly one
captured query and reads one response; its physical result is recorded below.
Browser `0x84` and `0x83` configuration reads and all
configuration writes remain disabled. Unknown revisions cannot advance past
the identity-probe stage.

## Offline audit of read-shaped transfers

### Physical WebHID identity exchange — 2026-10-07

After manually granting the local inspector access, the user-visible device
passed all report-layout checks. One browser-originated identity query completed
at `2026-10-07T09:14:57.456Z` in the in-app browser (reported user agent
`Chrome/154.0.0.0`, Windows). The saved result is
[`webhid-identity-20261007T091457Z.json`](../captures/inventory/webhid-identity-20261007T091457Z.json),
8,867 bytes, SHA-256
`e0a5bcb12be7e49f3be5fb680a9fd846d4645bd875e4ccb3515ed268b6a2c094`.

| Observation | Actual browser result |
| --- | --- |
| Sent feature report | ID 6, exact captured 519-byte body, one send |
| Received feature DataView | 14 bytes: `06 82 01 00 01 00 06 00 03 00 00 00 00 9B` |
| Response SHA-256 | `6411c6c46db2cb764cb1f5b91279de7bb6bb014af94176c432cc90d63391e281`, identical to the captured official-app response |
| Vendor input | ID 6; seven data bytes `0A 05 64 01 00 00 00`, matching captured wire report `06 0A 05 64 01 00 00 00` |
| Parser outcome | Observed RGB-profile Psd match, no parse error |
| Cleanup | Implementation removed listener and closed interface; no retry or follow-up command |

This **experimentally verifies the identity exchange on this attached unit and
browser environment**, including the returned feature DataView's ID prefix.
It is a browser API observation, not a new simultaneous USBPcap recording.
It does not establish exact revision, persistent side-effect absence, or
configuration read/write safety. Configuration reads and writes remain false.


The read-only script
[`audit-read-pairs.mjs`](../tools/packet-diff/audit-read-pairs.mjs) pairs
`SET_REPORT` requests with their following `GET_REPORT` responses in the
extracted official-app captures. Its output is
[`analysis/read-sequence-audit.json`](../analysis/read-sequence-audit.json)
(SHA-256 `5d19a13212e53820448182b2a0850d3e0e6308d979feaecb33abfa1dc5553cba`). The capture-derived
findings are:

| Capture | Read-shaped pairs | Request data after eight-byte header | Response | Following feature SET |
| --- | ---: | --- | --- | --- |
| `003` startup | Eight `0x82` | All 512 bytes zero; all eight 520-byte requests identical | Eight identical 14-byte reports containing `03 00 00 00 00 9B` | Next `0x82`, or none after final pair |
| `004` lighting page | One `0x84` | All 512 bytes zero | 136 bytes (128 data) | `0x04`, then `0x0A` |
| `008` brightness `3→4` | One `0x84` | All 512 bytes zero | 136 bytes (128 data) | `0x04`, then `0x0A` |
| `009` brightness `4→3` | One `0x84` | All 512 bytes zero | 136 bytes (128 data) | `0x04`, then `0x0A` |

All three `0x84` request buffers are identical; their returned blocks differ.
The `0x84` response in `009` matches the preceding `0x04` write in `008`
for the first 128 data bytes. This supports a state-read interpretation, but
all observed lighting-page read sequences also include app-originated writes.
The zero request bodies and repeated `0x82` responses do **not** establish
that the firmware's SET_REPORT command dispatch has no side effects. The
only browser report I/O available is one explicitly triggered, exact `0x82`
identity exchange; no configuration read or write command is available.

An additional read-only extraction of **interrupt-IN**, not just control
transfers, found a visible event during every `0x82` identity exchange in
capture `003`. Endpoint `0x82` delivered the same eight-byte report
`06 0A 05 64 01 00 00 00` in frames `11`, `16`, `23`, `28`, `35`, `40`,
`47`, and `53`. Each lies between an identity SET and the next identity SET;
some precede the paired GET completion and some follow it. Firmware's `0x82`
read branch sets bit address `0x5A`, and two other firmware paths test and
clear that bit; one prepares a report beginning `06 0A 05`. This is strong
evidence of a **transient input-report side effect** associated with the
identity exchange. The report's semantic meaning and any persistent effect
remain unknown. Capture `004` has one distinct interrupt report
`06 0A 07 00 01 00 00 00` after its `0x0A` write; captures `008` and
`009` have none on that endpoint. The extraction is saved in
[`analysis/vendor-input-reports.json`](../analysis/vendor-input-reports.json)
(SHA-256 `3fc0172da4f9b534dccc62e71b28942107113370f16ad6a6490bdddf304b5b25`).

[`src/protocol/identity.js`](../src/protocol/identity.js) contains the exact
captured `0x82` request and a response inspector. Its 520-byte request
matches startup frame 7 byte-for-byte by SHA-256. The gated browser action
passes the 519 data bytes to WebHID with report ID `6` supplied separately,
records the raw response, and closes without retry or follow-up command.
The [WebHID specification](https://wicg.github.io/webhid/) allows the
returned feature `DataView` to include the report ID, so an unexpected form
is retained raw rather than reinterpreted. `matchesObservedRgbPsd` compares
only six observed bytes and never verifies a revision.

The saved firmware image has a candidate read dispatcher at `0x4E1E–0x4F85`.
Its `0x82` branch selects code-flash `0xB3E3` for additional argument `1`,
exactly where the six captured identity bytes occur; its `0x84` branch
selects `0xC600` for chunk zero, where the captured lighting block occurs.
The `0x83` branch selects candidate layer bases `0xCC00`, `0xD000`,
`0xD400`, and `0xD800`. These are static code and saved-image correlations,
not live `0x83` evidence or a blanket safety proof. The `0x82` branch also
sets firmware bit address `0x5A`, associated with the observed vendor input
report; its semantic effect remains unresolved. The firmware SET_REPORT path
at `0x044B–0x0470` skips a separate state-changing branch for `0x80`-family
commands and does not dispatch `0x82` through the `0x03–0x0A` table. This
bounded evidence supports the single observed identity probe; see
[`firmware-analysis.md`](firmware-analysis.md#candidate-firmware-read-dispatcher).

## Command index

- [Startup report with second byte `0x82`](#observed-startup-report-06-82): model-discovery candidate; meaning unknown.
- [Lighting-page report with second byte `0x84`](#observed-lighting-page-report-06-84): state-read candidate; meaning unknown.
- Lighting-page SET reports with second bytes `0x04` and `0x0A` were also captured. The official app's code labels their builders `SetLED` and `SetLedRgbTab`; their effects and payload fields are unverified.

## Outer report format recovered from the app

Ghidra decompilation of `OemDrv.exe` at `0x48EF20` shows the app constructing a
520-byte feature buffer for its `CDevG5KB` path. The app selects report ID `6`
for the `Fw=0x18` **profile branch** (the value is read from `KB.ini`, not from a
proven device firmware version). The following header interpretation comes from
the app code and agrees with prefixes in captures `003` and `004`; the keyboard's
own interpretation has not been independently tested.

| Offset | Width | App's construction | Capture evidence |
| --- | --- | --- | --- |
| 0 | 1 | Report ID | `06` in both captures |
| 1 | 1 | Command argument passed to builder | `82`, `84`, `04`, `0A` observed |
| 2 | 1 | Additional argument passed to builder | `01` for `0x82`; `00` for captured lighting commands |
| 3 | 1 | Zero | `00` in captured prefixes |
| 4 | 1 | Total number of up-to-512-byte chunks | `01` in captured prefixes |
| 5 | 1 | Zero-based chunk index | `00` in captured prefixes |
| 6–7 | 2 | Chunk data length, little endian | `06 00`, `80 00`, `00 02` observed |
| 8–519 | Up to 512 | Data on app write paths; returned data on app read paths | Preserve raw bytes; structure unknown |

The app passes all 520 bytes to `HidD_SetFeature` and `HidD_GetFeature`, even
when a chunk contains fewer useful bytes. Its generic operation `1` sends a
feature report; operation `2` sends a feature report, then retrieves one and
copies returned data starting at offset 8. The separate `0x82` and `0x84`
read routines use the same 520-byte API buffers. This is static application
behavior, **not** a safe-to-replay command specification. No checksum has been
established for this report-ID-6 family. A checksum seen in the executable's
other report-ID-9 transport must not be carried over.

The enumerator at `0x48EB70` checks VID/PID, usage page `0xFF00`, usage `1`,
and a 520-byte feature buffer for the `Fw=0x18` profile branch. If that profile
has a nonzero six-byte `Psd`, it sends the `0x82` query and compares all six
returned bytes before accepting the candidate. The observed response suffix
`03 00 00 00 00 9B` matches the `Hi75 RGB` profile's `Psd`. This supports a
stronger identity check than VID/PID alone, but a browser implementation still
needs descriptor and revision validation before any writes.

## App command-path index

These entries describe code paths in the supplied executable. “Captured” means
the byte occurred in official-app traffic on the attached unit; it does not
verify payload meaning, persistence, or safe browser use.

| Second byte | App routine / label | Attached-unit evidence |
| --- | --- | --- |
| `0x82` | `0x48FF90`, six-byte profile identity query | Captured in `003` |
| `0x83` / `0x03` | `0x48F1A0` matrix read / `0x48F160` matrix write | No capture |
| `0x84` / `0x04` | `0x48F650` `GetLED` / `0x48F600` `SetLED` | Both captured in `004` |
| `0x85` / `0x05` | `0x48F400` `GetMacro` / `0x48F3B0` `SetMacro` | No capture |
| `0x86` / `0x06` | `0x48F8B0` `GetGame` / `0x48F850` `SetGame` | No capture |
| `0x8A` / `0x0A` | `0x48FCF0` `GetLedRgbTab` / `0x48FCA0` `SetLedRgbTab` | `0x0A` captured in `004`; `0x8A` not captured |
| `0x88` | `0x48FAC0` `GetRealData` | No capture; purpose and format unknown |
| `0x08` / `0x0E` | `0x490120` / `0x490150`, generic app write wrappers | No capture; `0x08` has a third-party RGB-streaming lead below; `0x0E` purpose unknown |
| `0x0B` | `0x48FF40` `SetScreenParam` | No capture; may serve other G5KB devices |
| `0x0C` | `0x492490` `AccessData_Page` writer | No capture; may serve screen/GIF devices |
| `0x0D` | `0x492830` `SetGIFParam` | No capture; may serve screen/GIF devices |
| `0x11` | `0x48FEF0` `ResetDevice` | No capture; never invoke during analysis |

## Configuration structures visible in the app

This section describes the supplied executable's in-memory conversion and
feature-report calls. These layouts have **not** been validated by receiving
and round-tripping corresponding configuration reads from the attached Hi75.
They are suitable for guiding capture analysis, not for enabling WebHID writes.

### Matrix / key assignments (`0x83` read, `0x03` write)

`FUN_0048F1A0` builds a `0x83` request with the requested layer in header byte
2. It asks for a caller-supplied byte count in up-to-512-byte chunks, sending a
520-byte feature report and calling `HidD_GetFeature` per chunk. Its app-side
copy takes the requested number of returned bytes from report offset 8. The
decompiled routine does not visibly validate echoed command, chunk index, or
length before that copy; a future driver should not assume those checks exist
on the device.

The saved firmware's candidate read dispatcher independently maps `0x83`
additional arguments `0–3` to code-flash bases `0xCC00`, `0xD000`,
`0xD400`, and `0xD800`, with a `0x200` stride for subsequent chunks. These
banks mirror configuration-shaped image bytes beginning at `0xB400`, but no
live `0x83` response or layer interpretation has yet been verified.

`FUN_00490D10` builds four layer arrays. It iterates up to `0x90` editor key
records per layer, looks up each record's matrix index from profile data,
converts it with `FUN_00490260`, and stores one **little-endian 32-bit word**
at `matrixIndex × 4` in that layer. The `0x03` write call sends `matrix length ×
4` bytes for each layer marked dirty by the app. The actual matrix length for
this RGB unit, the bytes read by `0x83`, reserved indices, and any layer marker
are not yet captured. A profile-dependent branch can place `00 00 5A A5` as
the last 32-bit word; applicability to this unit is unconfirmed.

The editor record's first word uses a high-byte category and low-24-bit
function ID. `FUN_00490260` maps those to a hardware word with category-specific
cases; `0xFFFFFFFF` is an invalid/unsupported return. `FUN_004786A0` uses a
static 115-pair Windows virtual-key → HID-keycode table at PE address
`0x60B7C0`; the reproducible extract is
`analysis/ghidra-oemdrv-635587cf/vk-to-hid.json` (SHA-256
`6df631f92154804bad97f15793aba998914be46d1498782af090db3ce378a772`).
That is an **app lookup**, not proof of the keyboard's entire keycode space.
The inverse decoder and complete meaning of each hardware word remain open.

### Macro buffer (`0x85` read, `0x05` write)

`FUN_0048F400` builds chunked `0x85` read requests; `FUN_0048F3B0` calls the
generic writer for command `0x05`. App serializer `FUN_00490D10` constructs a
buffer beginning with four bytes per used macro (two little-endian 16-bit
offset/length values), followed by variable-length records. `FUN_00490940`
serializes each record as a one-byte **UTF-16LE name byte length**, then that
many name bytes, then four bytes per action. The app caps the name scan at 30
wide characters; its action packing combines a kind/flag nibble, a duration
value, and a keycode from the VK→HID table or special cases. The precise
meaning of flags, duration units, ID allocation, maximum buffer length on
this unit, and device persistence are unverified. Do not construct macro
packets from this description yet.

### LED block and per-key RGB (`0x84`/`0x04`, `0x8A`/`0x0A`)

`FUN_00491840` reads 128 bytes via `GetLED`, checks the last two data bytes
for `5A A5`, modifies the in-memory block through one of two profile-dependent
converters, and calls `SetLED` with 128 bytes. Capture `004` shows this exact
read/SET sequence, but the two changed data bytes are not assigned setting
meanings. For a separate per-key RGB path, the app builds color data and calls
`SetLedRgbTab`. Capture `004` shows a `0x0A` header length of 512 bytes, with
`5A A5` at data offsets 506–507; the last two data bytes are zero. The app
also contains a 420-byte branch, whose applicability to this unit is unknown.
No `0x8A` read or controlled color/brightness change has been captured.

The `0x0A` builder in `FUN_00491840` lays out a 420-byte working table as
twenty 21-byte groups: the first group is zero-initialized, then nineteen
groups receive seven three-byte color values each. App profile channel-index
fields choose where the three components go within each triple. For the
captured RGB profile, frame 57's first 21 data bytes are zero, bytes 21–419
contain the table, bytes 420–505 are zero padding, bytes 506–507 are `5A A5`,
and bytes 508–511 are zero. The grouping follows the app code and this one
captured payload; whether each group represents a particular effect, LED, or
mode is still a hypothesis. No RGB channel meaning should be assigned from a
single unchanged-state capture.

### Verified brightness change: displayed 3 ↔ 4 on this unit

Two controlled official-app captures, [`008`](../captures/008_rgb_brightness_one_step/README.md)
and [`009`](../captures/009_rgb_brightness_4_to_3/README.md), isolate a single
byte in the 128-byte LED data block. The user reported changing **only** the
displayed brightness from 3 to 4, then 4 back to 3, with separate captures.

| Capture | `0x84` GET response | `0x04` SET | Difference within 128 data bytes |
| --- | --- | --- | --- |
| `008`, brightness `3→4` | Frame 32164 | Frame 32253 | Offset 60: `03→04`; no other differences |
| `009`, brightness `4→3` | Frame 6250 | Frame 6341 | Offset 60: `04→03`; no other differences |

The data begins at whole-report offset 8, so this field is whole-report offset
68. Both reports use report ID 6 and 520-byte request buffers, with the app
header `06 84 00 00 01 00 80 00` for the read request and
`06 04 00 00 01 00 80 00` for the write. The full 128-byte data read in
`009` is **byte-identical** to the 128-byte data written in `008`, showing
the changed value was readable when the next capture began. The `0x0A`
512-byte payload is identical between these two captures, so it did not carry
the observed brightness delta. The earlier lighting-page-open capture `004`
changed other bytes and must not be treated as a brightness experiment.

In the app's `FUN_00491430` converter, a loop writes 19 two-byte entries
starting at LED data offset 58 (`0x3A`). Verified offset 60 is the first
byte of its second entry. It is a **hypothesis** that the corresponding byte
of each other entry stores that mode's brightness; no other entry or mode
has a controlled change/reversal capture. The adjacent bytes' high/low
nibble meanings are also unresolved.

**Confidence:** experimentally verified association of LED data offset 60 and
displayed brightness values 3 and 4 for the attached, app-selected Hi75 RGB
unit. Treat equality between the byte and other displayed levels as a
hypothesis until tested. The firmware revision beyond captured USB
`bcdDevice=0x0500` is unknown; `008`/`009` did not repeat the `0x82`
identity query. The read-after-write comparison spans separate captures but
no unplug/power cycle, so nonvolatile persistence is **not** established.
The experiment does not prove that a browser can safely issue either report,
that the two-byte `5A A5` marker is a checksum, or that unknown data may be
rewritten. Browser write support remains disabled.

### Offline flash-image correlation — no new device command

The preserved `sinowisp` image from before capture `004` has exact byte matches
for three captured data blocks. The six returned identity bytes in startup
frame 10 occur at flash-image offset `0xB3E3`. The 128 returned `0x84` data
bytes in lighting frame 54 equal image bytes `0xC600–0xC67F`. The 512 `0x0A`
SET data bytes in frame 57 equal image bytes `0xC800–0xC9FF`. Each is the only
exact occurrence of that whole block in the 61,440-byte image. The first
128 data bytes sent with `0x04` in frame 55 differ from `0xC600–0xC67F` only
at data offsets 10 (`03→0B`) and 63 (`27→47`). This correlation gives a
concrete baseline for comparing future single-setting captures, but it does
not prove command semantics, flash write behavior, or field meanings.

The image also contains four-byte entries starting at `0xB400` whose positions
follow the RGB profile's matrix indices. Of 80 ordinary category-2 keys that
have app VK→HID lookup entries, 73 exactly match a `00 00 00 <HID>` image
entry at `0xB400 + 4 × matrixIndex`. The seven exceptions are modifier/Win
keys whose saved values all match a candidate HID modifier-bit ordering in
the second byte. At `0xB800`, 25 of 30 `[FN1]` profile
values match four saved bytes at the corresponding matrix index. Mirrored
blocks also appear at `0xCC00` and later offsets; their role is unknown.
Neither a live `0x83` response nor the mapping from its layer argument to
these image regions has been observed. See
[`firmware-analysis.md`](firmware-analysis.md) for source hashes, exact
comparison outputs, and disassembly caveats. These are offline observations,
not grounds to enable reads or writes in a browser.

### External `0x08` RGB-streaming lead — unverified on this unit

A [community SignalRGB Hi75 plugin](https://github.com/NollieL/SignalRgb_CN_Key/blob/main/Leobog%20Hi75.js)
uses VID/PID `258A:010C`, interface 1, usage page `FF00`, usage 1, and builds a
packet prefix `06 08 00 00 01 00 7A 01` for live RGB colors. This aligns
with the official app's generic `0x08` write wrapper at `0x490120`, but no
`0x08` packet has been captured from the attached keyboard. The plugin's
`0x017A` length field says 378 bytes, while its visible 96-color-index loop
produces 288 color bytes plus 24 trailing zeros (312 bytes) before padding to
520; that discrepancy is unresolved. Its VID/PID-and-usage check would be too
weak as our device fingerprint. The plugin's `device.send_report` call does
not itself establish WebHID report type, exact payload size, or safe behavior
for this particular revision. Do not replay it without controlled evidence.

### Observed startup report `06 82`

| Field | Value |
| --- | --- |
| Status / confidence level | Transfer bytes observed; purpose is a hypothesis |
| Applicable device fingerprint / firmware revision | Attached unit selected as `Hi75 RGB` by LEOBOG ONE; exact firmware revision unknown |
| Transport | USB HID class control transfer, `SET_REPORT` followed by `GET_REPORT` |
| HID interface | `wIndex=1`; vendor HID identity and full descriptor details in `usb.md` |
| Report ID | `6` in `wValue=0x0306`; payload also begins `06` |
| Command | Unknown; payload byte 1 observed as `82` |
| Subcommand | Unknown |
| Request length | 520 bytes including report ID; setup `wLength=0x0208` |
| Response length | 14 captured bytes including report ID; GET setup also requests 520 bytes |
| Packet layout | Request prefix `06 82 01 00 01 00 06 00`; response `06 82 01 00 01 00 06 00 03 00 00 00 00 9B`; all remaining request bytes preserved in raw capture |
| Checksum | Unknown |
| Persistence behavior | Unknown |
| Experimental evidence | `captures/003_idle_startup/traffic.pcapng`, SHA-256 `21e86edb7cdc81076933345636e7985c4c28bb9bbe7f1378f64087f0600ed69f`; eight identical SET/GET pairs, SET frames 7,13,19,25,31,37,43,49; response frames 10,18,22,30,34,42,46,52 |
| Open questions | The final six response bytes match `Psd=3,0,0,0,0,9B` in the RGB profile. Static app code at `0x48ECBE` and `0x48ECD5`–`0x48ECE4` compares them with a candidate record. The saved firmware's `0x82` branch selects `0xB3E3` and sets bit address `0x5A`; every captured identity exchange includes a vendor interrupt-IN report. Its meaning and persistence remain unknown, so this sequence is not classified as safe to replay. |

### Observed lighting-page report `06 84`

| Field | Value |
| --- | --- |
| Status / confidence level | Transfer bytes observed; purpose is a hypothesis |
| Applicable device fingerprint / firmware revision | Same attached unit and official app session as startup capture |
| Transport | USB HID class control transfers |
| HID interface | `wIndex=1` |
| Report ID | `6` in `wValue=0x0306` and captured payloads |
| Command | Unknown; second byte of first request/response observed as `84` |
| Subcommand | Unknown |
| Request length | Three SET_REPORT payloads of 520 bytes each, including report ID |
| Response length | One GET_REPORT response of 136 captured bytes, including report ID; setup requests 520 |
| Packet layout | SET frame 51 prefix `06 84 00 00 01 00 80 00`; response frame 54 prefix `06 84 00 00 01 00 80 00 00 03 03 02 00 00 04 04`; further SET prefixes: frame 55 `06 04 00 00 01 00 80 00`, frame 57 `06 0A 00 00 01 00 00 02`; complete bytes in derived capture JSON |
| Checksum | Unknown |
| Persistence behavior | Unknown |
| Experimental evidence | Opening the lighting page without changing a setting: `captures/004_lighting_open/traffic.pcapng`, SHA-256 `673b4761d66f89be42dce9efa3da9841f984271d79377a7e0c30f005e2cee391`; SET frames 51,55,57, GET frame 53, response frame 54 |
| Open questions | The app's `GetLED`/`SetLED` labels and read-modify-write flow align with these reports. Comparing the returned 128-byte data in frame 54 (offsets 8–135) to the first 128 data bytes sent in frame 55 shows exactly two differences: data offset 10, `03`→`0B`, and data offset 63, `27`→`47` (whole-report offsets 18 and 71). Both blocks end in `5A A5`, matching an app-side validity check at data offsets 126–127. Frame 57's `0x0A` data also contains `5A A5` at data offsets 506–507, then two zero bytes. The setting meanings, why page open changed these bytes, on-device effect, and persistence are unknown. This page-open capture alone does not establish a brightness field; the later controlled pair `008`/`009` does establish offset 60 for levels 3 and 4. |

## Command record template

Copy this section for each candidate command. Use `Unknown` for unestablished
facts and `Not applicable` only with an explanation.

### `<record identifier and descriptive label>`

| Field | Value |
| --- | --- |
| Status / confidence level | Unknown |
| Applicable device fingerprint / firmware revision | Unknown |
| Transport | Unknown; record observed transfer type and direction |
| HID interface | Unknown; configuration, interface number, alternate setting, usage page/usage, endpoint if applicable |
| Report ID | Unknown; distinguish descriptor ID, setup value, and any API representation |
| Command | Unknown; give offset/width only when supported |
| Subcommand | Unknown |
| Request length | Unknown; specify byte-count convention and whether report ID is included |
| Response length | Unknown; specify byte-count convention and whether report ID is included |
| Packet layout | See field tables below; unknown until populated from evidence |
| Checksum | Unknown; record coverage, algorithm, storage, and validation evidence if established |
| Persistence behavior | Unknown; separate immediate effect, app restart, USB reconnect, and power-cycle observations |
| Experimental evidence | Capture paths, SHA-256 hashes, packet/frame numbers, and experiment notes |
| Preconditions / sequencing | Unknown |
| Response matching / timing | Unknown |
| Side effects / write classification | Unknown |
| Errors / failure behavior | Unknown |
| Open questions / counterevidence | Unknown |

#### Packet layout

Define the offset origin and byte order explicitly. Keep separate request and
response tables. Do not strip a report ID or transport wrapper without recording
that transformation. Mark unmapped ranges `Unknown — preserve verbatim`.

Request:

| Byte offset / range | Width (bytes) | Observed bytes | Proposed meaning / encoding | Evidence | Confidence |
| --- | --- | --- | --- | --- | --- |

Response:

| Byte offset / range | Width (bytes) | Observed bytes | Proposed meaning / encoding | Evidence | Confidence |
| --- | --- | --- | --- | --- | --- |

#### Experimental evidence

- Device fingerprint reference:
- Official application version and executable hash:
- Capture/experiment ID and raw-file hash:
- Relevant frame numbers, directions, and exact bytes:
- Initial state and one intentional change:
- Observed outcome:
- Repeat and reversal experiments:
- Alternative explanations / counterevidence:
- Interpretation, confidence, and limits of applicability:

#### Future implementation constraints

- Required fingerprint and known-revision match:
- Proven state-read procedure and minimum editable range:
- Unknown bytes that must be retained:
- Persistence and recovery evidence:
- Checks required before any write support:

## Evidence history

Bootstrap: template created; zero protocol commands verified or implemented.

2026-09-19: metadata-only Windows inventory observed candidate HID capabilities,
including a vendor collection with feature report ID 6 and a 520-byte maximum
Windows report buffer. Evidence, hash, scope, and limitations are in
[`usb.md`](usb.md#local-candidate-observation--2026-09-19). This is transport
metadata for an unconfirmed candidate, not a verified proprietary command or
permission to send reports. Zero configuration commands remain verified.

2026-09-19: audited sinowisp 2.1.0 for recovery preservation; see
[`backup/README.md`](../backup/README.md). The original Hi75 preset is
`leobog-hi75`; firmware/bootloader/full reads all invoke a firmware-enable
operation that can modify flash. No device flash read, erase, or write was
issued. No dedicated EEPROM/configuration region is exposed by that CLI.
These are upstream ISP-tool findings, not experimental confirmation of our
unit's stock configuration protocol. Do not transfer ISP commands or report
meanings into the configurator. At that stage, no recovery image was acquired.

2026-09-19 (subsequent authorization): the user expressly authorized the normal
upstream read cycle and its firmware-enable side effect. sinowisp 2.1.0 with the
unchanged `leobog-hi75` preset successfully read application (61440 bytes),
bootloader (4096 bytes), and full preset flash (65536 bytes). All three exit
codes were zero, none of the dumps is all 00/FF, and the full payload exactly
equals the separately read application plus bootloader. Original ISP payloads,
hashes, command logs, and validation are in [`backup/README.md`](../backup/README.md).
No erase, write subcommand, configuration modification, or restore test occurred.
No separate EEPROM/configuration read section is exposed by this tool version.
This does not verify any stock configuration command or enable configurator writes.

2026-09-19: initial file-only inspection of the supplied `LEOBOG ONE` application
found two named Hi75 profiles sharing VID/PID but differing in `Psd` and knob
settings, plus HID feature-report API strings in `OemDrv.exe`. Literal values,
file hashes, confidence limits, and the recommended combined application-analysis
and capture approach are recorded in [`software-triage.md`](software-triage.md).
No command bytes or configuration fields were experimentally verified. Application
profile values must not be promoted to on-device capabilities without evidence.

2026-09-19: USBPcap capture `003_idle_startup` observed repeated 520-byte
`SET_REPORT` / `GET_REPORT` pairs with payload prefix `06 82` and identical
14-byte responses ending `03 00 00 00 00 9B`. Capture `004_lighting_open`
observed a `06 84` SET/GET pair plus two more SETs when the lighting page
opened. The directly observed bytes and hashes are indexed above. A later
45-second capture named `005_rgb_brightness_4_to_3` did not include the
intended UI action; it is not brightness evidence.

2026-09-22: static analysis of the supplied app found direct 520-byte
`HidD_SetFeature` / `HidD_GetFeature` call sites that build `0x82` and `0x84`
second bytes. The `0x82` call's parent compares six returned bytes against
a candidate device record. See [`app-disassembly.md`](app-disassembly.md) for
addresses and limitations. These code paths corroborate the observed transfer
shape but do not verify a safe browser-originated read or any editable field.

2026-09-22 (continued): Ghidra recovered the `CDevG5KB` report builder,
profile-dependent device-selection branch, and app command paths indexed above.
The captured `0x04` and `0x0A` SET reports align with app routines named
`SetLED` and `SetLedRgbTab`; this does not establish that opening the page
changed a setting. `FUN_00491840` reads an LED block before modifying and
sending it, and calls a per-layer keymap serializer. `FUN_00490260` converts
editor key records to 32-bit hardware values, with cases for multiple key
categories and macros. The complete keymap encoding, lighting byte semantics,
and persistence remain unverified on this unit. See [`app-disassembly.md`](app-disassembly.md)
and the saved decompiler exports for exact evidence.

2026-09-22 (further static analysis): the `0x83` matrix, `0x85` macro,
`0x8A` RGB-table, and `0x88` real-data read builders were decompiled, along
with additional app-only write wrappers. The matrix and macro serializers and
the 115-entry VK→HID lookup table are indexed above. USB descriptors already
present in capture `003` were decoded and recorded in [`usb.md`](usb.md).
Two attempted post-reboot topology probes (`006`, `007`) failed before producing
packets due an invalid USBPcap extcap stream; they are not protocol evidence.

2026-09-28: offline comparison of the preserved firmware image with captured
startup and lighting reports found exact six-, 128-, and 512-byte matches at
image offsets `0xB3E3`, `0xC600`, and `0xC800`, respectively. The RGB profile
and app VK→HID lookup also account for 73 of 80 ordinary saved key entries
at `0xB400`, while 25 of 30 `[FN1]` values match at `0xB800`. This substantially
strengthens the evidence that the saved image contains configuration-shaped
data, but no live keymap response, specific lighting field, write persistence,
or firmware handler is established. Reproducible scripts and exact outputs are
linked in [`firmware-analysis.md`](firmware-analysis.md).

2026-09-28 (controlled brightness pair): after repairing Wireshark's per-user
USBPcap extcap registration, official-app captures `008` and `009` recorded
displayed brightness `3→4→3`. Their `0x84` read / `0x04` write pairs each
changed only LED data offset 60 (`03→04`, then `04→03`). The second read
exactly matched the first write, while both `0x0A` RGB-table payloads matched
each other. This verifies that one field for those values on this unit, not
general WebHID write safety or power-cycle persistence.

2026-09-28 (key-editor open): capture `010` recorded one navigation from the
official app's lighting page into its key editor, with no remap or apply.
It contains no HID report transfers and no `0x83` read. This is a negative
observation for that UI action only, not proof that a keymap read is absent
from the firmware. The app contains a `0x83` builder, but a static scan of
analyzed calls to its virtual slot found no proprietary-app caller; see
[`app-disassembly.md`](app-disassembly.md). Live `0x83` response layout and
safe replay remain unverified.

2026-09-28 (descriptor correlation): the saved application image contains
byte-identical copies of captured USB device and configuration descriptors.
Immediately preceding them are 67- and 240-byte HID report descriptors with
the exact advertised lengths and parsed report sizes matching the Windows
inventory. The interface-1 vendor report ID 6 declares 519 Feature payload
bytes plus its ID byte, agreeing with the 520-byte app buffer. These bytes
come from the preserved image, not a live HID report-descriptor request; see
[`usb.md`](usb.md#hid-report-descriptors-recovered-from-the-saved-firmware-image).

2026-10-07 (first browser configuration read): the read-only driver
(`src/hid/transport.js`) sent `0x82`, `0x84` (128 bytes), `0x8A`, `0x83`
layers 0–3 and `0x85` (512 bytes each) once each, no retries. Saved as
[`backup/config/hi75-backup-2026-10-07T09-52-28.785Z.json`](../backup/config/hi75-backup-2026-10-07T09-52-28.785Z.json).
All four layers and the macro block are byte-identical to saved-image
`0xCC00`/`0xD000`/`0xD400`/`0xD800`/`0xDC00`, confirming the read dispatcher
mapping. The LED block differs from `0xC600` only at data offsets 10, 60, 61
and 63, and the RGB table from `0xC800` only at offsets 43–44, consistent with
official-app lighting writes made after the dump. Each layer's last two bytes
are `5A A5`. One vendor input report `0A 05 64 01 00 00 00` followed the
identity query, as before. No write was sent.

2026-10-07 (first browser write): the page's brightness control performed
`0x84` read → `0x04` write of the same 128-byte block with only data offset 60
changed → `0x84` read-back, several times, ending at level 0. Each read-back
matched the written block and the user confirmed the LEDs visibly changed each
time. This **experimentally verifies browser-originated `0x04` writes and the
brightness byte for levels 0–4** on this unit. Writes are persistent by
firmware design (sector erase/program at `0xA252`); a replug check is pending.

2026-10-07 (first keymap write and persistence): the page's key editor
performed `0x83` read → `0x03` write of the full 512-byte layer with one key
word changed → `0x83` read-back. The user confirmed the remapped key worked,
and that both the remap and brightness survived unplugging and replugging.
This **experimentally verifies browser `0x03` layer writes, the key-word
encoding for ordinary keys, and flash persistence** on this unit.

2026-10-07 (restore and knob press): the user confirmed restore-from-backup
and the knob-press remap (keymap matrix 84 word plus LED byte `0x1A` = 6) both
work on the device. Knob turn remains hard-coded volume in firmware.

2026-10-07 (macros): macro playback verified on `/` with both the official app
and the web page; byte layouts are identical. PgDn (matrix 88) never plays a
macro, with either tool. See `keycode-encoding.md`.
