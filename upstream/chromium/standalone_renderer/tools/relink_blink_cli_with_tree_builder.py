#!/usr/bin/env python3
"""Relink the Blink CLI with the standalone tree-builder bridge.

Normal Ninja currently tries to regenerate GN files, which is blocked in this
checkout by missing third_party deps. This helper reuses existing command dumps
and only recompiles the files touched by the standalone Blink tree-builder path.
"""

from __future__ import annotations

import argparse
import pathlib
import subprocess
import sys

import relink_blink_tree_builder_probe as relink


CLI_COMPILE_FILTERS = (
    "standalone_renderer/examples/render_blink_cli.cc",
    "standalone_renderer/src/blink_lifecycle_shim.cc",
    "standalone_renderer/src/blink_page_embedder.cc",
    "standalone_renderer/src/blink_runtime_adapter.cc",
    "standalone_renderer/src/blink_runtime_environment.cc",
    "standalone_renderer/src/standalone_frame.cc",
)

RENDERER_COMPILE_FILTERS = (
    "standalone_renderer/src/cpu_renderer.cc",
    "standalone_renderer/src/draw_command_serializer.cc",
    "standalone_renderer/src/incremental_damage.cc",
    "standalone_renderer/src/paint_translator.cc",
    "standalone_renderer/src/render_frame.cc",
    "standalone_renderer/src/renderer.cc",
    "standalone_renderer/src/retained_scene.cc",
)

TREE_BUILDER_COMPILE_FILTERS = (
    "core/html/parser/html_element_stack.cc",
    "core/html/parser/html_construction_site.cc",
    "core/html/parser/html_tree_builder.cc",
    "core/standalone_tree_builder_dom_shim.cc",
)

TREE_BUILDER_OBJECT_PREFIX = (
    "obj/third_party/blink/renderer/core/standalone_core_tree_builder_probe/"
)

EXTRA_DEFINES_BY_SOURCE = {
    "standalone_renderer/src/blink_runtime_adapter.cc": (),
    "core/html/parser/html_element_stack.cc": (
        "/DSTANDALONE_RENDERER_GN_PROBE=1",
    ),
    "core/html/parser/html_construction_site.cc": (
        "/DSTANDALONE_RENDERER_GN_PROBE=1",
    ),
    "core/html/parser/html_tree_builder.cc": (
        "/DSTANDALONE_RENDERER_GN_PROBE=1",
    ),
}


def read_commands(path: pathlib.Path) -> list[str]:
    data = path.read_bytes()
    if data.startswith(b"\xff\xfe") or data.startswith(b"\xfe\xff"):
        return data.decode("utf-16", errors="replace").splitlines()
    return data.decode("utf-8-sig", errors="replace").splitlines()


def compile_sources_from_commands(
    out_dir: pathlib.Path,
    commands: list[str],
    source_filters: tuple[str, ...],
    timeout: int,
) -> int:
    for source_filter in source_filters:
        normalized_filter = source_filter.replace("\\", "/")
        matches = [
            command
            for command in commands
            if "clang-cl.exe" in command
            and normalized_filter in command.replace("\\", "/")
        ]
        if not matches:
            templated_sources = {
                "standalone_renderer/src/render_frame.cc": (
                    "../../standalone_renderer/src/render_frame.cc",
                    "obj/standalone_renderer/html_css_renderer/render_frame.obj",
                ),
                "standalone_renderer/src/paint_translator.cc": (
                    "../../standalone_renderer/src/paint_translator.cc",
                    "obj/standalone_renderer/html_css_renderer/paint_translator.obj",
                ),
            }
            if normalized_filter not in templated_sources:
                print(f"missing compile command for {source_filter}")
                return 2
            replacement_source, replacement_object = templated_sources[
                normalized_filter
            ]
            template_matches = [
                command
                for command in commands
                if "clang-cl.exe" in command
                and "standalone_renderer/src/retained_scene.cc"
                in command.replace("\\", "/")
            ]
            if not template_matches:
                print(f"missing compile command for {source_filter}")
                return 2
            matches = [
                template_matches[0]
                .replace(
                    "../../standalone_renderer/src/retained_scene.cc",
                    replacement_source,
                )
                .replace(
                    "obj/standalone_renderer/html_css_renderer/retained_scene.obj",
                    replacement_object,
                )
            ]

        args = [
            arg
            for arg in relink.split_command_line(matches[0])
            if not arg.lower().startswith("/showincludes")
        ]
        forced_include = (
            "/FI../../standalone_renderer/stubs/"
            "standalone_network_namespace_forwards.h"
        )
        if (
            normalized_filter.startswith("core/")
            or normalized_filter.startswith("gen/third_party/blink/renderer/core/")
        ) and forced_include not in args:
            args.insert(1, forced_include)
        for define in EXTRA_DEFINES_BY_SOURCE.get(normalized_filter, ()):
            if define not in args:
                args.append(define)
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


