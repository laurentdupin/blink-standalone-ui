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
        or standalone_doc.get("page_evidence")
        or raw_audit.get("page_evidence")
        or {}
    )
    playwright_elements = playwright.get("selectedElements") or {}
    selectors = sorted(set(standalone_elements.keys()) | set(playwright_elements.keys()))
    selected = {}
    for selector in selectors:
        standalone_selector = selector
        if selector == ".fixture-target" and selector not in standalone_elements:
            standalone_selector = "fixture-target"
        elif selector == "[data-debug-id]" and selector not in standalone_elements:
            standalone_selector = "data-debug-id"
        s = standalone_elements.get(standalone_selector) or {}
        p = playwright_elements.get(selector) or {}
        standalone_layout = s.get("layout") or {}
        standalone_spaces = standalone_layout.get("rect_coordinate_spaces") or {}
        standalone_viewport_rect = standalone_layout.get("viewport_rect")
        playwright_viewport_rect = p.get("boundingRect")
        rect_warning = None
        if standalone_viewport_rect is None and standalone_layout.get("layout_rect") is not None:
            rect_warning = "standalone layout_rect is local; not comparable to Playwright viewport DOMRect"
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
            "rect_coordinate_spaces": standalone_spaces,
            "local_layout_rect": {
                "standalone": standalone_layout.get("local_layout_rect") or standalone_layout.get("layout_rect"),
                "coordinate_space": standalone_spaces.get("local_layout_rect", "local_layout_object_coordinates"),
            },
            "viewport_rect": {
                "standalone": standalone_viewport_rect,
                "standalone_coordinate_space": standalone_spaces.get("viewport_rect"),
                "playwright": playwright_viewport_rect,
                "playwright_coordinate_space": "viewport_dom_rect",
                "warning": rect_warning,
            },
            "layout_rect_legacy_do_not_compare_to_playwright": {
                "standalone": standalone_layout.get("layout_rect"),
                "playwright": playwright_viewport_rect,
                "warning": "legacy field may be local on standalone and viewport-relative on Playwright",
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
        "summary": "Standalone setup diff labels rect coordinate spaces. Comparisons should use selected_elements.*.viewport_rect; legacy layout_rect is local and is not comparable to Playwright DOMRect without mapping.",
    }
    args.out_json.parent.mkdir(parents=True, exist_ok=True)
    args.out_json.write_text(json.dumps(diff, indent=2), encoding="utf-8")
    print(json.dumps(diff, indent=2))


if __name__ == "__main__":
    main()
