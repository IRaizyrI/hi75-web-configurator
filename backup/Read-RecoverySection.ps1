#requires -Version 5.1
# Runs only a normal upstream read. Its enable_firmware side effect is authorized
# for this recovery task; this does not authorize any erase, write, or restoration.
[CmdletBinding()]
param(
    [Parameter(Mandatory=$true)][ValidateSet('firmware','bootloader','full')][string]$Section,
    [Parameter(Mandatory=$true)][string]$RunDirectory
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$runPath = (Resolve-Path -LiteralPath $RunDirectory).Path
$dumpRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot 'dumps')) + '\'
if (-not $runPath.StartsWith($dumpRoot, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Run directory must be beneath backup/dumps/.'
}
$sinoExe = Join-Path $PSScriptRoot 'audit\sinowisp-v2.1.0\sinowisp.exe'
$toolHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $sinoExe).Hash
if ($toolHash -ne '321910B82185567AFB1BBB9520E08CCECC009382FB8C8D179096B9F54F6997D7') {
    throw 'Tool differs from the reviewed official executable.'
}
$dumpPath = Join-Path $runPath ($Section + '.bin')
$logPath = Join-Path $runPath ($Section + '-read.txt')
$recordPath = Join-Path $runPath ($Section + '-command.json')
foreach ($path in @($dumpPath, $logPath, $recordPath)) {
    if (Test-Path -LiteralPath $path) { throw "Refusing to overwrite evidence: $path" }
}
$cliArgs = @('read','-d','leobog-hi75','-s',$Section,'--format','bin',$dumpPath)
$record = [ordered]@{
    executable=$sinoExe; executableSha256=$toolHash.ToLowerInvariant()
    arguments=$cliArgs; startedAtUtc=[DateTime]::UtcNow.ToString('o')
    endedAtUtc=$null; exitCode=$null; outputFile=[IO.Path]::GetFileName($logPath)
    outputFormat='bin'; section=$Section
    authorization='User explicitly authorized normal upstream read, including enable_firmware and required setup/exit only.'
    completed=$false
}
$record | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $recordPath -Encoding utf8
try {
    # Capture native stderr as well as stdout, including any upstream warnings.
    # Windows PowerShell treats native stderr as ErrorRecords; Continue retains it.
    $ErrorActionPreference = 'Continue'
    & $sinoExe @cliArgs 2>&1 | Tee-Object -FilePath $logPath
    $record.exitCode = $LASTEXITCODE
    $ErrorActionPreference = 'Stop'
    $record.completed = $record.exitCode -eq 0
} finally {
    $record.endedAtUtc = [DateTime]::UtcNow.ToString('o')
    $record | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $recordPath -Encoding utf8
}
if (-not $record.completed) { throw "Read failed; retain logs and any partial file. Exit: $($record.exitCode)" }
if (-not (Test-Path -LiteralPath $dumpPath -PathType Leaf)) { throw 'Read returned success without a dump file.' }
Get-Item -LiteralPath $dumpPath | Select-Object Name,Length
Get-FileHash -Algorithm SHA256 -LiteralPath $dumpPath
