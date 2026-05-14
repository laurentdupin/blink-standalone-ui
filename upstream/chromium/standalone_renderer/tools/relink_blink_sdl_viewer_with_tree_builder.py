#!/usr/bin/env python3
"""Relink the existing Blink SDL viewer object with the tree-builder bridge."""

from __future__ import annotations

import argparse
import pathlib
import subprocess
import sys

import relink_blink_cli_with_tree_builder as cli_relink
import relink_blink_tree_builder_probe as relink


SDL_VIEWER_OBJECT = (
    "obj/standalone_renderer/html_css_renderer_blink_sdl_viewer/sdl_viewer.obj"
)

SDL_LIBS = (
    "out/sdl3_static_mt2/SDL3-static.lib",
    "kernel32.lib",
    "user32.lib",
    "gdi32.lib",
    "winmm.lib",
    "imm32.lib",
    "ole32.lib",
    "oleaut32.lib",
    "version.lib",
    "uuid.lib",
    "advapi32.lib",
    "setupapi.lib",
    "shell32.lib",
    "dinput8.lib",
)

LIVE_RUNTIME_ADAPTER_OBJECT = (
    "obj/standalone_renderer/blink_live_frame_bridge_probe/"
    "blink_runtime_adapter.live.obj"
)
DEFAULT_RUNTIME_ADAPTER_OBJECT = (
    "obj/standalone_renderer/html_css_renderer_blink_runtime_adapter/"
    "blink_runtime_adapter.obj"
)
LIVE_SMOKE_OBJECT = (
    "obj/standalone_renderer/blink_live_frame_bridge_probe/"
    "live_frame_bridge_link_probe.obj"
)


def read_commands(path: pathlib.Path) -> list[str]:
    return cli_relink.read_commands(path)


def read_rsp_inputs(path: pathlib.Path) -> list[str]:
    data = path.read_text(encoding="utf-8", errors="replace")
    return relink.split_command_line(data)

def compile_sdl_viewer(out_dir: pathlib.Path,
                       sdl_commands: list[str],
                       timeout: int) -> int:
    matches = [
        command
        for command in sdl_commands
        if "clang-cl.exe" in command
        and "standalone_renderer/examples/sdl_viewer.cc"
        in command.replace("\\", "/")
    ]
    if not matches:
        print("missing compile command for SDL viewer")
        return 2
    args = [
        arg
        for arg in relink.split_command_line(matches[0])
        if not arg.lower().startswith("/showincludes")
    ]
    executable = relink.resolve_executable(out_dir, args[0])
    rsp_path = out_dir / "direct.recompile.sdl_viewer.rsp"
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
    print(f"standalone_renderer/examples/sdl_viewer.cc EXIT {result.returncode}")
    if result.stdout:
        print(result.stdout[-12000:])
    return result.returncode


def link_sdl_viewer(
    chromium_root: pathlib.Path,
    out_dir: pathlib.Path,
    cli_commands: list[str],
    tree_commands: list[str],
    live_rsp: pathlib.Path | None,
    timeout: int,
) -> int:
    link_commands = [
        command
        for command in cli_commands
        if "lld-link.exe" in command and "html_css_renderer_blink_cli.exe" in command
    ]
    if not link_commands:
        print("missing link command template for html_css_renderer_blink_cli.exe")
        return 2

    args = relink.split_command_line(link_commands[-1])
    executable = relink.resolve_executable(out_dir, args[0])
    link_args = [
        arg
        for arg in args[1:]
        if not arg.startswith("@")
        and not arg.startswith("/OUT:")
        and not arg.startswith("/PDB:")
    ]
    link_args.extend(
        [
            "/OUT:./html_css_renderer_blink_sdl_viewer.exe",
            "/PDB:./html_css_renderer_blink_sdl_viewer.exe.pdb",
        ]
    )

    if live_rsp and live_rsp.exists():
        inputs = read_rsp_inputs(live_rsp)
    else:
        inputs = cli_relink.collect_cli_link_inputs(out_dir, cli_commands, tree_commands)
    excluded = {
        "obj/standalone_renderer/html_css_renderer_blink_cli/render_blink_cli.obj",
        DEFAULT_RUNTIME_ADAPTER_OBJECT,
        LIVE_SMOKE_OBJECT,
    }
    inputs = [item for item in inputs if item.replace("\\", "/") not in excluded]
    if SDL_VIEWER_OBJECT not in inputs:
        inputs.insert(0, SDL_VIEWER_OBJECT)
    if (
        LIVE_RUNTIME_ADAPTER_OBJECT not in inputs
        and (out_dir / LIVE_RUNTIME_ADAPTER_OBJECT).exists()
    ):
        inputs.insert(1, LIVE_RUNTIME_ADAPTER_OBJECT)
    for lib in SDL_LIBS:
        item = lib
        if lib.startswith("out/"):
            item = str((chromium_root / lib).resolve())
        if item not in inputs:
            inputs.append(item)

    rsp_path = out_dir / "html_css_renderer_blink_sdl_viewer.tree_builder_bridge.rsp"
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


def run_sdl_viewer(out_dir: pathlib.Path, timeout: int) -> int:
    executable = out_dir / "html_css_renderer_blink_sdl_viewer.exe"
    env = {"SDL_VIDEODRIVER": "dummy"}
    result = subprocess.run(
        [
            str(executable),
            "--blink",
            "--html",
            "<main><p>Hello from Blink SDL</p></main>",
            "--viewport",
            "320x200",
            "--quit-after-ms",
            "50",
        ],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
        env=env,
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
        "--sdl-commands",
        type=pathlib.Path,
        default="generated/blink_live/standalone_blink_sdl.commands.txt",
    )
    parser.add_argument(
        "--live-rsp",
        type=pathlib.Path,
        default="generated/blink_live/live_frame_bridge_link_probe.rsp",
        help="Optional live Blink bridge response file to use as the viewer link input closure.",
    )
    parser.add_argument("--compile-timeout", type=int, default=120)
    parser.add_argument("--link-timeout", type=int, default=120)
    parser.add_argument("--run-timeout", type=int, default=20)
    parser.add_argument("--skip-sdl-compile", action="store_true")
    parser.add_argument("--no-run", action="store_true")
    args = parser.parse_args()

    chromium_root = pathlib.Path.cwd().resolve()
    out_dir = args.out_dir.resolve()
    cli_commands = read_commands(args.cli_commands.resolve())
    tree_commands = read_commands(args.tree_commands.resolve())
    if not args.skip_sdl_compile:
        sdl_commands = read_commands(args.sdl_commands.resolve())
        exit_code = compile_sdl_viewer(out_dir, sdl_commands,
                                       args.compile_timeout)
        if exit_code:
            return exit_code
    exit_code = link_sdl_viewer(
        chromium_root,
        out_dir,
        cli_commands,
        tree_commands,
        args.live_rsp.resolve() if args.live_rsp else None,
        args.link_timeout,
    )
    if exit_code or args.no_run:
        return exit_code
    return run_sdl_viewer(out_dir, args.run_timeout)


if __name__ == "__main__":
    sys.exit(main())
