#!/usr/bin/env python3
"""Validate HCSR example HTML files with the SDL compositor viewer.

The script intentionally writes all artifacts under the requested output
directory. It does not modify the external examples tree.
"""

from __future__ import annotations

import argparse
import json
import math
from pathlib import Path
import re
import subprocess
import time
from typing import Any
import warnings

from PIL import Image, ImageChops

warnings.filterwarnings("ignore", category=DeprecationWarning)

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_EXAMPLES_ROOT = Path(r"C:\Repos\UniversalGameEngine\HCSR\Examples")
DEFAULT_VIEWER = (
    ROOT
    / "build"
    / "cmake-live-image-png-ninja-vs18"
    / "blink_standalone_sdl_viewer_skia.exe"
)
PLAYWRIGHT_CAPTURE = ROOT / "tools" / "playwright_screenshot.cjs"


def parse_viewport(value: str) -> tuple[int, int]:
    if "x" not in value.lower():
        raise argparse.ArgumentTypeError("viewport must be WxH")
    width, height = value.lower().split("x", 1)
    return int(width), int(height)


def rel_to_repo(path: Path) -> str:
    try:
        return path.resolve().relative_to(ROOT.resolve()).as_posix()
    except ValueError:
        return str(path)


def rel_to_root(path: Path, root: Path) -> str:
    try:
        return path.resolve().relative_to(root.resolve()).as_posix()
    except ValueError:
        return path.name


def slug_for(path: Path, root: Path) -> str:
    relative = rel_to_root(path, root)
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "_", relative)
    return slug.rstrip("_") or path.stem


def enumerate_html(root: Path) -> list[Path]:
    return sorted(
        [
            path
            for path in root.rglob("*")
            if path.is_file() and path.suffix.lower() in {".html", ".htm"}
        ],
        key=lambda path: rel_to_root(path, root).lower(),
    )


def run_command(
    cmd: list[str],
    log_path: Path,
    timeout_seconds: int,
) -> tuple[int, float, str, bool]:
    start = time.perf_counter()
    timed_out = False
    try:
        completed = subprocess.run(
            cmd,
            cwd=ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout_seconds,
            encoding="utf-8",
            errors="replace",
        )
        output = completed.stdout
        exit_code = completed.returncode
    except subprocess.TimeoutExpired as exc:
        output = exc.stdout if isinstance(exc.stdout, str) else ""
        output += f"\nTIMEOUT after {timeout_seconds}s\n"
        exit_code = 124
        timed_out = True
    elapsed_ms = (time.perf_counter() - start) * 1000.0
    log_path.parent.mkdir(parents=True, exist_ok=True)
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={exit_code} elapsed_ms={elapsed_ms:.3f}\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return exit_code, elapsed_ms, output, timed_out


def parse_value(raw: str) -> Any:
    try:
        if any(ch in raw for ch in ".eE"):
            return float(raw)
        return int(raw)
    except ValueError:
        return raw


def parse_key_values(line: str) -> dict[str, Any]:
    values: dict[str, Any] = {}
    for match in re.finditer(r"(\w+)=([^\s]+)", line):
        values[match.group(1)] = parse_value(match.group(2))
    return values


def last_frame_metrics(output: str) -> dict[str, Any]:
    last: dict[str, Any] = {}
    for line in output.splitlines():
        text = line.strip()
        if text.startswith("frame="):
            last = parse_key_values(text)
    return last


def last_presentation_metrics(output: str) -> dict[str, Any]:
    last: dict[str, Any] = {}
    for line in output.splitlines():
        text = line.strip()
        if text.startswith("presentation="):
            last = parse_key_values(text)
    return last


def non_white_pixels(image: Image.Image) -> int:
    rgb = image.convert("RGB")
    return sum(1 for red, green, blue in rgb.getdata()
               if red < 245 or green < 245 or blue < 245)


