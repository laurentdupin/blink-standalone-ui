#!/usr/bin/env python3
"""Print a rough source manifest for the local Blink renderer cut."""

from __future__ import annotations

import argparse
from pathlib import Path


CANDIDATE_ROOTS = [
    ("dom", "third_party/blink/renderer/core/dom"),
    ("html", "third_party/blink/renderer/core/html"),
    ("css", "third_party/blink/renderer/core/css"),
    ("style", "third_party/blink/renderer/core/style"),
    ("layout", "third_party/blink/renderer/core/layout"),
    ("paint", "third_party/blink/renderer/core/paint"),
    ("page", "third_party/blink/renderer/core/page"),
    ("frame", "third_party/blink/renderer/core/frame"),
    ("events", "third_party/blink/renderer/core/events"),
    ("input", "third_party/blink/renderer/core/input"),
    ("scroll", "third_party/blink/renderer/core/scroll"),
    ("animation", "third_party/blink/renderer/core/animation"),
    ("geometry", "third_party/blink/renderer/core/geometry"),
    ("svg", "third_party/blink/renderer/core/svg"),
    ("mathml", "third_party/blink/renderer/core/mathml"),
    ("platform-fonts", "third_party/blink/renderer/platform/fonts"),
    ("platform-graphics", "third_party/blink/renderer/platform/graphics"),
    ("platform-geometry", "third_party/blink/renderer/platform/geometry"),
    ("platform-text", "third_party/blink/renderer/platform/text"),
    ("platform-transforms", "third_party/blink/renderer/platform/transforms"),
    ("platform-wtf", "third_party/blink/renderer/platform/wtf"),
    ("cc-paint", "cc/paint"),
    ("cc-base", "cc/base"),
    ("gfx-geometry", "ui/gfx/geometry"),
    ("ui-color", "ui/color"),
]

REJECTED_PATH_TOKENS = [
    "/ad_tracker/",
    "/accessibility/",
    "/bluetooth/",
    "/canvas/",
    "/clipboard/",
    "/content_capture/",
    "/credentialmanagement/",
    "/encryptedmedia/",
    "/fetch/",
    "/fileapi/",
    "/geolocation/",
    "/indexeddb/",
    "/inspector/",
    "/loader/",
    "/media/",
    "/messaging/",
    "/mojo/",
    "/navigation_api/",
    "/notifications/",
    "/offscreencanvas/",
    "/payments/",
    "/permissions/",
    "/presentation/",
    "/push_messaging/",
    "/serial/",
    "/service_worker/",
    "/speech/",
    "/storage/",
    "/streams/",
    "/webdatabase/",
    "/webgpu/",
    "/webrtc/",
    "/workers/",
    "/xmlhttprequest/",
]


def reason(path: str) -> str:
    wrapped = "/" + path.replace("\\", "/")
    for token in REJECTED_PATH_TOKENS:
        if token in wrapped:
            return f"blocked path token {token}"
    if "_test." in path or "_fuzzer." in path or "mock_" in path:
        return "test or fuzz-only source"
    return ""


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default=".")
    parser.add_argument("--show", choices=["summary", "accepted", "rejected"], default="summary")
    args = parser.parse_args()

    root = Path(args.root)
    accepted = []
    rejected = []
    for category, relative_root in CANDIDATE_ROOTS:
        absolute_root = root / relative_root
        if not absolute_root.is_dir():
            continue
        for path in absolute_root.rglob("*"):
            if path.suffix not in {".cc", ".h", ".cpp", ".hpp"}:
                continue
            relative = path.relative_to(root).as_posix()
            rejection = reason(relative)
            row = (category, relative, rejection)
            if rejection:
                rejected.append(row)
            else:
                accepted.append(row)

    if args.show == "summary":
        print(f"accepted: {len(accepted)}")
        print(f"rejected: {len(rejected)}")
        return 0

    rows = accepted if args.show == "accepted" else rejected
    for category, relative, rejection in rows:
        if rejection:
            print(f"{category}\t{relative}\t{rejection}")
        else:
            print(f"{category}\t{relative}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
