#!/usr/bin/env python3
"""Checks that the standalone renderer scaffold does not depend on forbidden services."""

import argparse
import pathlib
import sys


FORBIDDEN_TOKENS = [
    "//chrome",
    "//content",
    "//android_webview",
    "//ash",
    "//ios",
    "//extensions",
    "//remoting",
    "//pdf",
    "//printing",
    "//net",
    "//services/network",
    "//services/viz",
    "//gpu",
    "//device",
    "//media",
    "//mojo",
    "//third_party/webrtc",
    "//third_party/dawn",
    "//third_party/angle",
    "//v8/src",
    "v8::ScriptCompiler",
    "v8::Script::Compile",
    "v8::Function::Call",
    "fetch(",
    "XMLHttpRequest",
    "new Worker",
    "Worker(",
]

TEXT_SUFFIXES = {
    ".gn",
    ".gni",
    ".cmake",
    ".txt",
    ".h",
    ".cc",
    ".cpp",
    ".md",
    ".py",
}


def iter_files(root: pathlib.Path):
    for path in root.rglob("*"):
        relative = path.relative_to(root)
        if relative.parts and relative.parts[0] in {
            "_pydeps",
            "_tools",
            "out",
        }:
            continue
        if path.name in {
            "check_forbidden_deps.py",
            "inventory_chromium_cut.py",
            "print_blink_source_manifest.py",
            "trace_blink_include_closure.py",
        }:
            continue
        if relative.parts and relative.parts[0] == "docs":
            continue
        if path.is_file() and path.suffix in TEXT_SUFFIXES:
            yield path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", required=True)
    parser.add_argument("--stamp")
    args = parser.parse_args()

    root = pathlib.Path(args.root).resolve()
    failures = []
    for path in iter_files(root):
        text = path.read_text(encoding="utf-8", errors="ignore")
        for token in FORBIDDEN_TOKENS:
            if token in text:
                failures.append(f"{path.relative_to(root)}: forbidden token {token}")

    if failures:
        for failure in failures:
            print(failure, file=sys.stderr)
        return 1

    if args.stamp:
        pathlib.Path(args.stamp).write_text("ok\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
