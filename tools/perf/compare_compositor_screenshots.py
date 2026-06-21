#!/usr/bin/env python3
"""Compare SDL compositor CopyOutput screenshots against Playwright output."""

from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time
from typing import Any

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
PAINT_AUDIT_ROOT = (
    ROOT / "upstream" / "chromium" / "standalone_renderer" / "testdata" / "paint_audit"
)
DEFAULT_VIEWER = (
    ROOT
    / "build"
    / "cmake-live-image-png-ninja-vs18"
    / "blink_standalone_sdl_viewer_skia.exe"
)
DEFAULT_PAGES = [
    "00_text_only.html",
    "01_solid_box.html",
    "02_gradient_rounded_border.html",
    "03_transform_opacity.html",
    "04_overflow_clip.html",
    "05_image_data_png.html",
    "05b_image_data_svg.html",
    "05k_image_local_svg_route_map.html",
    "28_form_controls_basic.html",
]


def parse_viewport(value: str) -> tuple[int, int]:
    if "x" not in value.lower():
        raise argparse.ArgumentTypeError("viewport must be WxH")
    width, height = value.lower().split("x", 1)
    return int(width), int(height)


def rel(path: Path) -> str:
    try:
        return path.resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        return str(path)


def parse_value(raw: str) -> Any:
    value = raw.strip()
    try:
        if any(ch in value for ch in ".eE"):
            return float(value)
        return int(value)
    except ValueError:
        return value


def parse_key_values(line: str) -> dict[str, Any]:
    row: dict[str, Any] = {}
    for match in re.finditer(r"(\w+)=([^\s]+)", line):
        row[match.group(1)] = parse_value(match.group(2))
    return row


def non_white_pixels(image: Image.Image) -> int:
    rgb = image.convert("RGB")
    return sum(1 for r, g, b in rgb.getdata() if r < 245 or g < 245 or b < 245)


def mean_absolute_diff(a: Image.Image, b: Image.Image) -> float:
    a = a.convert("RGB")
    b = b.convert("RGB")
    if a.size != b.size:
        b = b.resize(a.size)
    total = 0
    count = 0
    for pa, pb in zip(a.getdata(), b.getdata()):
        total += abs(pa[0] - pb[0]) + abs(pa[1] - pb[1]) + abs(pa[2] - pb[2])
        count += 3
    return total / max(1, count)


def run_command(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float, str]:
    start = time.perf_counter()
    try:
        completed = subprocess.run(
            cmd,
            cwd=ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
            encoding="utf-8",
            errors="replace",
        )
        output = completed.stdout
        code = completed.returncode
    except subprocess.TimeoutExpired as exc:
        output = exc.stdout if isinstance(exc.stdout, str) else ""
        output += f"\nTIMEOUT after {timeout}s\n"
        code = 124
    elapsed_ms = (time.perf_counter() - start) * 1000.0
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={code} elapsed_ms={elapsed_ms:.3f}\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return code, elapsed_ms, output


def first_frame_metrics(output: str) -> dict[str, Any]:
    for line in output.splitlines():
        text = line.strip()
        if text.startswith("frame="):
            return parse_key_values(text)
    return {}


def last_frame_metrics(output: str) -> dict[str, Any]:
    last: dict[str, Any] = {}
    for line in output.splitlines():
        text = line.strip()
        if text.startswith("frame="):
            last = parse_key_values(text)
    return last


