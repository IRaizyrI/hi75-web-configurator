import { DEMO } from "./demo-data.js";

// In-memory stand-in for the keyboard's vendor interface, following the
// firmware's read dispatcher (CODE 0x4E1E) and write handlers (CODE 0x0495).
const fromHex = (h) => Uint8Array.from(h.match(/../g), (x) => Number.parseInt(x, 16));
const report = (reportId, reportCount) => ({ reportId, items: [{ reportSize: 8, reportCount }] });
const collection = (usagePage, inputReports, featureReports) => ({ usagePage, usage: 1, inputReports, featureReports, outputReports: [], children: [] });

export function createDemoDevice() {
  const flash = new Uint8Array(0x10000);
  flash.set(fromHex(DEMO.identityHex), 0xb3e3);
  flash.set(fromHex(DEMO.ledHex), 0xc600);
  flash.set(fromHex(DEMO.rgbTableHex), 0xc800);
  flash.set(fromHex(DEMO.keyColorsHex), 0xca00);
  DEMO.layersHex.forEach((h, i) => flash.set(fromHex(h), [0xcc00, 0xd000, 0xd400, 0xd800][i]));
  flash.set(fromHex(DEMO.macrosHex), 0xdc00);
  const readBase = { 0x82: () => 0xb3e3, 0x83: (a) => [0xcc00, 0xd000, 0xd400, 0xd800][a], 0x84: () => 0xc600, 0x85: () => 0xdc00, 0x86: () => 0xca00, 0x8a: () => 0xc800 };
  let last = null;
  return {
    demo: true, vendorId: 0x258a, productId: 0x010c, productName: "Hi75 (demo)", opened: false,
    collections: [
      collection(0x000c, [report(2, 2)], []),
      collection(0xff00, [report(3, 3)], []),
      collection(0xff00, [], [report(5, 5)]),
      collection(0xff00, [report(6, 7)], [report(6, 519)]),
    ],
    async open() { this.opened = true; },
    async close() { this.opened = false; },
    addEventListener() {}, removeEventListener() {},
    async sendFeatureReport(id, body) {
      const [cmd, arg, , , idx, lo, hi] = body;
      const data = body.slice(7, 7 + (lo | (hi << 8)));
      const sector = (addr, keep = 0) => { const s = new Uint8Array(512); s.set(data); if (keep) s.set(flash.subarray(addr + keep, addr + 512), keep); flash.set(s, addr); };
      if (cmd === 0x03 && arg < 4) sector([0xcc00, 0xd000, 0xd400, 0xd800][arg]);
      else if (cmd === 0x04) flash.set(data, 0xc600);
      else if (cmd === 0x05) sector(0xdc00 + 0x200 * idx);
      else if (cmd === 0x06) sector(0xca00, 378);
      else if (cmd === 0x0a) sector(0xc800);
      else if (cmd & 0x80) last = body;
      await new Promise((r) => setTimeout(r, 2));
    },
    async receiveFeatureReport() {
      const [cmd, arg, , , idx, lo, hi] = last;
      const len = lo | (hi << 8);
      const addr = readBase[cmd](arg) + (cmd === 0x82 ? 0 : 0x200 * idx);
      const out = new Uint8Array(520);
      out.set([6, ...last.slice(0, 7)]);
      out.set(flash.subarray(addr, addr + len), 8);
      return new DataView(out.buffer);
    },
  };
}
