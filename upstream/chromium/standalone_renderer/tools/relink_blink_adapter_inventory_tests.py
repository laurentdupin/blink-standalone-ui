#!/usr/bin/env python3
"""Rebuild blink_adapter_inventory_tests without invoking Ninja.

Ninja regeneration is unreliable in this checkout, but the existing
`ninja -t commands` dump contains enough information to recompile the small
standalone adapter policy surface directly.
"""

from __future__ import annotations

import argparse
import pathlib
import subprocess
import sys

import relink_blink_tree_builder_probe as relink


COMPILE_FILTERS = (
    "standalone_renderer/tests/blink_adapter_inventory_test.cc",
    "standalone_renderer/src/blink_adapter.cc",
    "standalone_renderer/src/blink_lifecycle_shim.cc",
    "standalone_renderer/src/blink_page_embedder.cc",
    "standalone_renderer/src/blink_runtime_adapter.cc",
    "standalone_renderer/src/blink_runtime_environment.cc",
    "standalone_renderer/src/standalone_frame.cc",
)

EXE_FILTERED_LINK_INPUT_SUBSTRINGS = relink.FILTERED_LINK_INPUT_SUBSTRINGS + (
    "third_party/blink/renderer/core/standalone_core_probe/",
    "third_party\\blink\\renderer\\core\\standalone_core_probe\\",
)


def compile_sources(
    out_dir: pathlib.Path,
    commands: list[str],
    timeout: int,
) -> int:
    for source_filter in COMPILE_FILTERS:
        normalized_filter = source_filter.replace("\\", "/")
        matches = [
            command
            for command in commands
            if "clang-cl.exe" in command
            and normalized_filter in command.replace("\\", "/")
        ]
        if not matches:
            print(f"missing compile command for {source_filter}")
            return 2
        args = [
            arg
            for arg in relink.split_command_line(matches[-1])
            if not arg.lower().startswith("/showincludes")
        ]
        executable = relink.resolve_executable(out_dir, args[0])
        rsp_path = out_dir / (
            "direct.recompile." + pathlib.Path(source_filter).stem + ".rsp"
        )
        rsp_path.write_text(subprocess.list2cmdline(args[1:]), encoding="utf-8")
        result = subprocess.run(
            [str(executable), "@" + str(rsp_path)],
            cwd=out_dir,
            shell=False,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
            timeout=timeout,
        )
        print(f"{source_filter} EXIT {result.returncode}")
        if result.stdout:
            print(result.stdout[-12000:])
        if result.returncode:
            return result.returncode
    return 0


def run_first_matching_link(
    out_dir: pathlib.Path,
    commands: list[str],
    needle: str,
    timeout: int,
    filter_rsp_inputs: bool = False,
) -> int:
    matches = [
        command
        for command in commands
        if "lld-link.exe" in command and needle in command
    ]
    if not matches:
        print(f"missing link command for {needle}")
        return 2
    args = relink.split_command_line(matches[-1])
    executable = relink.resolve_executable(out_dir, args[0])
    link_args = args[1:]
    if filter_rsp_inputs:
        filtered_args: list[str] = []
        for arg in link_args:
            if not arg.startswith("@"):
                filtered_args.append(arg)
                continue
            rsp_path = (out_dir / arg[1:]).resolve()
            inputs = rsp_path.read_text(encoding="utf-8", errors="replace").splitlines()
            filtered_inputs = [
                item
                for item in inputs
                if not any(
                    skip in item for skip in EXE_FILTERED_LINK_INPUT_SUBSTRINGS
                )
            ]
            filtered_rsp_path = out_dir / (
                pathlib.Path(arg[1:]).stem + ".filtered.rsp"
            )
            filtered_rsp_path.write_text(
                "\n".join(filtered_inputs) + "\n", encoding="utf-8"
            )
            filtered_args.append("@" + str(filtered_rsp_path))
        link_args = filtered_args
    result = subprocess.run(
        [str(executable)] + link_args,
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    if result.stdout:
        print(result.stdout[-12000:])
    print(f"{needle} LINK EXIT {result.returncode}")
    return result.returncode


def run_test(out_dir: pathlib.Path, timeout: int) -> int:
    executable = out_dir / "blink_adapter_inventory_tests.exe"
    result = subprocess.run(
        [str(executable)],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    if result.stdout:
        print(result.stdout[-12000:])
    print(f"RUN EXIT {result.returncode}")
    return result.returncode


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out-dir", type=pathlib.Path, default="generated/blink_live")
    parser.add_argument(
        "--commands",
        type=pathlib.Path,
        default="generated/blink_live/blink_adapter_inventory_tests.commands.txt",
    )
    parser.add_argument("--compile-timeout", type=int, default=120)
    parser.add_argument("--link-timeout", type=int, default=120)
    parser.add_argument("--run-timeout", type=int, default=20)
    parser.add_argument("--no-run", action="store_true")
    args = parser.parse_args()

    out_dir = args.out_dir.resolve()
    commands = relink.read_commands(args.commands.resolve())

    exit_code = compile_sources(out_dir, commands, args.compile_timeout)
    if exit_code:
        return exit_code

    exit_code = run_first_matching_link(
        out_dir,
        commands,
        "html_css_renderer_blink_runtime_adapter.lib",
        args.link_timeout,
    )
    if exit_code:
        return exit_code

    exit_code = run_first_matching_link(
        out_dir,
        commands,
        "blink_adapter_inventory_tests.exe",
        args.link_timeout,
        filter_rsp_inputs=True,
    )
    if exit_code or args.no_run:
        return exit_code
    return run_test(out_dir, args.run_timeout)


if __name__ == "__main__":
    sys.exit(main())
