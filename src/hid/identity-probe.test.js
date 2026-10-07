import assert from "node:assert/strict";
import test from "node:test";
import { probeIdentityOnce } from "./identity-probe.js";

const report = (reportId, reportCount) => ({ reportId, items: [{ reportSize: 8, reportCount }] });
const collection = (usagePage, inputReports, featureReports) => ({
  usagePage, usage: 1, inputReports, featureReports, outputReports: [], children: [],
});

function fakeDevice() {
  const calls = [];
  const device = {
    vendorId: 0x258a,
    productId: 0x010c,
    opened: false,
    collections: [
      collection(0x000c, [report(2, 2)], []),
      collection(0xff00, [report(3, 3)], []),
      collection(0xff00, [], [report(5, 5)]),
      collection(0xff00, [report(6, 7)], [report(6, 519)]),
    ],
    async open() { calls.push("open"); this.opened = true; },
    async close() { calls.push("close"); this.opened = false; },
    addEventListener(type, callback) { calls.push(type); this.callback = callback; },
    removeEventListener(type) { calls.push(`remove ${type}`); },
    async sendFeatureReport(id, body) { calls.push(["sendFeatureReport", id, body.length, Array.from(body.slice(0, 7))]); },
    async receiveFeatureReport(id) {
      calls.push(["receiveFeatureReport", id]);
      this.callback({ reportId: 6, data: new DataView(Uint8Array.from([0x0a, 5, 100, 1, 0, 0, 0]).buffer) });
      return new DataView(Uint8Array.from([6, 0x82, 1, 0, 1, 0, 6, 0, 3, 0, 0, 0, 0, 0x9b]).buffer);
    },
  };
  return { device, calls };
}

test("mismatched descriptor never opens or sends", async () => {
  const { device, calls } = fakeDevice();
  device.productId = 0x010d;
  await assert.rejects(probeIdentityOnce(device), /layout/);
  assert.deepEqual(calls, []);
});

test("one gated identity probe uses only observed query and closes", async () => {
  const { device, calls } = fakeDevice();
  const result = await probeIdentityOnce(device);
  assert.equal(result.sentBodyBytes, 519);
  assert.equal(result.responseBytes, 14);
  assert.equal(result.parsed.psdHex, "03000000009b");
  assert.equal(result.parsed.exactRevisionVerified, false);
  assert.deepEqual(result.vendorInputReports, [{ reportId: 6, bodyHex: "0a056401000000" }]);
  assert.deepEqual(calls.filter((call) => Array.isArray(call) && call[0] === "sendFeatureReport"), [
    ["sendFeatureReport", 6, 519, [0x82, 1, 0, 1, 0, 6, 0]],
  ]);
  assert.equal(calls.filter((call) => Array.isArray(call) && call[0] === "receiveFeatureReport").length, 1);
  assert.equal(calls.at(-1), "close");
  assert.equal(result.configurationReadAllowed, false);
  await assert.rejects(probeIdentityOnce(device), /already attempted/);
  assert.equal(calls.filter((call) => Array.isArray(call) && call[0] === "sendFeatureReport").length, 1);
});

test("failed feature query closes and cannot be retried", async () => {
  const { device, calls } = fakeDevice();
  device.sendFeatureReport = async () => { calls.push("failed send"); throw new Error("transfer rejected"); };
  await assert.rejects(probeIdentityOnce(device), /transfer rejected/);
  assert.equal(calls.at(-1), "close");
  await assert.rejects(probeIdentityOnce(device), /already attempted/);
  assert.equal(calls.filter((call) => call === "failed send").length, 1);
});
