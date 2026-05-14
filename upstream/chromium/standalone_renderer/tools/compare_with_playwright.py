#!/usr/bin/env python3
"""Render validation against a Chromium/Playwright reference screenshot."""

from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

from PIL import Image


def parse_viewport(value: str) -> tuple[int, int]:
    if "x" not in value:
        raise argparse.ArgumentTypeError("viewport must be WxH")
    width, height = value.lower().split("x", 1)
    return int(width), int(height)


def non_white_pixels(image: Image.Image) -> int:
    rgb = image.convert("RGB")
    count = 0
    for r, g, b in rgb.getdata():
        if r < 245 or g < 245 or b < 245:
            count += 1
    return count


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


def run(args: argparse.Namespace) -> int:
    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    standalone_bmp = out_dir / "standalone.bmp"
    standalone_json = out_dir / "standalone.json"
    reference_png = out_dir / "playwright.png"
    html_file = out_dir / "reference.html"
    html_file.write_text(
        "<!doctype html><html><head><meta charset='utf-8'>"
        f"<style>{args.css}</style></head><body>{args.html}</body></html>",
        encoding="utf-8",
    )

    width, height = parse_viewport(args.viewport)
    renderer_cmd = [
        args.renderer_exe,
        "--html",
        args.html,
        "--css",
        args.css,
        "--viewport",
        args.viewport,
        "--out",
        str(standalone_bmp),
        "--json",
        str(standalone_json),
        "--min-non-white",
        str(args.min_non_white),
    ]
    if not args.no_mode_flag:
        if args.blink:
            renderer_cmd.append("--blink")
        else:
            renderer_cmd.append("--manual")
    if args.skia_cpu:
        renderer_cmd.append("--skia-cpu")
    if args.allow_transitional_blink:
        renderer_cmd.append("--allow-transitional-blink")

    renderer = subprocess.run(
        renderer_cmd,
        text=True,
        capture_output=True,
        encoding="utf-8",
        errors="replace",
    )

    env = os.environ.copy()
    env.setdefault("npm_config_cache", str(out_dir / "npm-cache"))
    playwright_cmd = [
        "npx.cmd",
        "playwright",
        "screenshot",
        "--browser=chromium",
        f"--viewport-size={width},{height}",
        html_file.resolve().as_uri(),
        str(reference_png),
    ]
    playwright = subprocess.run(
        playwright_cmd,
        text=True,
        capture_output=True,
        env=env,
        encoding="utf-8",
        errors="replace",
    )

    if not standalone_bmp.exists():
        sys.stderr.write(renderer.stdout)
        sys.stderr.write(renderer.stderr)
        return renderer.returncode or 1
    if not reference_png.exists():
        sys.stderr.write(playwright.stdout)
        sys.stderr.write(playwright.stderr)
        return playwright.returncode or 1

    standalone = Image.open(standalone_bmp).convert("RGB")
    reference = Image.open(reference_png).convert("RGB")
    standalone_non_white = non_white_pixels(standalone)
    reference_non_white = non_white_pixels(reference)
    coverage_ratio = standalone_non_white / max(1, reference_non_white)
    diff = mean_absolute_diff(standalone, reference)

    report = {
        "standalone_bmp": str(standalone_bmp),
        "playwright_png": str(reference_png),
        "renderer_exit": renderer.returncode,
        "playwright_exit": playwright.returncode,
        "standalone_non_white": standalone_non_white,
        "reference_non_white": reference_non_white,
        "coverage_ratio": coverage_ratio,
        "mean_absolute_rgb_diff": diff,
    }
    (out_dir / "comparison.json").write_text(
        json.dumps(report, indent=2), encoding="utf-8"
    )
    print(json.dumps(report, indent=2))

    if renderer.returncode != 0:
        return renderer.returncode
    if standalone_non_white < args.min_non_white:
        return 3
    if coverage_ratio < args.min_coverage_ratio:
        return 4
    if diff > args.max_mean_diff:
        return 5
    return 0


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--renderer-exe", required=True)
    parser.add_argument("--html", required=True)
    parser.add_argument("--css", default="")
    parser.add_argument("--viewport", default="800x600")
    parser.add_argument("--out-dir", default=None)
    parser.add_argument("--blink", action="store_true")
    parser.add_argument("--manual", dest="blink", action="store_false")
    parser.set_defaults(blink=True)
    parser.add_argument(
        "--no-mode-flag",
        action="store_true",
        help="Do not pass --blink/--manual to older or non-live benchmark executables.",
    )
    parser.add_argument("--skia-cpu", action="store_true")
    parser.add_argument(
        "--allow-transitional-blink",
        action="store_true",
        help="Allow the renderer executable to emit non-real transitional Blink output.",
    )
    parser.add_argument("--min-non-white", type=int, default=50)
    parser.add_argument("--min-coverage-ratio", type=float, default=0.05)
    parser.add_argument("--max-mean-diff", type=float, default=240.0)
    args = parser.parse_args()
    if args.out_dir is None:
        args.out_dir = tempfile.mkdtemp(prefix="blink_standalone_compare_")
    return run(args)


if __name__ == "__main__":
    raise SystemExit(main())
