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
V8_ACTIONS = ("plan", "prepare", "gn-gen", "build")
DEPOT_TOOLS_WORK_DIR_NAME = "depot_tools"

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


def run(
    cmd: list[str],
    *,
    cwd: Path | None = None,
    extra_path: Path | None = None,
    extra_env: dict[str, str] | None = None,
) -> None:
    print("+ " + " ".join(cmd), flush=True)
    env = None
    if extra_path or extra_env:
        env = os.environ.copy()
        if extra_path:
            env["PATH"] = str(extra_path) + os.pathsep + env.get("PATH", "")
        if extra_env:
            env.update(extra_env)
    subprocess.run(cmd, cwd=str(cwd) if cwd else None, env=env, check=True)


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


def find_tool(
    explicit: str | None,
    name: str,
    depot_tools: Path | None,
    *,
    allow_python_entrypoint: bool,
) -> list[str] | None:
    if depot_tools:
        depot_tools = depot_tools.resolve()
    if explicit:
        explicit_path = Path(explicit).resolve()
        python_payload_marker = depot_tools / "python3_bin_reldir.txt" if depot_tools else None
        python_entrypoint = depot_tools / f"{name}.py" if depot_tools else None
        if (allow_python_entrypoint and os.name == "nt" and depot_tools and
                explicit_path.suffix.lower() in (".bat", ".cmd") and
                python_entrypoint and python_entrypoint.exists() and
                python_payload_marker and not python_payload_marker.exists()):
            return [sys.executable, str(python_entrypoint)]
        return [str(explicit_path)]
    if depot_tools:
        python_payload_marker = depot_tools / "python3_bin_reldir.txt"
        python_entrypoint = depot_tools / f"{name}.py"
        if (allow_python_entrypoint and os.name == "nt" and
                python_entrypoint.exists() and not python_payload_marker.exists()):
            return [sys.executable, str(python_entrypoint)]
        for candidate in tool_names(name):
            path = depot_tools / candidate
            if path.exists():
                return [str(path)]
    search_path = os.environ.get("PATH", "")
    if depot_tools:
        search_path = str(depot_tools) + os.pathsep + search_path
    for candidate in tool_names(name):
        found = shutil.which(candidate, path=search_path)
        if found:
            return [found]
    return None


def source_commit(source_v8_root: Path) -> str:
    return capture(["git", "-C", str(source_v8_root), "rev-parse", "HEAD"])


def ensure_git_work_copy(source_root: Path, work_copy_root: Path, commit: str, label: str) -> None:
    if not work_copy_root.exists():
        work_copy_root.parent.mkdir(parents=True, exist_ok=True)
        run([
            "git",
            "clone",
            "--shared",
            "--no-checkout",
            str(source_root),
            str(work_copy_root),
        ])
    elif not (work_copy_root / ".git").exists():
        raise RuntimeError(f"{label} work copy exists but is not a git checkout: {work_copy_root}")

    run(["git", "-C", str(work_copy_root), "remote", "set-url", "origin", str(source_root)])
    run(["git", "-C", str(work_copy_root), "fetch", "origin", commit, "--depth=1"])
    run(["git", "-C", str(work_copy_root), "checkout", "--detach", commit])


def ensure_work_copy(source_v8_root: Path, v8_work_root: Path, commit: str) -> None:
    ensure_git_work_copy(source_v8_root, v8_work_root, commit, "V8")


def ensure_depot_tools_work_copy(source_depot_tools_root: Path, depot_tools_work_root: Path) -> str:
    commit = source_commit(source_depot_tools_root)
    ensure_git_work_copy(source_depot_tools_root, depot_tools_work_root, commit, "depot_tools")
    return commit


def ensure_windows_git_bat(depot_tools_root: Path) -> None:
    if os.name != "nt":
        return
    git_bat = depot_tools_root / "git.bat"
    if git_bat.exists():
        return
    git_exe = shutil.which("git.exe") or shutil.which("git")
    if not git_exe:
        raise RuntimeError("git is required, and no git.exe was found on PATH.")
    write_file(git_bat, f'@echo off\n"{git_exe}" %*\n')


