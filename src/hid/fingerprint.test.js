import assert from "node:assert/strict";
import test from "node:test";
import { assessCandidate, deviceSnapshot } from "./fingerprint.js";

function report(reportId, reportCount) {
  return { reportId, items: [{ reportSize: 8, reportCount }] };
}

function fixture() {
  return {
    vendorId: 0x258a,
    productId: 0x010c,
    productName: "Gaming Keyboard",
    collections: [
      {
        usagePage: 0x000c,
        usage: 1,
        featureReports: [],
        inputReports: [report(2, 2)],
        outputReports: [],
        children: [],
      },
      {
        usagePage: 0xff00,
        usage: 1,
        featureReports: [],
        inputReports: [report(3, 3)],
        outputReports: [],
        children: [],
      },
      {
        usagePage: 0xff00,
        usage: 1,
        featureReports: [report(5, 5)],
        inputReports: [],
        outputReports: [],
        children: [],
      },
      {
        usagePage: 0xff00,
        usage: 1,
        featureReports: [report(6, 519)],
        inputReports: [report(6, 7)],
        outputReports: [],
        children: [],
      },
    ],
  };
}

test("descriptor-shaped device remains unverified and read-disabled", () => {
  const result = assessCandidate(fixture());
  assert.equal(result.status, "descriptor-layout candidate");
  assert.equal(result.exactModelVerified, false);
  assert.equal(result.revisionVerified, false);
  assert.equal(result.configurationReadAllowed, false);
  assert.equal(result.writesAllowed, false);
});

test("VID/PID alone never produces a descriptor-layout candidate", () => {
  const device = fixture();
  device.collections = [];
  assert.equal(assessCandidate(device).status, "unconfirmed 258A:010C device");
});

test("wrong feature length or usage cannot pass the shape check", () => {
  const device = fixture();
  device.collections[3].featureReports[0].items[0].reportCount = 518;
  assert.equal(assessCandidate(device).checks.featureId6, false);
  device.collections[3].featureReports[0].items[0].reportCount = 519;
  device.collections[3].usagePage = 0xff01;
  assert.equal(assessCandidate(device).checks.featureId6, false);
});

test("snapshot records report payload length and excludes serial", () => {
  const device = fixture();
  device.collections[3].type = 1;
  device.collections[3].featureReports[0].items[0].unitFactorLengthExponent = 2;
  device.collections[3].featureReports[0].items[0].isVolatile = false;
  device.serialNumber = "private";
  const snapshot = deviceSnapshot(device);
  assert.equal(snapshot.collections[3].featureReports[0].payloadBytes, 519);
  assert.equal(snapshot.collections[3].collectionType, 1);
  assert.equal(snapshot.collections[3].featureReports[0].items[0].unitFactorLengthExponent, 2);
  assert.equal(snapshot.collections[3].featureReports[0].items[0].isVolatile, false);
  assert.equal(JSON.stringify(snapshot).includes("private"), false);
});

test("ID 6 input and feature reports must share a vendor collection", () => {
  const device = fixture();
  const inputs = device.collections[3].inputReports;
  device.collections[3].inputReports = [];
  device.collections.push({ ...device.collections[3], inputReports: inputs, featureReports: [] });
  assert.equal(assessCandidate(device).checks.pairedId6, false);
  assert.equal(assessCandidate(device).configurationReadAllowed, false);
});