def compare_images(
    standalone_path: Path,
    reference_path: Path,
    diff_path: Path,
    threshold: int,
) -> dict[str, Any]:
    standalone = Image.open(standalone_path).convert("RGB")
    reference = Image.open(reference_path).convert("RGB")
    dimensions_match = standalone.size == reference.size
    if not dimensions_match:
        reference = reference.resize(standalone.size)

    total_channel_delta = 0
    max_channel_delta = 0
    changed_pixels = 0
    exact_changed_pixels = 0
    squared_delta = 0
    pixel_count = standalone.size[0] * standalone.size[1]
    for left, right in zip(standalone.getdata(), reference.getdata()):
        channel_deltas = [abs(int(left[i]) - int(right[i])) for i in range(3)]
        pixel_delta = max(channel_deltas)
        total_channel_delta += sum(channel_deltas)
        squared_delta += sum(delta * delta for delta in channel_deltas)
        max_channel_delta = max(max_channel_delta, pixel_delta)
        if pixel_delta > threshold:
            changed_pixels += 1
        if left != right:
            exact_changed_pixels += 1

    diff_path.parent.mkdir(parents=True, exist_ok=True)
    ImageChops.difference(standalone, reference).save(diff_path)
    return {
        "standalone_size": list(standalone.size),
        "reference_size": list(Image.open(reference_path).size),
        "dimensions_match": dimensions_match,
        "standalone_non_white": non_white_pixels(standalone),
        "reference_non_white": non_white_pixels(reference),
        "coverage_ratio": (
            non_white_pixels(standalone) / max(1, non_white_pixels(reference))
        ),
        "mean_absolute_rgb_diff": total_channel_delta / max(1, pixel_count * 3),
        "root_mean_square_rgb_diff": math.sqrt(
            squared_delta / max(1, pixel_count * 3)
        ),
        "max_channel_delta": max_channel_delta,
        "thresholded_different_pixel_count": changed_pixels,
        "thresholded_different_pixel_percent": (
            changed_pixels * 100.0 / max(1, pixel_count)
        ),
        "exact_different_pixel_count": exact_changed_pixels,
        "exact_different_pixel_percent": (
            exact_changed_pixels * 100.0 / max(1, pixel_count)
        ),
        "diff_png": rel_to_repo(diff_path),
    }


def read_interactive_points(state_json: Path, max_points: int) -> list[dict[str, Any]]:
    if max_points <= 0 or not state_json.exists():
        return []
    try:
        state = json.loads(state_json.read_text(encoding="utf-8"))
    except json.JSONDecodeError:
        return []
    candidates = sorted(
        state.get("interactiveElements", []),
        key=lambda item: (
            int(item.get("priority", 100)),
            int(item.get("order", 0)),
        ),
    )
    points = []
    seen: set[tuple[int, int]] = set()
    for item in candidates:
        try:
            x = int(round(float(item["x"])))
            y = int(round(float(item["y"])))
        except (KeyError, TypeError, ValueError):
            continue
        key = (x, y)
        if key in seen:
            continue
        seen.add(key)
        points.append({**item, "x": x, "y": y})
        if len(points) >= max_points:
            break
    return points


def read_json_file(path: Path) -> Any:
    if not path.exists():
        return None
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None


def form_controls_from_audit(audit_json: Path) -> list[dict[str, Any]]:
    audit = read_json_file(audit_json)
    if not isinstance(audit, dict):
        return []
    diagnostics = audit.get("form_control_diagnostics")
    if not isinstance(diagnostics, dict):
        return []
    controls = diagnostics.get("controls")
    return controls if isinstance(controls, list) else []


def control_absolute_bounds(control: dict[str, Any]) -> dict[str, float] | None:
    if not control.get("absolute_bounds_present"):
        return None
    bounds = control.get("absolute_bounds")
    if not isinstance(bounds, dict):
        return None
    try:
        x = float(bounds["x"])
        y = float(bounds["y"])
        width = float(bounds["width"])
        height = float(bounds["height"])
    except (KeyError, TypeError, ValueError):
        return None
    if width <= 0 or height <= 0:
        return None
    return {"x": x, "y": y, "width": width, "height": height}


def find_control_for_point(
    controls: list[dict[str, Any]], point: dict[str, Any]
) -> dict[str, Any] | None:
    point_id = str(point.get("id") or "")
    if point_id:
        for control in controls:
            if str(control.get("element_id") or "") == point_id:
                return control
    point_name = str(point.get("name") or "")
    point_type = str(point.get("type") or "").lower()
    point_tag = str(point.get("tagName") or "").upper()
    for control in controls:
        if point_tag and str(control.get("tag_name") or "").upper() != point_tag:
            continue
        if point_name and str(control.get("name_attr") or "") != point_name:
            continue
        if point_type and str(control.get("type_attr") or "").lower() != point_type:
            continue
        return control
    return None


