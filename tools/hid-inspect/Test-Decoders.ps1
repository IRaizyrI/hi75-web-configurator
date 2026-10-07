#requires -Version 5.1
# Synthetic fixtures only. This script does not enumerate or open any devices.
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
if (-not ('Hi75.Inventory.Native' -as [type])) {
    Add-Type -Path (Join-Path $PSScriptRoot 'NativeHid.cs')
}
function Assert-Equal($Actual, $Expected, [string]$Label) {
    if ($Actual -ne $Expected) { throw "$Label expected '$Expected', got '$Actual'" }
}
function Set-U16([byte[]]$Buffer, [int]$Offset, [uint16]$Value) {
    [BitConverter]::GetBytes($Value).CopyTo($Buffer, $Offset)
}
# A synthetic vendor-page value array. These are NOT Hi75 descriptor bytes.
$value = New-Object byte[] 72
Set-U16 $value 0 0xFF42
$value[2] = 7
Set-U16 $value 6 3
Set-U16 $value 8 0x1234
Set-U16 $value 10 0xFF43
$value[15] = 1
$value[16] = 1
Set-U16 $value 18 8
Set-U16 $value 20 37
[BitConverter]::GetBytes([int]-127).CopyTo($value, 40)
[BitConverter]::GetBytes([int]255).CopyTo($value, 44)
Set-U16 $value 56 0xABCD
Set-U16 $value 68 91
$decoded = [Hi75.Inventory.Native]::DecodeCapability($value, $true)
Assert-Equal $decoded['usagePage'] '0xFF42' 'Value usage page'
Assert-Equal $decoded['reportId'] 7 'Report ID'
Assert-Equal $decoded['linkCollectionIndex'] 3 'Link index'
Assert-Equal $decoded['linkUsageId'] '0x1234' 'Link usage'
Assert-Equal $decoded['linkUsagePage'] '0xFF43' 'Link usage page'
Assert-Equal $decoded['bitSize'] 8 'Bit size'
Assert-Equal $decoded['reportCount'] 37 'Report count'
Assert-Equal $decoded['logicalMin'] -127 'Signed logical minimum'
Assert-Equal $decoded['logicalMax'] 255 'Logical maximum'
Assert-Equal $decoded['usageId'] '0xABCD' 'Single usage'
Assert-Equal $decoded['usageMin'] $null 'No invented usage range'
Assert-Equal $decoded['dataIndexOrMin'] 91 'Data index'

$button = New-Object byte[] 72
Set-U16 $button 0 9
$button[12] = 1
$button[13] = 1
$button[14] = 1
Set-U16 $button 56 1
Set-U16 $button 58 16
Set-U16 $button 60 2
Set-U16 $button 62 4
Set-U16 $button 64 6
Set-U16 $button 66 8
Set-U16 $button 68 10
Set-U16 $button 70 25
$decoded = [Hi75.Inventory.Native]::DecodeCapability($button, $false)
Assert-Equal $decoded['usageMin'] '0x0001' 'Button range minimum'
Assert-Equal $decoded['usageMax'] '0x0010' 'Button range maximum'
Assert-Equal $decoded['usageId'] $null 'No invented single usage'
Assert-Equal $decoded['reportId'] 0 'Unnumbered report ID slot'
Assert-Equal $decoded['stringMax'] 4 'String range'
Assert-Equal $decoded['designatorMax'] 8 'Designator range'
Assert-Equal $decoded['dataIndexMax'] 25 'Data range'
Assert-Equal $decoded.ContainsKey('bitSize') $false 'No fabricated button bit size'

foreach ($stride in @(20, 24)) {
    $node = New-Object byte[] $stride
    Set-U16 $node 0 0x1234
    Set-U16 $node 2 0xFF42
    Set-U16 $node 4 2
    Set-U16 $node 6 3
    Set-U16 $node 8 4
    Set-U16 $node 10 5
    [BitConverter]::GetBytes([uint32]0x101).CopyTo($node, 12)
    $decoded = [Hi75.Inventory.Native]::DecodeLinkNode($node)
    Assert-Equal $decoded['usageId'] '0x1234' "Node usage ($stride-byte ABI)"
    Assert-Equal $decoded['usagePage'] '0xFF42' 'Node usage page'
    Assert-Equal $decoded['parentIndex'] 2 'Node parent'
    Assert-Equal $decoded['numberOfChildren'] 3 'Node children'
    Assert-Equal $decoded['nextSiblingIndex'] 4 'Node sibling'
    Assert-Equal $decoded['firstChildIndex'] 5 'Node child'
    Assert-Equal $decoded['collectionType'] 1 'Node type bits'
    Assert-Equal $decoded['isAlias'] $true 'Node alias bit'
}
$rejected = $false
try { [Hi75.Inventory.Native]::DecodeCapability((New-Object byte[] 71), $true) | Out-Null }
catch { $rejected = $true }
Assert-Equal $rejected $true 'Reject truncated capability'

# Guard against accidentally adding report I/O imports or read/write access.
$source = Get-Content -Raw -LiteralPath (Join-Path $PSScriptRoot 'NativeHid.cs')
if ($source -match '\b(HidD_Set\w*|HidD_GetFeature|HidD_GetInputReport|ReadFile|WriteFile|DeviceIoControl)\s*\(') {
    throw 'Unexpected device report I/O or generic IOCTL entry point.'
}
if ($source -notmatch 'CreateFileW\(path, 0, 3, IntPtr.Zero, 3, 0, IntPtr.Zero\)') {
    throw 'Review device open access: expected zero desired access.'
}
'Synthetic decoder fixtures and report-I/O guards passed. No devices accessed.'
