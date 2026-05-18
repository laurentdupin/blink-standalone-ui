#!/usr/bin/env python3
"""Small setup-diff helper for standalone-vs-Playwright page setup JSON."""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def load(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--standalone", required=True, type=Path)
    parser.add_argument("--playwright", required=True, type=Path)
    parser.add_argument("--out-json", required=True, type=Path)
    args = parser.parse_args()
    standalone = load(args.standalone).get("page_setup", {})
    playwright = load(args.playwright).get("playwright_setup", {})
    body = playwright.get("bodyComputedStyle") or {}
    html = playwright.get("htmlComputedStyle") or {}
    diff = {
        "standalone": str(args.standalone),
        "playwright": str(args.playwright),
        "viewport": {
            "standalone": standalone.get("viewport"),
            "playwright": playwright.get("viewport"),
        },
        "device_scale_factor": {
            "standalone": standalone.get("device_scale_factor"),
            "playwright": playwright.get("deviceScaleFactor"),
        },
        "base_url": {
            "standalone": standalone.get("base_url"),
            "playwright": playwright.get("baseURI"),
        },
        "body_margin": {
            "standalone": "see raw_audit/page_evidence when available",
            "playwright": body.get("margin"),
        },
        "body_rect": {
            "standalone": standalone.get("body_layout_rect"),
            "playwright": playwright.get("bodyRect"),
        },
        "font": {
            "standalone": standalone.get("default_font"),
            "playwright_body": body.get("font"),
            "playwright_html": html.get("font"),
        },
        "media_query_environment": {
            "standalone": standalone.get("media_query_environment"),
            "playwright": playwright.get("mediaQueryEnvironment"),
        },
        "selected_element_rects_playwright": playwright.get("selectedElementRects"),
        "summary": "Standalone setup dump currently carries viewport/base/style-source context and embeds raw_audit; Playwright setup contains computed style and DOMRect values.",
    }
    args.out_json.parent.mkdir(parents=True, exist_ok=True)
    args.out_json.write_text(json.dumps(diff, indent=2), encoding="utf-8")
    print(json.dumps(diff, indent=2))


if __name__ == "__main__":
    main()
