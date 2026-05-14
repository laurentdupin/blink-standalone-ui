#!/usr/bin/env python3
"""Inventory the local Chromium checkout for the standalone renderer cut."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Iterable


KEEP_PATHS = [
    "third_party/blink/renderer/core",
    "third_party/blink/renderer/platform",
    "third_party/blink/renderer/bindings",
    "third_party/blink/renderer/core/dom",
    "third_party/blink/renderer/core/html",
    "third_party/blink/renderer/core/css",
    "third_party/blink/renderer/core/style",
    "third_party/blink/renderer/core/layout",
    "third_party/blink/renderer/core/paint",
    "third_party/blink/renderer/core/page",
    "third_party/blink/renderer/core/frame",
    "third_party/blink/renderer/core/events",
    "third_party/blink/renderer/core/input",
    "third_party/blink/renderer/core/scroll",
    "third_party/blink/renderer/core/animation",
    "third_party/blink/renderer/core/geometry",
    "third_party/blink/renderer/core/svg",
    "third_party/blink/renderer/core/mathml",
    "third_party/blink/renderer/core/testing/dummy_page_holder.h",
    "third_party/blink/renderer/core/testing/dummy_page_holder.cc",
    "cc/paint",
    "cc/base",
    "third_party/skia",
    "ui/gfx/geometry",
    "ui/color",
    "third_party/icu",
    "third_party/harfbuzz",
    "third_party/ots",
    "third_party/libpng",
    "third_party/libjpeg_turbo",
    "third_party/libwebp",
    "third_party/zlib",
]

TOOL_PATHS = [
    ".gclient",
    "../.gclient",
    "buildtools/win/gn.exe",
    "third_party/depot_tools/gclient.bat",
    "third_party/depot_tools/gn.bat",
]

BUILD_FILES_TO_SCAN = [
    "third_party/blink/renderer/core/BUILD.gn",
    "third_party/blink/renderer/platform/BUILD.gn",
]

FORBIDDEN_TOKENS = [
    "//chrome",
    "//content",
    "//services/network",
    "//services/service_manager",
    "//services/viz",
    "//gpu",
    "//mojo",
    "//media",
    "//third_party/blink/renderer/core/xmlhttprequest",
    "//third_party/blink/renderer/core/workers",
    "//third_party/blink/renderer/core/fetch",
    "//third_party/blink/renderer/bindings/core/v8",
    "//v8",
    "XMLHttpRequest",
    "Worker",
    "fetch",
]


def count_files(path: Path) -> int:
    if path.is_file():
        return 1
    if not path.is_dir():
        return 0
    return sum(1 for child in path.rglob("*") if child.is_file())


def scan_forbidden(root: Path, files: Iterable[str]) -> list[dict[str, object]]:
    findings: list[dict[str, object]] = []
    for relative in files:
        path = root / relative
        if not path.exists():
            findings.append({"file": relative, "missing": True, "matches": []})
            continue

        matches = []
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        for line_number, line in enumerate(lines, start=1):
            for token in FORBIDDEN_TOKENS:
                if token in line:
                    matches.append({
                        "line": line_number,
                        "token": token,
                        "text": line.strip(),
                    })
        findings.append({"file": relative, "missing": False, "matches": matches})
    return findings


def build_report(root: Path) -> dict[str, object]:
    keep = []
    for relative in KEEP_PATHS:
        path = root / relative
        keep.append({
            "path": relative,
            "present": path.exists(),
            "type": "file" if path.is_file() else "directory" if path.is_dir() else "missing",
            "file_count": count_files(path),
        })

    tools = []
    for relative in TOOL_PATHS:
        path = (root / relative).resolve()
        tools.append({"path": relative, "present": path.exists()})

    return {
        "root": str(root.resolve()),
        "tooling": tools,
        "keep_paths": keep,
        "forbidden_build_edges": scan_forbidden(root, BUILD_FILES_TO_SCAN),
    }


def print_human(report: dict[str, object]) -> None:
    print(f"Chromium root: {report['root']}")
    print()
    print("Tooling:")
    for item in report["tooling"]:
        marker = "ok" if item["present"] else "missing"
        print(f"  [{marker}] {item['path']}")

    print()
    print("Keep paths:")
    for item in report["keep_paths"]:
        marker = "ok" if item["present"] else "missing"
        print(f"  [{marker}] {item['path']} ({item['file_count']} files)")

    print()
    print("Forbidden build edges in broad Blink targets:")
    for file_report in report["forbidden_build_edges"]:
        if file_report["missing"]:
            print(f"  [missing] {file_report['file']}")
            continue
        matches = file_report["matches"]
        print(f"  {file_report['file']}: {len(matches)} matches")
        for match in matches[:20]:
            print(f"    L{match['line']}: {match['token']} :: {match['text']}")
        if len(matches) > 20:
            print(f"    ... {len(matches) - 20} more")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default=".", help="Chromium checkout root")
    parser.add_argument("--json", action="store_true", help="Emit JSON")
    args = parser.parse_args()

    report = build_report(Path(args.root))
    if args.json:
        print(json.dumps(report, indent=2))
    else:
        print_human(report)

    missing_keep = [item["path"] for item in report["keep_paths"] if not item["present"]]
    return 2 if missing_keep else 0


if __name__ == "__main__":
    raise SystemExit(main())
