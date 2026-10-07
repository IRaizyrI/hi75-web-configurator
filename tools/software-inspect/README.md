# Static analysis of the supplied LEOBOG ONE application

`inspect_pe.py` inventories PE imports and selected strings with pefile and
Capstone. Its linear disassembly is a search index, not authoritative function
recovery. `ExportHidPaths.java` is a Ghidra headless script that decompiles
selected profile and HID paths and every analyzed direct caller of the
`HidD_SetFeature` / `HidD_GetFeature` thunks. Neither tool executes `OemDrv.exe`.
`extract_vk_hid_table.py` reads the fixed 115-pair lookup table referenced by
Ghidra function `0x4786A0` from this exact executable version and produces a
JSON evidence artifact; it rejects a different executable hash.

The analyzed source is `../../../LEOBOG ONE/OemDrv.exe` (SHA-256
`635587cf6334346ab9932479d309cfe5f395c45d77c698b0143d28bf5b661ee0`).
The source executable remains in the user-supplied directory; the project docs
record findings without redistributing it.

## Local Ghidra toolchain (2026-09-22)

- Official [Ghidra 12.1.3 release](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1.3_build):
  `ghidra_12.1.3_PUBLIC_20260817.zip`, SHA-256
  `93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54`.
- Eclipse Adoptium Temurin JDK 21.0.12.1+1 Windows x64 archive:
  `OpenJDK21U-jdk_x64_windows_hotspot_21.0.12.1_1.zip`, SHA-256
  `f9d6e191ab098c0d416e7d588a24420a8621cd2f4720dab2459b8b7b2d2d8b4e`.
  The version was selected from the [Adoptium API](https://api.adoptium.net/v3/assets/latest/21/hotspot?architecture=x64&image_type=jdk&os=windows&vendor=eclipse).
- Archives and extracted tools are under the workspace-level `local-tools/`; Ghidra
  analysis output is under `hi75-web/analysis/ghidra-oemdrv-635587cf/`.

The analyzed Ghidra project is `hi75-web/analysis/ghidra-projects/Hi75App`.
This Ghidra release's source-script loader fails on this host, including for a
bundled Ghidra script. We compiled `ExportHidPaths.java` against the installed
Ghidra JARs with JDK 21 and use the working class script at
`analysis/ghidra-oemdrv-635587cf/compiled-scripts-v2/ExportHidPaths.class`.
The Python/PyGhidra experiments in this directory did not produce a working
export and are not used for the documented findings.

To repeat a decompiler export from the workspace root in PowerShell, set
`JAVA_HOME` to `local-tools/jdk21/jdk-21.0.12.1+1`, `APPDATA` to
`local-tools/appdata-fresh`, and `LOCALAPPDATA` to
`local-tools/localappdata-fresh` (use absolute paths). Run Ghidra's
`support/analyzeHeadless.bat` against the saved project with `-process OemDrv.exe
-noanalysis -scriptPath <absolute compiled-scripts-v2 path> -postScript
ExportHidPaths.class <new absolute output directory> [function addresses]`.
The script refuses to overwrite `hid-paths.txt`, so use a new output directory
for each run. The saved `followup-*` exports include the exact requested
function addresses and decompiled output.

See `../../docs/app-disassembly.md` for interpreted findings, and
`../../docs/protocol.md` for the source of truth on observed device traffic.