def collect_cli_link_inputs(
    out_dir: pathlib.Path,
    cli_commands: list[str],
    tree_commands: list[str],
) -> list[str]:
    inputs = relink.collect_link_inputs(out_dir, cli_commands)
    for item in relink.collect_link_inputs(out_dir, tree_commands):
        normalized = item.replace("\\", "/")
        if normalized.endswith("/blink_tree_builder_link_probe.obj"):
            continue
        if item not in inputs:
            inputs.append(item)
    retained_scene_obj = "obj/standalone_renderer/html_css_renderer/retained_scene.obj"
    if retained_scene_obj not in inputs and (out_dir / retained_scene_obj).exists():
        inputs.append(retained_scene_obj)
    render_frame_obj = "obj/standalone_renderer/html_css_renderer/render_frame.obj"
    if render_frame_obj not in inputs and (out_dir / render_frame_obj).exists():
        inputs.append(render_frame_obj)
    paint_translator_obj = "obj/standalone_renderer/html_css_renderer/paint_translator.obj"
    if paint_translator_obj not in inputs and (out_dir / paint_translator_obj).exists():
        inputs.append(paint_translator_obj)
    for command in tree_commands:
        if "clang-cl.exe" not in command:
            continue
        for arg in relink.split_command_line(command):
            if not arg.startswith("/Fo"):
                continue
            obj = arg[3:].strip('"').replace("\\", "/")
            if not obj.startswith(TREE_BUILDER_OBJECT_PREFIX):
                continue
            if obj not in inputs and (out_dir / obj).exists():
                inputs.append(obj)
    return inputs


def link_cli(
    out_dir: pathlib.Path,
    cli_commands: list[str],
    tree_commands: list[str],
    timeout: int,
) -> int:
    link_commands = [
        command
        for command in cli_commands
        if "lld-link.exe" in command and "html_css_renderer_blink_cli.exe" in command
    ]
    if not link_commands:
        print("missing link command for html_css_renderer_blink_cli.exe")
        return 2

    args = relink.split_command_line(link_commands[-1])
    executable = relink.resolve_executable(out_dir, args[0])
    link_args = [arg for arg in args[1:] if not arg.startswith("@")]
    inputs = collect_cli_link_inputs(out_dir, cli_commands, tree_commands)
    rsp_path = out_dir / "html_css_renderer_blink_cli.tree_builder_bridge.rsp"
    rsp_path.write_text(subprocess.list2cmdline(inputs), encoding="utf-8")
    result = subprocess.run(
        [str(executable)] + link_args + ["@" + str(rsp_path), "/errorlimit:0"],
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
    print(f"LINK EXIT {result.returncode}")
    return result.returncode


def run_cli(out_dir: pathlib.Path, timeout: int) -> int:
    executable = out_dir / "html_css_renderer_blink_cli.exe"
    result = subprocess.run(
        [
            str(executable),
            "--html",
            "<main><p>Hello from Blink tree builder</p></main>",
            "--viewport",
            "320x200",
        ],
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
        "--cli-commands",
        type=pathlib.Path,
        default="generated/blink_live/html_css_renderer_blink_cli.commands.txt",
    )
    parser.add_argument(
        "--tree-commands",
        type=pathlib.Path,
        default="generated/blink_live/blink_tree_builder_link_probe.commands.txt",
    )
    parser.add_argument(
        "--renderer-commands",
        type=pathlib.Path,
        default="generated/blink_live/standalone_renderer_tests.commands.txt",
    )
    parser.add_argument("--compile-timeout", type=int, default=120)
    parser.add_argument("--link-timeout", type=int, default=120)
    parser.add_argument("--run-timeout", type=int, default=20)
    parser.add_argument("--skip-cli-compile", action="store_true")
    parser.add_argument("--skip-renderer-compile", action="store_true")
    parser.add_argument("--skip-tree-compile", action="store_true")
    parser.add_argument("--no-run", action="store_true")
    args = parser.parse_args()

    out_dir = args.out_dir.resolve()
    cli_commands = read_commands(args.cli_commands.resolve())
    tree_commands = read_commands(args.tree_commands.resolve())
    renderer_commands = read_commands(args.renderer_commands.resolve())

    if not args.skip_cli_compile:
        exit_code = compile_sources_from_commands(
            out_dir, cli_commands, CLI_COMPILE_FILTERS, args.compile_timeout
        )
        if exit_code:
            return exit_code
    if not args.skip_renderer_compile:
        exit_code = compile_sources_from_commands(
            out_dir, renderer_commands, RENDERER_COMPILE_FILTERS, args.compile_timeout
        )
        if exit_code:
            return exit_code
    if not args.skip_tree_compile:
        exit_code = compile_sources_from_commands(
            out_dir, tree_commands, TREE_BUILDER_COMPILE_FILTERS, args.compile_timeout
        )
        if exit_code:
            return exit_code
    exit_code = link_cli(out_dir, cli_commands, tree_commands, args.link_timeout)
    if exit_code or args.no_run:
        return exit_code
    return run_cli(out_dir, args.run_timeout)


if __name__ == "__main__":
    sys.exit(main())
