#!/usr/bin/env node
const fs = require("fs");
const path = require("path");
const childProcess = require("child_process");

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
    const roots = [];
    for (let dir = __dirname; dir && dir !== path.dirname(dir); dir = path.dirname(dir)) {
      roots.push(path.join(dir, "node_modules", "playwright"));
    }
    for (const npmCmd of process.platform === "win32" ? ["npm.cmd", "npm"] : ["npm"]) {
      try {
        roots.push(path.join(
          childProcess.execFileSync(npmCmd, ["root", "-g"], {
            encoding: "utf8",
            stdio: ["ignore", "pipe", "ignore"],
          }).trim(),
          "playwright"));
      } catch (_) {
      }
    }
    for (const candidate of roots) {
      try {
        return require(candidate);
      } catch (_) {
      }
    }
    const buildRoot = path.join(path.dirname(__dirname), "build");
    const stack = fs.existsSync(buildRoot) ? [buildRoot] : [];
    let visited = 0;
    while (stack.length && visited < 4000) {
      const dir = stack.pop();
      visited += 1;
      const candidate = path.join(dir, "node_modules", "playwright");
      if (fs.existsSync(candidate)) {
        try {
          return require(candidate);
        } catch (_) {
        }
      }
      let entries = [];
      try {
        entries = fs.readdirSync(dir, { withFileTypes: true });
      } catch (_) {
      }
      for (const entry of entries) {
        if (entry.isDirectory()) {
          stack.push(path.join(dir, entry.name));
        }
      }
    }
    throw firstError;
  }
}

function argValue(name) {
  const index = process.argv.indexOf(name);
  return index >= 0 && index + 1 < process.argv.length ? process.argv[index + 1] : null;
}

function argValues(name) {
  const values = [];
  for (let index = 0; index < process.argv.length; index += 1) {
    if (process.argv[index] === name && index + 1 < process.argv.length) {
      values.push(process.argv[index + 1]);
      index += 1;
    }
  }
  return values;
}

function parseAttrOverride(value) {
  const colon = value.indexOf(":");
  const equals = value.indexOf("=", colon + 1);
  if (colon <= 0 || equals <= colon + 1) {
    throw new Error(`Invalid --attr override '${value}', expected id:name=value`);
  }
  return {
    id: value.slice(0, colon),
    name: value.slice(colon + 1, equals),
    value: value.slice(equals + 1),
  };
}

function parseElementScroll(value) {
  const colon = value.indexOf(":");
  const comma = value.indexOf(",", colon + 1);
  if (colon <= 0 || comma <= colon + 1) {
    throw new Error(`Invalid --scroll-element '${value}', expected id:x,y`);
  }
  const x = Number(value.slice(colon + 1, comma));
  const y = Number(value.slice(comma + 1));
  if (!Number.isFinite(x) || !Number.isFinite(y)) {
    throw new Error(`Invalid --scroll-element '${value}', expected numeric x,y`);
  }
  return {
    id: value.slice(0, colon),
    x,
    y,
  };
}

