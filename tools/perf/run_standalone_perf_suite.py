#!/usr/bin/env python3
"""Compositor-path performance and correctness validation suite.

The active renderer is a single Chromium compositor path:

  Blink -> PaintArtifactCompositor -> cc -> GPU raster/shared image -> Viz

This runner intentionally does not request BMP output, software raster,
retained draw commands, or oracle comparisons.  It validates that the
standalone benchmark reaches the cc/GPU/Viz submission milestones and records
command/process timings for the selected HTML fixture set.
"""

from __future__ import annotations

import argparse
import csv
import fnmatch
import json
import math
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[2]
PAINT_AUDIT_ROOT = (
    ROOT / "upstream" / "chromium" / "standalone_renderer" / "testdata" / "paint_audit"
)
DEFAULT_BENCHMARK = (
    ROOT
    / "build"
    / "cmake-live-image-png-ninja-vs18"
    / "blink_standalone_render_benchmark_skia.exe"
)
DEFAULT_OUT = ROOT / "build" / "perf" / "compositor-suite"

RENDERER_PATH = "blink_paint_artifact_compositor_cc_viz_gpu_vulkan"

REQUIRED_TRUE_FIELDS = (
    "single_chromium_compositor_path",
    "paint_clean",
    "root_layer_available",
    "cc_host_created",
    "cc_root_layer_attached",
    "cc_commit_requested",
    "cc_frame_sink_requested",
    "cc_frame_sink_bound",
    "gpu_context_created",
    "raster_context_created",
    "shared_image_interface_available",
    "compositor_frame_submitted",
)

WARM_REQUIRED_TRUE_FIELDS = tuple(
    key for key in REQUIRED_TRUE_FIELDS if key != "single_chromium_compositor_path"
)

REQUIRED_TEXT_METRICS = (
    "paint_clean",
    "root_layer",
    "cc_host",
    "cc_attached",
    "cc_commit",
    "frame_sink_request",
    "frame_sink_bound",
    "gpu_context",
    "raster_context",
    "shared_image",
    "viz_submit",
)

FAILURE_MARKERS = (
    "SharedImageBackingFactory",
    "Context lost",
    "context lost",
    "MakeCurrent failed",
    "missing SharedImageBacking",
    "retained draw",
    "DrawCommandList",
    "SDL texture",
)


@dataclass
class CommandResult:
    code: int
    wall_ms: float
    launch_ms: float
    wait_ms: float
    output: str
    timed_out: bool = False


def rel(path: Path, base: Path = ROOT) -> str:
    try:
        return path.resolve().relative_to(base.resolve()).as_posix()
    except ValueError:
        return str(path)


def safe_case_name(path: Path) -> str:
    return path.stem.replace(" ", "_").replace("/", "_").replace("\\", "_")


def read_json(path: Path) -> dict[str, Any]:
    if not path.exists():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8", errors="replace"))
    except Exception as exc:
        return {"_json_error": str(exc)}


def write_json(path: Path, payload: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2), encoding="utf-8")


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


def parse_metric_line(output: str, prefix: str) -> dict[str, Any]:
    for line in output.splitlines():
        text = line.strip()
        if not text.startswith(prefix):
            continue
        row: dict[str, Any] = {}
        for token in text[len(prefix) :].strip().split():
            if "=" not in token:
                continue
            key, value = token.split("=", 1)
            row[key] = parse_value(value)
        return row
    return {}