def clamp_point_coordinate(value: float, limit: int) -> int:
    return int(round(max(0, min(limit - 1, value))))


def point_from_standalone_control_bounds(
    point: dict[str, Any],
    control: dict[str, Any] | None,
    viewport_size: tuple[int, int],
) -> dict[str, Any]:
    if control is None:
        return point
    bounds = control_absolute_bounds(control)
    if bounds is None:
        return point
    kind = str(point.get("pointKind") or "")
    x = bounds["x"] + bounds["width"] / 2.0
    y = bounds["y"] + bounds["height"] / 2.0
    if kind == "select-arrow":
        x = bounds["x"] + bounds["width"] - min(16.0, bounds["width"] * 0.15)
    width, height = viewport_size
    adjusted = dict(point)
    adjusted["playwright_x"] = point.get("x")
    adjusted["playwright_y"] = point.get("y")
    adjusted["x"] = clamp_point_coordinate(x, width)
    adjusted["y"] = clamp_point_coordinate(y, height)
    adjusted["standalone_coordinate_source"] = "form_control_absolute_bounds"
    adjusted["standalone_bounds"] = {
        "x": bounds["x"],
        "y": bounds["y"],
        "width": bounds["width"],
        "height": bounds["height"],
    }
    return adjusted


def standalone_interaction_points(
    raw_points: list[dict[str, Any]],
    audit_json: Path,
    max_points: int,
    viewport: str,
) -> list[dict[str, Any]]:
    if max_points <= 0:
        return []
    viewport_size = parse_viewport(viewport)
    controls = form_controls_from_audit(audit_json)
    adjusted_points: list[dict[str, Any]] = []
    seen: set[tuple[int, int, str, str]] = set()
    for point in raw_points:
        control = find_control_for_point(controls, point)
        adjusted = point_from_standalone_control_bounds(
            point, control, viewport_size
        )
        try:
            x = int(adjusted["x"])
            y = int(adjusted["y"])
        except (KeyError, TypeError, ValueError):
            continue
        key = (
            x,
            y,
            str(adjusted.get("pointKind") or ""),
            str(adjusted.get("id") or adjusted.get("name") or ""),
        )
        if key in seen:
            continue
        seen.add(key)
        adjusted_points.append(adjusted)
        if len(adjusted_points) >= max_points:
            break
    return adjusted_points


def filter_checkbox_and_last_radio_points(
    points: list[dict[str, Any]],
) -> list[dict[str, Any]]:
    last_radio_by_group: dict[str, int] = {}
    for index, point in enumerate(points):
        if str(point.get("pointKind") or "") != "radio-box":
            continue
        group = str(point.get("name") or point.get("id") or index)
        last_radio_by_group[group] = index
    filtered: list[dict[str, Any]] = []
    for index, point in enumerate(points):
        kind = str(point.get("pointKind") or "")
        if kind == "checkbox-box":
            filtered.append(point)
        elif kind == "radio-box":
            group = str(point.get("name") or point.get("id") or index)
            if last_radio_by_group.get(group) == index:
                filtered.append(point)
    return filtered


def semantic_points_for_supported_boundaries(
    points: list[dict[str, Any]],
) -> list[dict[str, Any]]:
    selected = filter_checkbox_and_last_radio_points(points)
    selected.extend(
        point
        for point in points
        if str(point.get("pointKind") or "") in {"select-arrow", "text-control"}
    )
    return selected


