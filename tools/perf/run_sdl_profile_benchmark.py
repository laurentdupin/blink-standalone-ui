#!/usr/bin/env python3
"""Validate the SDL-hosted Chromium compositor presentation path.

This is not a retained-renderer texture/upload profile.  The production SDL
viewer is now expected to host only the native window/event pump while rendered
pixels flow through Blink, PaintArtifactCompositor, cc, GPU raster/shared
images, Viz Display/SkiaRenderer, and Vulkan presentation.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[2]
PAINT_AUDIT_ROOT = (
    ROOT / "upstream" / "chromium" / "standalone_renderer" / "testdata" / "paint_audit"
)
DEFAULT_VIEWER = (
    ROOT
    / "build"
    / "cmake-live-image-png-ninja-vs18"
    / "blink_standalone_sdl_viewer_skia.exe"
)
DEFAULT_OUT = ROOT / "build" / "perf" / "sdl-compositor-profile"
DEFAULT_HTML = PAINT_AUDIT_ROOT / "00_text_only.html"

FRAME_REQUIRED = {
    "paint_clean": 1,
    "root_layer": 1,
    "cc_host": 1,
    "cc_attached": 1,
    "cc_commit": 1,
    "frame_sink_request": 1,
    "frame_sink_bound": 1,
    "gpu_context": 1,
    "raster_context": 1,
    "shared_image": 1,
    "viz_submit": 1,
    "viz_display": 1,
    "skia_gpu": 1,
}

PRESENTATION_REQUIRED = {
    "native_window": 1,
    "vulkan_instance": 1,
    "vulkan_queue": 1,
    "vulkan_surface": 1,
    "vulkan_swapchain": 1,
    "vulkan_present": 1,
    "viz_manager": 1,
    "viz_support": 1,
    "viz_display": 1,
    "cc_host": 1,
    "cc_attached": 1,
    "cc_commit": 1,
    "frame_sink_request": 1,
    "frame_sink_bound": 1,
    "gpu_context": 1,
    "raster_context": 1,
    "shared_image": 1,
    "viz_submit": 1,
    "skia_gpu": 1,
}

FAILURE_MARKERS = (
    "SharedImageBackingFactory",
    "Context lost",
    "context lost",
    "MakeCurrent failed",
    "missing SharedImageBacking",
    "SDL renderer",
    "texture upload",
)


def rel(path: Path) -> str:
    try:
        return path.resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        return str(path)


def parse_value(raw: str) -> Any:
    value = raw.strip()
    if value in {"true", "false"}:
        return value == "true"
    try:
        if any(ch in value for ch in ".eE"):
            return float(value)
        return int(value)
    except ValueError:
        return value


def parse_key_values(line: str) -> dict[str, Any]:
    row: dict[str, Any] = {}
    for match in re.finditer(r"(\w+)=([^\s]+)", line):
        row[match.group(1)] = parse_value(match.group(2))
    return row


def run_command(
    cmd: list[str],
    log_path: Path,
    timeout: int,
    sdl_video_driver: str | None,
) -> tuple[int, float, str]:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    env = os.environ.copy()
    if sdl_video_driver:
        env["SDL_VIDEODRIVER"] = sdl_video_driver
    start = time.perf_counter()
    try:
        completed = subprocess.run(
            cmd,
            cwd=ROOT,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
            encoding="utf-8",
            errors="replace",
        )
        output = completed.stdout
        code = completed.returncode
    except subprocess.TimeoutExpired as exc:
        output = exc.stdout if isinstance(exc.stdout, str) else ""
        output += f"\nTIMEOUT after {timeout}s\n"
        code = 124
    elapsed_ms = (time.perf_counter() - start) * 1000.0
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={code} elapsed_ms={elapsed_ms:.3f}\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return code, elapsed_ms, output


def parse_output(output: str) -> tuple[list[dict[str, Any]], list[dict[str, Any]], list[str]]:
    frames: list[dict[str, Any]] = []
    presentations: list[dict[str, Any]] = []
    diagnostics: list[str] = []
    for line in output.splitlines():
        text = line.strip()
        if text.startswith("frame="):
            frames.append(parse_key_values(text))
        elif text.startswith("presentation="):
            presentations.append(parse_key_values(text))
        elif text.startswith("diagnostic:"):
            diagnostics.append(text)
    return frames, presentations, diagnostics


def validate_row(
    failures: list[str],
    row: dict[str, Any] | None,
    required: dict[str, Any],
    label: str,
) -> None:
    if row is None:
        failures.append(f"missing {label} row")
        return
    for key, expected in required.items():
        actual = row.get(key)
        if actual != expected:
            failures.append(f"{label} expected {key}={expected}, got {actual}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--viewer", type=Path, default=DEFAULT_VIEWER)
    parser.add_argument("--html-file", type=Path, default=DEFAULT_HTML)
    parser.add_argument("--resource-root", type=Path, default=PAINT_AUDIT_ROOT)
    parser.add_argument("--out-dir", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--viewport", default="320x200")
    parser.add_argument("--quit-after-ms", type=int, default=1500)
    parser.add_argument("--timeout", type=int, default=60)
    parser.add_argument(
        "--sdl-video-driver",
        help="Optional SDL_VIDEODRIVER override. Leave unset for HWND/Vulkan validation.",
    )
    parser.add_argument(
        "--synthetic-input-smoke",
        action="store_true",
        help="Drive SDL-style pointer move/down/up and wheel update frames after the first presentation.",
    )
    parser.add_argument(
        "--synthetic-resize",
        help="Resize the SDL window to WxH and validate the resized Chromium compositor frame.",
    )
    args = parser.parse_args()

    if not args.viewer.exists():
        raise SystemExit(f"viewer not found: {args.viewer}")
    if not args.html_file.exists():
        raise SystemExit(f"html fixture not found: {args.html_file}")

    out_dir = args.out_dir.resolve()
    cmd = [
        str(args.viewer.resolve()),
        "--html-file",
        str(args.html_file.resolve()),
        "--resource-root",
        str(args.resource_root.resolve()),
        "--viewport",
        args.viewport,
        "--quit-after-ms",
        str(args.quit_after_ms),
    ]
    if args.synthetic_input_smoke:
        cmd.append("--synthetic-input-smoke")
    if args.synthetic_resize:
        cmd.extend(["--synthetic-resize", args.synthetic_resize])
    code, elapsed_ms, output = run_command(
        cmd, out_dir / "sdl_compositor_profile.log", args.timeout, args.sdl_video_driver
    )
    frames, presentations, diagnostics = parse_output(output)
    initial_frame = next((row for row in frames if row.get("reason") == "initial"), None)
    initial_presentation = next(
        (row for row in presentations if row.get("presentation") == "initial"), None
    )
    resize_frame = next(
        (row for row in frames if row.get("reason") == "synthetic_resize"), None
    )
    resize_presentation = next(
        (row for row in presentations if row.get("presentation") == "synthetic_resize"),
        None,
    )

    failures: list[str] = []
    if code != 0:
        failures.append(f"viewer exited {code}")
    validate_row(failures, initial_frame or (frames[0] if frames else None), FRAME_REQUIRED, "first frame")
    validate_row(
        failures,
        initial_presentation or (presentations[0] if presentations else None),
        PRESENTATION_REQUIRED,
        "first presentation",
    )
    if args.synthetic_input_smoke:
        for reason in (
            "synthetic_pointer_move",
            "synthetic_pointer_down",
            "synthetic_pointer_up",
            "synthetic_wheel",
        ):
            validate_row(
                failures,
                next((row for row in frames if row.get("reason") == reason), None),
                FRAME_REQUIRED,
                f"{reason} frame",
            )
    if args.synthetic_resize:
        validate_row(
            failures,
            resize_frame,
            FRAME_REQUIRED,
            "synthetic_resize frame",
        )
        validate_row(
            failures,
            resize_presentation,
            PRESENTATION_REQUIRED,
            "synthetic_resize presentation",
        )
        if resize_frame and resize_frame.get("viewport") != args.synthetic_resize:
            failures.append(
                f"synthetic_resize frame expected viewport={args.synthetic_resize}, "
                f"got {resize_frame.get('viewport')}"
            )
        if (
            resize_presentation
            and resize_presentation.get("surface") != args.synthetic_resize
        ):
            failures.append(
                f"synthetic_resize presentation expected surface={args.synthetic_resize}, "
                f"got {resize_presentation.get('surface')}"
            )
            validate_row(
                failures,
                next(
                    (row for row in presentations if row.get("presentation") == reason),
                    None,
                ),
                PRESENTATION_REQUIRED,
                f"{reason} presentation",
            )
    if "SWAP_ACK" not in output:
        failures.append("missing Chromium Vulkan SWAP_ACK diagnostic")
    for marker in FAILURE_MARKERS:
        if marker in output:
            failures.append(f"unexpected failure marker in output: {marker}")

    report = {
        "schema_version": 2,
        "viewer": rel(args.viewer),
        "html": rel(args.html_file),
        "viewport": args.viewport,
        "synthetic_resize": args.synthetic_resize,
        "command": cmd,
        "log": rel(out_dir / "sdl_compositor_profile.log"),
        "exit_code": code,
        "elapsed_ms": elapsed_ms,
        "frame_count": len(frames),
        "presentation_count": len(presentations),
        "first_frame": initial_frame or (frames[0] if frames else {}),
        "first_presentation": initial_presentation
        or (presentations[0] if presentations else {}),
        "resize_frame": resize_frame or {},
        "resize_presentation": resize_presentation or {},
        "diagnostics": diagnostics,
        "failure_count": len(failures),
        "failures": failures,
    }
    (out_dir / "sdl_compositor_profile_results.json").write_text(
        json.dumps(report, indent=2), encoding="utf-8"
    )
    print(json.dumps(report, indent=2))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
