#!/usr/bin/env python3
"""Small setup-diff helper for standalone-vs-Playwright page setup JSON."""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def load(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def nested_get(value: dict, keys: list[str], default=None):
    current = value
    for key in keys:
        if not isinstance(current, dict):
            return default
        current = current.get(key)
    return current if current is not None else default


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--standalone", required=True, type=Path)
    parser.add_argument("--playwright", required=True, type=Path)
    parser.add_argument("--out-json", required=True, type=Path)
    args = parser.parse_args()
    standalone_doc = load(args.standalone)
    standalone = standalone_doc.get("page_setup", {})
    raw_audit = standalone_doc.get("raw_audit") or {}
    playwright = load(args.playwright).get("playwright_setup", {})
    body = playwright.get("bodyComputedStyle") or {}
    html = playwright.get("htmlComputedStyle") or {}
    standalone_elements = (
        standalone.get("selected_elements")
        or standalone.get("selectedElements")
        or raw_audit.get("page_evidence")
        or {}
    )
    playwright_elements = playwright.get("selectedElements") or {}
    selectors = sorted(set(standalone_elements.keys()) | set(playwright_elements.keys()))
    selected = {}
    for selector in selectors:
        s = standalone_elements.get(selector) or {}
        p = playwright_elements.get(selector) or {}
        selected[selector] = {
            "present": {
                "standalone": s.get("present"),
                "playwright": p.get("present"),
            },
            "layout_object_type": {
                "standalone": nested_get(s, ["layout", "object_type"]),
                "playwright": p.get("interface"),
            },
            "display": {
                "standalone": nested_get(s, ["computed_style", "display"]),
                "playwright": nested_get(p, ["computedStyle", "display"]),
            },
            "position": {
                "standalone": nested_get(s, ["computed_style", "position"]),
                "playwright": nested_get(p, ["computedStyle", "position"]),
            },
            "box_sizing": {
                "standalone": nested_get(s, ["computed_style", "box_sizing"]),
                "playwright": nested_get(p, ["computedStyle", "boxSizing"]),
            },
            "width": {
                "standalone": nested_get(s, ["computed_style", "width"]),
                "playwright": nested_get(p, ["computedStyle", "width"]),
            },
            "height": {
                "standalone": nested_get(s, ["computed_style", "height"]),
                "playwright": nested_get(p, ["computedStyle", "height"]),
            },
            "layout_rect": {
                "standalone": nested_get(s, ["layout", "layout_rect"]),
                "playwright": p.get("boundingRect"),
            },
        }

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
        "selected_elements": selected,
        "selected_element_rects_playwright": playwright.get("selectedElementRects"),
        "summary": "Standalone and Playwright setup dumps include comparable selected-element computed-style and rect fields where available; unknown/inaccessible fields are preserved as null/status values.",
    }
    args.out_json.parent.mkdir(parents=True, exist_ok=True)
    args.out_json.write_text(json.dumps(diff, indent=2), encoding="utf-8")
    print(json.dumps(diff, indent=2))


if __name__ == "__main__":
    main()
