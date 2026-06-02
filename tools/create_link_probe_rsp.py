#!/usr/bin/env python3
"""Create a build-directory-relative lld-link response file for diagnostics."""

from __future__ import annotations

import argparse
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


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--build-dir", required=True, type=Path)
    parser.add_argument("--base-rsp", required=True, type=Path)
    parser.add_argument("--out-rsp", required=True, type=Path)
    parser.add_argument("--skip-substring", action="append", default=[])
    parser.add_argument("--append", action="append", default=[])
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
