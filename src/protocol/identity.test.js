import assert from "node:assert/strict";
import { createHash } from "node:crypto";
import test from "node:test";
import {
  capturedIdentityRequest,
  identityWebHidArguments,
  inspectCapturedIdentityResponse,
} from "./identity.js";

test("offline request matches the SHA-256 of captured startup frame 7", () => {
  const report = capturedIdentityRequest();
  assert.equal(report.length, 520);
  assert.equal(createHash("sha256").update(report).digest("hex"), "b2927ca4e2e12dd788bb91022eaeba0483bddfcec1ef34fb279ed520dad6bab6");
  const preview = identityWebHidArguments();
  assert.equal(preview.reportId, 6);
  assert.equal(preview.body.length, 519);
  assert.deepEqual(preview.body, report.slice(1));
});

test("captured response decodes six bytes without verifying a revision", () => {
  const response = Uint8Array.from([6, 0x82, 1, 0, 1, 0, 6, 0, 3, 0, 0, 0, 0, 0x9b]);
  const result = inspectCapturedIdentityResponse(response);
  assert.deepEqual(result.psd, Uint8Array.from([3, 0, 0, 0, 0, 0x9b]));
  assert.equal(result.matchesObservedRgbPsd, true);
  assert.equal(result.exactRevisionVerified, false);
  response[1] = 0x04;
  assert.throws(() => inspectCapturedIdentityResponse(response), /header/);
});
