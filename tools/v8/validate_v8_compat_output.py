#!/usr/bin/env python3
"""Validate generated V8 compatibility outputs needed by the CMake link."""

from __future__ import annotations

import argparse
from pathlib import Path
import sys


def read_object_names(path: Path) -> list[str]:
    names: list[str] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("#"):
            continue
        names.append(stripped)
    return names


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--monolith-lib", required=True, type=Path)
    parser.add_argument(
        "--toolchain",
        choices=("chromium-clang", "msvc"),
        default="chromium-clang",
        help="V8 compatibility toolchain used for the generated output.",
    )
    parser.add_argument(
        "--v8-include-dir",
        type=Path,
        help="Generated V8 public include root used by renderer compilation.",
    )
    parser.add_argument("--libcxx-object-dir", type=Path)
    parser.add_argument("--object-list", type=Path)
    parser.add_argument(
        "--build-hint",
        default=(
            "Configure with BLINK_STANDALONE_V8_COMPAT_ACTION=build and "
            "BLINK_STANDALONE_V8_SYNC_DEPS=ON, then build "
            "blink_standalone_v8_compat; or point "
            "BLINK_STANDALONE_V8_COMPAT_WORK_ROOT / "
            "BLINK_STANDALONE_V8_COMPAT_OUT_DIR at an existing generated "
            "compatibility build."
        ),
    )
    args = parser.parse_args()

    missing: list[Path] = []
    if not args.monolith_lib.is_file():
        missing.append(args.monolith_lib)

    if args.toolchain == "msvc":
        if not args.v8_include_dir:
            missing.append(Path("<missing --v8-include-dir>"))
        else:
            cppgc_heap_header = args.v8_include_dir / "cppgc" / "heap.h"
            if not cppgc_heap_header.is_file():
                missing.append(cppgc_heap_header)
            else:
                cppgc_heap_text = cppgc_heap_header.read_text(
                    encoding="utf-8", errors="replace"
                )
                has_msvc_stack_marker = "_AddressOfReturnAddress" in cppgc_heap_text
                has_raw_builtin_stack_marker = (
                    "__builtin_frame_address" in cppgc_heap_text
                    and "_AddressOfReturnAddress" not in cppgc_heap_text
                )
                if not has_msvc_stack_marker or has_raw_builtin_stack_marker:
                    print(
                        "V8/CppGC compatibility public headers are not "
                        "MSVC-patched.",
                        file=sys.stderr,
                    )
                    print(
                        "Expected cppgc/heap.h to use _AddressOfReturnAddress() "
                        "for native cl.exe; found an unpatched header at:",
                        file=sys.stderr,
                    )
                    print(f"  {cppgc_heap_header}", file=sys.stderr)
                    print(
                        "Configure with BLINK_STANDALONE_V8_COMPAT_ACTION=prepare "
                        "or build so the V8 MSVC patch queue is applied, or point "
                        "BLINK_STANDALONE_V8_INCLUDE_DIR at a prepared MSVC V8 "
                        "compatibility work copy.",
                        file=sys.stderr,
                    )
                    return 1

    object_names: list[str] = []
    if args.libcxx_object_dir or args.object_list:
        if not args.libcxx_object_dir or not args.object_list:
            parser.error(
                "--libcxx-object-dir and --object-list must be passed together"
            )
        if not args.libcxx_object_dir.is_dir():
            missing.append(args.libcxx_object_dir)
        object_names = read_object_names(args.object_list)
        if args.libcxx_object_dir.is_dir():
            for object_name in object_names:
                object_path = args.libcxx_object_dir / object_name
                if not object_path.is_file():
                    missing.append(object_path)

    if missing:
        print("V8/CppGC compatibility output is incomplete.", file=sys.stderr)
        print(f"Missing {len(missing)} required path(s):", file=sys.stderr)
        for path in missing[:50]:
            print(f"  {path}", file=sys.stderr)
        if len(missing) > 50:
            print(f"  ... and {len(missing) - 50} more", file=sys.stderr)
        print(args.build_hint, file=sys.stderr)
        return 1

    print(
        "V8/CppGC compatibility output is present: "
        f"{args.monolith_lib}"
        + (
            f" and {len(object_names)} libc++ objects."
            if object_names
            else "."
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
