# Hi75 recovery preservation record

## Result: no firmware dumps acquired

Audit date: **2026-09-19**. No erase, flash write, ISP-entry, firmware-enable,
reboot, or actual flash-read operation was issued. Only help/version and the
metadata/descriptor `list` operation were run against the official tool.

**The current sinowisp CLI cannot meet this task's strict no-write constraint.**
Its `read_cycle` unconditionally calls `enable_firmware()` before selecting any
read section. That operation is documented to set the firmware-enable LJMP byte
at `firmware_size - 5`, which is `0xEFFB` for the Hi75 preset. Even a bootloader-only
read follows this path. An already-set byte might remain unchanged, but that is
not established for this unit and the command is still sent.

`--reboot false` only suppresses the reboot after reading. It does **not** skip
firmware enable or prevent the initial switch to ISP mode. There is no CLI
read-only/no-enable option in the inspected release. No patched tool, guessed
region, alternate platform, or direct-packet workaround was attempted.

Evidence:

- [Pinned upstream read cycle](https://github.com/carlossless/sinowisp/blob/2e292356a74fd569255b904dd8445106a2481e43/src/flasher.rs#L16),
  also preserved in [source/flasher.rs](audit/sinowisp-v2.1.0/source/flasher.rs).
- [Firmware-enable implementation](https://github.com/carlossless/sinowisp/blob/2e292356a74fd569255b904dd8445106a2481e43/src/isp_device.rs#L177),
  also in [source/isp_device.rs](audit/sinowisp-v2.1.0/source/isp_device.rs).
- [Upstream read caveats](https://github.com/carlossless/sinowisp/tree/v2.1.0#reading),
  also in [source/README.md](audit/sinowisp-v2.1.0/source/README.md).

This folder currently preserves **audit evidence, not a recovery image**.
`SHA256SUMS` hashes that evidence; it must not be mistaken for proof that firmware
or configuration is backed up.

## Tool provenance and version

No executable was found by `Get-Command sinowisp*` or targeted file searches in
the workspace, user Cargo bin, Downloads, Desktop, and Scoop apps. One unrelated
Desktop subtree denied enumeration; this is not an exhaustive claim that no
copy exists anywhere on the machine.

Downloaded a local, pinned copy of the current official release for inspection;
no global installation or PATH change was made.

| Item | Value |
| --- | --- |
| Runtime version output | `sinowisp 2.1.0` |
| Official release | [v2.1.0](https://github.com/carlossless/sinowisp/releases/tag/v2.1.0) |
| Release publication | 2026-09-04 18:32:01 UTC |
| Source commit | `2e292356a74fd569255b904dd8445106a2481e43` |
| Windows asset | `sinowisp-x86_64-pc-windows-msvc-v2.1.0.tar.gz` |
| Archive bytes | 610947 |
| Archive SHA-256 | `63180e0d35fdd4e68834723fe2abec796e03cfdd1a168dc7745da83672ef71ab` |
| Executable SHA-256 | `321910b82185567afb1bbb9520e08ccecc009382fb8c8d179096b9f54f6997d7` |
| Executable bytes | 1522176 |
| Executable location | `audit/sinowisp-v2.1.0/sinowisp.exe` |

The archive hash was compared with the official release API's asset digest
before extraction. This is an integrity check, not independent publisher-signature
verification. [release.json](audit/sinowisp-v2.1.0/release.json) preserves that
metadata. Source files were retrieved from the exact commit above and retain
the upstream MIT [LICENSE](audit/sinowisp-v2.1.0/source/LICENSE).

## Device identifier and detected candidate

The executable's [read help](audit/sinowisp-v2.1.0/read-help.txt) explicitly lists
**`-d leobog-hi75`**. This is the original model's preset; `leobog-hi75c-pro` is a
separate name. [device_spec.rs](audit/sinowisp-v2.1.0/source/device_spec.rs) maps
both names to the same VID/PID and base platform parameters, further demonstrating
that preset matching is not exact-model identification.

The metadata-only [list result](audit/sinowisp-v2.1.0/list-candidate.txt) reports:

- VID/PID: `258A:010C`.
- Manufacturer/product: `BY Tech` / `Gaming Keyboard`.
- Interface 0: keyboard collection; interface 1: seven collections.
- Vendor-page collections include feature report IDs 5 and 6.
- Physical original-Hi75 identity and hardware/firmware revision: **unconfirmed**.
- Bootloader identity: **not probed**. Serial: unavailable in the earlier Windows
  inventory; this listing does not establish a serial number.

The list command did not enter ISP mode. Its Windows backend returns descriptor
data per collection; do not assume these representations are original on-wire
descriptor bytes without establishing backend provenance. Full physical
association/fingerprint work remains in [docs/usb.md](../docs/usb.md).

## Available regions and backup status

These sizes/ranges are **preset expectations from source**, not measurements of
this keyboard. Binary output is selected in the reference commands so a future
file's size can be compared directly; Intel HEX text length would differ.

| Region | Exposed CLI section | Preset address range | Expected binary bytes | Actual dump bytes | SHA-256 / result |
| --- | --- | --- | ---: | --- | --- |
| Application firmware | `firmware` (default) | `0x0000–0xEFFF` | 61440 | N/A: no file | Not acquired: mandatory enable side effect |
| Bootloader | `bootloader` | `0xF000–0xFFFF` | 4096 | N/A: no file | Not acquired: same enable side effect |
| Full preset flash | `full` | `0x0000–0xFFFF` | 65536 | N/A: no file | Not acquired: same enable side effect |
| Separate configuration / EEPROM-like region | None exposed | Unknown | Unknown | N/A: no file | No dedicated supported read operation found |

The Hi75 preset inherits a 2048-byte page size, interface 1, and ISP report ID 5.
These are upstream tool settings, not permission to use them as our stock
configuration protocol. `full` means firmware plus bootloader for the preset;
it does not establish coverage of separate EEPROM, data flash, option/security
bytes, or all persistent settings.

Upstream also documents reset-vector byte remapping in ISP reads. Thus even a
successful future `full` dump must be labeled an **ISP-format payload**, not
claimed to be a byte-exact physical flash image. Keep it unchanged. No offline
conversion or restore validation was performed here.

## Exact sinowisp commands executed

All paths below are relative to `hi75-web`. The executable invocations are the
ones used in this audit; stdout/stderr were saved to the adjacent named logs.

```powershell
$sinoExe = '.\backup\audit\sinowisp-v2.1.0\sinowisp.exe'
& $sinoExe --version
& $sinoExe --help
& $sinoExe read --help
& $sinoExe list --help
& $sinoExe list --vendor_id 0x258A --product_id 0x010C
```

`read --help` exits after displaying syntax; it is not a device read. The help
output mentions other subcommands because it is an unmodified tool listing;
none of those operations was invoked. [commands.json](audit/sinowisp-v2.1.0/commands.json)
records executable arguments and corresponding logs. Listing exited with code 0.

Release/source acquisition used the GitHub release API, HTTPS downloads from
the URLs in `release.json`, `Get-FileHash -Algorithm SHA256`, `tar -tzf` to check
archive contents, then extraction of its sole `sinowisp.exe` entry. No keyboard
packets are involved in those file operations.

## Verified read syntax — blocked, not executed

These commented commands document the supported syntax requested for planning.
**They are not a runnable no-write procedure. Do not uncomment them under the
current constraints.** No future run is authorized by the existence of this file.

```powershell
# From hi75-web, only after the read-side-effect constraint and exact identity
# have been resolved in a separately reviewed procedure:
# & $sinoExe read -d leobog-hi75 -s firmware --format bin .\backup\dumps\hi75-application-isp.bin
# & $sinoExe read -d leobog-hi75 -s bootloader --format bin .\backup\dumps\hi75-bootloader-isp.bin
# & $sinoExe read -d leobog-hi75 -s full --format bin .\backup\dumps\hi75-full-isp.bin
```

No configuration/EEPROM command is provided because the current CLI exposes no
such section. Do not vary size/address/platform arguments to probe unknown memory.

## Conservative preservation workflow

1. Preserve the version, help, executable hash, source audit, and candidate
   inventory already saved here. Confirm the physical model/revision separately.
2. Apply the no-write check to the complete read path, including setup and exit.
   **This audit stops here for device operations.** No dumps are available, and
   recovery capability has not been established.
3. If a future reviewed operation is authorized, assign a new timestamped dump
   directory under `backup/dumps/`; record exact command, UTC time, exit status,
   tool hash/version, physical unit, and complete stdout/stderr for each run.
   Refuse to overwrite any existing dump. Preserve failed/partial output as
   explicitly invalid evidence, never as a usable backup.
4. For any future dump, record its actual byte count and SHA-256 immediately.
   Validate the expected region length and flag all-zero/all-`FF` contents;
   correct size alone does not prove validity. Independent matching reads, if
   separately authorized, provide repeatability evidence, not restoration proof.
5. Never alter originals to undo remapping or invent missing bytes. Any derived
   representation needs a separate filename, hash, and documented transformation.
   Keep another copy offline. Hash verification requires no device access.

## Hashes and sizes

Run this **file-only** helper from `hi75-web`:

```powershell
.\backup\Update-BackupManifest.ps1
```

It hashes every file under `backup/audit/` and any future file under
`backup/dumps/`, writing relative-path SHA-256 entries to [SHA256SUMS](SHA256SUMS)
and exact sizes/hashes/categories to [FILE-INVENTORY.json](FILE-INVENTORY.json).
It never calls sinowisp or any device API. Firmware/configuration dumps, if ever
obtained, must reside under `backup/dumps/` to enter this manifest. There are
currently **zero dump files**; every existing entry is categorized as audit
evidence. Generated manifests and this README are excluded to avoid self-hashes.

The helper ran successfully under Windows PowerShell 5.1. All 20 resulting
checksum entries and recorded byte counts were independently rechecked against
the files; zero dump files were present.

To verify a selected file independently:

```powershell
Get-FileHash -Algorithm SHA256 -LiteralPath .\backup\audit\sinowisp-v2.1.0\sinowisp.exe
Get-Item -LiteralPath .\backup\audit\sinowisp-v2.1.0\sinowisp.exe | Select-Object Length
```

Local binaries/archive and device-path-containing logs are Git-ignored. Do not
publish firmware or private unit identifiers automatically; a local backup and
an open-source code repository serve different purposes.