def summarize_interaction_semantics(
    points: list[dict[str, Any]],
    audit_json: Path,
    click_repeats: int,
) -> dict[str, Any]:
    controls = form_controls_from_audit(audit_json)
    assertions: list[dict[str, Any]] = []
    last_radio_by_group: dict[str, int] = {}
    for index, point in enumerate(points):
        if str(point.get("pointKind") or "") != "radio-box":
            continue
        group = str(point.get("name") or point.get("id") or index)
        last_radio_by_group[group] = index
    for point_index, point in enumerate(points):
        kind = str(point.get("pointKind") or "")
        if kind not in {"checkbox-box", "radio-box", "select-arrow", "text-control"}:
            continue
        assertion: dict[str, Any] = {
            "pointKind": kind,
            "id": point.get("id") or "",
            "name": point.get("name") or "",
            "type": point.get("type") or "",
        }
        control = find_control_for_point(controls, point)
        if control is None:
            assertion["status"] = "control_not_found_in_standalone_audit"
            assertion["passed"] = False
            assertions.append(assertion)
            continue
        assertion["standalone_checked"] = control.get("checked")
        assertion["standalone_radio_group_checked"] = control.get(
            "radio_group_checked"
        )
        assertion["standalone_support_status"] = control.get(
            "standalone_support_status", ""
        )
        if kind == "checkbox-box":
            if click_repeats % 2 == 0:
                assertion["status"] = "not_asserted_even_click_repeats"
                assertion["passed"] = True
            else:
                expected = not bool(point.get("checked"))
                actual = bool(control.get("checked"))
                assertion["expected_checked"] = expected
                assertion["passed"] = actual == expected
                assertion["status"] = "checked_changed" if assertion[
                    "passed"
                ] else "checked_did_not_change"
        elif kind == "radio-box":
            group = str(point.get("name") or point.get("id") or point_index)
            if last_radio_by_group.get(group) != point_index:
                assertion["passed"] = True
                assertion["status"] = "radio_superseded_by_later_group_click"
            else:
                assertion["passed"] = bool(control.get("checked")) or bool(
                    control.get("radio_group_checked")
                )
                assertion["status"] = (
                    "radio_selected"
                    if assertion["passed"]
                    else "radio_not_selected_after_click"
                )
        elif kind == "select-arrow":
            assertion["passed"] = True
            assertion["status"] = (
                "popup_boundary_observed_not_asserted;"
                "standalone_does_not_provide_browser_select_popup"
            )
        else:
            assertion["passed"] = True
            assertion["status"] = (
                "text_editing_not_asserted;"
                "keyboard_text_input_dispatch_is_next_boundary"
            )
        assertions.append(assertion)
    failed = [item for item in assertions if not item.get("passed")]
    return {
        "audit_json": rel_to_repo(audit_json),
        "control_count": len(controls),
        "assertion_count": len(assertions),
        "failed_assertion_count": len(failed),
        "assertions": assertions,
    }


def run_interaction_smoke(
    html_file: Path,
    examples_root: Path,
    viewer: Path,
    page_dir: Path,
    viewport: str,
    timeout_seconds: int,
    points: list[dict[str, Any]],
    semantic_points: list[dict[str, Any]],
    click_repeats: int,
) -> dict[str, Any]:
    interaction_log = page_dir / "viewer_interaction.log"
    cmd = [
        str(viewer.resolve()),
        "--html-file",
        str(html_file.resolve()),
        "--resource-root",
        str(examples_root.resolve()),
        "--viewport",
        viewport,
        "--quit-after-ms",
        "1200",
    ]
    if points:
        cmd.extend(["--synthetic-sdl-click-repeats", str(max(1, click_repeats))])
    else:
        cmd.append("--synthetic-input-smoke")
    for point in points:
        cmd.extend(["--synthetic-sdl-click", f"{point['x']},{point['y']}"])
    exit_code, elapsed_ms, output, timed_out = run_command(
        cmd, interaction_log, timeout_seconds
    )
    return {
        "interaction_exit": exit_code,
        "interaction_timeout": timed_out,
        "interaction_elapsed_ms": elapsed_ms,
        "interaction_log": rel_to_repo(interaction_log),
        "interaction_points": points,
        "interaction_semantic_points": semantic_points,
        "interaction_last_frame_metrics": last_frame_metrics(output),
        "interaction_last_presentation_metrics": last_presentation_metrics(output),
    }


