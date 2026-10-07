// Offline representation of the exact report observed in startup capture 003.
// This module performs no HID I/O and does not classify the request as safe.
export const IDENTITY_REPORT_ID = 6;
export const IDENTITY_BODY_BYTES = 519;
const REQUEST_HEADER = Uint8Array.from([0x82, 0x01, 0x00, 0x01, 0x00, 0x06, 0x00]);
const OBSERVED_RGB_PSD = Uint8Array.from([0x03, 0x00, 0x00, 0x00, 0x00, 0x9b]);

export function capturedIdentityRequest() {
  const report = new Uint8Array(520);
  report[0] = IDENTITY_REPORT_ID;
  report.set(REQUEST_HEADER, 1);
  return report;
}

export function identityWebHidArguments() {
  const report = capturedIdentityRequest();
  // WebHID takes reportId separately; this is an offline argument preview.
  return { reportId: IDENTITY_REPORT_ID, body: report.slice(1) };
}

export function inspectCapturedIdentityResponse(report) {
  const bytes = Uint8Array.from(report);
  if (bytes.length < 14) throw new RangeError("Identity response shorter than captured 14-byte report");
  if (bytes[0] !== IDENTITY_REPORT_ID) throw new Error("Unexpected report ID");
  for (let i = 0; i < REQUEST_HEADER.length; i++) {
    if (bytes[i + 1] !== REQUEST_HEADER[i]) throw new Error(`Unexpected identity response header at offset ${i + 1}`);
  }
  const psd = bytes.slice(8, 14);
  return {
    psd,
    matchesObservedRgbPsd: psd.every((byte, i) => byte === OBSERVED_RGB_PSD[i]),
    extraBytes: bytes.slice(14),
    exactRevisionVerified: false,
  };
}
