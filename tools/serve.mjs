import { createServer } from "node:http";
import { readFile } from "node:fs/promises";
import { fileURLToPath } from "node:url";
import path from "node:path";

// Serves the same files GitHub Pages publishes: index.html (configurator),
// research/ (stock-firmware inspector), app/ and src/. Never backup/,
// captures/ or analysis/.
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const TYPES = { ".html": "text/html; charset=utf-8", ".js": "text/javascript; charset=utf-8", ".css": "text/css; charset=utf-8" };
const ALLOWED = /^\/(index\.html|research\/(index\.html)?|(app|src)\/[\w/.-]+\.(js|css))$/;
const port = Number(process.env.HI75_PORT || 8787);

const server = createServer(async (req, res) => {
  let pathname = new URL(req.url, "http://localhost").pathname;
  if (pathname === "/") pathname = "/index.html";
  if (pathname === "/research") { res.writeHead(301, { Location: "/research/" }).end(); return; }
  if (pathname.endsWith("/")) pathname += "index.html";
  res.setHeader("X-Content-Type-Options", "nosniff");
  res.setHeader("Cache-Control", "no-store");
  if (!ALLOWED.test(pathname) || pathname.includes("..") || /\.test\.js$/.test(pathname) || (req.method !== "GET" && req.method !== "HEAD")) {
    res.writeHead(404).end("Not found\n");
    return;
  }
  try {
    const bytes = await readFile(path.join(root, pathname));
    res.writeHead(200, { "Content-Type": TYPES[path.extname(pathname)] });
    res.end(req.method === "HEAD" ? undefined : bytes);
  } catch {
    res.writeHead(404).end("Not found\n");
  }
});

server.listen(port, "127.0.0.1", () => {
  console.log(`Hi75 configurator: http://localhost:${port}  (research tools: /research/)`);
});