def run_control_semantic_checks(
    html_file: Path,
    examples_root: Path,
    viewer: Path,
    page_dir: Path,
    viewport: str,
    timeout_seconds: int,
    points: list[dict[str, Any]],
    semantic_points: list[dict[str, Any]],
    baseline_audit: Path,
) -> dict[str, Any]:
    assertions: list[dict[str, Any]] = []
    runs: list[dict[str, Any]] = []
    unsupported_summary = summarize_interaction_semantics(
        [
            point
            for point in semantic_points
            if str(point.get("pointKind") or "") in {"select-arrow", "text-control"}
        ],
        baseline_audit,
        0,
    )
    assertions.extend(unsupported_summary.get("assertions", []))
    control_points = [
        point
        for point in points
        if str(point.get("pointKind") or "") in {"checkbox-box", "radio-box"}
    ]
    if control_points:
        audit_dir = ROOT / "build" / "validation" / "semantic_combined"
        audit_dir.mkdir(parents=True, exist_ok=True)
        audit_path = audit_dir / f"{page_dir.parent.parent.name}_{page_dir.name}.json"
        try:
            audit_path.unlink()
        except FileNotFoundError:
            pass
        log_path = page_dir / "semantic_controls.log"
        cmd = [
            str(viewer.resolve()),
            "--html-file",
            str(html_file.resolve()),
            "--resource-root",
            str(examples_root.resolve()),
            "--viewport",
            viewport,
            "--paint-artifact-dump",
            str(audit_path.resolve()),
            "--quit-after-ms",
            "1200",
            "--synthetic-sdl-click-repeats",
            "1",
        ]
        for point in control_points:
            try:
                click_x = int(point["x"])
                click_y = int(point["y"])
            except (KeyError, TypeError, ValueError):
                continue
            cmd.extend(["--synthetic-sdl-click", f"{click_x},{click_y}"])
        exit_code, elapsed_ms, output, timed_out = run_command(
            cmd, log_path, timeout_seconds
        )
        summary = summarize_interaction_semantics(control_points, audit_path, 1)
        assertions.extend(summary.get("assertions", []))
        runs.append(
            {
                "points": control_points,
                "exit": exit_code,
                "timeout": timed_out,
                "elapsed_ms": elapsed_ms,
                "log": rel_to_repo(log_path),
                "audit_json": rel_to_repo(audit_path),
                "last_frame_metrics": last_frame_metrics(output),
                "last_presentation_metrics": last_presentation_metrics(output),
                "semantic_summary": summary,
            }
        )
    failed = [item for item in assertions if not item.get("passed")]
    return {
        "control_semantic_runs": runs,
        "interaction_semantics": {
            "baseline_audit_json": rel_to_repo(baseline_audit),
            "assertion_count": len(assertions),
            "failed_assertion_count": len(failed),
            "assertions": assertions,
        },
        "control_semantic_failure_count": sum(1 for run in runs if run["exit"] != 0),
        "control_semantic_timeout_count": sum(1 for run in runs if run["timeout"]),
    }


