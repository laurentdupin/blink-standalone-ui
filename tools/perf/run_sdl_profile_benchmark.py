#!/usr/bin/env python3
"""Focused SDL retained texture/upload profile gate."""

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
DEFAULT_OUT = ROOT / "build" / "perf" / "sdl-profile"
VIEWPORT = "1280x720"
VIEWPORT_PIXELS = 1280 * 720


def rel(path: Path) -> str:
    try:
        return path.resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        return str(path)


def run_command(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float, str]:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    env = os.environ.copy()
    env["SDL_VIDEODRIVER"] = "dummy"
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


def parse_value(raw: str) -> Any:
    value = raw.strip()
    if value.endswith("ms"):
        value = value[:-2]
    if value in {"true", "false"}:
        return value == "true"
    try:
        if any(ch in value for ch in ".eE"):
            return float(value)
        return int(value)
    except ValueError:
        return raw


def parse_profile_rows(output: str) -> list[dict[str, Any]]:
    rows: list[dict[str, Any]] = []
    for line in output.splitlines():
        if not line.startswith("viewer profile: frame="):
            continue
        row: dict[str, Any] = {}
        for match in re.finditer(r"(\w+)=([^\s]+)", line):
            row[match.group(1)] = parse_value(match.group(2))
        rows.append(row)
    return rows


def percentile(values: list[float], pct: float) -> float | None:
    ordered = sorted(values)
    if not ordered:
        return None
    if len(ordered) == 1:
        return ordered[0]
    rank = (len(ordered) - 1) * pct
    lower = int(rank)
    upper = min(len(ordered) - 1, lower + 1)
    return ordered[lower] + (ordered[upper] - ordered[lower]) * (rank - lower)


def metric_stats(rows: list[dict[str, Any]], key: str) -> dict[str, Any]:
    values = [float(row[key]) for row in rows if isinstance(row.get(key), (int, float))]
    return {
        "count": len(values),
        "p50": percentile(values, 0.50),
        "p95": percentile(values, 0.95),
        "max": max(values) if values else None,
    }


def truthy_count(rows: list[dict[str, Any]], key: str) -> int:
    return sum(1 for row in rows if bool(row.get(key)))


def assert_equal(failures: list[str], row: dict[str, Any], key: str, expected: Any) -> None:
    actual = row.get(key)
    if actual != expected:
        failures.append(
            f"frame {row.get('frame')} expected {key}={expected}, got {actual}"
        )


def run_no_change(viewer: Path, out_dir: Path, timeout: int) -> dict[str, Any]:
    html = PAINT_AUDIT_ROOT / "00_text_only.html"
    cmd = [
        str(viewer),
        "--html-file",
        str(html),
        "--resource-root",
        str(PAINT_AUDIT_ROOT),
        "--viewport",
        VIEWPORT,
        "--profile",
        "--profile-summary-frames",
        "6",
        "--profile-no-change-frames",
        "5",
    ]
    code, elapsed_ms, output = run_command(cmd, out_dir / "no-change.log", timeout)
    rows = parse_profile_rows(output)
    measured = [row for row in rows if row.get("event") == "profile-no-change"]
    failures: list[str] = []
    if code != 0:
        failures.append(f"viewer exited {code}")
    if len(measured) != 5:
        failures.append(f"expected 5 no-change frames, got {len(measured)}")
    for row in measured:
        assert_equal(failures, row, "incremental", 1)
        assert_equal(failures, row, "full_redraw", 0)
        assert_equal(failures, row, "damage_rects", 0)
        assert_equal(failures, row, "lifecycle_count", 0)
        assert_equal(failures, row, "translation_count", 0)
        assert_equal(failures, row, "damage_pixels", 0)
        assert_equal(failures, row, "raster_pixels", 0)
        assert_equal(failures, row, "uploaded_pixels", 0)
        assert_equal(failures, row, "texture_copy_pixels", 0)
        assert_equal(failures, row, "texture_update_rects", 0)
        assert_equal(failures, row, "raster_skipped", 1)
        assert_equal(failures, row, "partial_redraw", 0)
    return {
        "name": "no_change",
        "command": cmd,
        "log": rel(out_dir / "no-change.log"),
        "exit_code": code,
        "elapsed_ms": elapsed_ms,
        "frame_count": len(rows),
        "measured_frame_count": len(measured),
        "failures": failures,
        "counts": {
            "no_change_flag_count": truthy_count(measured, "no_change"),
            "raster_skipped_count": truthy_count(measured, "raster_skipped"),
            "partial_redraw_count": truthy_count(measured, "partial_redraw"),
        },
        "stats": {
            "total_ms": metric_stats(measured, "total"),
            "damage_pixels": metric_stats(measured, "damage_pixels"),
            "raster_pixels": metric_stats(measured, "raster_pixels"),
            "uploaded_pixels": metric_stats(measured, "uploaded_pixels"),
            "texture_copy_pixels": metric_stats(measured, "texture_copy_pixels"),
            "texture_update_rects": metric_stats(measured, "texture_update_rects"),
            "texture_upload_ms": metric_stats(measured, "texture_upload"),
            "sdl_draw_present_ms": metric_stats(measured, "sdl_draw_present"),
        },
    }


