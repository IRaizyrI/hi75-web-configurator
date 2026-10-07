// Metadata-only WebHID operations. Keep report I/O out of this module.
export async function previouslyAllowedDevices() {
  return navigator.hid.getDevices();
}

export async function chooseCandidateDevices() {
  return navigator.hid.requestDevice({
    filters: [{ vendorId: 0x258a, productId: 0x010c }],
  });
}
