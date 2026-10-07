import test from "node:test";
import assert from "node:assert/strict";
import { readFileSync, existsSync } from "node:fs";
import { decodeKey, decodeLayer } from "./keycodes.js";
import { HI75_KEYS } from "./hi75-layout.js";

const dump = new URL("../../backup/dumps/20260919T085231Z/firmware.bin", import.meta.url);

test("decodes representative words", () => {
  assert.equal(decodeKey([0, 0, 0, 0x29]).label, "Esc");
  assert.equal(decodeKey([0, 0x04, 0, 0x2b]).label, "LAlt+Tab");
  assert.equal(decodeKey([2, 0, 0, 0xe9]).label, "Vol+");
  assert.equal(decodeKey([0x0d, 0, 0, 0]).label, "Fn");
  assert.equal(decodeKey([0x08, 0x03, 0x01, 0]).label, "LED bright+");
});

test("saved base layer decodes to the stock layout", { skip: !existsSync(dump) && "no local dump" }, () => {
  const img = readFileSync(dump);
  const keys = decodeLayer(new Uint8Array(img.subarray(0xcc00, 0xce00)), HI75_KEYS);
  const by = Object.fromEntries(keys.map((k) => [k.name, k.label]));
  assert.equal(by.Esc, "Esc");
  assert.equal(by.Q, "Q");
  assert.equal(by.LShift, "LShift");
  assert.equal(by.FN, "Fn");
  assert.equal(by.Space, "Space");
});