async function main() {
  if (process.argv.includes("--check-only")) {
    requirePlaywright();
    process.stdout.write(JSON.stringify({ playwrightAvailable: true }) + "\n");
    return;
  }

  const html = argValue("--html-file");
  const out = argValue("--out");
  const viewportArg = argValue("--viewport") || "320x200";
  const scrollX = Number(argValue("--scroll-x") || "0");
  const scrollY = Number(argValue("--scroll-y") || "0");
  const timeMsArg = argValue("--time-ms");
  const timeMs = Number(timeMsArg || "0");
  const timeRequested = timeMsArg !== null && timeMsArg !== undefined;
  const outJson = argValue("--out-json");
  const attrOverrides = argValues("--attr").map(parseAttrOverride);
  const elementScrolls = argValues("--scroll-element").map(parseElementScroll);
  if (!html || !out) {
    console.error("Usage: node tools/playwright_screenshot.cjs --html-file <path> --out <path> [--viewport WxH] [--scroll-x px] [--scroll-y px] [--scroll-element id:x,y] [--time-ms ms] [--attr id:name=value] [--out-json path]");
    process.exit(2);
  }
  const [width, height] = viewportArg.split("x").map((v) => Number(v));
  const { chromium } = requirePlaywright();
  fs.mkdirSync(path.dirname(out), { recursive: true });
  const browser = await chromium.launch();
  try {
    const page = await browser.newPage({ viewport: { width, height }, deviceScaleFactor: 1 });
    await page.goto(`file:///${html.replace(/\\/g, "/")}`);
    if (attrOverrides.length > 0) {
      await page.evaluate((overrides) => {
        for (const override of overrides) {
          const element = document.getElementById(override.id);
          if (!element) {
            continue;
          }
          element.setAttribute(override.name, override.value);
        }
      }, attrOverrides);
      await page.waitForTimeout(50);
    }
    if (scrollX || scrollY) {
      await page.evaluate(({ x, y }) => window.scrollTo(x, y), {
        x: scrollX,
        y: scrollY,
      });
      await page.waitForTimeout(50);
    }
    if (elementScrolls.length > 0) {
      await page.evaluate((scrolls) => {
        for (const scroll of scrolls) {
          const element = document.getElementById(scroll.id);
          if (!element) {
            continue;
          }
          element.scrollTo(scroll.x, scroll.y);
        }
      }, elementScrolls);
      await page.waitForTimeout(50);
    }
    const playwrightTimeMode = timeRequested ? "deterministic_web_animations_current_time" : "not_requested";
    if (timeRequested) {
      await page.evaluate(async (requestedTimeMs) => {
        await document.fonts.ready;
        for (const animation of document.getAnimations({ subtree: true })) {
          try {
            animation.pause();
            animation.currentTime = requestedTimeMs;
          } catch {
            // Ignore animations that cannot be controlled through Web Animations.
          }
        }
      }, timeMs);
      await page.waitForTimeout(50);
    }
    await page.screenshot({ path: out });
    if (outJson) {
      const state = await page.evaluate(() => ({
        scrollX: window.scrollX,
        scrollY: window.scrollY,
        innerWidth: window.innerWidth,
        innerHeight: window.innerHeight,
        documentWidth: Math.max(
          document.documentElement.scrollWidth,
          document.body ? document.body.scrollWidth : 0),
        documentHeight: Math.max(
          document.documentElement.scrollHeight,
          document.body ? document.body.scrollHeight : 0),
      }));
      state.interactiveElements = await page.evaluate(() => {
        const selector = [
          "input",
          "textarea",
          "select",
          "button",
          "a[href]",
          "[contenteditable]",
          "[tabindex]",
          "[role='button']",
          "[role='combobox']",
          "[role='textbox']",
        ].join(",");
        const clamp = (value, limit) => Math.max(0, Math.min(limit - 1, value));
        const points = [];
        let order = 0;
        const addPoint = (element, rect, pointKind, priority, x, y) => {
          points.push({
            tagName: element.tagName,
            id: element.id || "",
            name: element.getAttribute("name") || "",
            type: element.getAttribute("type") || "",
            role: element.getAttribute("role") || "",
            pointKind,
            priority,
            order: order++,
            x: clamp(x, window.innerWidth),
            y: clamp(y, window.innerHeight),
            width: rect.width,
            height: rect.height,
            rectLeft: rect.left,
            rectTop: rect.top,
            rectRight: rect.right,
            rectBottom: rect.bottom,
          });
        };
        for (const element of Array.from(document.querySelectorAll(selector))) {
            const rect = element.getBoundingClientRect();
            const style = window.getComputedStyle(element);
            const visible =
              rect.width > 0 &&
              rect.height > 0 &&
              rect.right >= 0 &&
              rect.bottom >= 0 &&
              rect.left <= window.innerWidth &&
              rect.top <= window.innerHeight &&
              style.visibility !== "hidden" &&
              style.display !== "none" &&
              Number(style.opacity || "1") > 0;
            if (!visible) {
              continue;
            }
            const tagName = element.tagName.toLowerCase();
            const inputType = (element.getAttribute("type") || "text").toLowerCase();
            const role = (element.getAttribute("role") || "").toLowerCase();
            const centerX = rect.left + rect.width / 2;
            const centerY = rect.top + rect.height / 2;
            if (tagName === "select" || role === "combobox") {
              addPoint(
                element,
                rect,
                "select-arrow",
                0,
                rect.right - Math.min(16, rect.width * 0.15),
                centerY);
              addPoint(element, rect, "select-center", 4, centerX, centerY);
              continue;
            }
            if (tagName === "input" &&
                (inputType === "checkbox" || inputType === "radio")) {
              addPoint(element, rect, `${inputType}-box`, 1, centerX, centerY);
              continue;
            }
            if (tagName === "textarea" ||
                role === "textbox" ||
                element.isContentEditable ||
                (tagName === "input" &&
                 !["button", "checkbox", "color", "file", "hidden", "image", "radio",
                   "range", "reset", "submit"].includes(inputType))) {
              addPoint(element, rect, "text-control", 2, centerX, centerY);
              continue;
            }
            addPoint(element, rect, "center", 3, centerX, centerY);
        }
        return points.sort((left, right) =>
          left.priority - right.priority || left.order - right.order);
      });
      state.elementScrolls = {};
      for (const scroll of elementScrolls) {
        state.elementScrolls[scroll.id] = await page.evaluate((id) => {
          const element = document.getElementById(id);
          return element
            ? { scrollLeft: element.scrollLeft, scrollTop: element.scrollTop }
            : null;
        }, scroll.id);
      }
      state.requestedTimeMs = timeMs;
      state.appliedTimeMs = timeMs > 0 ? timeMs : 0;
      state.playwrightTimeMode = playwrightTimeMode;
      fs.writeFileSync(outJson, JSON.stringify(state, null, 2));
    }
  } finally {
    await browser.close();
  }
}

main().catch((error) => {
  console.error(error && error.stack ? error.stack : String(error));
  process.exit(1);
});
