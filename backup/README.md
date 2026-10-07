# Hi75 recovery backup

## Completed recovery read — 2026-09-19

Three unmodified binary ISP payloads were acquired using the official installed
**sinowisp 2.1.0**, preset **`leobog-hi75`**, in:

[`dumps/20260919T085231Z/`](dumps/20260919T085231Z/)

The user explicitly authorized the normal upstream read cycle, including its
`enable_firmware()` side effect and required setup/exit. Only the three normal
read operations were issued. No `sinowisp write`, erase, manual device writes,
configuration edits, experimental commands, image conversion, or write-back
recovery tests were performed.

All reads returned exit code 0. All files exist and match the preset sizes.
None is empty, entirely `00`, or entirely `FF`. The full dump equals the
application dump followed by the bootloader dump, byte for byte (zero differing
bytes). After the normal reboot, the same eight stock-mode HID collection paths
were present. This is an enumeration check, not a functional keyboard test.

## Dumps, sizes, and hashes

Sizes are actual binary file lengths, not Intel HEX text sizes. The supported
`--format bin` option was used to preserve upstream output directly and make
size validation unambiguous. No bytes were added, removed, or rewritten.

| File | Region | Actual bytes | Preset bytes | All 00 / all FF |
| --- | --- | ---: | ---: | --- |
| [firmware.bin](dumps/20260919T085231Z/firmware.bin) | Application firmware | 61440 | 61440 | No / No |
| [bootloader.bin](dumps/20260919T085231Z/bootloader.bin) | Bootloader | 4096 | 4096 | No / No |
| [full.bin](dumps/20260919T085231Z/full.bin) | Full preset flash | 65536 | 65536 | No / No |

SHA-256:

```text
31ee5b474b06b5bd26f32e15e379ce8c3251913b57dfebc3194a7c4dbdcc7ad0  dumps/20260919T085231Z/firmware.bin
0f8dc851d7a6eaedfba8aae7bda1ae2739f6d55fbe85f78f4c2261875f2edc6f  dumps/20260919T085231Z/bootloader.bin
60db40800015ae902b2dea89c9d04713342f244195426e6ab6d544ec74699f3a  dumps/20260919T085231Z/full.bin
```

Optional MD5 comparison values (SHA-256 remains the integrity standard):

| File | MD5 |
| --- | --- |
| firmware.bin | `ccb4f3e48976c62c0607bf01c5aef473` |
| bootloader.bin | `3e0ebd0c440af5236d7ff8872343f85d` |
| full.bin | `2dd88734768914b1a0db9513a51b85e9` |

The bootloader MD5 matches the Hi75 entry in the locally preserved upstream
[source README](audit/sinowisp-v2.1.0/source/README.md). This supports bootloader
consistency, not unique model identification or proof of restoration. A different
user's application MD5 is not an acceptance criterion.

[validation.json](dumps/20260919T085231Z/validation.json) records exact counts of
`00` and `FF` bytes, sizes, hashes, exit status, and cross-dump comparison.

## Tool, preset, and identity verification

The preflight re-ran the installed executable's version/help/list commands. Its
hash still matched the official release previously downloaded and audited.