def validate_page(
    html_file: Path,
    examples_root: Path,
    viewer: Path,
    out_dir: Path,
    viewport: str,
    timeout_seconds: int,
    screenshot_after_ms: int,
    threshold: int,
    run_interactions: bool,
    max_interaction_points: int,
    interaction_click_repeats: int,
    click_affordance_points: bool,
    control_semantic_checks: bool,
) -> dict[str, Any]:
    page_slug = slug_for(html_file, examples_root)
    page_dir = out_dir / "pages" / page_slug
    page_dir.mkdir(parents=True, exist_ok=True)
    standalone_png = page_dir / "viewer.png"
    reference_png = page_dir / "playwright.png"
    diff_png = page_dir / "diff.png"
    playwright_state = page_dir / "playwright_state.json"
    viewer_audit = out_dir / "viewer_audits" / f"{page_slug}.json"
    viewer_audit.parent.mkdir(parents=True, exist_ok=True)
    viewer_log = page_dir / "viewer.log"
    playwright_log = page_dir / "playwright.log"

    viewer_quit_after_ms = max(1000, screenshot_after_ms + 800)
    viewer_cmd = [
        str(viewer.resolve()),
        "--html-file",
        str(html_file.resolve()),
        "--resource-root",
        str(examples_root.resolve()),
        "--viewport",
        viewport,
        "--quit-after-ms",
        str(viewer_quit_after_ms),
        "--screenshot-out",
        str(standalone_png.resolve()),
        "--screenshot-after-ms",
        str(max(0, screenshot_after_ms)),
        "--paint-artifact-dump",
        str(viewer_audit.resolve()),
    ]
    viewer_exit, viewer_elapsed_ms, viewer_output, viewer_timeout = run_command(
        viewer_cmd, viewer_log, timeout_seconds
    )

    playwright_cmd = [
        "node",
        str(PLAYWRIGHT_CAPTURE.resolve()),
        "--html-file",
        str(html_file.resolve()),
        "--out",
        str(reference_png.resolve()),
        "--viewport",
        viewport,
        "--time-ms",
        str(max(0, screenshot_after_ms)),
        "--out-json",
        str(playwright_state.resolve()),
    ]
    playwright_exit, playwright_elapsed_ms, _, playwright_timeout = run_command(
        playwright_cmd, playwright_log, timeout_seconds
    )

    result: dict[str, Any] = {
        "file": rel_to_root(html_file, examples_root),
        "html_file": str(html_file),
        "viewer_exit": viewer_exit,
        "viewer_timeout": viewer_timeout,
        "viewer_elapsed_ms": viewer_elapsed_ms,
        "playwright_exit": playwright_exit,
        "playwright_timeout": playwright_timeout,
        "playwright_elapsed_ms": playwright_elapsed_ms,
        "viewer_log": rel_to_repo(viewer_log),
        "playwright_log": rel_to_repo(playwright_log),
        "viewer_png": rel_to_repo(standalone_png),
        "playwright_png": rel_to_repo(reference_png),
        "playwright_state_json": rel_to_repo(playwright_state),
        "viewer_audit_json": rel_to_repo(viewer_audit),
        "viewer_png_exists": standalone_png.exists(),
        "playwright_png_exists": reference_png.exists(),
        "last_frame_metrics": last_frame_metrics(viewer_output),
        "last_presentation_metrics": last_presentation_metrics(viewer_output),
    }
    if run_interactions:
        raw_interaction_points = read_interactive_points(
            playwright_state, max(max_interaction_points * 4, max_interaction_points)
        )
        semantic_points = semantic_points_for_supported_boundaries(
            raw_interaction_points[:max_interaction_points]
        )
        interaction_points = standalone_interaction_points(
            raw_interaction_points,
            viewer_audit,
            max_interaction_points,
            viewport,
        )
        interaction_points = filter_checkbox_and_last_radio_points(
            interaction_points
        )
        smoke_points = interaction_points if click_affordance_points else []
        result.update(
            run_interaction_smoke(
                html_file,
                examples_root,
                viewer,
                page_dir,
                viewport,
                timeout_seconds,
                smoke_points,
                semantic_points,
                interaction_click_repeats,
            )
        )
        result["available_affordance_points"] = interaction_points
        if control_semantic_checks:
            result.update(
                run_control_semantic_checks(
                    html_file,
                    examples_root,
                    viewer,
                    page_dir,
                    viewport,
                    timeout_seconds,
                    interaction_points,
                    semantic_points,
                    viewer_audit,
                )
            )
        else:
            unsupported_summary = summarize_interaction_semantics(
                [
                    point
                    for point in semantic_points
                    if str(point.get("pointKind") or "")
                    in {"select-arrow", "text-control"}
                ],
                viewer_audit,
                0,
            )
            result["interaction_semantics"] = {
                "baseline_audit_json": rel_to_repo(viewer_audit),
                "assertion_count": len(unsupported_summary.get("assertions", [])),
                "failed_assertion_count": 0,
                "assertions": unsupported_summary.get("assertions", []),
                "status": "control_semantic_checks_not_requested",
            }
    if standalone_png.exists() and reference_png.exists():
        result["comparison"] = compare_images(
            standalone_png, reference_png, diff_png, threshold
        )
    else:
        missing = []
        if not standalone_png.exists():
            missing.append("viewer_png")
        if not reference_png.exists():
            missing.append("playwright_png")
        result["missing_artifacts"] = missing
    return result


def status_for(result: dict[str, Any], mean_diff_threshold: float,
               pixel_diff_percent_threshold: float) -> str:
    if result["viewer_timeout"] or result["playwright_timeout"]:
        return "timeout"
    if result.get("interaction_timeout"):
        return "interaction_timeout"
    if result["viewer_exit"] != 0:
        return "viewer_failed"
    if result.get("interaction_exit", 0) != 0:
        return "interaction_failed"
    if result.get("control_semantic_timeout_count", 0):
        return "control_semantic_timeout"
    if result.get("control_semantic_failure_count", 0):
        return "control_semantic_failed"
    if result["playwright_exit"] != 0:
        return "playwright_failed"
    if result.get("missing_artifacts"):
        return "missing_artifacts"
    comparison = result.get("comparison", {})
    if not comparison.get("dimensions_match", False):
        return "dimension_mismatch"
    if (
        comparison.get("mean_absolute_rgb_diff", 0.0) > mean_diff_threshold
        or comparison.get("thresholded_different_pixel_percent", 0.0)
        > pixel_diff_percent_threshold
    ):
        return "visual_flag"
    return "acceptable"


