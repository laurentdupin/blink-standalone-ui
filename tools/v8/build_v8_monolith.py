#!/usr/bin/env python3
"""Prepare or build the standalone V8 compatibility monolith.

This script intentionally works in a generated work root, never inside the
tracked Chromium snapshot. The source input is the pinned V8 submodule, and the
generated checkout lives under --work-root/src/v8 so gclient can own dependency
material without colliding with upstream/chromium.
"""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
from typing import Iterable


DEFAULT_OUT_NAME = "chromium_static"

GN_ARG_VALUES: list[tuple[str, object]] = [
    ("is_debug", False),
    ("target_cpu", "x64"),
    ("v8_target_cpu", "x64"),
    ("is_component_build", False),
    ("v8_monolithic", True),
    ("v8_static_library", True),
    ("v8_use_external_startup_data", False),
    ("use_lld", True),
    ("is_clang", True),
    ("clang_use_chrome_plugins", False),
    ("treat_warnings_as_errors", False),
    ("use_custom_libcxx", True),
    ("enable_safe_libcxx", True),
    ("v8_enable_pointer_compression", True),
    ("v8_enable_pointer_compression_shared_cage", True),
    ("v8_enable_webassembly", False),
    ("v8_enable_i18n_support", False),
    ("v8_enable_v8_checks", False),
    ("v8_enable_temporal_support", False),
    ("v8_enable_fuzztest", False),
    ("enable_rust", False),
    ("use_allocator_shim", False),
    ("use_partition_alloc_as_malloc", False),
    ("use_siso", False),
    ("use_remoteexec", False),
    ("symbol_level", 1),
]


GCLIENT_CUSTOM_VARS: dict[str, object] = {
    "checkout_android": False,
    "checkout_chromium": False,
    "checkout_fuchsia": False,
    "checkout_fuchsia_boot_images": "",
    "checkout_ios": False,
    "checkout_src_internal": False,
    "checkout_v8_builtins_pgo_profiles": False,
    "checkout_v8_perf": False,
    "download_gcmole": False,
    "download_jsfunfuzz": False,
}


def run(cmd: list[str], *, cwd: Path | None = None) -> None:
    print("+ " + " ".join(cmd), flush=True)
    subprocess.run(cmd, cwd=str(cwd) if cwd else None, check=True)


def capture(cmd: list[str], *, cwd: Path | None = None) -> str:
    return subprocess.check_output(cmd, cwd=str(cwd) if cwd else None, text=True).strip()


def quote_gn_value(value: object) -> str:
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, int):
        return str(value)
    if isinstance(value, str):
        escaped = value.replace("\\", "\\\\").replace('"', '\\"')
        return f'"{escaped}"'
    raise TypeError(f"Unsupported GN arg type: {type(value)!r}")


def gn_args_text(clang_base_path: str | None) -> str:
    values = list(GN_ARG_VALUES)
    if clang_base_path:
        values.append(("clang_base_path", clang_base_path.replace("\\", "/")))
    return "".join(f"{key}={quote_gn_value(value)}\n" for key, value in values)


def gclient_text(v8_url: str) -> str:
    vars_lines = []
    for key in sorted(GCLIENT_CUSTOM_VARS):
        value = repr(GCLIENT_CUSTOM_VARS[key])
        vars_lines.append(f'      "{key}": {value},')
    custom_vars = "\n".join(vars_lines)
    return f"""solutions = [
  {{
    "name": "v8",
    "url": "{v8_url}",
    "deps_file": "DEPS",
    "managed": False,
    "custom_vars": {{
{custom_vars}
    }},
  }},
]
target_os = []
"""


def tool_names(name: str) -> list[str]:
    suffixes = [".bat", ".cmd", ".exe", "", ".py"] if os.name == "nt" else ["", ".py"]
    names = []
    for suffix in suffixes:
        candidate = name if not suffix else f"{name}{suffix}"
        if candidate not in names:
            names.append(candidate)
    return names


def find_tool(explicit: str | None, name: str, depot_tools: Path | None) -> str | None:
    if explicit:
        return explicit
    if depot_tools:
        for candidate in tool_names(name):
            path = depot_tools / candidate
            if path.exists():
                return str(path)
    search_path = os.environ.get("PATH", "")
    if depot_tools:
        search_path = str(depot_tools) + os.pathsep + search_path
    for candidate in tool_names(name):
        found = shutil.which(candidate, path=search_path)
        if found:
            return found
    return None


def source_commit(source_v8_root: Path) -> str:
    return capture(["git", "-C", str(source_v8_root), "rev-parse", "HEAD"])


