# Read-only dump of the Hi75 configuration over the vendor feature report
# (report ID 6, 520 bytes). Sends only read commands 0x82/0x83/0x84/0x85/0x8A,
# the same ones the web page uses. Output: JSON in hi75-config-backup/1 shape.
param([string]$OutFile, [string]$RawChunk)  # RawChunk "cmd,arg,chunkIndex,length" (read commands only)

Add-Type -TypeDefinition @'
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;

public static class Hi75Read {
    [DllImport("hid.dll")] static extern void HidD_GetHidGuid(out Guid g);
    [DllImport("setupapi.dll", CharSet = CharSet.Unicode)] static extern IntPtr SetupDiGetClassDevsW(ref Guid g, IntPtr e, IntPtr p, uint f);
    [DllImport("setupapi.dll")] static extern bool SetupDiEnumDeviceInterfaces(IntPtr s, IntPtr i, ref Guid g, uint idx, ref IfData d);
    [DllImport("setupapi.dll", CharSet = CharSet.Unicode)] static extern bool SetupDiGetDeviceInterfaceDetailW(IntPtr s, ref IfData d, IntPtr det, uint sz, out uint req, IntPtr info);
    [DllImport("setupapi.dll")] static extern bool SetupDiDestroyDeviceInfoList(IntPtr s);
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)] static extern SafeFileHandle CreateFileW(string p, uint a, uint s, IntPtr sec, uint d, uint f, IntPtr t);
    [DllImport("hid.dll")] static extern bool HidD_GetPreparsedData(SafeFileHandle h, out IntPtr d);
    [DllImport("hid.dll")] static extern bool HidD_FreePreparsedData(IntPtr d);
    [DllImport("hid.dll")] static extern int HidP_GetCaps(IntPtr d, byte[] caps);
    [DllImport("hid.dll", SetLastError = true)] static extern bool HidD_SetFeature(SafeFileHandle h, byte[] b, int n);
    [DllImport("hid.dll", SetLastError = true)] static extern bool HidD_GetFeature(SafeFileHandle h, byte[] b, int n);
    [StructLayout(LayoutKind.Sequential)] struct IfData { public int cb; public Guid g; public int flags; public IntPtr r; }

    static SafeFileHandle Open() {
        Guid g; HidD_GetHidGuid(out g);
        IntPtr set = SetupDiGetClassDevsW(ref g, IntPtr.Zero, IntPtr.Zero, 0x12);
        try {
            for (uint i = 0; ; i++) {
                var d = new IfData(); d.cb = Marshal.SizeOf(d);
                if (!SetupDiEnumDeviceInterfaces(set, IntPtr.Zero, ref g, i, ref d)) break;
                uint req; SetupDiGetDeviceInterfaceDetailW(set, ref d, IntPtr.Zero, 0, out req, IntPtr.Zero);
                IntPtr buf = Marshal.AllocHGlobal((int)req);
                try {
                    Marshal.WriteInt32(buf, IntPtr.Size == 8 ? 8 : 6);
                    if (!SetupDiGetDeviceInterfaceDetailW(set, ref d, buf, req, out req, IntPtr.Zero)) continue;
                    string path = Marshal.PtrToStringUni(buf + 4);
                    if (path.IndexOf("vid_258a&pid_010c", StringComparison.OrdinalIgnoreCase) < 0) continue;
                    var h = CreateFileW(path, 0xC0000000, 3, IntPtr.Zero, 3, 0, IntPtr.Zero);
                    if (h.IsInvalid) continue;
                    IntPtr pp; if (!HidD_GetPreparsedData(h, out pp)) { h.Dispose(); continue; }
                    var caps = new byte[64]; HidP_GetCaps(pp, caps); HidD_FreePreparsedData(pp);
                    ushort usagePage = BitConverter.ToUInt16(caps, 2);
                    ushort featLen = BitConverter.ToUInt16(caps, 8);
                    if (usagePage == 0xFF00 && featLen == 520) return h;
                    h.Dispose();
                } finally { Marshal.FreeHGlobal(buf); }
            }
        } finally { SetupDiDestroyDeviceInfoList(set); }
        throw new Exception("Hi75 vendor interface (FF00, 520-byte feature) not found");
    }

    public static string ReadChunk(byte cmd, byte arg, byte idx, int n) {
        if ((cmd & 0x80) == 0) throw new Exception("read commands only");
        using (var h = Open()) {
            var req = new byte[520];
            req[0] = 6; req[1] = cmd; req[2] = arg; req[4] = 1; req[5] = idx; req[6] = (byte)(n & 0xff); req[7] = (byte)(n >> 8);
            if (!HidD_SetFeature(h, req, 520)) throw new Exception("SetFeature failed");
            System.Threading.Thread.Sleep(20);
            var resp = new byte[520]; resp[0] = 6;
            if (!HidD_GetFeature(h, resp, 520)) throw new Exception("GetFeature failed");
            var o = new System.Text.StringBuilder();
            for (int i = 0; i < n; i++) o.Append(resp[8 + i].ToString("x2"));
            return o.ToString();
        }
    }

    public static Dictionary<string, string> ReadAll() {
        var res = new Dictionary<string, string>();
        using (var h = Open()) {
            Func<byte, byte, int, string> read = (cmd, arg, len) => {
                var o = new System.Text.StringBuilder();
                int chunks = Math.Max(1, (len + 511) / 512);
                for (int c = 0; c < chunks; c++) {
                    int n = Math.Min(512, len - c * 512);
                    var req = new byte[520];
                    req[0] = 6; req[1] = cmd; req[2] = arg; req[4] = (byte)chunks; req[5] = (byte)c; req[6] = (byte)(n & 0xff); req[7] = (byte)(n >> 8);
                    if (!HidD_SetFeature(h, req, 520)) throw new Exception("SetFeature failed " + Marshal.GetLastWin32Error());
                    System.Threading.Thread.Sleep(20);
                    var resp = new byte[520]; resp[0] = 6;
                    if (!HidD_GetFeature(h, resp, 520)) throw new Exception("GetFeature failed " + Marshal.GetLastWin32Error());
                    if (resp[1] != cmd || resp[5] != c) throw new Exception("Unexpected reply header");
                    for (int i = 0; i < n; i++) o.Append(resp[8 + i].ToString("x2"));
                }
                return o.ToString();
            };
            res["identityHex"] = read(0x82, 1, 6);
            res["ledHex"] = read(0x84, 0, 128);
            res["rgbTableHex"] = read(0x8A, 0, 512);
            for (byte l = 0; l < 4; l++) res["layer" + l] = read(0x83, l, 512);
            res["macrosHex"] = read(0x85, 0, 512);
            res["gameHex"] = read(0x86, 0, 512);
        }
        return res;
    }
}
'@

if ($RawChunk) { $p = $RawChunk.Split(",") | ForEach-Object { [int]$_ }; [Hi75Read]::ReadChunk($p[0], $p[1], $p[2], $p[3]); return }
$r = [Hi75Read]::ReadAll()
$out = [ordered]@{
  schema = "hi75-config-backup/1"; readAt = (Get-Date).ToUniversalTime().ToString("o")
  identityHex = $r["identityHex"]; ledHex = $r["ledHex"]; rgbTableHex = $r["rgbTableHex"]
  layersHex = @($r["layer0"], $r["layer1"], $r["layer2"], $r["layer3"]); macrosHex = $r["macrosHex"]; keyColorsHex = $r["gameHex"]
}
$json = $out | ConvertTo-Json -Depth 4
if ($OutFile) { [IO.File]::WriteAllText($OutFile, $json) } else { $json }
