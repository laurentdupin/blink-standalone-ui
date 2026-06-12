#!/usr/bin/env python3
"""Deterministic standalone-vs-Playwright animation frame comparison runner."""

from __future__ import annotations

import argparse
import html
import json
import math
import statistics
import sys
import time
from collections import Counter
from pathlib import Path
from typing import Any

from run_benchmark_comparison import (
    COMPARE_SCRIPT,
    DEFAULT_BENCHMARK,
    DEFAULT_CASES,
    PLAYWRIGHT_SCRIPT,
    ROOT,
    add_element_scroll_args,
    add_scroll_args,
    fallback_scalar_from_text,
    load_manifest,
    metric_value,
    pillow_available,
    playwright_available,
    read_json,
    read_text,
    resolve_case,
    run,
    unsupported_css_diagnostics,
)


DEFAULT_HCSR_ROOT = Path(r"C:\Repos\UniversalGameEngine\HCSR")


def format_ms(value: float) -> str:
    if math.isclose(value, round(value), abs_tol=0.0001):
        return str(int(round(value)))
    return f"{value:.3f}".rstrip("0").rstrip(".")


def time_token(value: float) -> str:
    return format_ms(value).replace(".", "_")


def percentile(values: list[float], percent: float) -> float | None:
    if not values:
        return None
    ordered = sorted(values)
    if len(ordered) == 1:
        return ordered[0]
    rank = (len(ordered) - 1) * (percent / 100.0)
    low = math.floor(rank)
    high = math.ceil(rank)
    if low == high:
        return ordered[low]
    return ordered[low] + (ordered[high] - ordered[low]) * (rank - low)


def numeric(value: Any) -> float | None:
    if value is None or value == "":
        return None
    try:
        return float(value)
    except (TypeError, ValueError):
        return None


