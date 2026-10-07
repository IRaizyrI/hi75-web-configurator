import { chooseCandidateDevices, previouslyAllowedDevices } from "../hid/device.js";
import { deviceSnapshot } from "../hid/fingerprint.js";
import { probeIdentityOnce } from "../hid/identity-probe.js";
import { setConfigCandidate } from "./config-view.js";

const status = document.querySelector("#status");
const devicesNode = document.querySelector("#devices");
const snapshotNode = document.querySelector("#snapshot");
const chooseButton = document.querySelector("#choose");
const refreshButton = document.querySelector("#refresh");
const probeButton = document.querySelector("#probe");
const downloadButton = document.querySelector("#download");
let lastSnapshot = null;
let probeCandidate = null;
let probeAttempted = false;

function hex(value, width = 4) {
  return Number(value).toString(16).toUpperCase().padStart(width, "0");
}

function showDevices(devices) {
  devicesNode.replaceChildren();
  if (devices.length === 0) {
    devicesNode.textContent = "No devices returned. Use the chooser, or check browser permissions and the USB connection.";
    snapshotNode.textContent = "No device selected yet.";
    downloadButton.disabled = true;
    lastSnapshot = null;
    probeCandidate = null;
    setConfigCandidate(null);
    probeButton.disabled = true;
    return;
  }
  const list = document.createElement("ol");
  const snapshots = devices.map(deviceSnapshot);
  const candidates = devices.filter((_, index) => snapshots[index].assessment.status === "descriptor-layout candidate");
  probeCandidate = candidates.length === 1 ? candidates[0] : null;
  setConfigCandidate(probeCandidate);
  probeButton.disabled = probeCandidate === null || probeAttempted;
  for (const device of snapshots) {
    const row = document.createElement("li");
    const name = document.createElement("strong");
    name.textContent = `${device.productName || "Unnamed HID device"} · ${hex(device.vendorId)}:${hex(device.productId)}`;
    const result = document.createElement("p");
    result.textContent = `${device.assessment.status}; exact model/revision unverified`;
    row.append(name, result);
    list.append(row);
  }
  devicesNode.append(list);
  lastSnapshot = {
    schemaVersion: 2,
    source: "hi75-web WebHID inspector",
    mode: "metadata-only",
    browserUserAgent: navigator.userAgent,
    capturedAt: new Date().toISOString(),
    devices: snapshots,
  };
  snapshotNode.textContent = JSON.stringify(lastSnapshot, null, 2);
  downloadButton.disabled = false;
}

async function run(action) {
  chooseButton.disabled = true;
  refreshButton.disabled = true;
  probeButton.disabled = true;
  try {
    const devices = await action();
    showDevices(devices);
    status.textContent = `${devices.length} HID interface${devices.length === 1 ? "" : "s"} returned. No reports sent or read.`;
  } catch (error) {
    probeCandidate = null;
    status.textContent = `${error?.name || "Error"}: ${error?.message || String(error)}`;
  } finally {
    chooseButton.disabled = false;
    refreshButton.disabled = false;
    probeButton.disabled = probeCandidate === null || probeAttempted;
  }
}

async function runIdentityProbe() {
  if (!probeCandidate || !lastSnapshot) return;
  if (probeAttempted) return;
  probeAttempted = true;
  lastSnapshot.mode = "identity-probe-attempted";
  chooseButton.disabled = true;
  refreshButton.disabled = true;
  probeButton.disabled = true;
  status.textContent = "Sending the single captured identity query and reading its reply…";
  try {
    const probe = await probeIdentityOnce(probeCandidate);
    lastSnapshot.identityProbe = { capturedAt: new Date().toISOString(), ...probe };
    snapshotNode.textContent = JSON.stringify(lastSnapshot, null, 2);
    status.textContent = probe.parsed?.matchesObservedRgbPsd
      ? "Identity bytes match the observed Hi75 RGB profile; exact revision remains unverified."
      : `Identity response recorded without a profile match${probe.parseError ? ` (${probe.parseError})` : ""}.`;
  } catch (error) {
    lastSnapshot.identityProbe = {
      capturedAt: new Date().toISOString(),
      error: `${error?.name || "Error"}: ${error?.message || String(error)}`,
      noRetrySent: true,
      configurationReadAllowed: false,
      writesAllowed: false,
    };
    snapshotNode.textContent = JSON.stringify(lastSnapshot, null, 2);
    status.textContent = `Identity probe failed: ${error?.name || "Error"}: ${error?.message || String(error)}. No retry was sent.`;
  } finally {
    // Keep the captured result visible until downloaded; a fresh page is an
    // explicit new session, never an automatic retry.
    chooseButton.disabled = true;
    refreshButton.disabled = true;
    probeButton.disabled = true;
  }
}

if (!window.isSecureContext || !("hid" in navigator)) {
  chooseButton.disabled = true;
  refreshButton.disabled = true;
  status.textContent = "WebHID unavailable. Use current Chrome or Edge on http://localhost:8787; check that WebHID is enabled.";
} else {
  status.textContent = "Ready. The chooser requests browser permission for 258A:010C only.";
  chooseButton.addEventListener("click", () => run(chooseCandidateDevices));
  refreshButton.addEventListener("click", () => run(previouslyAllowedDevices));
  probeButton.addEventListener("click", runIdentityProbe);
  navigator.hid.addEventListener("connect", () => {
    status.textContent = "A HID device connected. Refresh to inspect it.";
  });
  navigator.hid.addEventListener("disconnect", () => {
    probeCandidate = null;
    setConfigCandidate(null);
    probeButton.disabled = true;
    status.textContent = "A HID device disconnected. Refresh to update the list.";
  });
}

downloadButton.addEventListener("click", () => {
  if (!lastSnapshot) return;
  const blob = new Blob([`${JSON.stringify(lastSnapshot, null, 2)}\n`], { type: "application/json" });
  const url = URL.createObjectURL(blob);
  const link = document.createElement("a");
  link.href = url;
  link.download = `hi75-webhid-metadata-${lastSnapshot.capturedAt.replaceAll(":", "-")}.json`;
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
});