def run_scroll(viewer: Path, out_dir: Path, timeout: int) -> dict[str, Any]:
    html = PAINT_AUDIT_ROOT / "51b_svg_text_city_route_document_scroll.html"
    cmd = [
        str(viewer),
        "--html-file",
        str(html),
        "--resource-root",
        str(PAINT_AUDIT_ROOT),
        "--viewport",
        VIEWPORT,
        "--profile",
        "--profile-summary-frames",
        "6",
        "--profile-auto-scroll-frames",
        "5",
        "--profile-auto-scroll-step",
        "120",
    ]
    code, elapsed_ms, output = run_command(cmd, out_dir / "scroll.log", timeout)
    rows = parse_profile_rows(output)
    measured = [row for row in rows if row.get("event") == "profile-auto-scroll"]
    failures: list[str] = []
    if code != 0:
        failures.append(f"viewer exited {code}")
    if len(measured) != 5:
        failures.append(f"expected 5 scroll frames, got {len(measured)}")
    for row in measured:
        assert_equal(failures, row, "incremental", 1)
        assert_equal(failures, row, "full_redraw", 0)
        assert_equal(failures, row, "scroll_reuse", 1)
        damage_pixels = int(row.get("damage_pixels", 0))
        raster_pixels = int(row.get("raster_pixels", 0))
        uploaded_pixels = int(row.get("uploaded_pixels", 0))
        if damage_pixels > 0:
            assert_equal(failures, row, "partial_redraw", 1)
            if uploaded_pixels < damage_pixels:
                failures.append(
                    f"frame {row.get('frame')} uploaded_pixels {uploaded_pixels} "
                    f"is smaller than damage_pixels {damage_pixels}"
                )
        if raster_pixels >= VIEWPORT_PIXELS:
            failures.append(
                f"frame {row.get('frame')} touched full viewport raster area "
                f"({raster_pixels})"
            )
        if int(row.get("texture_update_rects", 0)) <= 0:
            failures.append(f"frame {row.get('frame')} had no texture update rects")
    return {
        "name": "scroll",
        "command": cmd,
        "log": rel(out_dir / "scroll.log"),
        "exit_code": code,
        "elapsed_ms": elapsed_ms,
        "frame_count": len(rows),
        "measured_frame_count": len(measured),
        "failures": failures,
        "counts": {
            "scroll_reuse_count": truthy_count(measured, "scroll_reuse"),
            "raster_skipped_count": truthy_count(measured, "raster_skipped"),
            "partial_redraw_count": truthy_count(measured, "partial_redraw"),
        },
        "stats": {
            "total_ms": metric_stats(measured, "total"),
            "cpu_replay_ms": metric_stats(measured, "cpu_replay"),
            "damage_pixels": metric_stats(measured, "damage_pixels"),
            "raster_pixels": metric_stats(measured, "raster_pixels"),
            "texture_upload_ms": metric_stats(measured, "texture_upload"),
            "sdl_draw_present_ms": metric_stats(measured, "sdl_draw_present"),
            "uploaded_pixels": metric_stats(measured, "uploaded_pixels"),
            "texture_copy_pixels": metric_stats(measured, "texture_copy_pixels"),
            "texture_update_rects": metric_stats(measured, "texture_update_rects"),
        },
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--viewer", type=Path, default=DEFAULT_VIEWER)
    parser.add_argument("--out-dir", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--timeout", type=int, default=60)
    args = parser.parse_args()
    if not args.viewer.exists():
        raise SystemExit(f"viewer not found: {args.viewer}")

    out_dir = args.out_dir.resolve()
    out_dir.mkdir(parents=True, exist_ok=True)
    report = {
        "viewer": rel(args.viewer),
        "viewport": VIEWPORT,
        "cases": [
            run_no_change(args.viewer.resolve(), out_dir, args.timeout),
            run_scroll(args.viewer.resolve(), out_dir, args.timeout),
        ],
    }
    failures = [
        failure
        for case in report["cases"]
        for failure in case.get("failures", [])
    ]
    report["failure_count"] = len(failures)
    report["failures"] = failures
    (out_dir / "sdl_profile_results.json").write_text(
        json.dumps(report, indent=2), encoding="utf-8"
    )
    print(json.dumps(report, indent=2))
    return 0 if not failures else 1


if __name__ == "__main__":
    raise SystemExit(main())
