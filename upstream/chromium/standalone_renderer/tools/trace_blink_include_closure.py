#!/usr/bin/env python3
"""Trace local quoted-include closure for a Blink adapter seed.

The tracer is deliberately conservative. It follows quoted includes that can be
resolved inside the local checkout and reports missing, external, and blocked
paths. It does not invoke GN, gclient, Ninja, or the compiler.
"""

from __future__ import annotations

import argparse
import re
from collections import deque
from pathlib import Path


DEFAULT_SEEDS = [
    "third_party/blink/renderer/core/testing/dummy_page_holder.h",
    "third_party/blink/renderer/core/testing/dummy_page_holder.cc",
]

BLOCKED_PATH_TOKENS = [
    "services/network/",
    "services/service_manager/",
    "services/viz/",
    "gpu/",
    "media/",
    "mojo/",
    "third_party/blink/renderer/core/fetch/",
    "third_party/blink/renderer/core/loader/",
    "third_party/blink/renderer/core/workers/",
    "third_party/blink/renderer/core/xmlhttprequest/",
    "third_party/blink/renderer/bindings/core/v8/",
    "v8/",
]

INCLUDE_RE = re.compile(r"^\s*#\s*include\s+([<\"])([^>\"]+)[>\"]")


def normalize(path: Path | str) -> str:
    return str(path).replace("\\", "/")


def is_blocked(relative: str) -> str:
    normalized = normalize(relative)
    for token in BLOCKED_PATH_TOKENS:
        if token in normalized:
            return token
    return ""


def resolve_include(root: Path, including_file: Path, include: str) -> Path | None:
    root_relative = root / include
    if root_relative.exists():
        return root_relative

    local_relative = including_file.parent / include
    if local_relative.exists():
        return local_relative

    return None


def read_includes(path: Path) -> tuple[list[tuple[str, bool]], list[str]]:
    includes: list[tuple[str, bool]] = []
    errors: list[str] = []
    try:
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError as exc:
        return includes, [f"{normalize(path)}: {exc}"]

    for line in lines:
        match = INCLUDE_RE.match(line)
        if not match:
            continue
        delimiter, include = match.groups()
        includes.append((include, delimiter == '"'))
    return includes, errors


def trace(root: Path, seeds: list[str], max_files: int) -> dict[str, object]:
    queue = deque()
    visited: set[Path] = set()
    blocked: list[tuple[str, str]] = []
    missing: list[tuple[str, str]] = []
    external: list[tuple[str, str]] = []
    errors: list[str] = []

    for seed in seeds:
        path = (root / seed).resolve()
        if path.exists():
            queue.append(path)
        else:
            missing.append(("<seed>", seed))

    while queue and len(visited) < max_files:
        path = queue.popleft()
        if path in visited:
            continue
        visited.add(path)

        relative = normalize(path.relative_to(root))
        blocked_token = is_blocked(relative)
        if blocked_token:
            blocked.append((relative, blocked_token))

        includes, read_errors = read_includes(path)
        errors.extend(read_errors)
        for include, quoted in includes:
            if not quoted:
                external.append((relative, include))
                continue

            resolved = resolve_include(root, path, include)
            if resolved is None:
                missing.append((relative, include))
                continue

            try:
                resolved.relative_to(root)
            except ValueError:
                external.append((relative, include))
                continue

            if resolved.suffix.lower() in {".h", ".cc", ".hh", ".hpp", ".cpp", ".inc"}:
                queue.append(resolved.resolve())

    return {
        "visited": sorted(normalize(path.relative_to(root)) for path in visited),
        "blocked": sorted(set(blocked)),
        "missing": sorted(set(missing)),
        "external": sorted(set(external)),
        "errors": errors,
        "truncated": bool(queue),
        "max_files": max_files,
    }


def print_summary(report: dict[str, object], show: str) -> None:
    print(f"visited: {len(report['visited'])}")
    print(f"blocked: {len(report['blocked'])}")
    print(f"missing: {len(report['missing'])}")
    print(f"external/system: {len(report['external'])}")
    print(f"truncated: {report['truncated']}")

    if show == "summary":
        return

    rows = report[show]
    for row in rows:
        if isinstance(row, tuple):
            print("\t".join(row))
        else:
            print(row)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default=".")
    parser.add_argument("--seed", action="append", default=[])
    parser.add_argument("--max-files", type=int, default=5000)
    parser.add_argument(
        "--show",
        choices=["summary", "visited", "blocked", "missing", "external", "errors"],
        default="summary",
    )
    args = parser.parse_args()

    seeds = args.seed or DEFAULT_SEEDS
    report = trace(Path(args.root).resolve(), seeds, args.max_files)
    print_summary(report, args.show)
    return 1 if report["errors"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