def write_markdown(summary: dict[str, Any], out_path: Path) -> None:
    rows = summary["results"]
    worst = sorted(
        [row for row in rows if "comparison" in row],
        key=lambda row: row["comparison"].get("mean_absolute_rgb_diff", 0.0),
        reverse=True,
    )[:12]
    lines = [
        "# HCSR Examples Validation",
        "",
        f"- Examples root: `{summary['examples_root']}`",
        f"- Viewport: `{summary['viewport']}`",
        f"- Screenshot time: `{summary['screenshot_after_ms']} ms`",
        f"- Files tested: `{summary['page_count']}`",
        f"- Viewer failures: `{summary['viewer_failure_count']}`",
        f"- Viewer timeouts: `{summary['viewer_timeout_count']}`",
        f"- Interaction failures: `{summary['interaction_failure_count']}`",
        f"- Interaction timeouts: `{summary['interaction_timeout_count']}`",
        f"- Control semantic command failures: `{summary['control_semantic_failure_count']}`",
        f"- Control semantic command timeouts: `{summary['control_semantic_timeout_count']}`",
        f"- Interaction semantic assertion failures: `{summary['interaction_semantic_failure_count']}`",
        f"- Playwright failures: `{summary['playwright_failure_count']}`",
        f"- Playwright timeouts: `{summary['playwright_timeout_count']}`",
        f"- Missing screenshot artifacts: `{summary['missing_artifact_count']}`",
        f"- Acceptable comparisons: `{summary['acceptable_count']}`",
        f"- Flagged visual comparisons: `{summary['visual_flag_count']}`",
        "",
        "## Worst Visual Differences",
        "",
        "| File | Mean RGB Diff | Changed > threshold | Coverage | Diff |",
        "| --- | ---: | ---: | ---: | --- |",
    ]
    for row in worst:
        comparison = row["comparison"]
        lines.append(
            "| {file} | {mean:.3f} | {changed:.3f}% | {coverage:.3f} | {diff} |".format(
                file=row["file"],
                mean=comparison.get("mean_absolute_rgb_diff", 0.0),
                changed=comparison.get("thresholded_different_pixel_percent", 0.0),
                coverage=comparison.get("coverage_ratio", 0.0),
                diff=comparison.get("diff_png", ""),
            )
        )
    lines.extend(["", "## Non-Acceptable Rows", ""])
    non_acceptable = [row for row in rows if row["status"] != "acceptable"]
    if not non_acceptable:
        lines.append("None.")
    else:
        lines.extend([
            "| File | Status | Viewer Exit | Playwright Exit | Mean RGB Diff |",
            "| --- | --- | ---: | ---: | ---: |",
        ])
        for row in non_acceptable:
            comparison = row.get("comparison", {})
            lines.append(
            "| {file} | {status} | {viewer} | {pw} | {mean:.3f} |".format(
                file=row["file"],
                status=row["status"],
                viewer=row["viewer_exit"],
                pw=row["playwright_exit"],
                    mean=comparison.get("mean_absolute_rgb_diff", 0.0),
                )
            )
    out_path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--examples-root", type=Path, default=DEFAULT_EXAMPLES_ROOT)
    parser.add_argument("--viewer", type=Path, default=DEFAULT_VIEWER)
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--viewport", default="1280x720")
    parser.add_argument("--timeout", type=int, default=90)
    parser.add_argument("--screenshot-after-ms", type=int, default=500)
    parser.add_argument("--compare-threshold", type=int, default=8)
    parser.add_argument("--mean-diff-threshold", type=float, default=5.0)
    parser.add_argument("--pixel-diff-percent-threshold", type=float, default=5.0)
    parser.add_argument("--skip-interactions", action="store_true")
    parser.add_argument("--max-interaction-points", type=int, default=6)
    parser.add_argument("--interaction-click-repeats", type=int, default=2)
    parser.add_argument("--click-affordance-points", action="store_true")
    parser.add_argument("--control-semantic-checks", action="store_true")
    args = parser.parse_args()

    examples_root = args.examples_root.resolve()
    viewer = args.viewer.resolve()
    if not examples_root.exists():
        raise SystemExit(f"examples root not found: {examples_root}")
    if not viewer.exists():
        raise SystemExit(f"viewer not found: {viewer}")
    parse_viewport(args.viewport)
    html_files = enumerate_html(examples_root)
    if not html_files:
        raise SystemExit(f"no HTML files found under: {examples_root}")

    out_dir = args.out_dir.resolve()
    out_dir.mkdir(parents=True, exist_ok=True)
    results = []
    for index, html_file in enumerate(html_files, start=1):
        print(f"[{index}/{len(html_files)}] {rel_to_root(html_file, examples_root)}")
        result = validate_page(
            html_file,
            examples_root,
            viewer,
            out_dir,
            args.viewport,
            args.timeout,
            args.screenshot_after_ms,
            args.compare_threshold,
            not args.skip_interactions,
            args.max_interaction_points,
            args.interaction_click_repeats,
            args.click_affordance_points,
            args.control_semantic_checks,
        )
        result["status"] = status_for(
            result,
            args.mean_diff_threshold,
            args.pixel_diff_percent_threshold,
        )
        results.append(result)

    summary: dict[str, Any] = {
        "schema_version": 1,
        "examples_root": str(examples_root),
        "viewer": str(viewer),
        "viewport": args.viewport,
        "screenshot_after_ms": max(0, args.screenshot_after_ms),
        "compare_threshold": args.compare_threshold,
        "mean_diff_threshold": args.mean_diff_threshold,
        "pixel_diff_percent_threshold": args.pixel_diff_percent_threshold,
        "interaction_probe_enabled": not args.skip_interactions,
        "max_interaction_points": args.max_interaction_points,
        "interaction_click_repeats": args.interaction_click_repeats,
        "click_affordance_points": args.click_affordance_points,
        "control_semantic_checks": args.control_semantic_checks,
        "page_count": len(results),
        "viewer_failure_count": sum(1 for row in results if row["viewer_exit"] != 0),
        "viewer_timeout_count": sum(1 for row in results if row["viewer_timeout"]),
        "interaction_failure_count": sum(
            1 for row in results if row.get("interaction_exit", 0) != 0
        ),
        "interaction_timeout_count": sum(
            1 for row in results if row.get("interaction_timeout")
        ),
        "control_semantic_failure_count": sum(
            row.get("control_semantic_failure_count", 0) for row in results
        ),
        "control_semantic_timeout_count": sum(
            row.get("control_semantic_timeout_count", 0) for row in results
        ),
        "interaction_semantic_failure_count": sum(
            row.get("interaction_semantics", {}).get("failed_assertion_count", 0)
            for row in results
        ),
        "playwright_failure_count": sum(
            1 for row in results if row["playwright_exit"] != 0
        ),
        "playwright_timeout_count": sum(
            1 for row in results if row["playwright_timeout"]
        ),
        "missing_artifact_count": sum(
            1 for row in results if row.get("missing_artifacts")
        ),
        "acceptable_count": sum(1 for row in results if row["status"] == "acceptable"),
        "visual_flag_count": sum(1 for row in results if row["status"] == "visual_flag"),
        "status_counts": {},
        "results": results,
    }
    for row in results:
        summary["status_counts"][row["status"]] = (
            summary["status_counts"].get(row["status"], 0) + 1
        )
    (out_dir / "summary.json").write_text(
        json.dumps(summary, indent=2), encoding="utf-8"
    )
    write_markdown(summary, out_dir / "summary.md")
    print(json.dumps({key: value for key, value in summary.items()
                      if key != "results"}, indent=2))
    return 1 if (
        summary["viewer_failure_count"]
        or summary["viewer_timeout_count"]
        or summary["interaction_failure_count"]
        or summary["interaction_timeout_count"]
        or summary["control_semantic_failure_count"]
        or summary["control_semantic_timeout_count"]
        or summary["interaction_semantic_failure_count"]
        or summary["playwright_failure_count"]
        or summary["playwright_timeout_count"]
        or summary["missing_artifact_count"]
    ) else 0


if __name__ == "__main__":
    raise SystemExit(main())