def compare_page(
    viewer: Path,
    html_file: Path,
    out_dir: Path,
    viewport: str,
    timeout: int,
    screenshot_after_ms: int,
) -> dict[str, Any]:
    page_name = html_file.stem
    standalone_png = out_dir / f"{page_name}.standalone.png"
    reference_png = out_dir / f"{page_name}.playwright.png"
    viewer_log = out_dir / f"{page_name}.viewer.log"
    playwright_log = out_dir / f"{page_name}.playwright.log"
    width, height = parse_viewport(viewport)
    viewer_quit_after_ms = max(800, screenshot_after_ms + 700)

    viewer_cmd = [
        str(viewer.resolve()),
        "--html-file",
        str(html_file.resolve()),
        "--resource-root",
        str(html_file.parent.resolve()),
        "--viewport",
        viewport,
        "--quit-after-ms",
        str(viewer_quit_after_ms),
        "--screenshot-out",
        str(standalone_png.resolve()),
        "--screenshot-after-ms",
        str(max(0, screenshot_after_ms)),
    ]
    viewer_code, viewer_elapsed_ms, viewer_output = run_command(
        viewer_cmd, viewer_log, timeout
    )

    env = os.environ.copy()
    env.setdefault("npm_config_cache", str(out_dir / "npm-cache"))
    playwright_driver = out_dir / "_playwright_capture.js"
    playwright_driver.write_text(
        r"""
const { chromium } = require('playwright');

async function main() {
  const width = Number(process.argv[2]);
  const height = Number(process.argv[3]);
  const captureMs = Number(process.argv[4]);
  const url = process.argv[5];
  const outPath = process.argv[6];
  const browser = await chromium.launch();
  const page = await browser.newPage({ viewport: { width, height } });
  try {
    await page.goto(url, { waitUntil: 'load' });
    await page.evaluate(async (ms) => {
      await new Promise((resolve) => requestAnimationFrame(resolve));
      for (const animation of document.getAnimations({ subtree: true })) {
        try {
          animation.pause();
          animation.currentTime = ms;
        } catch (error) {
          // Ignore animations that cannot be manually sampled.
        }
      }
      await new Promise((resolve) => requestAnimationFrame(resolve));
    }, Math.max(0, captureMs));
    await page.screenshot({ path: outPath });
  } finally {
    await browser.close();
  }
}

main().catch((error) => {
  console.error(error && error.stack ? error.stack : error);
  process.exit(1);
});
""",
        encoding="utf-8",
    )
    playwright_cmd = [
        "node",
        str(playwright_driver.resolve()),
        str(width),
        str(height),
        str(max(0, screenshot_after_ms)),
        html_file.resolve().as_uri(),
        str(reference_png.resolve()),
    ]
    start = time.perf_counter()
    try:
        playwright_completed = subprocess.run(
            playwright_cmd,
            cwd=ROOT,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
            encoding="utf-8",
            errors="replace",
        )
        playwright_output = playwright_completed.stdout
        playwright_code = playwright_completed.returncode
    except subprocess.TimeoutExpired as exc:
        playwright_output = exc.stdout if isinstance(exc.stdout, str) else ""
        playwright_output += f"\nTIMEOUT after {timeout}s\n"
        playwright_code = 124
    playwright_elapsed_ms = (time.perf_counter() - start) * 1000.0
    playwright_log.write_text(
        f"$ {' '.join(playwright_cmd)}\nexit={playwright_code} "
        f"elapsed_ms={playwright_elapsed_ms:.3f}\n\n{playwright_output}",
        encoding="utf-8",
        errors="replace",
    )

    result: dict[str, Any] = {
        "page": html_file.name,
        "standalone_png": rel(standalone_png),
        "reference_png": rel(reference_png),
        "viewer_exit": viewer_code,
        "playwright_exit": playwright_code,
        "viewer_elapsed_ms": viewer_elapsed_ms,
        "playwright_elapsed_ms": playwright_elapsed_ms,
        "initial_frame_metrics": first_frame_metrics(viewer_output),
        "capture_frame_metrics": last_frame_metrics(viewer_output),
    }
    if standalone_png.exists() and reference_png.exists():
        standalone = Image.open(standalone_png).convert("RGB")
        reference = Image.open(reference_png).convert("RGB")
        standalone_non_white = non_white_pixels(standalone)
        reference_non_white = non_white_pixels(reference)
        result.update(
            {
                "standalone_size": list(standalone.size),
                "reference_size": list(reference.size),
                "standalone_non_white": standalone_non_white,
                "reference_non_white": reference_non_white,
                "coverage_ratio": standalone_non_white / max(1, reference_non_white),
                "mean_absolute_rgb_diff": mean_absolute_diff(standalone, reference),
            }
        )
    else:
        result["missing_artifacts"] = [
            name
            for name, path in (
                ("standalone", standalone_png),
                ("playwright", reference_png),
            )
            if not path.exists()
        ]
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--viewer", type=Path, default=DEFAULT_VIEWER)
    parser.add_argument("--paint-audit-root", type=Path, default=PAINT_AUDIT_ROOT)
    parser.add_argument("--page", action="append", default=[])
    parser.add_argument("--viewport", default="800x600")
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--timeout", type=int, default=90)
    parser.add_argument(
        "--screenshot-after-ms",
        type=int,
        default=250,
        help="Delay compositor CopyOutput capture so async resource updates can settle.",
    )
    args = parser.parse_args()

    if not args.viewer.exists():
        raise SystemExit(f"viewer not found: {args.viewer}")
    pages = args.page or DEFAULT_PAGES
    html_files = []
    for page in pages:
        path = Path(page)
        if not path.is_absolute():
            path = args.paint_audit_root / page
        if not path.exists():
            raise SystemExit(f"page not found: {path}")
        html_files.append(path)

    out_dir = args.out_dir.resolve()
    out_dir.mkdir(parents=True, exist_ok=True)
    results = [
        compare_page(
            args.viewer,
            html_file,
            out_dir,
            args.viewport,
            args.timeout,
            args.screenshot_after_ms,
        )
        for html_file in html_files
    ]
    summary = {
        "schema_version": 1,
        "viewer": rel(args.viewer),
        "viewport": args.viewport,
        "screenshot_after_ms": max(0, args.screenshot_after_ms),
        "page_count": len(results),
        "viewer_failure_count": sum(1 for item in results if item["viewer_exit"] != 0),
        "playwright_failure_count": sum(
            1 for item in results if item["playwright_exit"] != 0
        ),
        "results": results,
    }
    (out_dir / "comparison_results.json").write_text(
        json.dumps(summary, indent=2), encoding="utf-8"
    )
    print(json.dumps(summary, indent=2))
    if summary["viewer_failure_count"] or summary["playwright_failure_count"]:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
