// Metadata-only Windows HID inventory. No HID report I/O entry points are imported.
// Native layouts follow hidpi.h; references and limitations are in README.md.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.Win32.SafeHandles;

namespace Hi75.Inventory
{
    public static class Native
    {
        const uint Present = 2, AllClasses = 4, DeviceInterface = 16;
        const int NoMoreItems = 259, InsufficientBuffer = 122;
        const int HidSuccess = 0x00110000;

        [StructLayout(LayoutKind.Sequential)]
        struct DeviceInfo { public uint Size; public Guid ClassGuid; public uint DevInst; public IntPtr Reserved; }
        [StructLayout(LayoutKind.Sequential)]
        struct InterfaceInfo { public uint Size; public Guid ClassGuid; public uint Flags; public IntPtr Reserved; }

        [DllImport("hid.dll")] static extern void HidD_GetHidGuid(out Guid guid);
        [DllImport("setupapi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        static extern IntPtr SetupDiGetClassDevsW(IntPtr guid, string enumerator, IntPtr parent, uint flags);
        [DllImport("setupapi.dll", SetLastError = true)]
        static extern bool SetupDiEnumDeviceInterfaces(IntPtr set, IntPtr info, ref Guid guid, uint index, ref InterfaceInfo data);
        [DllImport("setupapi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        static extern bool SetupDiGetDeviceInterfaceDetailW(IntPtr set, ref InterfaceInfo data, IntPtr detail, uint size, out uint required, ref DeviceInfo info);
        [DllImport("setupapi.dll", SetLastError = true)]
        static extern bool SetupDiEnumDeviceInfo(IntPtr set, uint index, ref DeviceInfo info);
        [DllImport("setupapi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        static extern bool SetupDiGetDeviceRegistryPropertyW(IntPtr set, ref DeviceInfo info, uint property, out uint type, [Out] byte[] buffer, uint size, out uint required);
        [DllImport("setupapi.dll")] static extern bool SetupDiDestroyDeviceInfoList(IntPtr set);
        [DllImport("cfgmgr32.dll", CharSet = CharSet.Unicode)]
        static extern uint CM_Get_Device_IDW(uint devInst, StringBuilder buffer, uint length, uint flags);
        [DllImport("cfgmgr32.dll")] static extern uint CM_Get_Parent(out uint parent, uint devInst, uint flags);
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        static extern SafeFileHandle CreateFileW(string path, uint access, uint share, IntPtr security, uint disposition, uint flags, IntPtr template);
        [DllImport("hid.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.U1)]
        static extern bool HidD_GetAttributes(SafeFileHandle handle, [In, Out] byte[] attributes);
        [DllImport("hid.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.U1)]
        static extern bool HidD_GetManufacturerString(SafeFileHandle handle, [Out] byte[] buffer, uint length);
        [DllImport("hid.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.U1)]
        static extern bool HidD_GetProductString(SafeFileHandle handle, [Out] byte[] buffer, uint length);
        [DllImport("hid.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.U1)]
        static extern bool HidD_GetSerialNumberString(SafeFileHandle handle, [Out] byte[] buffer, uint length);
        [DllImport("hid.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.U1)]
        static extern bool HidD_GetPreparsedData(SafeFileHandle handle, out IntPtr data);
        [DllImport("hid.dll")] [return: MarshalAs(UnmanagedType.U1)]
        static extern bool HidD_FreePreparsedData(IntPtr data);
        [DllImport("hid.dll")] static extern int HidP_GetCaps(IntPtr data, [Out] byte[] caps);
        [DllImport("hid.dll")] static extern int HidP_GetButtonCaps(int type, [Out] byte[] caps, ref ushort count, IntPtr data);
        [DllImport("hid.dll")] static extern int HidP_GetValueCaps(int type, [Out] byte[] caps, ref ushort count, IntPtr data);
        [DllImport("hid.dll")] static extern int HidP_GetLinkCollectionNodes([Out] byte[] nodes, ref uint count, IntPtr data);

        static Dictionary<string, object> Map() { return new Dictionary<string, object>(); }
        static string Hex(int value) { return "0x" + value.ToString("X4"); }
        static ushort U16(byte[] b, int at) { return BitConverter.ToUInt16(b, at); }
        static uint U32(byte[] b, int at) { return BitConverter.ToUInt32(b, at); }
        static void Error(List<string> errors, string operation) {
            int code = Marshal.GetLastWin32Error();
            errors.Add(operation + ": Win32 " + code + " (" + new Win32Exception(code).Message + ")");
        }
        static void Status(List<string> errors, string operation, int status) {
            errors.Add(operation + ": HID status 0x" + unchecked((uint)status).ToString("X8"));
        }
        static string InstanceId(uint devInst, List<string> errors) {
            var b = new StringBuilder(1024);
            uint status = CM_Get_Device_IDW(devInst, b, (uint)b.Capacity, 0);
            if (status == 0) return b.ToString();
            errors.Add("CM_Get_Device_ID: CONFIGRET 0x" + status.ToString("X"));
            return null;
        }
        static object Property(IntPtr set, ref DeviceInfo info, uint property, List<string> errors) {
            uint type, required;
            var bytes = new byte[65536];
            if (!SetupDiGetDeviceRegistryPropertyW(set, ref info, property, out type, bytes, (uint)bytes.Length, out required)) {
                Error(errors, "SetupDiGetDeviceRegistryProperty(" + property + ")");
                return null;
            }
            if (type == 1 || type == 2 || type == 7) {
                string value = Encoding.Unicode.GetString(bytes, 0, (int)required).TrimEnd('\0');
                return type == 7 ? (object)value.Split(new char[] { '\0' }, StringSplitOptions.RemoveEmptyEntries) : value;
            }
            if (type == 4 && required == 4) return U32(bytes, 0);
            return BitConverter.ToString(bytes, 0, (int)required).Replace("-", " ");
        }
        static Dictionary<string, object> Pnp(IntPtr set, ref DeviceInfo info, List<string> errors) {
            var result = Map();
            result["instanceId"] = InstanceId(info.DevInst, errors);
            result["classGuid"] = info.ClassGuid.ToString();
            uint[] properties = { 0, 1, 2, 4, 11, 12, 13, 14, 22, 35 };
            string[] names = { "deviceDescription", "hardwareIds", "compatibleIds", "service", "registryManufacturer", "friendlyName", "locationInformation", "physicalDeviceObjectName", "busNumber", "locationPaths" };
            for (int i = 0; i < properties.Length; i++) result[names[i]] = Property(set, ref info, properties[i], errors);
            var parents = new List<string>();
            uint current = info.DevInst;
            var seen = new HashSet<uint>();
            for (int i = 0; i < 32 && seen.Add(current); i++) {
                uint parent;
                uint status = CM_Get_Parent(out parent, current, 0);
                if (status != 0) {
                    result["parentChainEndConfigRet"] = "0x" + status.ToString("X");
                    break;
                }
                parents.Add(InstanceId(parent, errors));
                current = parent;
            }
            result["parentInstanceIds"] = parents;
            result["usbInterfaceNumberHint"] = null;
            result["usbInterfaceNumberHintSource"] = null;
            var identities = new List<string> { result["instanceId"] as string };
            identities.AddRange(parents);
            foreach (string id in identities) {
                if (id == null) continue;
                var match = Regex.Match(id, @"&MI_([0-9A-F]{2})(?:&|\\|$)", RegexOptions.IgnoreCase);
                if (match.Success) {
                    result["usbInterfaceNumberHint"] = Convert.ToInt32(match.Groups[1].Value, 16);
                    result["usbInterfaceNumberHintSource"] = id;
                    break;
                }
            }
            return result;
        }
        static string GetString(SafeFileHandle handle, int kind, List<string> errors) {
            // HID string requests have a 4093-byte limit; 256 UTF-16 chars suffice.
            byte[] buffer = new byte[512];
            bool ok = kind == 0 ? HidD_GetManufacturerString(handle, buffer, (uint)buffer.Length)
                : kind == 1 ? HidD_GetProductString(handle, buffer, (uint)buffer.Length)
                : HidD_GetSerialNumberString(handle, buffer, (uint)buffer.Length);
            if (!ok) { Error(errors, new string[] { "HidD_GetManufacturerString", "HidD_GetProductString", "HidD_GetSerialNumberString" }[kind]); return null; }
            return Encoding.Unicode.GetString(buffer).Split('\0')[0];
        }

        // Public pure decoders allow ABI/fixture tests without touching hardware.
        public static Dictionary<string, object> DecodeCapability(byte[] bytes, bool value) {
            if (bytes == null || bytes.Length != 72) throw new ArgumentException("A capability record must be 72 bytes.");
            var r = Map();
            r["usagePage"] = Hex(U16(bytes, 0)); r["reportId"] = bytes[2];
            r["isAlias"] = bytes[3] != 0; r["mainItemFlags"] = Hex(U16(bytes, 4));
            r["linkCollectionIndex"] = U16(bytes, 6); r["linkUsageId"] = Hex(U16(bytes, 8));
            r["linkUsagePage"] = Hex(U16(bytes, 10)); r["isUsageRange"] = bytes[12] != 0;
            r["isStringRange"] = bytes[13] != 0; r["isDesignatorRange"] = bytes[14] != 0;
            r["isAbsolute"] = bytes[15] != 0;
            r["usageId"] = bytes[12] == 0 ? (object)Hex(U16(bytes, 56)) : null;
            r["usageMin"] = bytes[12] != 0 ? (object)Hex(U16(bytes, 56)) : null;
            r["usageMax"] = bytes[12] != 0 ? (object)Hex(U16(bytes, 58)) : null;
            r["stringIndexOrMin"] = U16(bytes, 60);
            r["stringMax"] = bytes[13] != 0 ? (object)U16(bytes, 62) : null;
            r["designatorIndexOrMin"] = U16(bytes, 64);
            r["designatorMax"] = bytes[14] != 0 ? (object)U16(bytes, 66) : null;
            r["dataIndexOrMin"] = U16(bytes, 68);
            r["dataIndexMax"] = bytes[12] != 0 ? (object)U16(bytes, 70) : null;
            if (value) {
                r["hasNull"] = bytes[16] != 0; r["bitSize"] = U16(bytes, 18); r["reportCount"] = U16(bytes, 20);
                r["unitsExponentRaw"] = U32(bytes, 32); r["unitsRaw"] = U32(bytes, 36);
                r["logicalMin"] = BitConverter.ToInt32(bytes, 40); r["logicalMax"] = BitConverter.ToInt32(bytes, 44);
                r["physicalMin"] = BitConverter.ToInt32(bytes, 48); r["physicalMax"] = BitConverter.ToInt32(bytes, 52);
            }
            // Button ReportCount is API-version dependent; retain it as raw bytes
            // rather than interpreting the formerly reserved space on old Windows.
            r["nativeCapabilityHex"] = BitConverter.ToString(bytes).Replace("-", " ");
            return r;
        }
        static List<Dictionary<string, object>> Capabilities(IntPtr data, int type, ushort count, bool value, List<string> errors) {
            var list = new List<Dictionary<string, object>>();
            if (count == 0) return list;
            byte[] bytes = new byte[count * 72];
            ushort actual = count;
            int status = value ? HidP_GetValueCaps(type, bytes, ref actual, data) : HidP_GetButtonCaps(type, bytes, ref actual, data);
            if (status != HidSuccess || actual > count) { Status(errors, value ? "HidP_GetValueCaps" : "HidP_GetButtonCaps", status); return list; }
            for (int i = 0; i < actual; i++) {
                byte[] entry = new byte[72]; Array.Copy(bytes, i * 72, entry, 0, 72);
                list.Add(DecodeCapability(entry, value));
            }
            return list;
        }
        public static Dictionary<string, object> DecodeLinkNode(byte[] bytes) {
            if (bytes == null || bytes.Length < 16) throw new ArgumentException("A link node requires at least its 16-byte prefix.");
            var r = Map();
            r["usageId"] = Hex(U16(bytes, 0)); r["usagePage"] = Hex(U16(bytes, 2));
            r["parentIndex"] = U16(bytes, 4); r["numberOfChildren"] = U16(bytes, 6);
            r["nextSiblingIndex"] = U16(bytes, 8); r["firstChildIndex"] = U16(bytes, 10);
            r["collectionType"] = U32(bytes, 12) & 255; r["isAlias"] = (U32(bytes, 12) & 256) != 0;
            return r;
        }
        static Dictionary<string, object> ReadCapabilities(IntPtr data, List<string> errors) {
            byte[] caps = new byte[64];
            int status = HidP_GetCaps(data, caps);
            if (status != HidSuccess) { Status(errors, "HidP_GetCaps", status); return null; }
            var r = Map(); r["usageId"] = Hex(U16(caps, 0)); r["usagePage"] = Hex(U16(caps, 2));
            r["nativeHidpCapsHex"] = BitConverter.ToString(caps).Replace("-", " ");
            var reports = Map();
            for (int type = 0; type < 3; type++) {
                int countOffset = 46 + type * 6;
                var report = Map();
                report["maxWindowsReportBytesIncludingIdSlot"] = U16(caps, 4 + type * 2);
                report["declaredButtonCapabilityCount"] = U16(caps, countOffset);
                report["declaredValueCapabilityCount"] = U16(caps, countOffset + 2);
                report["dataIndexCount"] = U16(caps, countOffset + 4);
                var buttons = Capabilities(data, type, U16(caps, countOffset), false, errors);
                var values = Capabilities(data, type, U16(caps, countOffset + 2), true, errors);
                report["buttonCapabilities"] = buttons; report["valueCapabilities"] = values;
                var ids = new SortedSet<int>();
                foreach (var c in buttons) ids.Add(Convert.ToInt32(c["reportId"]));
                foreach (var c in values) ids.Add(Convert.ToInt32(c["reportId"]));
                report["reportIdsFromCapabilities"] = new List<int>(ids);
                report["exactWireBytesPerReportId"] = null;
                reports[new string[] { "input", "output", "feature" }[type]] = report;
            }
            r["reports"] = reports;
            uint count = U16(caps, 44); r["declaredLinkCollectionCount"] = count;
            var nodes = new List<Dictionary<string, object>>();
            if (count > 0) {
                int stride = IntPtr.Size == 8 ? 24 : 20;
                byte[] bytes = new byte[count * stride]; uint actual = count;
                status = HidP_GetLinkCollectionNodes(bytes, ref actual, data);
                if (status != HidSuccess || actual > count) Status(errors, "HidP_GetLinkCollectionNodes", status);
                else for (int i = 0; i < actual; i++) {
                    byte[] entry = new byte[stride]; Array.Copy(bytes, i * stride, entry, 0, stride);
                    var node = DecodeLinkNode(entry); node["index"] = i; nodes.Add(node);
                }
            }
            r["linkCollections"] = nodes;
            return r;
        }
        static bool Matches(string identity, int vid, int pid) {
            string text = (identity ?? "").ToUpperInvariant();
            return (vid < 0 || text.Contains("VID_" + vid.ToString("X4"))) &&
                   (pid < 0 || text.Contains("PID_" + pid.ToString("X4")));
        }
        static IntPtr DeviceSet(Guid? guid, string enumerator, uint flags) {
            IntPtr ptr = IntPtr.Zero;
            try {
                if (guid.HasValue) { ptr = Marshal.AllocHGlobal(16); Marshal.StructureToPtr(guid.Value, ptr, false); }
                IntPtr set = SetupDiGetClassDevsW(ptr, enumerator, IntPtr.Zero, flags);
                if (set == new IntPtr(-1)) throw new Win32Exception(Marshal.GetLastWin32Error());
                return set;
            } finally { if (ptr != IntPtr.Zero) Marshal.FreeHGlobal(ptr); }
        }
        public static Dictionary<string, object> Collect(int vid, int pid) {
            if (vid < -1 || vid > 65535 || pid < -1 || pid > 65535) throw new ArgumentOutOfRangeException();
            var result = Map(); var errors = new List<string>(); result["errors"] = errors;
            result["filterVid"] = vid < 0 ? null : (object)Hex(vid);
            result["filterPid"] = pid < 0 ? null : (object)Hex(pid);
            var devices = new List<Dictionary<string, object>>(); result["hidCollections"] = devices;
            Guid guid; HidD_GetHidGuid(out guid);
            IntPtr set = DeviceSet(guid, null, Present | DeviceInterface);
            try {
                for (uint i = 0; ; i++) {
                    var entry = new InterfaceInfo(); entry.Size = (uint)Marshal.SizeOf(typeof(InterfaceInfo));
                    if (!SetupDiEnumDeviceInterfaces(set, IntPtr.Zero, ref guid, i, ref entry)) {
                        if (Marshal.GetLastWin32Error() != NoMoreItems) Error(errors, "SetupDiEnumDeviceInterfaces");
                        break;
                    }
                    var info = new DeviceInfo(); info.Size = (uint)Marshal.SizeOf(typeof(DeviceInfo));
                    uint required;
                    SetupDiGetDeviceInterfaceDetailW(set, ref entry, IntPtr.Zero, 0, out required, ref info);
                    if (Marshal.GetLastWin32Error() != InsufficientBuffer || required < 6) {
                        Error(errors, "SetupDiGetDeviceInterfaceDetail(size)"); continue;
                    }
                    IntPtr detail = Marshal.AllocHGlobal(checked((int)required));
                    try {
                        // cbSize includes ABI padding; DevicePath starts at offset 4 on both architectures.
                        Marshal.WriteInt32(detail, IntPtr.Size == 8 ? 8 : 6);
                        if (!SetupDiGetDeviceInterfaceDetailW(set, ref entry, detail, required, out required, ref info)) {
                            Error(errors, "SetupDiGetDeviceInterfaceDetail"); continue;
                        }
                        string path = Marshal.PtrToStringUni(IntPtr.Add(detail, 4));
                        if (!Matches(path, vid, pid)) continue;
                        var d = Map(); var deviceErrors = new List<string>(); devices.Add(d);
                        d["devicePath"] = path; d["errors"] = deviceErrors; d["pnp"] = Pnp(set, ref info, deviceErrors);
                        d["vid"] = null; d["pid"] = null; d["hidDeviceVersionNumber"] = null;
                        d["manufacturerString"] = null; d["productString"] = null; d["serialNumberString"] = null;
                        d["capabilities"] = null; d["metadataHandleOpened"] = false;
                        d["matchesReportedVidPidHintOnly"] = Matches(path, 0x258A, 0x010C);
                        // Desired access is exactly zero: no GENERIC_READ/GENERIC_WRITE.
                        // Share flags permit existing users; they do not grant this handle write access.
                        using (SafeFileHandle handle = CreateFileW(path, 0, 3, IntPtr.Zero, 3, 0, IntPtr.Zero)) {
                            if (handle.IsInvalid) { Error(deviceErrors, "CreateFile(metadata only)"); continue; }
                            d["metadataHandleOpened"] = true;
                            byte[] attrs = new byte[12]; attrs[0] = 12;
                            if (HidD_GetAttributes(handle, attrs)) {
                                d["vid"] = Hex(U16(attrs, 4)); d["pid"] = Hex(U16(attrs, 6));
                                d["hidDeviceVersionNumber"] = Hex(U16(attrs, 8));
                            } else Error(deviceErrors, "HidD_GetAttributes");
                            d["manufacturerString"] = GetString(handle, 0, deviceErrors);
                            d["productString"] = GetString(handle, 1, deviceErrors);
                            d["serialNumberString"] = GetString(handle, 2, deviceErrors);
                            IntPtr data;
                            if (!HidD_GetPreparsedData(handle, out data)) Error(deviceErrors, "HidD_GetPreparsedData");
                            else try { d["capabilities"] = ReadCapabilities(data, deviceErrors); }
                            finally { HidD_FreePreparsedData(data); }
                        }
                    } finally { Marshal.FreeHGlobal(detail); }
                }
            } finally { SetupDiDestroyDeviceInfoList(set); }
            var usb = new List<Dictionary<string, object>>(); result["usbPnpNodes"] = usb;
            set = DeviceSet(null, "USB", Present | AllClasses);
            try {
                for (uint i = 0; ; i++) {
                    var info = new DeviceInfo(); info.Size = (uint)Marshal.SizeOf(typeof(DeviceInfo));
                    if (!SetupDiEnumDeviceInfo(set, i, ref info)) {
                        if (Marshal.GetLastWin32Error() != NoMoreItems) Error(errors, "SetupDiEnumDeviceInfo(USB)");
                        break;
                    }
                    var nodeErrors = new List<string>(); string id = InstanceId(info.DevInst, nodeErrors);
                    if (!Matches(id, vid, pid)) continue;
                    var node = Pnp(set, ref info, nodeErrors); node["errors"] = nodeErrors; usb.Add(node);
                }
            } finally { SetupDiDestroyDeviceInfoList(set); }
            return result;
        }
    }
}
