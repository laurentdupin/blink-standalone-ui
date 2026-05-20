#!/usr/bin/env node
const fs = require("fs");
const path = require("path");

function requirePlaywright() {
  try {
    return require("playwright");
  } catch (firstError) {
    const pathEntries = (process.env.PATH || "").split(path.delimiter);
    for (const entry of pathEntries) {
      if (!entry.toLowerCase().endsWith(`${path.sep}.bin`)) continue;
      const candidate = path.join(path.dirname(entry), "playwright");
      try {
        return require(candidate);
      } catch (_) {
      }
    }
    throw firstError;
  }
}

function argValue(name) {
  const index = process.argv.indexOf(name);
  return index >= 0 && index + 1 < process.argv.length ? process.argv[index + 1] : null;
}

async function main() {
  const html = argValue("--html-file");
  const out = argValue("--out");
  const viewportArg = argValue("--viewport") || "320x200";
  if (!html || !out) {
    console.error("Usage: node tools/playwright_screenshot.cjs --html-file <path> --out <path> [--viewport WxH]");
    process.exit(2);
  }
  const [width, height] = viewportArg.split("x").map((v) => Number(v));
  const { chromium } = requirePlaywright();
  fs.mkdirSync(path.dirname(out), { recursive: true });
  const browser = await chromium.launch();
  try {
    const page = await browser.newPage({ viewport: { width, height }, deviceScaleFactor: 1 });
    await page.goto(`file:///${html.replace(/\\/g, "/")}`);
    await page.screenshot({ path: out });
  } finally {
    await browser.close();
  }
}

main().catch((error) => {
  console.error(error && error.stack ? error.stack : String(error));
  process.exit(1);
});
