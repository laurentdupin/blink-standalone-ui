#!/usr/bin/env python3
"""Audit the standalone Blink platform source cut before compiling.

The script consumes a Ninja `-t commands` dump for the probe target, extracts
Blink platform translation units, and scans their quoted include closure for
dependency families that should not be present in the standalone renderer
runtime. It is intentionally static: no compiler, Ninja executor, gclient, or
git process is launched.
"""

from __future__ import annotations

import argparse
import collections
import fnmatch
import json
import re
from pathlib import Path


SOURCE_RE = re.compile(r"(?:^|\s)(?:\.\./\.\./)?(?P<path>third_party[\\/].+?\.cc)(?:\s|$)")
INCLUDE_RE = re.compile(r"^\s*#\s*include\s+([<\"])([^>\"]+)[>\"]")

PLATFORM_PREFIX = "third_party/blink/renderer/platform/"

FORBIDDEN = [
    ("network", ["services/network/", "net/", "third_party/blink/public/common/loader/"]),
    ("gpu", ["gpu/", "components/viz/common/gpu/", "components/viz/common/resources/"]),
    ("viz-frame-sink", ["components/viz/common/quads/", "components/viz/common/surfaces/", "frame_sinks/"]),
    ("mojo", ["mojo/", ".mojom"]),
    ("media", ["media/", "third_party/blink/renderer/platform/media"]),
    ("webrtc", ["webrtc/", "peerconnection/", "third_party/blink/public/platform/web_rtc"]),
    ("browser-exported-api", ["third_party/blink/public/platform/web_url_", "web_graphics_context_3d"]),
    ("canvas-runtime", ["canvas_resource", "offscreen_canvas", "canvas_resource_provider"]),
    ("storage", ["/storage/", "storage/"]),
]

V8_FORBIDDEN = ("script-v8", ["bindings/core/v8/", "v8/"])

DEFAULT_SKIP = [
    "third_party/blink/renderer/platform/wtf/*",
    "third_party/blink/renderer/platform/heap/*",
    "third_party/blink/renderer/platform/fonts/*",
    "third_party/blink/renderer/platform/text/*",
    "third_party/blink/renderer/platform/geometry/*",
    "third_party/blink/renderer/platform/transforms/*",
    "third_party/blink/renderer/platform/image-decoders/*",
]


def norm(path: str | Path) -> str:
    return str(path).replace("\\", "/")


def extract_sources(commands: Path) -> list[str]:
    sources: set[str] = set()
    for line in commands.read_text(encoding="utf-8", errors="replace").splitlines():
        if " /c " not in line and " -c " not in line:
            continue
        for match in SOURCE_RE.finditer(line):
            source = norm(match.group("path"))
            if source.startswith(PLATFORM_PREFIX):
                sources.add(source)
    return sorted(sources)


def _eval_standalone_condition(line: str) -> bool | None:
    compact = re.sub(r"\s+", "", line)
    if "defined(STANDALONE_RENDERER_GN_PROBE)" in compact:
        return "!defined(STANDALONE_RENDERER_GN_PROBE)" not in compact
    if "STANDALONE_RENDERER_GN_PROBE" in compact:
        if compact.startswith("#ifdef"):
            return True
        if compact.startswith("#ifndef"):
            return False
    return None


def read_includes(path: Path) -> list[tuple[str, bool]]:
    includes: list[tuple[str, bool]] = []
    try:
        raw_lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError:
        return includes
    lines: list[str] = []
    current = ""
    for line in raw_lines:
        if line.rstrip().endswith("\\"):
            current += line.rstrip()[:-1]
            continue
        lines.append(current + line)
        current = ""
    if current:
        lines.append(current)
    active_stack: list[tuple[bool, bool | None]] = [(True, None)]
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("#if"):
            condition = _eval_standalone_condition(stripped)
            parent_active = active_stack[-1][0]
            active_stack.append(
                (parent_active and (condition if condition is not None else True), condition)
            )
            continue
        if stripped.startswith("#else") and len(active_stack) > 1:
            parent_active = active_stack[-2][0]
            condition = active_stack[-1][1]
            active_stack[-1] = (
                parent_active and ((not condition) if condition is not None else True),
                condition,
            )
            continue
        if stripped.startswith("#endif") and len(active_stack) > 1:
            active_stack.pop()
            continue
        if not active_stack[-1][0]:
            continue
        match = INCLUDE_RE.match(line)
        if not match:
            continue
        delimiter, include = match.groups()
        includes.append((include, delimiter == '"'))
    return includes


