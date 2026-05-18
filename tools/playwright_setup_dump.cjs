#!/usr/bin/env node
const fs = require("fs");
const { chromium } = require("playwright");

function argValue(name) {
  const index = process.argv.indexOf(name);
  return index >= 0 && index + 1 < process.argv.length ? process.argv[index + 1] : null;
}

async function main() {
  const html = argValue("--html-file");
  const out = argValue("--out-json");
  const viewportArg = argValue("--viewport") || "320x200";
  if (!html || !out) {
    console.error("Usage: node tools/playwright_setup_dump.cjs --html-file <path> --out-json <path> [--viewport WxH]");
    process.exit(2);
  }
  const [width, height] = viewportArg.split("x").map((v) => Number(v));
  const browser = await chromium.launch();
  const page = await browser.newPage({ viewport: { width, height }, deviceScaleFactor: 1 });
  await page.goto(`file:///${html.replace(/\\/g, "/")}`);
  const setup = await page.evaluate(() => {
    const pickStyle = (element) => {
      if (!element) return null;
      const style = getComputedStyle(element);
      return {
        margin: style.margin,
        padding: style.padding,
        border: style.border,
        borderTopWidth: style.borderTopWidth,
        borderRightWidth: style.borderRightWidth,
        borderBottomWidth: style.borderBottomWidth,
        borderLeftWidth: style.borderLeftWidth,
        width: style.width,
        height: style.height,
        display: style.display,
        position: style.position,
        boxSizing: style.boxSizing,
        font: style.font,
        fontFamily: style.fontFamily,
        fontSize: style.fontSize,
        backgroundColor: style.backgroundColor,
        backgroundImage: style.backgroundImage,
        overflowX: style.overflowX,
        overflowY: style.overflowY,
        transform: style.transform,
        transformOrigin: style.transformOrigin,
        opacity: style.opacity,
        visibility: style.visibility,
        objectFit: style.objectFit,
        objectPosition: style.objectPosition,
      };
    };
    const rect = (element) => {
      if (!element) return null;
      const r = element.getBoundingClientRect();
      return { x: r.x, y: r.y, width: r.width, height: r.height, left: r.left, top: r.top, right: r.right, bottom: r.bottom };
    };
    const selectors = [
      "html",
      "body",
      ".box",
      ".card",
      ".child",
      "img",
      "table",
      ".fixture-target",
      "[data-debug-id]",
    ];
    const elementInfo = (selector) => {
      const element = selector === "html"
        ? document.documentElement
        : selector === "body"
          ? document.body
          : document.querySelector(selector);
      if (!element) return { present: false };
      const clientRects = Array.from(element.getClientRects()).map((r) => ({
        x: r.x,
        y: r.y,
        width: r.width,
        height: r.height,
        left: r.left,
        top: r.top,
        right: r.right,
        bottom: r.bottom,
      }));
      return {
        present: true,
        selector,
        tagName: element.tagName,
        id: element.id || "",
        className: typeof element.className === "string" ? element.className : "",
        interface: element.constructor && element.constructor.name ? element.constructor.name : "unknown",
        computedStyle: pickStyle(element),
        boundingRect: rect(element),
        clientRects,
      };
    };
    const selected = {};
    for (const selector of selectors) {
      selected[selector] = elementInfo(selector);
    }
    return {
      viewport: { width: innerWidth, height: innerHeight },
      deviceScaleFactor: devicePixelRatio,
      compatMode: document.compatMode,
      locationHref: location.href,
      baseURI: document.baseURI,
      htmlComputedStyle: pickStyle(document.documentElement),
      bodyComputedStyle: pickStyle(document.body),
      htmlRect: rect(document.documentElement),
      bodyRect: rect(document.body),
      selectedElements: selected,
      selectedElementRects: Object.fromEntries(
        Object.entries(selected).map(([selector, info]) => [
          selector,
          info && info.present ? info.boundingRect : null,
        ])
      ),
      mediaQueryEnvironment: {
        maxWidth600: matchMedia("(max-width: 600px)").matches,
        minWidth768: matchMedia("(min-width: 768px)").matches,
        hoverHover: matchMedia("(hover: hover)").matches,
        pointerFine: matchMedia("(pointer: fine)").matches,
        prefersDark: matchMedia("(prefers-color-scheme: dark)").matches,
        reducedMotion: matchMedia("(prefers-reduced-motion: reduce)").matches,
      },
    };
  });
  await browser.close();
  fs.mkdirSync(require("path").dirname(out), { recursive: true });
  fs.writeFileSync(out, JSON.stringify({ playwright_setup: setup }, null, 2));
}

main().catch((error) => {
  console.error(error && error.stack ? error.stack : String(error));
  process.exit(1);
});