def write_file(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8", newline="\n")


def format_tool(command: list[str] | None) -> str:
    return " ".join(command) if command else "<not found>"


def remap_depot_tools_explicit(
    explicit: str | None,
    source_depot_tools_root: Path | None,
    effective_depot_tools_root: Path | None,
) -> str | None:
    if not explicit or not source_depot_tools_root or not effective_depot_tools_root:
        return explicit
    if source_depot_tools_root == effective_depot_tools_root:
        return explicit
    explicit_path = Path(explicit).resolve()
    try:
        relative_path = explicit_path.relative_to(source_depot_tools_root)
    except ValueError:
        return explicit
    return str(effective_depot_tools_root / relative_path)


def print_plan(args: argparse.Namespace, commit: str, paths: dict[str, Path], tools: dict[str, list[str] | None]) -> None:
    print("V8 compatibility build plan")
    print(f"  action: {args.action}")
    print(f"  source_v8_root: {paths['source_v8_root']}")
    print(f"  source_commit: {commit}")
    print(f"  work_root: {paths['work_root']}")
    print(f"  generated_gclient_root: {paths['gclient_root']}")
    print(f"  generated_v8_work_copy: {paths['v8_work_root']}")
    print(f"  output_dir: {paths['out_dir']}")
    if paths.get("source_depot_tools_root"):
        print(f"  source_depot_tools_root: {paths['source_depot_tools_root']}")
    if paths.get("effective_depot_tools_root"):
        print(f"  effective_depot_tools_root: {paths['effective_depot_tools_root']}")
    if paths.get("effective_depot_tools_commit"):
        print(f"  effective_depot_tools_commit: {paths['effective_depot_tools_commit']}")
    print(f"  git_cache_root: {paths['git_cache_root']}")
    print(f"  sync_deps: {args.sync_deps}")
    print(f"  gclient: {format_tool(tools['gclient'])}")
    print(f"  gn: {format_tool(tools['gn'])}")
    print(f"  ninja: {format_tool(tools['ninja'])}")
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
    parser.add_argument(
        "--action",
        choices=V8_ACTIONS,
        help=(
            "Wrapper stage to run: plan prints paths only; prepare creates the "
            "generated work copy, .gclient, optional sync, and args.gn; gn-gen "
            "also runs gn gen; build also runs ninja v8_monolith."
        ),
    )
    parser.add_argument(
        "--build",
        action="store_true",
        help="Compatibility alias for --action build.",
    )
    parser.add_argument(
        "--print-plan",
        action="store_true",
        help="Compatibility alias for --action plan.",
    )
    args = parser.parse_args(list(argv))

    requested_actions = []
    if args.action:
        requested_actions.append(args.action)
    if args.build:
        requested_actions.append("build")
    if args.print_plan:
        requested_actions.append("plan")
    if requested_actions:
        selected = requested_actions[0]
        if any(action != selected for action in requested_actions):
            parser.error("--action, --build, and --print-plan requested conflicting actions")
        args.action = selected
    else:
        args.action = "plan"
    return args


def main(argv: Iterable[str]) -> int:
    args = parse_args(argv)

    source_v8_root = args.source_v8_root.resolve()
    source_depot_tools_root = args.depot_tools.resolve() if args.depot_tools else None
    work_root = args.work_root.resolve()
    gclient_root = work_root / "src"
    v8_work_root = gclient_root / "v8"
    depot_tools_work_root = work_root / DEPOT_TOOLS_WORK_DIR_NAME
    git_cache_root = work_root / "git_cache"
    out_dir = (args.out_dir.resolve() if args.out_dir else v8_work_root / "out" / args.out_name)

    if not (source_v8_root / "include" / "v8-version.h").exists():
        raise RuntimeError(f"--source-v8-root does not look like a V8 checkout: {source_v8_root}")
    if source_depot_tools_root and not (source_depot_tools_root / "gclient.py").exists():
        raise RuntimeError(f"--depot-tools does not look like a depot_tools checkout: {source_depot_tools_root}")

    commit = source_commit(source_v8_root)
    effective_depot_tools_root = source_depot_tools_root
    effective_depot_tools_commit: str | None = None
    allow_python_entrypoint = True
    if args.action != "plan" and source_depot_tools_root:
        effective_depot_tools_commit = ensure_depot_tools_work_copy(source_depot_tools_root, depot_tools_work_root)
        effective_depot_tools_root = depot_tools_work_root
        ensure_windows_git_bat(effective_depot_tools_root)
        allow_python_entrypoint = False
    gclient_explicit = remap_depot_tools_explicit(
        args.gclient,
        source_depot_tools_root,
        effective_depot_tools_root,
    )
    gn_explicit = remap_depot_tools_explicit(
        args.gn,
        source_depot_tools_root,
        effective_depot_tools_root,
    )
    tools = {
        "gclient": find_tool(
            gclient_explicit,
            "gclient",
            effective_depot_tools_root,
            allow_python_entrypoint=allow_python_entrypoint,
        ),
        "gn": find_tool(
            gn_explicit,
            "gn",
            effective_depot_tools_root,
            allow_python_entrypoint=True,
        ),
        "ninja": find_tool(
            args.ninja,
            "ninja",
            effective_depot_tools_root,
            allow_python_entrypoint=allow_python_entrypoint,
        ),
    }
    paths = {
        "source_v8_root": source_v8_root,
        "source_depot_tools_root": source_depot_tools_root,
        "effective_depot_tools_root": effective_depot_tools_root,
        "effective_depot_tools_commit": effective_depot_tools_commit,
        "git_cache_root": git_cache_root,
        "work_root": work_root,
        "gclient_root": gclient_root,
        "v8_work_root": v8_work_root,
        "out_dir": out_dir,
    }

    if args.action == "plan":
        print_plan(args, commit, paths, tools)
        return 0
    print_plan(args, commit, paths, tools)

    ensure_work_copy(source_v8_root, v8_work_root, commit)
    write_file(gclient_root / ".gclient", gclient_text("https://chromium.googlesource.com/v8/v8.git"))
    generated_env = {
        "GIT_CACHE_PATH": str(git_cache_root),
    }

    if args.sync_deps:
        if not tools["gclient"]:
            raise RuntimeError("gclient is required for --sync-deps; pass --gclient or --depot-tools.")
        run(
            [*tools["gclient"], "sync", "--no-history"],
            cwd=gclient_root,
            extra_path=effective_depot_tools_root,
            extra_env=generated_env,
        )

    write_file(out_dir / "args.gn", gn_args_text(args.clang_base_path))
    if args.action == "prepare":
        return 0

    if not tools["gn"]:
        raise RuntimeError(f"gn is required for --action {args.action}; pass --gn or put gn on PATH.")
    run(
        [*tools["gn"], "gen", str(out_dir)],
        cwd=v8_work_root,
        extra_path=effective_depot_tools_root,
        extra_env=generated_env,
    )
    if args.action == "gn-gen":
        return 0

    if not tools["ninja"]:
        raise RuntimeError("ninja is required for --action build; pass --ninja or put ninja on PATH.")
    ninja_cmd = [*tools["ninja"], "-C", str(out_dir)]
    if args.jobs:
        ninja_cmd.append(f"-j{args.jobs}")
    ninja_cmd.append("v8_monolith")
    run(ninja_cmd, cwd=v8_work_root, extra_path=effective_depot_tools_root, extra_env=generated_env)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv[1:]))
    except subprocess.CalledProcessError as exc:
        raise SystemExit(exc.returncode)
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
