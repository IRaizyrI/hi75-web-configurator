import { assessCandidate } from "./fingerprint.js";
import { identityWebHidArguments, inspectCapturedIdentityResponse } from "../protocol/identity.js";

const hex = (bytes) => Array.from(bytes, (byte) => byte.toString(16).padStart(2, "0")).join("");
const bytesOf = (view) => new Uint8Array(view.buffer, view.byteOffset, view.byteLength).slice();
const attemptedDevices = new WeakSet();

// One exact official-app identity query. It sends a feature SET_REPORT and may
// cause a vendor input event. It does not issue a configuration write command.
export async function probeIdentityOnce(device) {
  const assessment = assessCandidate(device);
  if (assessment.status !== "descriptor-layout candidate") {
    throw new Error("Browser-visible HID layout does not match the captured candidate");
  }
  if (device.opened) throw new Error("Close the existing HID connection before probing identity");
  if (attemptedDevices.has(device)) throw new Error("Identity query already attempted for this device; no retry allowed");
  const vendorInputReports = [];
  const onInput = (event) => {
    if (event.reportId === 6) {
      vendorInputReports.push({ reportId: 6, bodyHex: hex(bytesOf(event.data)) });
    }
  };
  let opened = false;
  try {
    await device.open();
    opened = true;
    device.addEventListener("inputreport", onInput);
    const { reportId, body } = identityWebHidArguments();
    attemptedDevices.add(device);
    await device.sendFeatureReport(reportId, body);
    // Match the official app's observed delay between SET and GET.
    await new Promise((resolve) => setTimeout(resolve, 20));
    const data = await device.receiveFeatureReport(reportId);
    // The WebHID spec allows the OS-returned feature DataView to include its
    // report ID. Preserve raw bytes and only parse the observed 06-prefixed form.
    const response = bytesOf(data);
    await new Promise((resolve) => setTimeout(resolve, 100));
    let parsed = null;
    let parseError = null;
    try {
      const inspected = inspectCapturedIdentityResponse(response);
      parsed = {
        psdHex: hex(inspected.psd),
        matchesObservedRgbPsd: inspected.matchesObservedRgbPsd,
        exactRevisionVerified: false,
      };
    } catch (error) {
      parseError = error.message;
    }
    return {
      source: "single browser-originated 0x82 identity query",
      reportId,
      sentBodyBytes: body.length,
      responseBytes: response.length,
      responseHex: hex(response),
      parsed,
      parseError,
      vendorInputReports,
      configurationReadAllowed: false,
      writesAllowed: false,
    };
  } finally {
    if (opened) {
      device.removeEventListener("inputreport", onInput);
      await device.close();
    }
  }
}