def resolve_include(root: Path, including_file: Path, include: str) -> Path | None:
    root_relative = root / include
    if root_relative.exists():
        return root_relative
    local_relative = including_file.parent / include
    if local_relative.exists():
        return local_relative
    return None


def forbidden_category(include_or_path: str, forbidden: list[tuple[str, list[str]]]) -> str | None:
    value = norm(include_or_path)
    for category, tokens in forbidden:
        for token in tokens:
            if token in value:
                return category
    return None


def should_skip_closure(source: str, skip: list[str]) -> bool:
    return any(fnmatch.fnmatch(source, pattern) for pattern in skip)


def scan_source(
    root: Path,
    source: str,
    max_depth: int,
    skip_closure: bool,
    forbidden: list[tuple[str, list[str]]],
) -> list[dict[str, str]]:
    findings: list[dict[str, str]] = []
    queue: collections.deque[tuple[Path, int]] = collections.deque()
    visited: set[str] = set()
    source_path = root / source
    queue.append((source_path, 0))

    while queue:
        path, depth = queue.popleft()
        path_norm = norm(path.relative_to(root)) if path.is_absolute() else norm(path)
        if path_norm in visited:
            continue
        visited.add(path_norm)

        path_category = forbidden_category(path_norm, forbidden)
        if path_category:
            findings.append(
                {
                    "source": source,
                    "from": path_norm,
                    "include": path_norm,
                    "category": path_category,
                    "kind": "path",
                }
            )

        if depth >= max_depth or (depth > 0 and skip_closure):
            continue

        for include, quoted in read_includes(path):
            category = forbidden_category(include, forbidden)
            if category:
                findings.append(
                    {
                        "source": source,
                        "from": path_norm,
                        "include": include,
                        "category": category,
                        "kind": "include",
                    }
                )
            if not quoted:
                continue
            resolved = resolve_include(root, path, include)
            if not resolved:
                continue
            try:
                resolved.relative_to(root)
            except ValueError:
                continue
            if resolved.suffix.lower() in {".h", ".hh", ".hpp", ".inc"}:
                queue.append((resolved, depth + 1))
    return findings


def source_group(source: str) -> str:
    relative = source.removeprefix(PLATFORM_PREFIX)
    parts = relative.split("/")
    if len(parts) >= 2:
        return f"{parts[0]}/{parts[1]}"
    return parts[0]


def print_text(findings: list[dict[str, str]], limit: int) -> None:
    by_category: dict[str, set[str]] = collections.defaultdict(set)
    by_group: dict[str, set[str]] = collections.defaultdict(set)
    by_source: dict[str, list[dict[str, str]]] = collections.defaultdict(list)
    for finding in findings:
        by_category[finding["category"]].add(finding["source"])
        by_group[source_group(finding["source"])].add(finding["source"])
        by_source[finding["source"]].append(finding)

    print(f"forbidden findings: {len(findings)}")
    print(f"affected sources: {len(by_source)}")
    print("")
    print("categories:")
    for category, sources in sorted(by_category.items()):
        print(f"  {category}: {len(sources)} sources")
    print("")
    print("suggested source clusters:")
    for group, sources in sorted(by_group.items(), key=lambda item: (-len(item[1]), item[0])):
        print(f"  {group}: {len(sources)} sources")
    print("")
    print("top source findings:")
    for source, rows in sorted(by_source.items())[:limit]:
        first = rows[0]
        print(f"  {source}")
        print(f"    {first['category']}: {first['include']} from {first['from']}")
        extra = len(rows) - 1
        if extra:
            print(f"    +{extra} more")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default=".")
    parser.add_argument("--commands", required=True)
    parser.add_argument("--max-depth", type=int, default=2)
    parser.add_argument("--limit", type=int, default=80)
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--include-v8", action="store_true")
    parser.add_argument("--skip", action="append", default=[])
    args = parser.parse_args()

    root = Path(args.root).resolve()
    commands = (root / args.commands).resolve()
    skip = DEFAULT_SKIP + args.skip
    forbidden = list(FORBIDDEN)
    if args.include_v8:
        forbidden.append(V8_FORBIDDEN)
    findings: list[dict[str, str]] = []
    for source in extract_sources(commands):
        findings.extend(
            scan_source(
                root,
                source,
                max_depth=args.max_depth,
                skip_closure=should_skip_closure(source, skip),
                forbidden=forbidden,
            )
        )

    if args.json:
        print(json.dumps(findings, indent=2, sort_keys=True))
    else:
        print_text(findings, args.limit)
    return 1 if findings else 0


if __name__ == "__main__":
    raise SystemExit(main())
