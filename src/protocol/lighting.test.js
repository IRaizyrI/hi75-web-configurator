import test from "node:test";
import assert from "node:assert/strict";
import { readFileSync, existsSync } from "node:fs";
import { decodeLighting, encodeLighting } from "./lighting.js";
import { encodeMacros, parseMacros, macroKeyWord } from "./macros.js";

const backupUrl = new URL("../../backup/config/hi75-backup-2026-10-07T09-52-28.785Z.json", import.meta.url);

test("live backup decodes to effect 2 with brightness 3 and stock palette", { skip: !existsSync(backupUrl) && "no backup" }, () => {
  const b = JSON.parse(readFileSync(backupUrl));
  const led = Buffer.from(b.ledHex, "hex"), rgb = Buffer.from(b.rgbTableHex, "hex");
  const l = decodeLighting(new Uint8Array(led), new Uint8Array(rgb));
  assert.equal(l.hw, 2);
  assert.equal(l.effects[1].level, 3);
  assert.deepEqual(l.effects[0].palette.slice(0, 3), [[255, 0, 0], [0, 255, 0], [0, 0, 255]]);
  const next = encodeLighting(new Uint8Array(led), new Uint8Array(rgb), { hw: 5, level: 2, speedLevel: 1, colorIndex: 0, slotColor: [1, 2, 3] });
  assert.equal(next.led[10], 5);
  assert.equal(next.led[0x3a + 8], 2);
  assert.equal(next.led[0x3a + 9], 0x10);
  assert.deepEqual(Array.from(next.rgb.subarray(21 * 5, 21 * 5 + 3)), [1, 2, 3]);
  const changedLed = Array.from(next.led).map((x, i) => (x === led[i] ? -1 : i)).filter((i) => i >= 0);
  assert.deepEqual(changedLed, [10, 0x3a + 8, 0x3a + 9]);
});

test("macro buffer round-trips and matches the app layout", () => {
  const macros = [
    { name: "Hi", actions: [{ kind: 0, down: true, delay: 10, code: 0x0b }, { kind: 1, down: false, delay: 0x1234, code: 0xe1 }] },
    { name: "", actions: [{ kind: 2, down: true, delay: 0, code: 1 }] },
  ];
  const buf = encodeMacros(macros);
  // header: 2 entries; first record at 8, len = 1 + 4 + 8
  assert.deepEqual(Array.from(buf.subarray(0, 8)), [8, 0, 13, 0, 21, 0, 5, 0]);
  assert.deepEqual(Array.from(buf.subarray(8, 21)), [4, 0x48, 0, 0x69, 0, 0x00, 0, 10, 0x0b, 0x90, 0x12, 0x34, 0xe1]);
  assert.deepEqual(parseMacros(buf), macros);
  assert.deepEqual(parseMacros(new Uint8Array(512)), []);
  assert.deepEqual(macroKeyWord(2, 3), [3, 1, 3, 2]);
});