def html_escape(value: Any) -> str:
    return html.escape(str(value))


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def image_link(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<span class="missing">missing</span>'
    relative = html.escape(rel(path, out_dir))
    return f'<a href="{relative}"><img src="{relative}" alt="{html.escape(label)}"></a>'


def frame_times(start_ms: float, step_ms: float, frames: int) -> list[float]:
    return [start_ms + (index * step_ms) for index in range(frames)]


def build_frame_commands(
    *,
    case: dict[str, Any],
    benchmark: Path,
    html_path: Path,
    resource_root: Path,
    viewport: str,
    time_ms: float,
    retained: Path,
    oracle: Path,
    metrics: Path,
    audit: Path,
    setup: Path,
    crash: Path,
    playwright_png: Path,
) -> tuple[list[str], list[str]]:
    time_value = format_ms(time_ms)
    bench_cmd = [
        str(benchmark),
        "--html-file",
        str(html_path),
        "--resource-root",
        str(resource_root),
        "--viewport",
        viewport,
        "--out",
        str(retained),
        "--json",
        str(metrics),
        "--dump-paint-artifact",
        str(audit),
        "--dump-page-setup",
        str(setup),
        "--paint-oracle=skia-paint-record",
        "--oracle-out",
        str(oracle),
        "--crash-dump",
        str(crash),
        "--debug-command-coverage",
        "--strict-text-blob-typefaces",
        "--time-ms",
        time_value,
    ]
    for attr in case.get("attrs", []):
        bench_cmd.extend(["--attr", attr])
    add_scroll_args(bench_cmd, case.get("scroll"))
    add_element_scroll_args(bench_cmd, case.get("element_scroll"))

    pw_cmd = [
        "node",
        str(PLAYWRIGHT_SCRIPT),
        "--html-file",
        str(html_path),
        "--out",
        str(playwright_png),
        "--viewport",
        viewport,
        "--time-ms",
        time_value,
    ]
    for attr in case.get("attrs", []):
        pw_cmd.extend(["--attr", attr])
    add_scroll_args(pw_cmd, case.get("scroll"))
    add_element_scroll_args(pw_cmd, case.get("element_scroll"))
    return bench_cmd, pw_cmd


def compare_images(
    *,
    standalone: Path,
    playwright: Path,
    out_json: Path,
    out_dir: Path,
    log_path: Path,
    timeout: int,
) -> tuple[int, float, str]:
    return run(
        [
            sys.executable,
            str(COMPARE_SCRIPT),
            "--standalone",
            str(standalone),
            "--playwright",
            str(playwright),
            "--out-json",
            str(out_json),
            "--out-dir",
            str(out_dir),
            "--compare-background",
            "auto-corners",
        ],
        log_path,
        timeout,
    )


def summarize_case(case_name: str, frames: list[dict[str, Any]]) -> dict[str, Any]:
    classifications = Counter(
        str(frame.get("diff_classification") or "unclassified") for frame in frames
    )
    exact_values = [
        int(value)
        for value in (frame.get("retained_vs_playwright_exact") for frame in frames)
        if value not in ("", None)
    ]
    advance_times = [
        value
        for value in (numeric(frame.get("standalone_advance_and_render_ms")) for frame in frames)
        if value is not None
    ]
    benchmark_elapsed = [
        value
        for value in (numeric(frame.get("benchmark_elapsed_seconds")) for frame in frames)
        if value is not None
    ]
    playwright_elapsed = [
        value
        for value in (numeric(frame.get("playwright_elapsed_seconds")) for frame in frames)
        if value is not None
    ]
    worst_frame = max(
        frames,
        key=lambda frame: int(frame.get("retained_vs_playwright_exact") or -1),
        default={},
    )
    return {
        "name": case_name,
        "frame_count": len(frames),
        "benchmark_success_count": sum(1 for frame in frames if frame.get("benchmark_exit") == 0),
        "playwright_success_count": sum(1 for frame in frames if frame.get("playwright_exit") == 0),
        "classification_counts": dict(sorted(classifications.items())),
        "worst_frame_index": worst_frame.get("frame_index", ""),
        "worst_frame_time_ms": worst_frame.get("time_ms", ""),
        "worst_frame_exact": worst_frame.get("retained_vs_playwright_exact", ""),
        "worst_frame_classification": worst_frame.get("diff_classification", ""),
        "retained_vs_playwright_exact": {
            "min": min(exact_values) if exact_values else "",
            "avg": statistics.fmean(exact_values) if exact_values else "",
            "p95": percentile([float(value) for value in exact_values], 95),
            "max": max(exact_values) if exact_values else "",
        },
        "standalone_advance_and_render_ms": {
            "min": min(advance_times) if advance_times else "",
            "avg": statistics.fmean(advance_times) if advance_times else "",
            "p95": percentile(advance_times, 95),
            "max": max(advance_times) if advance_times else "",
        },
        "benchmark_elapsed_seconds": {
            "avg": statistics.fmean(benchmark_elapsed) if benchmark_elapsed else "",
            "max": max(benchmark_elapsed) if benchmark_elapsed else "",
        },
        "playwright_elapsed_seconds": {
            "avg": statistics.fmean(playwright_elapsed) if playwright_elapsed else "",
            "max": max(playwright_elapsed) if playwright_elapsed else "",
        },
        "frames": frames,
    }


def write_html_summary(out_dir: Path, report: dict[str, Any]) -> Path:
    generated = time.strftime("%Y-%m-%d %H:%M:%S")
    case_rows = []
    frame_rows = []
    for case_summary in report["cases"]:
        case_name = case_summary["name"]
        worst_frame = case_summary.get("worst_frame_index", "")
        worst_dir = (
            out_dir
            / case_name
            / f"frame_{int(worst_frame):04d}_t{time_token(float(case_summary.get('worst_frame_time_ms') or 0))}"
            if worst_frame != ""
            else out_dir / case_name
        )
        exact = case_summary.get("retained_vs_playwright_exact", {})
        advance = case_summary.get("standalone_advance_and_render_ms", {})
        classes = ", ".join(
            f"{name}: {count}"
            for name, count in case_summary.get("classification_counts", {}).items()
        )
        case_rows.append(
            "<tr>"
            f"<td>{html_escape(case_name)}</td>"
            f"<td>{html_escape(case_summary['frame_count'])}</td>"
            f"<td>{html_escape(case_summary['benchmark_success_count'])}</td>"
            f"<td>{html_escape(case_summary['playwright_success_count'])}</td>"
            f"<td>{html_escape(classes)}</td>"
            f"<td>{html_escape(case_summary.get('worst_frame_index', ''))}</td>"
            f"<td>{html_escape(case_summary.get('worst_frame_time_ms', ''))}</td>"
            f"<td>{html_escape(case_summary.get('worst_frame_exact', ''))}</td>"
            f"<td>{html_escape(case_summary.get('worst_frame_classification', ''))}</td>"
            f"<td>{html_escape(format_number(exact.get('avg')))}</td>"
            f"<td>{html_escape(format_number(exact.get('p95')))}</td>"
            f"<td>{html_escape(format_number(advance.get('avg')))}</td>"
            f"<td>{html_escape(format_number(advance.get('p95')))}</td>"
            f"<td>{image_link(worst_dir / 'retained.bmp', out_dir, 'worst retained')}</td>"
            f"<td>{image_link(worst_dir / 'playwright.png', out_dir, 'worst playwright')}</td>"
            "</tr>"
        )
        for frame in case_summary["frames"]:
            frame_dir = out_dir / frame["artifact_dir"]
            frame_rows.append(
                "<tr>"
                f"<td>{html_escape(case_name)}</td>"
                f"<td>{html_escape(frame['frame_index'])}</td>"
                f"<td>{html_escape(frame['time_ms'])}</td>"
                f"<td>{html_escape(frame.get('benchmark_exit', ''))}</td>"
                f"<td>{html_escape(frame.get('playwright_exit', ''))}</td>"
                f"<td>{html_escape(frame.get('retained_vs_oracle_exact', ''))}</td>"
                f"<td>{html_escape(frame.get('retained_vs_playwright_exact', ''))}</td>"
                f"<td>{html_escape(frame.get('diff_classification', ''))}</td>"
                f"<td>{html_escape(frame.get('standalone_advance_and_render_ms', ''))}</td>"
                f"<td>{html_escape(frame.get('benchmark_elapsed_seconds', ''))}</td>"
                f"<td>{html_escape(frame.get('playwright_elapsed_seconds', ''))}</td>"
                f"<td>{image_link(frame_dir / 'retained.bmp', out_dir, 'retained')}</td>"
                f"<td>{image_link(frame_dir / 'playwright.png', out_dir, 'playwright')}</td>"
                f'<td><a href="{html.escape(rel(frame_dir, out_dir))}/">artifacts</a></td>'
                "</tr>"
            )
    class_counts = ", ".join(
        f"{html_escape(name)}: {html_escape(count)}"
        for name, count in report.get("classification_counts", {}).items()
    )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>Dynamic Animation Comparison</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  h1 {{ margin: 0 0 4px; font-size: 24px; }}
  h2 {{ margin-top: 28px; }}
  .meta {{ color: #59636e; margin: 0 0 16px; }}
  table {{ border-collapse: collapse; width: 100%; background: white; margin-bottom: 24px; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; vertical-align: top; font-size: 12px; }}
  th {{ position: sticky; top: 0; background: #eef2f6; z-index: 1; }}
  img {{ width: 160px; max-height: 100px; object-fit: contain; background: white; border: 1px solid #d8dee4; }}
  .missing {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>Dynamic Animation Comparison</h1>
<p class="meta">Generated {html_escape(generated)} for case set <strong>{html_escape(report['case_set'])}</strong>. Frames: {html_escape(report['frame_count'])}, start: {html_escape(report['start_ms'])}ms, step: {html_escape(report['step_ms'])}ms, viewport override: {html_escape(report.get('viewport_override') or 'manifest')}.</p>
<p class="meta">Classification counts: {class_counts or 'none'}</p>
<h2>Case Summary</h2>
<table>
  <thead><tr><th>Case</th><th>Frames</th><th>Bench OK</th><th>PW OK</th><th>Classes</th><th>Worst frame</th><th>Worst time</th><th>Worst exact</th><th>Worst class</th><th>Exact avg</th><th>Exact p95</th><th>Render avg ms</th><th>Render p95 ms</th><th>Worst retained</th><th>Worst Playwright</th></tr></thead>
  <tbody>{''.join(case_rows)}</tbody>
</table>
<h2>Frames</h2>
<table>
  <thead><tr><th>Case</th><th>Frame</th><th>Time ms</th><th>Bench</th><th>PW</th><th>R/O exact</th><th>R/P exact</th><th>Class</th><th>Render ms</th><th>Bench s</th><th>PW s</th><th>Retained</th><th>Playwright</th><th>Artifacts</th></tr></thead>
  <tbody>{''.join(frame_rows)}</tbody>
</table>
"""
    index = out_dir / "index.html"
    index.write_text(page, encoding="utf-8")
    return index


def format_number(value: Any) -> str:
    if value in ("", None):
        return ""
    try:
        return f"{float(value):.2f}"
    except (TypeError, ValueError):
        return str(value)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Compare standalone and Playwright animation output across deterministic frame timestamps."
    )
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--cases-file", type=Path, default=DEFAULT_CASES)
    parser.add_argument("--case-set", default="dynamic-local")
    parser.add_argument("--out-dir", type=Path, default=ROOT / "build" / "dynamic-comparison" / "dynamic-local")
    parser.add_argument("--viewport", help="Override all manifest viewports, e.g. 1280x720.")
    parser.add_argument("--hcsr-root", type=Path, default=DEFAULT_HCSR_ROOT)
    parser.add_argument("--start-ms", type=float, default=0.0)
    parser.add_argument("--step-ms", type=float, default=1000.0 / 60.0)
    parser.add_argument("--frames", type=int, default=120)
    parser.add_argument("--timeout", type=int, default=90)
    parser.add_argument("--limit-cases", type=int)
    parser.add_argument("--limit-frames", type=int)
    args = parser.parse_args()

    if not args.benchmark.exists():
        raise SystemExit(f"Benchmark not found: {args.benchmark}")
    if args.frames <= 0:
        raise SystemExit("--frames must be positive")
    if args.step_ms <= 0:
        raise SystemExit("--step-ms must be positive")

    cases_by_name, sets = load_manifest(args.cases_file)
    selected_names = sets.get(args.case_set)
    if selected_names is None:
        raise SystemExit(f"Unknown case set '{args.case_set}' in {args.cases_file}")
    if args.limit_cases:
        selected_names = selected_names[: args.limit_cases]
    frames = frame_times(args.start_ms, args.step_ms, args.limit_frames or args.frames)

    args.out_dir.mkdir(parents=True, exist_ok=True)
    has_playwright, playwright_detail = playwright_available()
    has_pillow, pillow_detail = pillow_available()
    if not has_playwright:
        raise SystemExit(
            "Playwright unavailable. Install with `npm install --no-save playwright` "
            "then `npx playwright install chromium` from the repo root."
        )
    if not has_pillow:
        raise SystemExit("Pillow unavailable. Install with `python -m pip install pillow`.")

    case_summaries: list[dict[str, Any]] = []
    for case_index, case_name in enumerate(selected_names, 1):
        case = cases_by_name[case_name]
        html_path, resource_root = resolve_case(case, args.hcsr_root)
        viewport = args.viewport or case.get("viewport", "1280x720")
        print(f"[{case_index}/{len(selected_names)}] {case_name} ({len(frames)} frames)", flush=True)
        frame_rows: list[dict[str, Any]] = []
        for frame_index, time_ms in enumerate(frames):
            token = time_token(time_ms)
            frame_dir = args.out_dir / case_name / f"frame_{frame_index:04d}_t{token}"
            frame_dir.mkdir(parents=True, exist_ok=True)

            retained = frame_dir / "retained.bmp"
            oracle = frame_dir / "oracle.bmp"
            metrics = frame_dir / "metrics.json"
            audit = frame_dir / "audit.json"
            setup = frame_dir / "standalone-setup.json"
            crash = frame_dir / "frame.dmp"
            playwright_png = frame_dir / "playwright.png"

            bench_cmd, pw_cmd = build_frame_commands(
                case=case,
                benchmark=args.benchmark,
                html_path=html_path,
                resource_root=resource_root,
                viewport=viewport,
                time_ms=time_ms,
                retained=retained,
                oracle=oracle,
                metrics=metrics,
                audit=audit,
                setup=setup,
                crash=crash,
                playwright_png=playwright_png,
            )
            benchmark_exit, benchmark_elapsed, _ = run(
                bench_cmd, frame_dir / "benchmark.log", args.timeout
            )
            playwright_exit, playwright_elapsed, _ = run(
                pw_cmd, frame_dir / "playwright.log", args.timeout
            )

            retained_oracle_exit = ""
            if retained.exists() and oracle.exists():
                retained_oracle_exit, _, _ = compare_images(
                    standalone=retained,
                    playwright=oracle,
                    out_json=frame_dir / "retained-vs-oracle.json",
                    out_dir=frame_dir / "retained-vs-oracle-crops",
                    log_path=frame_dir / "retained-vs-oracle.log",
                    timeout=args.timeout,
                )
            retained_playwright_exit = ""
            if retained.exists() and playwright_png.exists():
                retained_playwright_exit, _, _ = compare_images(
                    standalone=retained,
                    playwright=playwright_png,
                    out_json=frame_dir / "retained-vs-playwright.json",
                    out_dir=frame_dir / "retained-vs-playwright-crops",
                    log_path=frame_dir / "retained-vs-playwright.log",
                    timeout=args.timeout,
                )

            metrics_json = read_json(metrics)
            metrics_text = read_text(metrics)
            unsupported_css_count, first_unsupported_css = unsupported_css_diagnostics(metrics_json)
            retained_oracle = read_json(frame_dir / "retained-vs-oracle.json")
            retained_playwright = read_json(frame_dir / "retained-vs-playwright.json")
            status = {
                "case": case_name,
                "frame_index": frame_index,
                "time_ms": format_ms(time_ms),
                "viewport": viewport,
                "fixture": str(html_path),
                "resource_root": str(resource_root),
                "benchmark_exit": benchmark_exit,
                "playwright_exit": playwright_exit,
                "retained_vs_oracle_exit": retained_oracle_exit,
                "retained_vs_playwright_exit": retained_playwright_exit,
                "benchmark_elapsed_seconds": benchmark_elapsed,
                "playwright_elapsed_seconds": playwright_elapsed,
                "missing_resource_count": metrics_json.get("missing_resource_count", "")
                or fallback_scalar_from_text(metrics_text, "missing_resource_count"),
                "diagnostic_count": metrics_json.get("diagnostic_count", ""),
                "unsupported_css_diagnostic_count": unsupported_css_count,
                "first_unsupported_css_diagnostic": first_unsupported_css,
                "standalone_advance_and_render_ms": metric_value(
                    metrics_json, "render_timing_diagnostics", "advance_and_render_ms"
                )
                or fallback_scalar_from_text(metrics_text, "advance_and_render_ms"),
                "retained_vs_oracle_exact": metric_value(
                    retained_oracle, "exact_pixel_difference_count"
                ),
                "retained_vs_playwright_exact": metric_value(
                    retained_playwright, "exact_pixel_difference_count"
                ),
                "diff_classification": metric_value(
                    retained_playwright, "diff_classification"
                ),
                "artifact_dir": rel(frame_dir, args.out_dir),
            }
            (frame_dir / "status.json").write_text(json.dumps(status, indent=2), encoding="utf-8")
            frame_rows.append(status)

        case_summaries.append(summarize_case(case_name, frame_rows))

    classification_counts = Counter()
    for case_summary in case_summaries:
        classification_counts.update(case_summary["classification_counts"])
    report = {
        "case_set": args.case_set,
        "case_count": len(selected_names),
        "frame_count": len(frames),
        "start_ms": format_ms(args.start_ms),
        "step_ms": format_ms(args.step_ms),
        "viewport_override": args.viewport or "",
        "classification_counts": dict(sorted(classification_counts.items())),
        "dependencies": {
            "playwright_available": has_playwright,
            "playwright_detail": playwright_detail,
            "pillow_available": has_pillow,
            "pillow_detail": pillow_detail,
        },
        "cases": case_summaries,
    }
    (args.out_dir / "summary.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
    index = write_html_summary(args.out_dir, report)
    print(f"Wrote dynamic comparison summary to {index}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