def run_command(cmd: list[str], log_path: Path, timeout: int) -> CommandResult:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    start = time.perf_counter()
    launch_ms = 0.0
    wait_ms = 0.0
    timed_out = False
    creationflags = 0
    if sys.platform == "win32":
        creationflags = subprocess.CREATE_NEW_PROCESS_GROUP
    try:
        launch_start = time.perf_counter()
        proc = subprocess.Popen(
            cmd,
            cwd=ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            encoding="utf-8",
            errors="replace",
            creationflags=creationflags,
        )
        launch_ms = (time.perf_counter() - launch_start) * 1000.0
        try:
            wait_start = time.perf_counter()
            output, _ = proc.communicate(timeout=timeout)
            wait_ms = (time.perf_counter() - wait_start) * 1000.0
            code = proc.returncode
        except subprocess.TimeoutExpired:
            timed_out = True
            code = 124
            try:
                proc.kill()
            except Exception:
                pass
            output, _ = proc.communicate(timeout=5)
            output = (output or "") + f"\nTIMEOUT after {timeout}s\n"
    except Exception as exc:
        code = 124
        output = f"COMMAND_ERROR: {exc}\n"
    wall_ms = (time.perf_counter() - start) * 1000.0
    log_path.write_text(
        f"$ {' '.join(cmd)}\n"
        f"exit={code} wall_ms={wall_ms:.3f} launch_ms={launch_ms:.3f} "
        f"wait_ms={wait_ms:.3f} timed_out={str(timed_out).lower()} "
        f"timeout_s={timeout}\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return CommandResult(code, wall_ms, launch_ms, wait_ms, output, timed_out)


def discover_html_files(root: Path, filters: list[str]) -> list[Path]:
    files = sorted(path for path in root.rglob("*.html") if path.is_file())
    if not filters:
        return files
    selected: list[Path] = []
    for path in files:
        rel_path = path.relative_to(root).as_posix()
        if any(fnmatch.fnmatch(path.stem, pattern) or fnmatch.fnmatch(rel_path, pattern) for pattern in filters):
            selected.append(path)
    return selected


def select_files(
    files: list[Path],
    start_index: int,
    limit: int | None,
    shard_index: int | None,
    shard_count: int | None,
) -> tuple[list[Path], dict[str, Any]]:
    if start_index < 1:
        raise ValueError("--start-index is 1-based")
    if (shard_index is None) != (shard_count is None):
        raise ValueError("--shard-index and --shard-count must be provided together")
    selected = files
    if shard_count is not None:
        if shard_count <= 0 or shard_index is None or not 0 <= shard_index < shard_count:
            raise ValueError("invalid shard selection")
        selected = [path for idx, path in enumerate(selected) if idx % shard_count == shard_index]
    selected = selected[start_index - 1 :]
    if limit is not None:
        selected = selected[: max(0, limit)]
    return selected, {
        "available_page_count": len(files),
        "selected_page_count": len(selected),
        "start_index": start_index,
        "limit": limit,
        "shard_index": shard_index,
        "shard_count": shard_count,
    }


def validate_result(
    payload: dict[str, Any],
    text_metrics: dict[str, Any],
    output: str,
) -> list[str]:
    failures: list[str] = []
    if payload.get("renderer_path") != RENDERER_PATH:
        failures.append(f"unexpected renderer_path={payload.get('renderer_path')!r}")
    for key in REQUIRED_TRUE_FIELDS:
        if payload.get(key) is not True:
            failures.append(f"expected json {key}=true, got {payload.get(key)!r}")
    for key in REQUIRED_TEXT_METRICS:
        if text_metrics.get(key) != 1:
            failures.append(f"expected text metric {key}=1, got {text_metrics.get(key)!r}")
    for marker in FAILURE_MARKERS:
        if marker in output:
            failures.append(f"unexpected failure marker in output: {marker}")
    for scenario in payload.get("warm_scenarios", []) or []:
        if not isinstance(scenario, dict):
            failures.append("invalid warm_scenarios entry")
            continue
        scenario_name = scenario.get("scenario", "<unknown>")
        if scenario.get("failure_count", 0):
            failures.append(
                f"warm scenario {scenario_name} reported {scenario.get('failure_count')} failing frame(s)"
            )
        for frame in scenario.get("frames", []) or []:
            if not isinstance(frame, dict):
                failures.append(f"warm scenario {scenario_name} has invalid frame entry")
                continue
            if frame.get("frame_skipped_due_to_no_demand") is True:
                continue
            for key in WARM_REQUIRED_TRUE_FIELDS:
                if frame.get(key) is not True:
                    failures.append(
                        f"warm scenario {scenario_name} iteration {frame.get('iteration')} expected {key}=true, got {frame.get(key)!r}"
                    )
                    break
    return failures


def run_case(
    benchmark: Path,
    html_path: Path,
    root: Path,
    out_dir: Path,
    viewport: str,
    timeout: int,
    extra_args: list[str],
    trace_stages: bool,
) -> dict[str, Any]:
    case_dir = out_dir / "pages" / safe_case_name(html_path)
    json_path = case_dir / "compositor.json"
    log_path = case_dir / "benchmark.log"
    cmd = [
        str(benchmark),
        "--html-file",
        str(html_path),
        "--resource-root",
        str(root),
        "--viewport",
        viewport,
        "--json",
        str(json_path),
        *extra_args,
    ]
    if trace_stages:
        cmd.append("--trace-stages")
    result = run_command(cmd, log_path, timeout)
    payload = read_json(json_path)
    text_metrics = parse_metric_line(result.output, "compositor_metrics")
    text_timing = parse_metric_line(result.output, "compositor_timing")
    failures: list[str] = []
    if result.code != 0:
        failures.append(f"benchmark exited {result.code}")
    if result.timed_out:
        failures.append(f"benchmark timed out after {timeout}s")
    if payload.get("_json_error"):
        failures.append(f"json parse failed: {payload['_json_error']}")
    if not payload:
        failures.append("benchmark did not write compositor json")
    else:
        failures.extend(validate_result(payload, text_metrics, result.output))

    timing = payload.get("timing", {}) if isinstance(payload.get("timing"), dict) else {}
    warm_scenarios = (
        payload.get("warm_scenarios", [])
        if isinstance(payload.get("warm_scenarios"), list)
        else []
    )
    return {
        "name": safe_case_name(html_path),
        "html": rel(html_path),
        "log": rel(log_path),
        "json": rel(json_path) if json_path.exists() else "",
        "command": cmd,
        "exit_code": result.code,
        "timed_out": result.timed_out,
        "wall_ms": result.wall_ms,
        "launch_ms": result.launch_ms,
        "wait_ms": result.wait_ms,
        "process_elapsed_ms": timing.get("process_elapsed_ms"),
        "runtime_create_ms": timing.get("runtime_create_ms"),
        "initialize_ms": timing.get("initialize_ms"),
        "advance_frame_ms": timing.get("advance_frame_ms"),
        "warm_scenarios": warm_scenarios,
        "text_metrics": text_metrics,
        "text_timing": text_timing,
        "compositor": {
            key: payload.get(key)
            for key in [
                "paint_clean",
                "frame_advanced",
                "frame_skipped_due_to_no_demand",
                "root_layer_available",
                "cc_host_created",
                "cc_root_layer_attached",
                "cc_commit_requested",
                "cc_frame_sink_bound",
                "gpu_context_created",
                "raster_context_created",
                "shared_image_interface_available",
                "compositor_frame_submitted",
                "viz_display_created",
                "skia_renderer_gpu_path_reached",
                "compositor_layer_count",
                "paint_chunk_count",
                "display_item_count",
            ]
        },
        "failures": failures,
    }


def percentile(values: list[float], pct: float) -> float | None:
    clean = sorted(v for v in values if math.isfinite(v))
    if not clean:
        return None
    if len(clean) == 1:
        return clean[0]
    rank = (len(clean) - 1) * pct
    lower = int(rank)
    upper = min(len(clean) - 1, lower + 1)
    return clean[lower] + (clean[upper] - clean[lower]) * (rank - lower)


def stats(rows: list[dict[str, Any]], key: str) -> dict[str, Any]:
    values = [float(row[key]) for row in rows if isinstance(row.get(key), (int, float))]
    return {
        "count": len(values),
        "p50": percentile(values, 0.50),
        "p95": percentile(values, 0.95),
        "max": max(values) if values else None,
    }


def stats_from_values(values: list[float]) -> dict[str, Any]:
    clean = [float(value) for value in values if isinstance(value, (int, float))]
    return {
        "count": len(clean),
        "p50": percentile(clean, 0.50),
        "p95": percentile(clean, 0.95),
        "max": max(clean) if clean else None,
    }


def summarize_warm(rows: list[dict[str, Any]]) -> dict[str, Any]:
    scenarios: dict[str, dict[str, Any]] = {}
    for row in rows:
        for scenario in row.get("warm_scenarios", []) or []:
            if not isinstance(scenario, dict):
                continue
            name = str(scenario.get("scenario", "unknown"))
            bucket = scenarios.setdefault(
                name,
                {
                    "page_count": 0,
                    "frame_count": 0,
                    "effective_frame_count": 0,
                    "failure_count": 0,
                    "gpu_submission_frame_count": 0,
                    "skipped_frame_count": 0,
                    "advance_frame_values": [],
                },
            )
            bucket["page_count"] += 1
            bucket["failure_count"] += int(scenario.get("failure_count") or 0)
            for frame in scenario.get("frames", []) or []:
                if not isinstance(frame, dict):
                    continue
                bucket["frame_count"] += 1
                if frame.get("effective") is True:
                    bucket["effective_frame_count"] += 1
                if frame.get("frame_skipped_due_to_no_demand") is True:
                    bucket["skipped_frame_count"] += 1
                elif frame.get("compositor_frame_submitted") is True:
                    bucket["gpu_submission_frame_count"] += 1
                value = frame.get("advance_frame_ms")
                if isinstance(value, (int, float)):
                    bucket["advance_frame_values"].append(float(value))

    summary: dict[str, Any] = {}
    for name, bucket in scenarios.items():
        values = bucket.pop("advance_frame_values")
        bucket["advance_frame_ms"] = stats_from_values(values)
        summary[name] = bucket
    return summary


def summarize(rows: list[dict[str, Any]]) -> dict[str, Any]:
    failures = [
        f"{row['name']}: {failure}"
        for row in rows
        for failure in row.get("failures", [])
    ]
    return {
        "page_count": len(rows),
        "failure_count": len(failures),
        "failures": failures,
        "wall_ms": stats(rows, "wall_ms"),
        "process_elapsed_ms": stats(rows, "process_elapsed_ms"),
        "advance_frame_ms": stats(rows, "advance_frame_ms"),
        "initialize_ms": stats(rows, "initialize_ms"),
        "gpu_submission_page_count": sum(
            1
            for row in rows
            if row.get("compositor", {}).get("compositor_frame_submitted") is True
        ),
        "warm": summarize_warm(rows),
    }


def write_csv(path: Path, rows: list[dict[str, Any]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "name",
        "html",
        "exit_code",
        "wall_ms",
        "process_elapsed_ms",
        "initialize_ms",
        "advance_frame_ms",
        "cc_frame_sink_bound",
        "gpu_context_created",
        "raster_context_created",
        "shared_image_interface_available",
        "compositor_frame_submitted",
        "failure_count",
    ]
    with path.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fields)
        writer.writeheader()
        for row in rows:
            compositor = row.get("compositor", {})
            writer.writerow(
                {
                    "name": row.get("name"),
                    "html": row.get("html"),
                    "exit_code": row.get("exit_code"),
                    "wall_ms": row.get("wall_ms"),
                    "process_elapsed_ms": row.get("process_elapsed_ms"),
                    "initialize_ms": row.get("initialize_ms"),
                    "advance_frame_ms": row.get("advance_frame_ms"),
                    "cc_frame_sink_bound": compositor.get("cc_frame_sink_bound"),
                    "gpu_context_created": compositor.get("gpu_context_created"),
                    "raster_context_created": compositor.get("raster_context_created"),
                    "shared_image_interface_available": compositor.get(
                        "shared_image_interface_available"
                    ),
                    "compositor_frame_submitted": compositor.get(
                        "compositor_frame_submitted"
                    ),
                    "failure_count": len(row.get("failures", [])),
                }
            )


def write_markdown(path: Path, report: dict[str, Any]) -> None:
    summary = report["summary"]
    warm_summary = summary.get("warm", {})
    lines = [
        "# Compositor Perf Baseline",
        "",
        "Generated by `tools/perf/run_standalone_perf_suite.py`.",
        "",
        "Active path: Blink/PaintArtifactCompositor -> cc -> GPU raster/shared image -> Viz.",
        "",
        f"- Pages: {summary['page_count']}",
        f"- Failures: {summary['failure_count']}",
        f"- GPU submissions: {summary['gpu_submission_page_count']}",
        f"- `advance_frame_ms` p95: {summary['advance_frame_ms']['p95']}",
        f"- `process_elapsed_ms` p95: {summary['process_elapsed_ms']['p95']}",
        "",
        "## Warm Compositor Scenarios",
        "",
    ]
    if warm_summary:
        lines.extend(
            [
                "| Scenario | Pages | Frames | Effective frames | Failures | GPU submissions | p50 | p95 | max |",
                "| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |",
            ]
        )
        for name, data in sorted(warm_summary.items()):
            timing = data.get("advance_frame_ms", {})
            lines.append(
                f"| `{name}` | {data.get('page_count')} | {data.get('frame_count')} | "
                f"{data.get('effective_frame_count')} | {data.get('failure_count')} | "
                f"{data.get('gpu_submission_frame_count')} | {timing.get('p50')} | "
                f"{timing.get('p95')} | {timing.get('max')} |"
            )
    else:
        lines.append("Warm no-change, scroll, and attribute-toggle timings are not measured in this run.")
    lines.extend(
        [
            "",
        "The benchmark does not generate CPU-raster images or retained-renderer oracle output.",
        "SDL/window presentation is validated separately by `run_sdl_profile_benchmark.py`.",
        "",
        ]
    )
    path.write_text("\n".join(lines), encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--root", type=Path, default=PAINT_AUDIT_ROOT)
    parser.add_argument("--out-dir", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--viewport", default="320x200")
    parser.add_argument("--timeout", type=int, default=90)
    parser.add_argument("--filter", action="append", default=[])
    parser.add_argument("--start-index", type=int, default=1)
    parser.add_argument("--limit", type=int)
    parser.add_argument("--shard-index", type=int)
    parser.add_argument("--shard-count", type=int)
    parser.add_argument("--benchmark-arg", action="append", default=[])
    parser.add_argument(
        "--warm-scenario",
        action="append",
        default=[],
        help="Warm compositor scenario to run inside each benchmark process. Can be repeated or comma-separated.",
    )
    parser.add_argument(
        "--warm-iterations",
        type=int,
        default=0,
        help="Number of post-cold AdvanceFrame calls per warm scenario.",
    )
    parser.add_argument("--trace-stages", action="store_true")
    parser.add_argument("--build-config-name", default="")
    parser.add_argument("--write-baseline-doc", action="store_true")
    # Accepted for old automation compatibility; no longer used by the
    # compositor-path suite.
    parser.add_argument("--no-docs", action="store_true", help=argparse.SUPPRESS)
    parser.add_argument("--skip-warm-modes", action="store_true", help=argparse.SUPPRESS)
    parser.add_argument("--playwright-top", type=int, default=0, help=argparse.SUPPRESS)
    parser.add_argument("--playwright-all", action="store_true", help=argparse.SUPPRESS)
    parser.add_argument("--correctness-timeout", type=int, default=0, help=argparse.SUPPRESS)
    parser.add_argument("--retries", type=int, default=0, help=argparse.SUPPRESS)
    args = parser.parse_args()

    benchmark = args.benchmark.resolve()
    html_root = args.root.resolve()
    out_dir = args.out_dir.resolve()
    if not benchmark.exists():
        raise SystemExit(f"benchmark not found: {benchmark}")
    if not html_root.exists():
        raise SystemExit(f"fixture root not found: {html_root}")

    try:
        files, selection = select_files(
            discover_html_files(html_root, args.filter),
            args.start_index,
            args.limit,
            args.shard_index,
            args.shard_count,
        )
    except ValueError as exc:
        print(str(exc), file=sys.stderr)
        return 2
    if not files:
        print("No HTML files matched.", file=sys.stderr)
        return 2

    rows: list[dict[str, Any]] = []
    started = time.strftime("%Y-%m-%dT%H:%M:%S%z")
    for index, html_path in enumerate(files, start=1):
        print(f"[{index}/{len(files)}] {html_path.relative_to(html_root).as_posix()}", flush=True)
        extra_args = list(args.benchmark_arg)
        if args.warm_iterations > 0:
            extra_args.extend(["--warm-iterations", str(args.warm_iterations)])
            for scenario in args.warm_scenario:
                extra_args.extend(["--warm-scenario", scenario])
        rows.append(
            run_case(
                benchmark,
                html_path,
                html_root,
                out_dir,
                args.viewport,
                args.timeout,
                extra_args,
                args.trace_stages,
            )
        )
        write_json(
            out_dir / "standalone_perf_results.partial.json",
            {
                "schema_version": 2,
                "generated_at": started,
                "selection": selection,
                "pages": rows,
                "summary": summarize(rows),
            },
        )

    report = {
        "schema_version": 2,
        "generated_at": started,
        "repo": rel(ROOT),
        "benchmark": rel(benchmark),
        "build_config_name": args.build_config_name,
        "paint_audit_root": rel(html_root),
        "viewport": args.viewport,
        "selection": selection,
        "measurement_caveats": [
            "wall_ms is Python subprocess wall time and includes process launch and teardown.",
            "process_elapsed_ms starts at benchmark main and excludes Python orchestration.",
            "advance_frame_ms covers the measured compositor AdvanceFrame call.",
            "SDL/window Vulkan presentation is validated by run_sdl_profile_benchmark.py.",
        ],
        "summary": summarize(rows),
        "pages": rows,
    }
    write_json(out_dir / "standalone_perf_results.json", report)
    write_csv(out_dir / "standalone_perf_results.csv", rows)
    if args.write_baseline_doc and not args.no_docs:
        write_markdown(ROOT / "docs" / "PERF_BASELINE.md", report)
    print(json.dumps({"summary": report["summary"], "results": rel(out_dir)}, indent=2))
    return 0 if report["summary"]["failure_count"] == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
