#requires -Version 5.1
# Offline only: reads local dump bytes. Does not invoke sinowisp or access HID.
[CmdletBinding()]
param([Parameter(Mandatory=$true)][string]$RunDirectory)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$runPath = (Resolve-Path -LiteralPath $RunDirectory).Path
$preset = Get-Content -Raw -LiteralPath (Join-Path $runPath 'preset.json') | ConvertFrom-Json
$regions = @(
    @{Name='firmware'; Expected=[int]$preset.firmwareBytes},
    @{Name='bootloader'; Expected=[int]$preset.bootloaderBytes},
    @{Name='full'; Expected=[int]$preset.fullBytes}
)
$buffers = @{}
$results = @(
    foreach ($region in $regions) {
        $path = Join-Path $runPath ($region.Name + '.bin')
        $record = Get-Content -Raw -LiteralPath (Join-Path $runPath ($region.Name + '-command.json')) | ConvertFrom-Json
        if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { throw "Missing dump: $path" }
        $bytes = [IO.File]::ReadAllBytes($path)
        $buffers[$region.Name] = $bytes
        $zeroCount = 0; $ffCount = 0
        foreach ($value in $bytes) {
            if ($value -eq 0) { $zeroCount++ }
            if ($value -eq 255) { $ffCount++ }
        }
        [ordered]@{
            file=$region.Name+'.bin'; section=$region.Name; format='binary ISP payload'
            exists=$true; bytes=$bytes.Length; expectedPresetBytes=$region.Expected
            expectedSizeMatches=($bytes.Length -eq $region.Expected)
            readExitCode=$record.exitCode; readCompleted=$record.completed
            zeroByteCount=$zeroCount; ffByteCount=$ffCount
            empty=($bytes.Length -eq 0)
            all00=($bytes.Length -gt 0 -and $zeroCount -eq $bytes.Length)
            allFF=($bytes.Length -gt 0 -and $ffCount -eq $bytes.Length)
            sha256=(Get-FileHash -Algorithm SHA256 -LiteralPath $path).Hash.ToLowerInvariant()
            md5=(Get-FileHash -Algorithm MD5 -LiteralPath $path).Hash.ToLowerInvariant()
        }
    }
)
$differences = 0
$firstOffsets = [Collections.Generic.List[int]]::new()
$lengthsAllowComparison = $buffers.full.Length -eq ($buffers.firmware.Length + $buffers.bootloader.Length)
if ($lengthsAllowComparison) {
    for ($i = 0; $i -lt $buffers.full.Length; $i++) {
        $expectedByte = if ($i -lt $buffers.firmware.Length) { $buffers.firmware[$i] } else { $buffers.bootloader[$i - $buffers.firmware.Length] }
        if ($buffers.full[$i] -ne $expectedByte) {
            $differences++
            if ($firstOffsets.Count -lt 64) { $firstOffsets.Add($i) }
        }
    }
}
$validation = [ordered]@{
    validatedAtUtc=[DateTime]::UtcNow.ToString('o')
    method='Local byte scan, Get-FileHash SHA256/MD5, and full-versus-concatenated-regions byte comparison; originals unchanged.'
    dumps=$results
    comparison=[ordered]@{
        lengthsAllowComparison=$lengthsAllowComparison
        fullEqualsFirmwarePlusBootloader=($lengthsAllowComparison -and $differences -eq 0)
        differingByteCount= if ($lengthsAllowComparison) { $differences } else { $null }
        firstDifferingOffsetsInFull=$firstOffsets.ToArray()
    }
    restorationTested=$false
    note='Integrity and consistency checks do not prove recovery. ISP payload layout may differ from physical flash.'
}
$json = $validation | ConvertTo-Json -Depth 8
$json | Set-Content -LiteralPath (Join-Path $runPath 'validation.json') -Encoding utf8
$json
