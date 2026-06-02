#!/usr/bin/env python3
"""Create a build-directory-relative lld-link response file for diagnostics."""

from __future__ import annotations

import argparse
import re
import shlex
from pathlib import Path


def normalize_path(path_text: str, root: Path, build_dir: Path) -> str:
    text = path_text.strip()
    quoted = len(text) >= 2 and text[0] == '"' and text[-1] == '"'
    if quoted:
        text = text[1:-1]

    path = Path(text)
    if not path.is_absolute() and (root / path).exists():
        path = (root / path).resolve()
    if path.is_absolute():
        try:
            text = str(path.relative_to(build_dir))
        except ValueError:
            text = str(path)

    return f'"{text}"' if quoted or " " in text else text


def cmake_source_to_obj(source_text: str, object_dir: Path) -> Path | None:
    source = source_text.strip()
    if not source.endswith((".cc", ".cpp", ".cxx", ".c")):
        return None
    source = source.replace("${BLINK_STANDALONE_CHROMIUM_ROOT}", "upstream/chromium")
    source = source.replace("${CMAKE_CURRENT_SOURCE_DIR}", ".")
    source = source.lstrip("/")
    return object_dir / f"{source}.obj"


def append_live_sources(
    entries: list[str],
    *,
    root: Path,
    build_dir: Path,
    live_sources_file: Path,
    source_substrings: list[str],
    skip_substrings: list[str],
    object_dir: Path,
) -> None:
    source_pattern = re.compile(r"\$\{[^}]+\}/[^)\s]+|[A-Za-z0-9_./\\-]+\.(?:cc|cpp|cxx|c)")
    for line in live_sources_file.read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("#"):
            continue
        match = source_pattern.search(stripped)
        if not match:
            continue
        source = match.group(0).replace("\\", "/")
        if any(token in source for token in skip_substrings):
            continue
        if source_substrings and not any(token in source for token in source_substrings):
            continue
        obj = cmake_source_to_obj(source, object_dir)
        if obj is None:
            continue
        entries.append(normalize_path(str(obj), root, build_dir))


def dedupe_preserving_order(entries: list[str]) -> list[str]:
    seen: set[str] = set()
    result: list[str] = []
    for entry in entries:
        key = entry.strip().strip('"').replace("\\", "/").lower()
        if key in seen:
            continue
        seen.add(key)
        result.append(entry)
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--build-dir", required=True, type=Path)
    parser.add_argument("--base-rsp", required=True, type=Path)
    parser.add_argument("--out-rsp", required=True, type=Path)
    parser.add_argument("--skip-substring", action="append", default=[])
    parser.add_argument("--append", action="append", default=[])
    parser.add_argument("--append-live-sources-from", type=Path)
    parser.add_argument("--append-live-source-substring", action="append", default=[])
    parser.add_argument(
        "--object-dir",
        type=Path,
        default=Path("CMakeFiles/blink_standalone_render_benchmark_skia.dir"),
    )
    parser.add_argument("--verify", action="store_true")
    args = parser.parse_args()

    root = Path.cwd()
    build_dir = (root / args.build_dir).resolve()
    base_rsp = (root / args.base_rsp).resolve()
    out_rsp = (root / args.out_rsp).resolve()

    entries: list[str] = []
    for line in base_rsp.read_text().splitlines():
        for token in shlex.split(line, posix=False):
            stripped = token.strip()
            if not stripped:
                continue
            if any(skip in stripped for skip in args.skip_substring):
                continue
            entries.append(normalize_path(stripped, root, build_dir))

    for item in args.append:
        item_path = Path(item)
        if not item_path.is_absolute():
            item_path = (root / item_path).resolve()
        try:
            rel = item_path.relative_to(build_dir)
            entries.append(str(rel))
        except ValueError:
            entries.append(f'"{item_path}"')

    if args.append_live_sources_from:
        live_sources_file = (root / args.append_live_sources_from).resolve()
        object_dir = args.object_dir
        if not object_dir.is_absolute():
            object_dir = build_dir / object_dir
        append_live_sources(
            entries,
            root=root,
            build_dir=build_dir,
            live_sources_file=live_sources_file,
            source_substrings=args.append_live_source_substring,
            skip_substrings=args.skip_substring,
            object_dir=object_dir,
        )

    entries = dedupe_preserving_order(entries)

    if args.verify:
        missing = []
        for entry in entries:
            token = entry.strip().strip('"')
            is_local_lib = token.endswith(".lib") and ("\\" in token or "/" in token)
            if (token.endswith(".obj") or is_local_lib) and not (build_dir / token).exists():
                candidate = Path(token)
                if not candidate.is_absolute() or not candidate.exists():
                    missing.append(token)
        if missing:
            print(f"missing inputs: {len(missing)}")
            for token in missing[:50]:
                print(token)
            return 2

    out_rsp.parent.mkdir(parents=True, exist_ok=True)
    out_rsp.write_text("\n".join(entries) + "\n")
    print(f"wrote {out_rsp} ({len(entries)} entries)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
