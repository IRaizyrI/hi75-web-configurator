#requires -Version 5.1
# File-only hashing. Never invokes sinowisp or accesses a device.
[CmdletBinding()]
param()
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$backupRoot = [IO.Path]::GetFullPath($PSScriptRoot).TrimEnd('\', '/')
$backupPrefix = $backupRoot + [IO.Path]::DirectorySeparatorChar
$entries = @(
    # Only actual recovery runs: excludes downloaded tools, source trees and
    # the historical audit-only manifest. Run folders contain dumps + metadata.
    foreach ($category in @('dumps')) {
        $categoryPath = Join-Path $backupRoot $category
        if (-not (Test-Path -LiteralPath $categoryPath -PathType Container)) { continue }
        # Do not follow links out of the backup directory.
        if ((Get-Item -LiteralPath $categoryPath).Attributes -band [IO.FileAttributes]::ReparsePoint) {
            throw "Refusing linked evidence directory: $categoryPath"
        }
        $pending = [Collections.Generic.Queue[string]]::new()
        $pending.Enqueue($categoryPath)
        while ($pending.Count -gt 0) {
            foreach ($item in Get-ChildItem -LiteralPath $pending.Dequeue() -Force) {
                if ($item.Attributes -band [IO.FileAttributes]::ReparsePoint) {
                    throw "Refusing linked evidence entry: $($item.FullName)"
                }
                if ($item.PSIsContainer) { $pending.Enqueue($item.FullName); continue }
                if (-not $item.FullName.StartsWith($backupPrefix, [StringComparison]::OrdinalIgnoreCase)) {
                    throw 'Evidence escaped the backup directory.'
                }
                $relative = $item.FullName.Substring($backupPrefix.Length).Replace('\', '/')
                if ($relative -match '[\r\n]') { throw 'Unsupported newline in evidence filename.' }
                [pscustomobject][ordered]@{
                    category = if ($item.Extension -in @('.bin','.hex','.ihx')) { 'recovery_dump' } else { 'recovery_metadata' }
                    path = $relative
                    bytes = $item.Length
                    sha256 = (Get-FileHash -Algorithm SHA256 -LiteralPath $item.FullName).Hash.ToLowerInvariant()
                }
            }
        }
    }
) | Sort-Object path
$entries = @($entries)
$lines = @($entries | ForEach-Object { '{0}  {1}' -f $_.sha256, $_.path })
$utf8 = [Text.UTF8Encoding]::new($false)
$manifest = if ($lines.Count) { ($lines -join "`n") + "`n" } else { '' }
[IO.File]::WriteAllText((Join-Path $backupRoot 'SHA256SUMS'), $manifest, $utf8)
$inventory = [ordered]@{
    schemaVersion = 2
    generatedAtUtc = [DateTime]::UtcNow.ToString('o')
    dumpFileCount = @($entries | Where-Object category -EQ 'recovery_dump').Count
    metadataFileCount = @($entries | Where-Object category -EQ 'recovery_metadata').Count
    note = 'Only recovery runs are included, not the tool audit. A hash does not prove restoration.'
    files = $entries
}
[IO.File]::WriteAllText((Join-Path $backupRoot 'FILE-INVENTORY.json'), ($inventory | ConvertTo-Json -Depth 8) + "`n", $utf8)
Write-Output ("Hashed {0} recovery dumps and {1} directly relevant metadata files." -f $inventory.dumpFileCount, $inventory.metadataFileCount)
