# Reverse-engineering procedure

## Scope

Investigate the stock firmware through static analysis of the official LEOBOG
application together with traffic that the application generates on the attached
keyboard. The user explicitly chose application disassembly as the primary
method. Capture controlled changes to validate code-derived hypotheses. Do not
replay unknown commands, send guessed writes, or flash firmware. Disassembly
of the keyboard firmware remains Plan B if app analysis and captures cannot
resolve a required behavior.

## Capture naming

Use one directory per experiment:

```text
captures/<NNN>_<lowercase_action_or_setting>[_<before>_to_<after>]/
```

Use unique ascending sequence numbers, at least three digits, lowercase ASCII,
and underscores. Never reuse or overwrite an experiment ID. Append `_repeat_01`
or another descriptive suffix when useful, retaining a new sequence number.

Naming examples (some capture IDs are now used; inspect metadata before
interpreting a directory name):

```text
001_idle_startup/
002_rgb_brightness_50_to_60/
003_rgb_brightness_60_to_70/
004_key_esc_to_f13/
```

Numbers in a name must reflect values actually shown by the application. If it
uses discrete levels instead of percentages, use names such as
`002_rgb_brightness_level_2_to_3`. Key-remapping examples are for later phases,
not the next experiment.

Suggested contents:

```text
traffic.pcapng          Original capture in its native format (.pcap also OK)
metadata.md            Experiment record using the template below
sha256.txt             Hashes of the original evidence files
descriptors/           Raw and decoded descriptors, if collected in this run
screenshots/           Optional UI evidence
derived/               Exports, normalized packets, and comparison results
```

Retain originals unchanged. Every derived file must identify its input/hash,
tool/version, command/options, offset convention, and any filtered or removed
bytes. An optional sanitized sharing copy is derived evidence; do not silently
replace the original. Review USB captures for sensitive keystrokes and identifiers
before publication.

## First capture sequence

1. Record the physical identity and descriptors listed in `usb.md`. Record the
   official application version and current visible settings without updating
   firmware or resetting the keyboard.
2. Close other keyboard configuration/RGB software. Start USB capture before
   opening the official app. If practical, include USB connection/enumeration;
   document exactly when connection occurred.
3. For `001_idle_startup`, open the official app, allow it to settle, and record
   an idle interval without changing settings. Note event timestamps and duration.
   Startup itself may send writes: do not assume it is a pure read sequence.
4. For the next capture, keep effect, color, speed, profile, and other settings
   constant; change brightness by one available step in the official UI. Record
   both values and the action time. If the app requires Apply/Save, record that
   click separately. Allow responses to finish before stopping capture.
5. Repeat with a second brightness step if available, then use a new capture to
   return to the original brightness. Record any automatic UI changes. These
   repeated/reversed changes help distinguish a value field from counters or
   unrelated startup traffic.
6. Preserve raw files and metadata. Analyze the actual packets before proposing
   any browser-originated request. Persistence tests come later as separate,
   documented experiments; do not infer persistence from a UI change alone.

If brightness is unavailable, record the available controls before selecting a
different single-variable experiment. Do not invent UI values or supported modes.

## Experiment metadata template

```markdown
# <capture directory name>

- Date/time with timezone:
- Operator / unit alias:
- Physical model/revision evidence:
- Descriptor/fingerprint evidence paths and hashes:
- Firmware version (or Unknown) and source:
- OS/version and USB topology:
- Official app version, download source, executable hash:
- Capture tool/version, capture interface, filters, file format:
- Other keyboard/RGB software closed:
- Raw evidence filenames and SHA-256 hashes:
- Capture start/end times; dropped packets or known gaps:
- Initial state (profile, RGB effect/color/speed/brightness, other relevant state):
- Single intended change, exact before/after values and displayed units:
- Timestamped actions (connect, app launch, setting change, Apply/Save, stop):
- Observed keyboard result / unexpected changes:
- Relevant USB frame numbers (after analysis):
- Repeat/reversal capture references:
- Interpretation and confidence (keep observation separate from hypothesis):
- Confounders / unresolved questions:
- Privacy review / derived sharing copies:
```

## Packet comparison requirements

`tools/packet-diff/extract_control.py` extracts USB control requests and
responses into `derived/control-transfers.json`, retaining raw report payloads,
USB setup, frame numbers, and input hashes. `compare_reports.py` compares
specified saved payload frames byte by byte, with explicit offset and length.
Further sequence-level comparison tooling should:

- Preserve direction, transfer type, interface/endpoint, setup fields, report ID,
  timestamps, original frame numbers, and raw payloads.
- Match comparable request/response sequences and flag unmatched traffic.
- Report lengths and changed byte offsets/ranges without assuming command fields.
- Keep raw and normalized representations linked; document every normalization.
- Compare baseline, repeated changes, and reversal captures reproducibly.

A differing byte is an observation, not proof of a field's meaning. Record
hypotheses, alternatives, and validating experiments in `protocol.md`.

## Visible Wireshark capture when USBPcap elevation is required

The attempted automated USBPcap extcap probes `006` and `007` produced no
packets, and a direct `USBPcapCMD` attempt raised a UAC prompt that was not
visible to the remote automation session. Do not leave an invisible elevated
recorder running. On 2026-09-28, `tshark -G folders` showed Wireshark's
personal extcap path as `%APPDATA%\Wireshark\extcap`; the installed
`USBPcapCMD.exe` existed only in `C:\Program Files\USBPcap`, so Wireshark did
not list USB capture interfaces. A byte-identical copy was placed in that
per-user extcap directory. Subsequent `tshark -D` listed `USBPcap1`,
`USBPcap2`, and `USBPcap3`. Wireshark was already running, so its UI must be
restarted to discover the new helper. This repaired interface enumeration;
it did not start a capture or confirm that elevation works.

For the next controlled capture, start Wireshark visibly on the Windows
desktop, approve UAC yourself if prompted, and select the USBPcap interface
carrying this Hi75 (previous successful captures used bus 2; verify the
current device address in the new capture). Save the raw `.pcapng` before
closing Wireshark.

For lighting, record a short idle baseline, change **one** brightness step in
LEOBOG ONE, then stop and save that capture. Record a separate reversal from
the new brightness back to the original value. Note the exact displayed
before/after values and UTC times in each capture's metadata. Do not use a
capture from opening the lighting page alone as brightness evidence: capture
`004` shows the app sent two writes simply by opening it. Keep unrelated
settings untouched. Captures only observe traffic the official app chooses to
send; no browser-originated report or manual HID write is part of this step.

## Backup handling

`backup/` contains validated `sinowisp` firmware, bootloader, and full-flash
recovery reads. See `backup/README.md` for the authorized read-side effect,
commands, validation, and hashes. No separate configuration storage read
section or configuration restore command is known. Future configuration exports
must record source fingerprint, firmware version, format version, integrity
hash, and known coverage/omissions. Firmware dumps and configuration backups
are distinct artifacts; do not assume interchangeability.
