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
    points = []
    seen: set[tuple[int, int]] = set()
    for item in state.get("interactiveElements", []):
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


def run_interaction_smoke(
    html_file: Path,
    examples_root: Path,
    viewer: Path,
    page_dir: Path,
    viewport: str,
    timeout_seconds: int,
    points: list[dict[str, Any]],
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
        cmd.extend(["--synthetic-sdl-click-repeats", "2"])
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
        "interaction_last_frame_metrics": last_frame_metrics(output),
        "interaction_last_presentation_metrics": last_presentation_metrics(output),
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
) -> dict[str, Any]:
    page_slug = slug_for(html_file, examples_root)
    page_dir = out_dir / "pages" / page_slug
    page_dir.mkdir(parents=True, exist_ok=True)
    standalone_png = page_dir / "viewer.png"
    reference_png = page_dir / "playwright.png"
    diff_png = page_dir / "diff.png"
    playwright_state = page_dir / "playwright_state.json"
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
        "viewer_png_exists": standalone_png.exists(),
        "playwright_png_exists": reference_png.exists(),
        "last_frame_metrics": last_frame_metrics(viewer_output),
        "last_presentation_metrics": last_presentation_metrics(viewer_output),
    }
    if run_interactions:
        interaction_points = read_interactive_points(
            playwright_state, max_interaction_points
        )
        result.update(
            run_interaction_smoke(
                html_file,
                examples_root,
                viewer,
                page_dir,
                viewport,
                timeout_seconds,
                interaction_points,
            )
        )
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
        "page_count": len(results),
        "viewer_failure_count": sum(1 for row in results if row["viewer_exit"] != 0),
        "viewer_timeout_count": sum(1 for row in results if row["viewer_timeout"]),
        "interaction_failure_count": sum(
            1 for row in results if row.get("interaction_exit", 0) != 0
        ),
        "interaction_timeout_count": sum(
            1 for row in results if row.get("interaction_timeout")
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
        or summary["playwright_failure_count"]
        or summary["playwright_timeout_count"]
        or summary["missing_artifact_count"]
    ) else 0


if __name__ == "__main__":
    raise SystemExit(main())
