#!/usr/bin/env python3
"""Aggregate content-aware comparison JSON files."""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--input-dir", required=True, type=Path)
    parser.add_argument("--out-json", required=True, type=Path)
    parser.add_argument("--glob", default="*-content-compare.json")
    args = parser.parse_args()

    rows = []
    for path in sorted(args.input_dir.rglob(args.glob)):
        data = json.loads(path.read_text(encoding="utf-8"))
        rows.append({
            "name": path.stem.replace("-content-compare", ""),
            "path": str(path),
            "changed_percent_full_viewport": data.get("changed_percent_full_viewport", 0),
            "changed_percent_union_content_bbox": data.get("changed_percent_union_content_bbox", 0),
            "changed_percent_playwright_content_bbox": data.get("changed_percent_playwright_content_bbox", 0),
            "standalone_non_background_pixels": data.get("standalone_non_background_pixels", 0),
            "playwright_non_background_pixels": data.get("playwright_non_background_pixels", 0),
            "missing_content_percent": data.get("missing_content_percent", 0),
            "extra_content_percent": data.get("extra_content_percent", 0),
            "blank_or_nearly_blank": data.get("blank_or_nearly_blank", False),
            "background": data.get("background"),
            "threshold": data.get("threshold"),
        })

    rows.sort(
        key=lambda row: (
            not row["blank_or_nearly_blank"],
            -float(row["missing_content_percent"]),
            -float(row["changed_percent_union_content_bbox"]),
        )
    )
    summary = {
        "sort": [
            "blank_or_nearly_blank first",
            "missing_content_percent descending",
            "changed_percent_union_content_bbox descending",
        ],
        "count": len(rows),
        "rows": rows,
    }
    args.out_json.parent.mkdir(parents=True, exist_ok=True)
    args.out_json.write_text(json.dumps(summary, indent=2), encoding="utf-8")
    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    main()
