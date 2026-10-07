import { createServer } from "node:http";
import { readFile } from "node:fs/promises";
import { fileURLToPath } from "node:url";
import path from "node:path";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const assets = new Map([
  // Production configurator at /, stock-firmware research inspector at /research/.
  ["/", ["app/index.html", "text/html; charset=utf-8"]],
  ["/index.html", ["app/index.html", "text/html; charset=utf-8"]],
  ["/research", ["index.html", "text/html; charset=utf-8"]],
  ["/research/", ["index.html", "text/html; charset=utf-8"]],
  ["/src/ui/app.js", ["src/ui/app.js", "text/javascript; charset=utf-8"]],
  ["/src/ui/styles.css", ["src/ui/styles.css", "text/css; charset=utf-8"]],
  ["/src/hid/device.js", ["src/hid/device.js", "text/javascript; charset=utf-8"]],
  ["/src/hid/fingerprint.js", ["src/hid/fingerprint.js", "text/javascript; charset=utf-8"]],
  ["/src/hid/identity-probe.js", ["src/hid/identity-probe.js", "text/javascript; charset=utf-8"]],
  ["/src/protocol/identity.js", ["src/protocol/identity.js", "text/javascript; charset=utf-8"]],
  ["/src/ui/config-view.js", ["src/ui/config-view.js", "text/javascript; charset=utf-8"]],
  ["/src/hid/transport.js", ["src/hid/transport.js", "text/javascript; charset=utf-8"]],
  ["/src/protocol/lighting.js", ["src/protocol/lighting.js", "text/javascript; charset=utf-8"]],
  ["/src/protocol/macros.js", ["src/protocol/macros.js", "text/javascript; charset=utf-8"]],
  ["/src/protocol/frame.js", ["src/protocol/frame.js", "text/javascript; charset=utf-8"]],
  ["/src/protocol/keycodes.js", ["src/protocol/keycodes.js", "text/javascript; charset=utf-8"]],
  ["/src/protocol/hi75-layout.js", ["src/protocol/hi75-layout.js", "text/javascript; charset=utf-8"]],
]);
const port = Number(process.env.HI75_PORT || 8787);

const server = createServer(async (req, res) => {
  const pathname = new URL(req.url, "http://localhost").pathname;
  // Explicit assets, plus any .js/.css under src/ or app/ (never backup/, captures/ or analysis/).
  const entry = assets.get(pathname) ?? (/^\/(src|app)\/[\w/-]+\.(js|css)$/.test(pathname) && !pathname.includes("..")
    ? [pathname.slice(1), pathname.endsWith(".css") ? "text/css; charset=utf-8" : "text/javascript; charset=utf-8"]
    : undefined);
  res.setHeader("X-Content-Type-Options", "nosniff");
  res.setHeader("Cache-Control", "no-store");
  if (!entry || (req.method !== "GET" && req.method !== "HEAD")) {
    res.writeHead(404).end("Not found\n");
    return;
  }
  try {
    const bytes = await readFile(path.join(root, entry[0]));
    res.writeHead(200, { "Content-Type": entry[1] });
    res.end(req.method === "HEAD" ? undefined : bytes);
  } catch {
    res.writeHead(500).end("Asset unavailable\n");
  }
});

server.listen(port, "127.0.0.1", () => {
  console.log(`Hi75 metadata inspector: http://localhost:${port}`);
});
