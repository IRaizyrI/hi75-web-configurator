import test from "node:test";
import assert from "node:assert/strict";
import { buildBody, parseReply } from "./frame.js";
import { identityWebHidArguments } from "./identity.js";

test("identity request built from framing equals the captured body", () => {
  assert.deepEqual(buildBody({ command: 0x82, arg: 1, length: 6 }), identityWebHidArguments().body);
});

test("parses captured identity reply with report ID prefix", () => {
  const r = parseReply([0x06, 0x82, 0x01, 0x00, 0x01, 0x00, 0x06, 0x00, 3, 0, 0, 0, 0, 0x9b]);
  assert.equal(r.command, 0x82);
  assert.deepEqual(Array.from(r.data), [3, 0, 0, 0, 0, 0x9b]);
  assert.equal(r.truncated, false);
});

test("parses reply without report ID and rejects oversize chunks", () => {
  const r = parseReply([0x84, 0, 0, 1, 0, 2, 0, 0xaa, 0xbb]);
  assert.deepEqual(Array.from(r.data), [0xaa, 0xbb]);
  assert.throws(() => buildBody({ command: 0x83, length: 513 }));
});