def ensure_work_copy(source_v8_root: Path, v8_work_root: Path, commit: str) -> None:
    if not v8_work_root.exists():
        v8_work_root.parent.mkdir(parents=True, exist_ok=True)
        run([
            "git",
            "clone",
            "--shared",
            "--no-checkout",
            str(source_v8_root),
            str(v8_work_root),
        ])
    elif not (v8_work_root / ".git").exists():
        raise RuntimeError(f"V8 work copy exists but is not a git checkout: {v8_work_root}")

    run(["git", "-C", str(v8_work_root), "remote", "set-url", "origin", str(source_v8_root)])
    run(["git", "-C", str(v8_work_root), "fetch", "origin", commit, "--depth=1"])
    run(["git", "-C", str(v8_work_root), "checkout", "--detach", commit])


def write_file(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8", newline="\n")


def print_plan(args: argparse.Namespace, commit: str, paths: dict[str, Path], tools: dict[str, str | None]) -> None:
    print("V8 compatibility build plan")
    print(f"  source_v8_root: {paths['source_v8_root']}")
    print(f"  source_commit: {commit}")
    print(f"  work_root: {paths['work_root']}")
    print(f"  generated_gclient_root: {paths['gclient_root']}")
    print(f"  generated_v8_work_copy: {paths['v8_work_root']}")
    print(f"  output_dir: {paths['out_dir']}")
    print(f"  sync_deps: {args.sync_deps}")
    print(f"  build: {args.build}")
    print(f"  gclient: {tools['gclient'] or '<not found>'}")
    print(f"  gn: {tools['gn'] or '<not found>'}")
    print(f"  ninja: {tools['ninja'] or '<not found>'}")
    print("  gn_args:")
    for line in gn_args_text(args.clang_base_path).splitlines():
        print(f"    {line}")


def parse_args(argv: Iterable[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source-v8-root", required=True, type=Path)
    parser.add_argument("--work-root", required=True, type=Path)
    parser.add_argument("--out-name", default=DEFAULT_OUT_NAME)
    parser.add_argument("--out-dir", type=Path)
    parser.add_argument("--gn")
    parser.add_argument("--ninja")
    parser.add_argument("--gclient")
    parser.add_argument("--depot-tools", type=Path)
    parser.add_argument("--jobs", type=int)
    parser.add_argument("--clang-base-path")
    parser.add_argument("--sync-deps", dest="sync_deps", action="store_true")
    parser.add_argument("--no-sync-deps", dest="sync_deps", action="store_false")
    parser.set_defaults(sync_deps=False)
    parser.add_argument("--build", action="store_true", help="Run gn gen and ninja v8_monolith.")
    parser.add_argument("--print-plan", action="store_true", help="Print paths and GN args without cloning, syncing, or building.")
    return parser.parse_args(list(argv))


def main(argv: Iterable[str]) -> int:
    args = parse_args(argv)

    source_v8_root = args.source_v8_root.resolve()
    work_root = args.work_root.resolve()
    gclient_root = work_root / "src"
    v8_work_root = gclient_root / "v8"
    out_dir = (args.out_dir.resolve() if args.out_dir else v8_work_root / "out" / args.out_name)

    if not (source_v8_root / "include" / "v8-version.h").exists():
        raise RuntimeError(f"--source-v8-root does not look like a V8 checkout: {source_v8_root}")

    commit = source_commit(source_v8_root)
    tools = {
        "gclient": find_tool(args.gclient, "gclient", args.depot_tools),
        "gn": find_tool(args.gn, "gn", args.depot_tools),
        "ninja": find_tool(args.ninja, "ninja", args.depot_tools),
    }
    paths = {
        "source_v8_root": source_v8_root,
        "work_root": work_root,
        "gclient_root": gclient_root,
        "v8_work_root": v8_work_root,
        "out_dir": out_dir,
    }

    if args.print_plan or not args.build:
        print_plan(args, commit, paths, tools)
        if not args.build:
            return 0

    ensure_work_copy(source_v8_root, v8_work_root, commit)
    write_file(gclient_root / ".gclient", gclient_text("https://chromium.googlesource.com/v8/v8.git"))

    if args.sync_deps:
        if not tools["gclient"]:
            raise RuntimeError("gclient is required for --sync-deps; pass --gclient or --depot-tools.")
        run([tools["gclient"], "sync", "--no-history"], cwd=gclient_root)

    if not tools["gn"]:
        raise RuntimeError("gn is required for --build; pass --gn or put gn on PATH.")
    if not tools["ninja"]:
        raise RuntimeError("ninja is required for --build; pass --ninja or put ninja on PATH.")

    write_file(out_dir / "args.gn", gn_args_text(args.clang_base_path))
    run([tools["gn"], "gen", str(out_dir)], cwd=v8_work_root)
    ninja_cmd = [tools["ninja"], "-C", str(out_dir)]
    if args.jobs:
        ninja_cmd.append(f"-j{args.jobs}")
    ninja_cmd.append("v8_monolith")
    run(ninja_cmd, cwd=v8_work_root)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv[1:]))
    except subprocess.CalledProcessError as exc:
        raise SystemExit(exc.returncode)
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