| Item | Verified value / evidence |
| --- | --- |
| Runtime version | `sinowisp 2.1.0`; [version output](dumps/20260919T085231Z/version.txt) |
| Executable | `audit/sinowisp-v2.1.0/sinowisp.exe` |
| Executable bytes | 1522176 |
| Executable SHA-256 | `321910b82185567afb1bbb9520e08ccecc009382fb8c8d179096b9f54f6997d7` |
| Release | [v2.1.0](https://github.com/carlossless/sinowisp/releases/tag/v2.1.0) |
| Pinned source commit | `2e292356a74fd569255b904dd8445106a2481e43` |
| Windows archive SHA-256 | `63180e0d35fdd4e68834723fe2abec796e03cfdd1a168dc7745da83672ef71ab` |
| Device preset | `leobog-hi75`, explicitly listed in [read help](dumps/20260919T085231Z/read-help.txt) |
| Available sections | `firmware`, `bootloader`, `full` |
| Firmware / bootloader / page bytes | 61440 / 4096 / 2048 |
| Preset ISP interface / report ID | 1 / 5 |
| USB enumeration | One physical `258A:010C` candidate, eight HID collections |
| HID manufacturer / product | `BY Tech` / `Gaming Keyboard` |
| HID device version attribute | `0x0500`; not established as firmware version |
| Serial | Getter unavailable; no unique serial established |
| Physical model | Original wired LEOBOG Hi75, identified by the user |

Geometry and page size are derived from the pinned preset source because the
CLI does not dynamically print or discover them. [preset.json](dumps/20260919T085231Z/preset.json)
records the values and source hashes. The installed help exposes all preset
names and three read sections; the read logs independently confirm output sizes.
No geometry, VID/PID, platform, interface, or report-ID override was supplied to
any read. VID/PID options were used only to filter metadata listings.

The USB strings/preset do not independently distinguish all revisions or the
Hi75c Pro. Strong configurator fingerprinting is still required before enabling
configuration writes. The user's model identification and current single-device
inventory were used for this expressly authorized backup.

## Exact commands and output

From `hi75-web`, the equivalent exact arguments are:

```powershell
$sinoExe = '.\backup\audit\sinowisp-v2.1.0\sinowisp.exe'
$runDir = '.\backup\dumps\20260919T085231Z'
& $sinoExe --version
& $sinoExe --help
& $sinoExe read --help
& $sinoExe list --help
& $sinoExe list --vendor_id 0x258A --product_id 0x010C
& $sinoExe read -d leobog-hi75 -s firmware --format bin "$runDir\firmware.bin"
& $sinoExe read -d leobog-hi75 -s bootloader --format bin "$runDir\bootloader.bin"
& $sinoExe read -d leobog-hi75 -s full --format bin "$runDir\full.bin"
& $sinoExe list --vendor_id 0x258A --product_id 0x010C
```

These are a record, not an instruction to overwrite the existing files.
The actual process invocations used absolute paths. `commands.json`, the three
`*-command.json` files, and `postflight-command.json` in the run directory retain
those exact argument arrays, UTC times, exit codes, and output-log filenames.
Full stdout/stderr, including each upstream MD5 and success message, are retained
in `firmware-read.txt`, `bootloader-read.txt`, and `full-read.txt`.

The native inventory tool additionally saved `windows-device-before.json` and
`windows-device-after.json` with tool hashes and descriptor-capability metadata.
`device-before.txt` and `device-after.txt` retain sinowisp's listings. Descriptor
representations from its Windows backend are not assumed to be raw on-wire bytes.

The reads were invoked sequentially with [Read-RecoverySection.ps1](Read-RecoverySection.ps1),
which pins the executable hash, restricts operations to the three preset read
sections, logs the invocation before execution, and refuses to overwrite existing
dumps/logs. It has no erase or write mode. Its presence does not authorize future
unrelated device operations.

## Scope and recovery limitations

> No separate EEPROM/configuration read section is exposed by this version of sinowisp.

No alternative method was invented or attempted. `full` covers the preset's
firmware-plus-bootloader range; coverage of any separate data flash, EEPROM,
option/security bytes, or all persistent keyboard settings is not established.

Normal upstream reads can set the firmware-enable LJMP opcode at
`firmware_size - 5` (`0xEFFB` for this preset). That specific side effect was
explicitly authorized. Reads also enter ISP mode as needed and reboot afterward.
It is unknown whether the opcode byte actually changed on this unit.

The upstream ISP read representation remaps reset-vector bytes. These files are
**ISP-format payloads**, not asserted to be byte-exact physical flash images.
They remain untouched. No conversion, disassembly, flashing, or restore test
was performed. Integrity and consistency checks cannot guarantee restoration.

## File-only verification and preservation

From `hi75-web`:

```powershell
.\backup\Validate-Recovery.ps1 -RunDirectory .\backup\dumps\20260919T085231Z
.\backup\Update-BackupManifest.ps1
```

These scripts access local files only. Validation refreshes `validation.json`;
regenerate the manifest afterward if validation metadata changes.

[SHA256SUMS](SHA256SUMS) uses conventional lowercase SHA-256, two spaces, and a
path relative to `backup/`. It includes only actual recovery dumps and directly
relevant per-run metadata. Downloaded executables, archives, upstream source,
and the earlier tool audit are excluded. [FILE-INVENTORY.json](FILE-INVENTORY.json)
records exact sizes, hashes, and separate dump/metadata categories.

Preserve the original run directory and manifests together. Keep an independent
offline copy; none has been made automatically. Dump folders are Git-ignored to
avoid publishing firmware and device identifiers unintentionally.

The earlier no-read audit is retained at
[audit/preauthorization-README.md](audit/preauthorization-README.md), with its old
manifests. It describes the earlier authorization state and is superseded by this
completed, explicitly authorized read. It is excluded from recovery SHA256SUMS.
