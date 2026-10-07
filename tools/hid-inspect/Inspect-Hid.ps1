#requires -Version 5.1
<#
.SYNOPSIS
Enumerates Windows HID metadata without reading or sending HID reports.
.EXAMPLE
.\Inspect-Hid.ps1 -OutputPath .\inventory.json
.EXAMPLE
.\Inspect-Hid.ps1 -VendorId 0x258A -ProductId 0x010C
#>
[CmdletBinding()]
param(
    [ValidateRange(-1, 65535)][int]$VendorId = -1,
    [ValidateRange(-1, 65535)][int]$ProductId = -1,
    [string]$OutputPath
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
if ([Environment]::OSVersion.Platform -ne [PlatformID]::Win32NT) {
    throw 'This tool requires Windows and its native HID/SetupAPI libraries.'
}

# Fail before enumeration if the requested evidence path already exists.
$inventoryPath = $null
if ($OutputPath) {
    $inventoryPath = $ExecutionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($OutputPath)
    if (Test-Path -LiteralPath $inventoryPath) { throw "Refusing to overwrite evidence: $inventoryPath" }
    if (-not (Test-Path -LiteralPath (Split-Path -Parent $inventoryPath) -PathType Container)) {
        throw 'Output directory must already exist.'
    }
}
if (-not ('Hi75.Inventory.Native' -as [type])) {
    Add-Type -Path (Join-Path $PSScriptRoot 'NativeHid.cs')
}
$inventory = [Hi75.Inventory.Native]::Collect($VendorId, $ProductId)
$inventory['schemaVersion'] = 1
$inventory['toolVersion'] = '0.1.0'
$inventory['collectedAtUtc'] = [DateTime]::UtcNow.ToString('o')
$inventory['osVersion'] = [Environment]::OSVersion.VersionString
$inventory['powershellVersion'] = $PSVersionTable.PSVersion.ToString()
$inventory['processBits'] = [IntPtr]::Size * 8
$inventory['sourceHashes'] = @(
    'Inspect-Hid.ps1', 'NativeHid.cs' | ForEach-Object {
        $sourceHash = Get-FileHash -Algorithm SHA256 -LiteralPath (Join-Path $PSScriptRoot $_)
        [ordered]@{ file = $_; sha256 = $sourceHash.Hash }
    }
)
$inventory['safety'] = 'Metadata only; zero desired access; no HID report reads/writes, firmware access, resets, or driver changes.'
$inventory['limitations'] = @(
    'VID/PID matches are candidates only, not model identification or write authorization.',
    'Each HID entry is a Windows top-level collection, not necessarily a separate USB interface.',
    'Report lengths are Windows maximum buffers per type/collection, including the report-ID slot (zero for unnumbered reports).',
    'Report IDs come from exposed button/value capabilities; padding-only definitions may not be represented.',
    'Exact per-ID wire lengths and raw HID report descriptors are not obtained by this tool.',
    'USB PnP nodes/MI hints are not a complete USB interface/endpoint descriptor export; use USBView.',
    'Null or failed queries mean unavailable, not absent. See per-device errors.',
    'Strings and paths may contain serial numbers or other identifying information.'
)
$json = ConvertTo-Json -InputObject $inventory -Depth 32
if ($inventoryPath) {
    # CreateNew also prevents a race from overwriting an existing capture.
    $stream = [IO.File]::Open($inventoryPath, [IO.FileMode]::CreateNew, [IO.FileAccess]::Write)
    try {
        $bytes = [Text.UTF8Encoding]::new($false).GetBytes($json + [Environment]::NewLine)
        $stream.Write($bytes, 0, $bytes.Length)
    } finally { $stream.Dispose() }
    Write-Verbose "Saved inventory: $inventoryPath"
}
# Standard output is JSON only, suitable for copying or ConvertFrom-Json.
$json
