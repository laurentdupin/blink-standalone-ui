#!/usr/bin/env python3
"""Standalone renderer performance and correctness baseline suite.

The suite intentionally drives the existing standalone benchmark executable
instead of adding a second renderer harness.  It records the benchmark's
in-process timings, raw Blink probe stage timings, retained-vs-oracle
correctness, and optional Playwright comparisons for slow/problematic pages.
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
from typing import Any, Callable


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
DEFAULT_OUT = ROOT / "build" / "perf"
COMPARE_SCRIPT = ROOT / "tools" / "content_aware_compare.py"
PLAYWRIGHT_SCRIPT = ROOT / "tools" / "playwright_screenshot.cjs"


@dataclass
class CommandResult:
    code: int
    wall_ms: float
    output: str
    timed_out: bool = False
    timeout_s: int | None = None
    kill_error: str = ""
    kill_output: str = ""


WINDOWS_STATUS_NAMES = {
    0xC0000005: "windows_access_violation",
    0xC000001D: "windows_illegal_instruction",
    0xC0000409: "windows_stack_buffer_overrun",
}


def rel(path: Path, base: Path = ROOT) -> str:
    try:
        return path.resolve().relative_to(base.resolve()).as_posix()
    except ValueError:
        return str(path)


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


def read_cmake_cache(cache_path: Path) -> dict[str, str]:
    values: dict[str, str] = {}
    if not cache_path.exists():
        return values
    for line in cache_path.read_text(encoding="utf-8", errors="replace").splitlines():
        if not line or line.startswith(("#", "//")) or "=" not in line:
            continue
        key_type, value = line.split("=", 1)
        key = key_type.split(":", 1)[0]
        values[key] = value
    return values


def build_config_metadata(
    benchmark: Path, build_config_name: str | None
) -> dict[str, Any]:
    build_dir = benchmark.parent
    cache = read_cmake_cache(build_dir / "CMakeCache.txt")
    perf_build = cache.get("BLINK_STANDALONE_PERF_BUILD")
    if build_config_name:
        name = build_config_name
    elif perf_build and perf_build.upper() in {"ON", "TRUE", "1"}:
        name = "x64-Perf"
    elif "perf" in build_dir.name.lower():
        name = "perf"
    else:
        name = "checked/current"
    return {
        "name": name,
        "benchmark": rel(benchmark),
        "build_dir": rel(build_dir),
        "cmake_cache": rel(build_dir / "CMakeCache.txt")
        if (build_dir / "CMakeCache.txt").exists()
        else "",
        "cmake_build_type": cache.get("CMAKE_BUILD_TYPE", ""),
        "blink_standalone_perf_build": perf_build or "",
        "blink_standalone_build_sdl_viewer": cache.get(
            "BLINK_STANDALONE_BUILD_SDL_VIEWER", ""
        ),
        "defines_policy": (
            "perf preset omits forced SK_ENABLE_OPTIMIZE_SIZE, CPU_NO_SIMD, "
            "SKCMS_DISABLE_HSW, and SKCMS_DISABLE_SKX; DCHECK_ALWAYS_ON remains "
            "enabled because the current standalone Blink cut does not compile "
            "without DCHECK declarations"
            if perf_build and perf_build.upper() in {"ON", "TRUE", "1"}
            else "checked/current preset keeps historical correctness-oriented defines"
        ),
    }


def terminate_process_tree(proc: subprocess.Popen[str], timeout: int = 10) -> tuple[str, str]:
    if proc.poll() is not None:
        return "", ""
    output = ""
    error = ""
    if sys.platform == "win32":
        try:
            completed = subprocess.run(
                ["taskkill", "/PID", str(proc.pid), "/T", "/F"],
                cwd=ROOT,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                timeout=timeout,
            )
            output = completed.stdout or ""
            if completed.returncode != 0 and proc.poll() is None:
                error = f"taskkill exited {completed.returncode}"
        except Exception as exc:
            error = str(exc)
        if proc.poll() is None:
            try:
                proc.kill()
            except Exception as exc:
                error = error or str(exc)
    else:
        try:
            proc.kill()
        except Exception as exc:
            error = str(exc)
    try:
        proc.wait(timeout=timeout)
    except subprocess.TimeoutExpired:
        error = error or "process did not exit after kill"
    return output, error


def exit_status_name(code: int) -> str:
    if sys.platform == "win32":
        return WINDOWS_STATUS_NAMES.get(code & 0xFFFFFFFF, "")
    if code < 0:
        return f"signal_{-code}"
    return ""


def run_command(cmd: list[str], log_path: Path, timeout: int) -> CommandResult:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    start = time.perf_counter()
    timed_out = False
    kill_error = ""
    kill_output = ""
    creationflags = 0
    if sys.platform == "win32":
        creationflags = subprocess.CREATE_NEW_PROCESS_GROUP
    try:
        proc = subprocess.Popen(
            cmd,
            cwd=ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            creationflags=creationflags,
        )
        try:
            output, _ = proc.communicate(timeout=timeout)
            code = proc.returncode
        except subprocess.TimeoutExpired:
            timed_out = True
            code = 124
            kill_output, kill_error = terminate_process_tree(proc)
            try:
                output, _ = proc.communicate(timeout=2)
            except subprocess.TimeoutExpired:
                kill_error = kill_error or "process did not exit after kill"
                output = ""
            output = output or ""
            output += f"\nTIMEOUT after {timeout}s; terminated process tree\n"
            if kill_output:
                output += f"TASKKILL_OUTPUT:\n{kill_output}\n"
            if kill_error:
                output += f"KILL_ERROR: {kill_error}\n"
    except Exception as exc:
        code = 124
        output = f"COMMAND_ERROR: {exc}\n"
    wall_ms = (time.perf_counter() - start) * 1000.0
    log_path.write_text(
        f"$ {' '.join(cmd)}\n"
        f"exit={code} wall_ms={wall_ms:.3f} timed_out={str(timed_out).lower()} timeout_s={timeout}\n\n"
        f"{output}",
        encoding="utf-8",
        errors="replace",
    )
    return CommandResult(
        code=code,
        wall_ms=wall_ms,
        output=output,
        timed_out=timed_out,
        timeout_s=timeout if timed_out else None,
        kill_error=kill_error,
        kill_output=kill_output,
    )


def percentile(values: list[float], pct: float) -> float | None:
    clean = sorted(v for v in values if math.isfinite(v))
    if not clean:
        return None
    if len(clean) == 1:
        return clean[0]
    rank = (len(clean) - 1) * pct
    lower = math.floor(rank)
    upper = math.ceil(rank)
    if lower == upper:
        return clean[int(rank)]
    return clean[lower] + (clean[upper] - clean[lower]) * (rank - lower)


def stats(values: list[float]) -> dict[str, Any]:
    clean = [v for v in values if math.isfinite(v)]
    if not clean:
        return {"count": 0, "p50_ms": None, "p95_ms": None, "max_ms": None}
    return {
        "count": len(clean),
        "p50_ms": percentile(clean, 0.50),
        "p95_ms": percentile(clean, 0.95),
        "max_ms": max(clean),
    }


def nested(data: dict[str, Any], *keys: str, default: Any = None) -> Any:
    current: Any = data
    for key in keys:
        if not isinstance(current, dict) or key not in current:
            return default
        current = current[key]
    return current


def as_float(value: Any) -> float | None:
    try:
        result = float(value)
    except (TypeError, ValueError):
        return None
    return result if math.isfinite(result) else None


def timing_from_metrics(metrics: dict[str, Any]) -> dict[str, Any]:
    timing = metrics.get("render_timing_diagnostics")
    return timing if isinstance(timing, dict) else {}


def raw_probe_timing(metrics: dict[str, Any]) -> dict[str, Any]:
    timing = nested(
        metrics,
        "render_result",
        "raw_paint_artifact_audit_json",
        "render_timing_diagnostics",
        default={},
    )
    return timing if isinstance(timing, dict) else {}


def presented_frame_ms(metrics: dict[str, Any]) -> float | None:
    timing = timing_from_metrics(metrics)
    advance = as_float(timing.get("advance_and_render_ms"))
    raster = as_float(timing.get("cpu_raster_replay_ms"))
    if advance is None or raster is None:
        return None
    return advance + raster


def process_startup_overhead_ms(wall_ms: float, metrics: dict[str, Any]) -> float | None:
    process_elapsed = as_float(timing_from_metrics(metrics).get("process_elapsed_ms"))
    if process_elapsed is None:
        return None
    return max(0.0, wall_ms - process_elapsed)


def command_count(metrics: dict[str, Any]) -> int:
    value = nested(metrics, "render_timing_diagnostics", "retained_command_count", default=0)
    try:
        return int(value)
    except (TypeError, ValueError):
        return 0


def raw_chunk_count(metrics: dict[str, Any]) -> int:
    value = nested(metrics, "render_timing_diagnostics", "raw_chunk_count", default=0)
    try:
        return int(value)
    except (TypeError, ValueError):
        return 0


def document_max_scroll_y(metrics: dict[str, Any]) -> float:
    value = nested(metrics, "render_result", "document_max_scroll_offset", "y", default=0)
    parsed = as_float(value)
    return parsed if parsed is not None else 0.0


def has_real_blink_paint(metrics: dict[str, Any]) -> bool:
    diagnostics = metrics.get("diagnostics")
    if not isinstance(diagnostics, list):
        return False
    return any("paint artifact source: real Blink PaintArtifact" in str(item) for item in diagnostics)


def discover_html_files(root: Path, filters: list[str]) -> list[Path]:
    files = sorted(
        (path for path in root.rglob("*") if path.suffix.lower() in {".html", ".htm"}),
        key=lambda path: path.relative_to(root).as_posix().lower(),
    )
    if not filters:
        return files
    selected: list[Path] = []
    for path in files:
        name = path.stem
        relative = path.relative_to(root).as_posix()
        if any(fnmatch.fnmatch(name, pattern) or fnmatch.fnmatch(relative, pattern) for pattern in filters):
            selected.append(path)
    return selected


def infer_attribute_toggle(html_path: Path) -> tuple[str, str, str, str] | None:
    """Infer a real attribute toggle from simple data-* fixtures.

    This is intentionally generic: it looks for an element id with a data-*
    attribute and another value for the same data attribute somewhere in the
    source, typically from CSS selectors like [data-state="on"].
    """
    import re

    text = html_path.read_text(encoding="utf-8", errors="replace")
    element_re = re.compile(
        r"<(?P<tag>[a-zA-Z0-9:-]+)(?P<attrs>[^>]*\bid=['\"](?P<id>[^'\"]+)['\"][^>]*)>",
        re.IGNORECASE,
    )
    data_re = re.compile(r"\b(?P<name>data-[a-zA-Z0-9_-]+)=['\"](?P<value>[^'\"]+)['\"]")
    for element in element_re.finditer(text):
        element_id = element.group("id")
        attrs = element.group("attrs")
        for data_attr in data_re.finditer(attrs):
            name = data_attr.group("name")
            previous_value = data_attr.group("value")
            values = []
            for value_match in re.finditer(
                rf"{re.escape(name)}\s*=\s*['\"]([^'\"]+)['\"]", text
            ):
                value = value_match.group(1)
                if value not in values:
                    values.append(value)
            for current_value in values:
                if current_value != previous_value:
                    return element_id, name, previous_value, current_value
    return None


def benchmark_base_cmd(
    benchmark: Path,
    html_path: Path,
    resource_root: Path,
    viewport: str,
    out_path: Path,
    json_path: Path,
) -> list[str]:
    return [
        str(benchmark),
        "--html-file",
        str(html_path),
        "--resource-root",
        str(resource_root),
        "--viewport",
        viewport,
        "--skia-cpu",
        "--blink",
        "--min-non-white",
        "0",
        "--out",
        str(out_path),
        "--json",
        str(json_path),
    ]


def run_benchmark_case(
    benchmark: Path,
    html_path: Path,
    resource_root: Path,
    case_dir: Path,
    mode: str,
    viewport: str,
    timeout: int,
    retries: int,
    extra_args: list[str] | None = None,
    *,
    oracle: bool = False,
    disable_skia_raster: bool = False,
) -> dict[str, Any]:
    out_path = case_dir / f"{mode}.bmp"
    json_path = case_dir / f"{mode}.json"
    audit_path = case_dir / f"{mode}-audit.json"
    cmd = benchmark_base_cmd(
        benchmark, html_path, resource_root, viewport, out_path, json_path
    )
    if extra_args:
        cmd.extend(extra_args)
    cmd.extend(["--dump-paint-artifact", str(audit_path)])
    oracle_path = None
    if oracle:
        oracle_path = case_dir / f"{mode}-oracle.bmp"
        cmd.extend(["--paint-oracle=skia-paint-record", "--oracle-out", str(oracle_path)])
    if disable_skia_raster:
        cmd.append("--disable-skia-raster")
        # The benchmark still requires --out to be syntactically present.
    attempts: list[CommandResult] = []
    final_log_path = case_dir / f"{mode}.log"
    for attempt in range(retries + 1):
        for path in [out_path, json_path, audit_path]:
            if path.exists():
                path.unlink()
        if oracle_path and oracle_path.exists():
            oracle_path.unlink()
        log_name = f"{mode}.log" if attempt == 0 else f"{mode}-retry{attempt}.log"
        final_log_path = case_dir / log_name
        result = run_command(cmd, final_log_path, timeout)
        attempts.append(result)
        if not result.timed_out:
            break
    status_name = exit_status_name(result.code)
    metrics = read_json(json_path)
    payload: dict[str, Any] = {
        "mode": mode,
        "exit_code": result.code,
        "exit_status": status_name,
        "timed_out": result.timed_out,
        "timeout_s": result.timeout_s,
        "wall_ms": result.wall_ms,
        "log": rel(final_log_path),
        "image": rel(out_path) if out_path.exists() else "",
        "metrics_json": rel(json_path) if json_path.exists() else "",
        "audit_json": rel(audit_path) if audit_path.exists() else "",
        "oracle_image": rel(oracle_path) if oracle_path and oracle_path.exists() else "",
        "metrics": metrics,
        "timing": timing_from_metrics(metrics),
        "probe_timing": raw_probe_timing(metrics),
        "presented_frame_ms": presented_frame_ms(metrics),
        "process_startup_overhead_ms": process_startup_overhead_ms(result.wall_ms, metrics),
        "real_blink_paint": has_real_blink_paint(metrics),
        "missing_resource_count": metrics.get("missing_resource_count", None),
        "diagnostic_count": metrics.get("diagnostic_count", None),
        "retained_command_count": command_count(metrics),
        "raw_chunk_count": raw_chunk_count(metrics),
    }
    if len(attempts) > 1 or any(attempt.timed_out for attempt in attempts):
        payload["attempts"] = [
            {
                "attempt": index,
                "exit_code": attempt.code,
                "timed_out": attempt.timed_out,
                "timeout_s": attempt.timeout_s,
                "wall_ms": attempt.wall_ms,
                "log": rel(case_dir / (f"{mode}.log" if index == 0 else f"{mode}-retry{index}.log")),
                "kill_error": attempt.kill_error,
                "kill_output": attempt.kill_output,
                "exit_status": exit_status_name(attempt.code),
            }
            for index, attempt in enumerate(attempts)
        ]
    if result.timed_out:
        payload["failure_classification"] = "timeout"
        payload["reason"] = f"benchmark child exceeded {timeout}s timeout"
    elif result.code == 0 and any(attempt.timed_out for attempt in attempts[:-1]):
        payload["failure_classification"] = "flaky_timeout_recovered"
        payload["reason"] = "benchmark child timed out on an earlier attempt and recovered on retry"
    elif result.code != 0:
        payload["failure_classification"] = status_name or "benchmark_exit_nonzero"
        payload["reason"] = (
            f"benchmark child exited with {status_name} ({result.code})"
            if status_name
            else f"benchmark child exited with code {result.code}"
        )
    if result.kill_error:
        payload["kill_error"] = result.kill_error
    if result.kill_output:
        payload["kill_output"] = result.kill_output
    return payload


def compare_images(a: Path, b: Path, out_json: Path, out_dir: Path, timeout: int) -> dict[str, Any]:
    if not a.exists() or not b.exists():
        return {
            "exit_code": 2,
            "skipped": True,
            "reason": "missing input image",
        }
    cmd = [
        sys.executable,
        str(COMPARE_SCRIPT),
        "--standalone",
        str(a),
        "--playwright",
        str(b),
        "--out-json",
        str(out_json),
        "--out-dir",
        str(out_dir),
    ]
    result = run_command(cmd, out_json.with_suffix(".log"), timeout)
    payload = read_json(out_json)
    payload["exit_code"] = result.code
    payload["timed_out"] = result.timed_out
    payload["timeout_s"] = result.timeout_s
    if result.timed_out:
        payload["reason"] = f"comparison exceeded {timeout}s timeout"
    if result.kill_error:
        payload["kill_error"] = result.kill_error
    return payload


def playwright_available() -> bool:
    result = run_command(
        ["node", str(PLAYWRIGHT_SCRIPT), "--check-only"],
        DEFAULT_OUT / "playwright-check.log",
        30,
    )
    return result.code == 0


def run_playwright_capture(html_path: Path, out_path: Path, out_json: Path, viewport: str, timeout: int) -> CommandResult:
    cmd = [
        "node",
        str(PLAYWRIGHT_SCRIPT),
        "--html-file",
        str(html_path),
        "--out",
        str(out_path),
        "--viewport",
        viewport,
        "--out-json",
        str(out_json),
    ]
    return run_command(cmd, out_path.with_suffix(".log"), timeout)


def summarize(rows: list[dict[str, Any]]) -> dict[str, Any]:
    cold_rows = [row for row in rows if row.get("cold", {}).get("exit_code") == 0]
    values_by_key: dict[str, list[float]] = {
        "cold_presented_frame_ms": [],
        "cold_process_startup_overhead_ms": [],
        "cold_process_elapsed_ms": [],
        "cold_command_wall_ms": [],
        "cold_input_setup_ms": [],
        "cold_blink_embedder_create_ms": [],
        "cold_blink_initialize_ms": [],
        "cold_advance_and_render_ms": [],
        "cold_cpu_raster_replay_ms": [],
        "cold_output_image_write_ms": [],
        "probe_input_setup_ms": [],
        "probe_html_parse_document_setup_ms": [],
        "probe_style_update_ms": [],
        "probe_layout_lifecycle_ms": [],
        "probe_prepaint_paint_lifecycle_ms": [],
        "probe_paint_artifact_generation_ms": [],
        "probe_paint_artifact_extraction_ms": [],
        "probe_total_ms": [],
        "warm_no_change_presented_frame_ms": [],
        "warm_scroll_presented_frame_ms": [],
        "warm_attr_toggle_presented_frame_ms": [],
    }
    for row in cold_rows:
        cold = row["cold"]
        timing = cold.get("timing", {})
        probe = cold.get("probe_timing", {})
        for metric_key, source_key in [
            ("cold_process_elapsed_ms", "process_elapsed_ms"),
            ("cold_advance_and_render_ms", "advance_and_render_ms"),
            ("cold_cpu_raster_replay_ms", "cpu_raster_replay_ms"),
            ("cold_output_image_write_ms", "output_image_write_ms"),
        ]:
            value = as_float(timing.get(source_key))
            if value is not None:
                values_by_key[metric_key].append(value)
        if cold.get("presented_frame_ms") is not None:
            values_by_key["cold_presented_frame_ms"].append(float(cold["presented_frame_ms"]))
        if cold.get("process_startup_overhead_ms") is not None:
            values_by_key["cold_process_startup_overhead_ms"].append(
                float(cold["process_startup_overhead_ms"])
            )
        values_by_key["cold_command_wall_ms"].append(float(cold.get("wall_ms", 0.0)))
        for metric_key, source_key in [
            ("cold_input_setup_ms", "input_setup_ms"),
            ("cold_blink_embedder_create_ms", "blink_embedder_create_ms"),
            ("cold_blink_initialize_ms", "blink_initialize_ms"),
        ]:
            value = as_float(timing.get(source_key))
            if value is not None:
                values_by_key[metric_key].append(value)
        for metric_key, source_key in [
            ("probe_input_setup_ms", "input_setup_ms"),
            ("probe_html_parse_document_setup_ms", "html_parse_document_setup_ms"),
            ("probe_style_update_ms", "style_update_ms"),
            ("probe_layout_lifecycle_ms", "layout_lifecycle_ms"),
            ("probe_prepaint_paint_lifecycle_ms", "prepaint_paint_lifecycle_ms"),
            ("probe_paint_artifact_generation_ms", "paint_artifact_generation_ms"),
            ("probe_paint_artifact_extraction_ms", "paint_artifact_extraction_ms"),
            ("probe_total_ms", "total_probe_ms"),
        ]:
            value = as_float(probe.get(source_key))
            if value is not None:
                values_by_key[metric_key].append(value)
        for mode_key, stats_key in [
            ("warm_no_change", "warm_no_change_presented_frame_ms"),
            ("warm_scroll", "warm_scroll_presented_frame_ms"),
            ("warm_attr_toggle", "warm_attr_toggle_presented_frame_ms"),
        ]:
            mode = row.get(mode_key)
            if isinstance(mode, dict) and mode.get("presented_frame_ms") is not None:
                values_by_key[stats_key].append(float(mode["presented_frame_ms"]))
    correctness_failures = [
        row
        for row in rows
        if row.get("correctness", {}).get("exit_code") != 0
        or row.get("correctness", {}).get("diff_classification") == "structural_layout_or_paint"
    ]
    timeout_count = 0
    recovered_timeout_count = 0
    for row in rows:
        for value in row.values():
            if isinstance(value, dict):
                if value.get("timed_out"):
                    timeout_count += 1
                if value.get("failure_classification") == "flaky_timeout_recovered":
                    recovered_timeout_count += 1
    return {
        "page_count": len(rows),
        "cold_success_count": len(cold_rows),
        "failure_count": len(rows) - len(cold_rows),
        "timeout_count": timeout_count,
        "recovered_timeout_count": recovered_timeout_count,
        "real_blink_paint_count": sum(1 for row in cold_rows if row.get("cold", {}).get("real_blink_paint")),
        "correctness_failure_count": len(correctness_failures),
        "stats": {key: stats(value) for key, value in values_by_key.items()},
        "slowest_20": [
            {
                "name": row["name"],
                "cold_presented_frame_ms": row.get("cold", {}).get("presented_frame_ms"),
                "cold_process_elapsed_ms": nested(row.get("cold", {}), "timing", "process_elapsed_ms"),
                "advance_and_render_ms": nested(row.get("cold", {}), "timing", "advance_and_render_ms"),
                "cpu_raster_replay_ms": nested(row.get("cold", {}), "timing", "cpu_raster_replay_ms"),
                "style_update_ms": nested(row.get("cold", {}), "probe_timing", "style_update_ms"),
                "layout_lifecycle_ms": nested(row.get("cold", {}), "probe_timing", "layout_lifecycle_ms"),
                "prepaint_paint_lifecycle_ms": nested(row.get("cold", {}), "probe_timing", "prepaint_paint_lifecycle_ms"),
                "paint_artifact_extraction_ms": nested(row.get("cold", {}), "probe_timing", "paint_artifact_extraction_ms"),
                "retained_command_count": row.get("cold", {}).get("retained_command_count"),
                "raw_chunk_count": row.get("cold", {}).get("raw_chunk_count"),
                "correctness": row.get("correctness", {}).get("diff_classification"),
            }
            for row in sorted(
                cold_rows,
                key=lambda item: float(item.get("cold", {}).get("presented_frame_ms") or -1),
                reverse=True,
            )[:20]
        ],
    }


def write_csv(path: Path, rows: list[dict[str, Any]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "name",
        "cold_exit",
        "cold_presented_frame_ms",
        "process_elapsed_ms",
        "advance_and_render_ms",
        "cpu_raster_replay_ms",
        "style_update_ms",
        "layout_lifecycle_ms",
        "prepaint_paint_lifecycle_ms",
        "paint_artifact_generation_ms",
        "paint_artifact_extraction_ms",
        "retained_command_count",
        "raw_chunk_count",
        "document_max_scroll_y",
        "correctness_exit",
        "correctness_classification",
        "playwright_classification",
    ]
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields)
        writer.writeheader()
        for row in rows:
            cold = row.get("cold", {})
            writer.writerow(
                {
                    "name": row.get("name"),
                    "cold_exit": cold.get("exit_code"),
                    "cold_presented_frame_ms": cold.get("presented_frame_ms"),
                    "process_elapsed_ms": nested(cold, "timing", "process_elapsed_ms"),
                    "advance_and_render_ms": nested(cold, "timing", "advance_and_render_ms"),
                    "cpu_raster_replay_ms": nested(cold, "timing", "cpu_raster_replay_ms"),
                    "style_update_ms": nested(cold, "probe_timing", "style_update_ms"),
                    "layout_lifecycle_ms": nested(cold, "probe_timing", "layout_lifecycle_ms"),
                    "prepaint_paint_lifecycle_ms": nested(cold, "probe_timing", "prepaint_paint_lifecycle_ms"),
                    "paint_artifact_generation_ms": nested(cold, "probe_timing", "paint_artifact_generation_ms"),
                    "paint_artifact_extraction_ms": nested(cold, "probe_timing", "paint_artifact_extraction_ms"),
                    "retained_command_count": cold.get("retained_command_count"),
                    "raw_chunk_count": cold.get("raw_chunk_count"),
                    "document_max_scroll_y": row.get("document_max_scroll_y"),
                    "correctness_exit": row.get("correctness", {}).get("exit_code"),
                    "correctness_classification": row.get("correctness", {}).get("diff_classification"),
                    "playwright_classification": row.get("playwright", {}).get("diff_classification"),
                }
            )


def write_partial_report(
    out_dir: Path,
    generated_at: str,
    benchmark: Path,
    build_config_name: str | None,
    completed_rows: list[dict[str, Any]],
    current_row: dict[str, Any] | None = None,
    run_selection: dict[str, Any] | None = None,
) -> None:
    pages = list(completed_rows)
    if current_row is not None:
        pages.append(current_row)
    write_json(
        out_dir / "standalone_perf_results.partial.json",
        {
            "schema_version": 1,
            "generated_at": generated_at,
            "repo": rel(ROOT),
            "benchmark": rel(benchmark),
            "build_config": build_config_metadata(benchmark, build_config_name),
            "run_selection": run_selection or {},
            "partial": True,
            "pages": pages,
        },
    )


def select_html_files(
    html_files: list[Path],
    *,
    start_index: int,
    limit: int | None,
    shard_index: int | None,
    shard_count: int | None,
) -> tuple[list[Path], dict[str, Any]]:
    total_count = len(html_files)
    if start_index < 1:
        raise ValueError("--start-index is 1-based and must be at least 1")
    if (shard_index is None) != (shard_count is None):
        raise ValueError("--shard-index and --shard-count must be provided together")
    if shard_count is not None:
        if shard_count < 1:
            raise ValueError("--shard-count must be at least 1")
        if shard_index is None or shard_index < 0 or shard_index >= shard_count:
            raise ValueError("--shard-index must be in [0, shard-count)")
        indexed = [
            (index, path)
            for index, path in enumerate(html_files, start=1)
            if (index - 1) % shard_count == shard_index
        ]
    else:
        indexed = list(enumerate(html_files, start=1))
    indexed = [(index, path) for index, path in indexed if index >= start_index]
    if limit is not None:
        indexed = indexed[:limit]
    selected = [path for _, path in indexed]
    selection = {
        "total_discovered_count": total_count,
        "selected_count": len(selected),
        "start_index": start_index,
        "limit": limit,
        "shard_index": shard_index,
        "shard_count": shard_count,
        "selected_global_indices": [index for index, _ in indexed],
    }
    return selected, selection


def merge_reports(inputs: list[Path], out_dir: Path, *, no_docs: bool) -> int:
    merged_pages: dict[str, dict[str, Any]] = {}
    reports: list[dict[str, Any]] = []
    for path in inputs:
        report = read_json(path)
        if not report or "pages" not in report:
            raise ValueError(f"missing pages in {path}")
        reports.append(report)
        for row in report["pages"]:
            key = str(row.get("html") or row.get("name"))
            if key in merged_pages:
                raise ValueError(f"duplicate page in merge inputs: {key}")
            merged_pages[key] = row
    first = reports[0]
    pages = [
        merged_pages[key]
        for key in sorted(merged_pages.keys(), key=lambda value: value.lower())
    ]
    generated = time.strftime("%Y-%m-%dT%H:%M:%S%z")
    report = {
        "schema_version": 1,
        "generated_at": generated,
        "repo": first.get("repo", rel(ROOT)),
        "benchmark": first.get("benchmark", ""),
        "build_config": first.get("build_config", {}),
        "paint_audit_root": first.get("paint_audit_root", ""),
        "viewport": first.get("viewport", ""),
        "device_scale_factor": first.get("device_scale_factor", 1),
        "resource_root_policy": first.get("resource_root_policy", ""),
        "measurement_caveats": first.get("measurement_caveats", []),
        "merged_from": [rel(path) for path in inputs],
        "summary": summarize(pages),
        "pages": pages,
        "playwright_status": first.get("playwright_status", "not_requested"),
    }
    out_dir.mkdir(parents=True, exist_ok=True)
    write_json(out_dir / "standalone_perf_results.json", report)
    write_csv(out_dir / "standalone_perf_results.csv", pages)
    if not no_docs:
        write_baseline_doc(ROOT / "docs" / "PERF_BASELINE.md", report)
    summary = report["summary"]
    print(f"Wrote {rel(out_dir / 'standalone_perf_results.json')}")
    print(
        f"Pages: {summary['page_count']} "
        f"failures: {summary['failure_count']} "
        f"correctness_failures: {summary['correctness_failure_count']} "
        f"timeouts: {summary.get('timeout_count', 0)} "
        f"recovered_timeouts: {summary.get('recovered_timeout_count', 0)}"
    )
    return (
        0
        if summary["failure_count"] == 0
        and summary["correctness_failure_count"] == 0
        and summary.get("timeout_count", 0) == 0
        else 1
    )


def markdown_table(rows: list[dict[str, Any]]) -> str:
    lines = [
        "| Page | Cold presented ms | Advance ms | Raster ms | Style ms | Layout ms | Prepaint/Paint ms | Extraction ms | Commands | Correctness |",
        "| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |",
    ]
    for row in rows:
        def fmt(value: Any) -> str:
            number = as_float(value)
            return "" if number is None else f"{number:.2f}"

        lines.append(
            "| "
            + " | ".join(
                [
                    str(row.get("name", "")),
                    fmt(row.get("cold_presented_frame_ms")),
                    fmt(row.get("advance_and_render_ms")),
                    fmt(row.get("cpu_raster_replay_ms")),
                    fmt(row.get("style_update_ms")),
                    fmt(row.get("layout_lifecycle_ms")),
                    fmt(row.get("prepaint_paint_lifecycle_ms")),
                    fmt(row.get("paint_artifact_extraction_ms")),
                    str(row.get("retained_command_count", "")),
                    str(row.get("correctness", "")),
                ]
            )
            + " |"
        )
    return "\n".join(lines)


def failure_markdown_table(rows: list[dict[str, Any]]) -> str:
    failures = [
        row
        for row in rows
        if row.get("cold", {}).get("exit_code") != 0
        or row.get("correctness", {}).get("exit_code") != 0
        or row.get("correctness", {}).get("diff_classification")
        == "structural_layout_or_paint"
    ]
    if not failures:
        return "No cold render or retained-vs-oracle correctness failures were recorded."
    lines = [
        "| Page | Cold exit | Correctness exit | Classification | Reason | Log |",
        "| --- | ---: | ---: | --- | --- | --- |",
    ]
    for row in failures:
        correctness = row.get("correctness", {})
        lines.append(
            "| "
            + " | ".join(
                [
                    str(row.get("name", "")),
                    str(row.get("cold", {}).get("exit_code", "")),
                    str(correctness.get("exit_code", "")),
                    str(correctness.get("diff_classification", "")),
                    str(row.get("cold", {}).get("reason", "") or correctness.get("reason", "")),
                    str(row.get("cold", {}).get("log", "")),
                ]
            )
            + " |"
        )
    return "\n".join(lines)


def playwright_markdown_table(rows: list[dict[str, Any]]) -> str:
    compared = [row for row in rows if isinstance(row.get("playwright"), dict)]
    if not compared:
        return "No Playwright comparisons were recorded for this run."
    lines = [
        "| Page | Playwright classification | Compare exit |",
        "| --- | --- | ---: |",
    ]
    for row in compared:
        playwright = row.get("playwright", {})
        lines.append(
            f"| {row.get('name', '')} | "
            f"{playwright.get('diff_classification', '')} | "
            f"{playwright.get('exit_code', '')} |"
        )
    return "\n".join(lines)


def write_baseline_doc(path: Path, report: dict[str, Any]) -> None:
    summary = report["summary"]
    generated = report["generated_at"]
    rows = report["pages"]
    lines = [
        "# Standalone Renderer Performance Baseline",
        "",
        f"Generated: `{generated}`",
        "",
        "This file is generated by `tools/perf/run_standalone_perf_suite.py`.",
        "The first-frame timings come from `blink_standalone_render_benchmark_skia` using real Blink + Skia CPU at `1280x720` and device scale 1.",
        "",
        "The suite passes `--min-non-white 0` because the fixture corpus includes intentional all-white, transparent, missing-resource, and unsupported-resource pages. Visual correctness is gated by retained-vs-Skia-oracle comparison instead of a non-white smoke threshold.",
        "",
        "Important caveat: current warm incremental benchmark timings include previous-frame setup in the same process, so warm no-change/scroll/toggle rows are recorded for result correctness and rough cost only. A future benchmark harness should isolate per-frame warm timings in one live renderer session.",
        "",
        "## Build Configuration",
        "",
        f"- Name: `{report.get('build_config', {}).get('name', '')}`",
        f"- Benchmark: `{report.get('build_config', {}).get('benchmark', report.get('benchmark', ''))}`",
        f"- Build directory: `{report.get('build_config', {}).get('build_dir', '')}`",
        f"- CMake build type: `{report.get('build_config', {}).get('cmake_build_type', '')}`",
        f"- `BLINK_STANDALONE_PERF_BUILD`: `{report.get('build_config', {}).get('blink_standalone_perf_build', '')}`",
        f"- Defines policy: {report.get('build_config', {}).get('defines_policy', '')}",
        "",
        "## Summary",
        "",
        f"- Pages enumerated: `{summary['page_count']}`",
        f"- Cold render successes: `{summary['cold_success_count']}`",
        f"- Cold render failures: `{summary['failure_count']}`",
        f"- Timed-out child commands: `{summary.get('timeout_count', 0)}`",
        f"- Recovered child timeouts: `{summary.get('recovered_timeout_count', 0)}`",
        f"- Real Blink PaintArtifact successes: `{summary['real_blink_paint_count']}`",
        f"- Correctness failures against Skia PaintRecord oracle: `{summary['correctness_failure_count']}`",
        "",
        "## Aggregate Timings",
        "",
        "| Metric | Count | p50 ms | p95 ms | max ms |",
        "| --- | ---: | ---: | ---: | ---: |",
    ]
    for key, value in summary["stats"].items():
        p50 = "" if value["p50_ms"] is None else f"{value['p50_ms']:.2f}"
        p95 = "" if value["p95_ms"] is None else f"{value['p95_ms']:.2f}"
        max_value = "" if value["max_ms"] is None else f"{value['max_ms']:.2f}"
        lines.append(
            f"| `{key}` | {value['count']} | {p50} | {p95} | {max_value} |"
        )
    lines.extend(["", "## Slowest 20 Cold Presented Frames", "", markdown_table(summary["slowest_20"]), ""])
    lines.extend(
        [
            "## Correctness Failures And Gaps",
            "",
            failure_markdown_table(rows),
            "",
            "The retained-vs-oracle gate compares benchmark output against the local Skia PaintRecord oracle when the cold render succeeds. Pages that fail cold rendering are listed as correctness gaps because no oracle comparison can be made.",
            "",
            "## Playwright Spot Checks",
            "",
            f"Playwright status: `{report.get('playwright_status', 'available_or_recorded')}`",
            "",
            playwright_markdown_table(rows),
            "",
        ]
    )
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines), encoding="utf-8")


def make_row(
    benchmark: Path,
    html_path: Path,
    resource_root: Path,
    out_dir: Path,
    viewport: str,
    timeout: int,
    correctness_timeout: int,
    retries: int,
    *,
    run_warm_modes: bool,
    extra_benchmark_args: list[str] | None = None,
    on_update: Callable[[dict[str, Any]], None] | None = None,
) -> dict[str, Any]:
    name = html_path.stem
    case_dir = out_dir / "pages" / name
    case_dir.mkdir(parents=True, exist_ok=True)
    row: dict[str, Any] = {
        "name": name,
        "html": rel(html_path),
        "resource_root": rel(resource_root),
        "status": "started",
    }
    if on_update:
        on_update(row)
    cold = run_benchmark_case(
        benchmark,
        html_path,
        resource_root,
        case_dir,
        "cold",
        viewport,
        timeout,
        retries,
        extra_args=extra_benchmark_args,
        oracle=True,
    )
    row["cold"] = cold
    row["status"] = "cold_complete"
    if on_update:
        on_update(row)
    row["document_max_scroll_y"] = document_max_scroll_y(cold["metrics"])
    if cold["exit_code"] == 0:
        correctness = compare_images(
            case_dir / "cold.bmp",
            case_dir / "cold-oracle.bmp",
            case_dir / "correctness-retained-vs-oracle.json",
            case_dir / "correctness-retained-vs-oracle",
            correctness_timeout,
        )
    else:
        reason = cold.get("reason") or "cold render failed"
        correctness = {"exit_code": cold["exit_code"], "skipped": True, "reason": reason}
    row["correctness"] = correctness
    row["status"] = "correctness_complete" if cold["exit_code"] == 0 else "failed"
    if on_update:
        on_update(row)

    if cold["exit_code"] != 0:
        return row

    if run_warm_modes:
        no_change = run_benchmark_case(
            benchmark,
            html_path,
            resource_root,
            case_dir,
            "warm-no-change",
            viewport,
            timeout,
            retries,
            extra_args=[*(extra_benchmark_args or []), "--incremental"],
        )
        no_change["measurement_caveat"] = (
            "current benchmark invocation includes previous-frame render before the measured identical incremental result"
        )
        row["warm_no_change"] = no_change
        row["status"] = "warm_no_change_complete"
        if on_update:
            on_update(row)

        max_scroll_y = row["document_max_scroll_y"]
        if max_scroll_y > 0:
            scroll_y = str(int(min(120.0, max_scroll_y)))
            scroll = run_benchmark_case(
                benchmark,
                html_path,
                resource_root,
                case_dir,
                "warm-scroll",
                viewport,
                timeout,
                retries,
                extra_args=[
                    *(extra_benchmark_args or []),
                    "--incremental",
                    "--previous-scroll-y",
                    "0",
                    "--scroll-y",
                    scroll_y,
                ],
            )
            scroll["requested_scroll_y"] = float(scroll_y)
            scroll["measurement_caveat"] = (
                "current benchmark invocation includes previous-frame render before the measured scroll incremental result"
            )
            row["warm_scroll"] = scroll
        else:
            row["warm_scroll"] = {"skipped": True, "reason": "document not vertically scrollable"}
        row["status"] = "warm_scroll_complete"
        if on_update:
            on_update(row)

        toggle = infer_attribute_toggle(html_path)
        if toggle:
            element_id, attr_name, previous_value, current_value = toggle
            attr = run_benchmark_case(
                benchmark,
                html_path,
                resource_root,
                case_dir,
                "warm-attr-toggle",
                viewport,
                timeout,
                retries,
                extra_args=[
                    *(extra_benchmark_args or []),
                    "--incremental",
                    "--previous-attr",
                    f"{element_id}:{attr_name}={previous_value}",
                    "--attr",
                    f"{element_id}:{attr_name}={current_value}",
                ],
            )
            attr["toggle"] = {
                "element_id": element_id,
                "attribute": attr_name,
                "previous": previous_value,
                "current": current_value,
            }
            attr["measurement_caveat"] = (
                "current benchmark invocation includes previous-frame render before the measured attribute incremental result"
            )
            row["warm_attr_toggle"] = attr
        else:
            row["warm_attr_toggle"] = {"skipped": True, "reason": "no simple data-* attribute toggle inferred"}
        row["status"] = "complete"
        if on_update:
            on_update(row)
    else:
        row["status"] = "complete"
        if on_update:
            on_update(row)
    return row


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--root", type=Path, default=PAINT_AUDIT_ROOT)
    parser.add_argument("--out-dir", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--viewport", default="1280x720")
    parser.add_argument("--timeout", type=int, default=120)
    parser.add_argument("--correctness-timeout", type=int, default=60)
    parser.add_argument("--retries", type=int, default=0, help="retry a benchmark child this many times after timeout")
    parser.add_argument("--benchmark-arg", action="append", default=[], help="extra argument passed through to each benchmark child")
    parser.add_argument("--filter", action="append", default=[], help="fnmatch pattern for page stem or relative path; default is all")
    parser.add_argument("--start-index", type=int, default=1, help="1-based global page index to start from after filtering")
    parser.add_argument("--limit", type=int, help="developer iteration limit; omitted runs the full enumeration")
    parser.add_argument("--shard-index", type=int, help="0-based shard index after filtering")
    parser.add_argument("--shard-count", type=int, help="number of deterministic modulo shards after filtering")
    parser.add_argument("--merge-json", type=Path, action="append", default=[], help="merge one or more standalone_perf_results.json files and exit")
    parser.add_argument("--skip-warm-modes", action="store_true")
    parser.add_argument("--playwright-top", type=int, default=10, help="compare the N slowest cold pages against Playwright when available")
    parser.add_argument("--playwright-all", action="store_true", help="compare every successful page against Playwright")
    parser.add_argument("--build-config-name", help="label recorded in result JSON/docs, e.g. checked-current or x64-Perf")
    parser.add_argument("--no-docs", action="store_true")
    args = parser.parse_args()
    if args.retries < 0:
        print("--retries must be non-negative", file=sys.stderr)
        return 2

    if args.merge_json:
        return merge_reports(args.merge_json, args.out_dir.resolve(), no_docs=args.no_docs)

    html_root = args.root.resolve()
    benchmark = args.benchmark.resolve()
    out_dir = args.out_dir.resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    html_files = discover_html_files(html_root, args.filter)
    try:
        html_files, run_selection = select_html_files(
            html_files,
            start_index=args.start_index,
            limit=args.limit,
            shard_index=args.shard_index,
            shard_count=args.shard_count,
        )
    except ValueError as exc:
        print(str(exc), file=sys.stderr)
        return 2
    if not html_files:
        print("No HTML files matched.", file=sys.stderr)
        return 2

    rows: list[dict[str, Any]] = []
    started = time.strftime("%Y-%m-%dT%H:%M:%S%z")
    for index, html_path in enumerate(html_files, start=1):
        print(f"[{index}/{len(html_files)}] {html_path.relative_to(html_root).as_posix()}", flush=True)
        row = make_row(
            benchmark,
            html_path,
            html_root,
            out_dir,
            args.viewport,
            args.timeout,
            args.correctness_timeout,
            args.retries,
            run_warm_modes=not args.skip_warm_modes,
            extra_benchmark_args=args.benchmark_arg,
            on_update=lambda current_row: write_partial_report(
                out_dir,
                started,
                benchmark,
                args.build_config_name,
                rows,
                current_row,
                run_selection=run_selection,
            ),
        )
        rows.append(row)
        write_partial_report(
            out_dir,
            started,
            benchmark,
            args.build_config_name,
            rows,
            run_selection=run_selection,
        )

    summary = summarize(rows)
    report: dict[str, Any] = {
        "schema_version": 1,
        "generated_at": started,
        "repo": rel(ROOT),
        "benchmark": rel(benchmark),
        "build_config": build_config_metadata(benchmark, args.build_config_name),
        "run_selection": run_selection,
        "paint_audit_root": rel(html_root),
        "viewport": args.viewport,
        "device_scale_factor": 1,
        "resource_root_policy": "paint_audit root is passed as --resource-root for every page",
        "measurement_caveats": [
            "Benchmark process startup is measured as subprocess wall time minus in-process process_elapsed_ms when available.",
            "The suite passes --min-non-white 0 because paint_audit includes intentional all-white/transparent/broken-resource fixtures; retained-vs-oracle comparison is the correctness gate.",
            "Current warm incremental timings include previous-frame setup in the same benchmark invocation; warm results are still recorded to expose damage/no-change behavior.",
            "Benchmark presentation is BMP output, not SDL/GPU upload/present.",
        ],
        "summary": summary,
        "pages": rows,
    }

    play_count = len(rows) if args.playwright_all else max(0, args.playwright_top)
    play_available = play_count > 0 and playwright_available()
    if play_available:
        candidates = sorted(
            [row for row in rows if row.get("cold", {}).get("exit_code") == 0],
            key=lambda row: float(row.get("cold", {}).get("presented_frame_ms") or -1),
            reverse=True,
        )
        if not args.playwright_all:
            candidates = candidates[:play_count]
        for row in candidates:
            html_path = ROOT / row["html"]
            case_dir = out_dir / "pages" / row["name"]
            out_png = case_dir / "playwright.png"
            out_json = case_dir / "playwright.json"
            result = run_playwright_capture(html_path, out_png, out_json, args.viewport, args.timeout)
            row["playwright_capture"] = {
                "exit_code": result.code,
                "timed_out": result.timed_out,
                "timeout_s": result.timeout_s,
                "wall_ms": result.wall_ms,
                "image": rel(out_png) if out_png.exists() else "",
                "json": rel(out_json) if out_json.exists() else "",
            }
            if result.timed_out:
                row["playwright_capture"]["reason"] = (
                    f"playwright capture exceeded {args.timeout}s timeout"
                )
            if result.code == 0:
                row["playwright"] = compare_images(
                    case_dir / "cold.bmp",
                    out_png,
                    case_dir / "correctness-retained-vs-playwright.json",
                    case_dir / "correctness-retained-vs-playwright",
                    args.correctness_timeout,
                )
            write_partial_report(
                out_dir,
                started,
                benchmark,
                args.build_config_name,
                rows,
                run_selection=run_selection,
            )
    elif play_count > 0:
        report["playwright_status"] = "unavailable"
    else:
        report["playwright_status"] = "not_requested"

    # Recompute after optional Playwright rows are added.
    report["summary"] = summarize(rows)
    write_json(out_dir / "standalone_perf_results.json", report)
    write_csv(out_dir / "standalone_perf_results.csv", rows)
    if not args.no_docs:
        write_baseline_doc(ROOT / "docs" / "PERF_BASELINE.md", report)

    print(f"Wrote {rel(out_dir / 'standalone_perf_results.json')}")
    final_summary = report["summary"]
    print(
        f"Pages: {final_summary['page_count']} "
        f"failures: {final_summary['failure_count']} "
        f"correctness_failures: {final_summary['correctness_failure_count']} "
        f"timeouts: {final_summary.get('timeout_count', 0)} "
        f"recovered_timeouts: {final_summary.get('recovered_timeout_count', 0)}"
    )
    return (
        0
        if final_summary["failure_count"] == 0
        and final_summary["correctness_failure_count"] == 0
        and final_summary.get("timeout_count", 0) == 0
        else 1
    )


if __name__ == "__main__":
    raise SystemExit(main())
