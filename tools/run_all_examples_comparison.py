#!/usr/bin/env python3
"""Run standalone/oracle/Playwright comparisons for all paint-audit examples."""

from __future__ import annotations

import argparse
import html
import json
import subprocess
import sys
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
FIXTURE_DIR = ROOT / "upstream" / "chromium" / "standalone_renderer" / "testdata" / "paint_audit"
DEFAULT_BENCHMARK = ROOT / "build" / "cmake-live-image-png-ninja-vs" / "blink_standalone_render_benchmark_skia.exe"
COMPARE_SCRIPT = ROOT / "tools" / "content_aware_compare.py"


def run(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float]:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    started = time.time()
    try:
        completed = subprocess.run(
            cmd,
            cwd=ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=timeout,
        )
        output = completed.stdout
        code = completed.returncode
    except subprocess.TimeoutExpired as exc:
        output = (exc.stdout or "") if isinstance(exc.stdout, str) else ""
        output += f"\nTIMEOUT after {timeout}s\n"
        code = 124
    elapsed = time.time() - started
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={code} elapsed={elapsed:.2f}s\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return code, elapsed


def read_json(path: Path) -> dict:
    if not path.exists():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:  # pragma: no cover - diagnostic script.
        return {"_json_error": str(exc)}


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def image_cell(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<td class="missing">missing</td>'
    return (
        '<td>'
        f'<a href="{html.escape(rel(path, out_dir))}">'
        f'<img src="{html.escape(rel(path, out_dir))}" alt="{html.escape(label)}">'
        "</a>"
        "</td>"
    )


def metric_value(data: dict, *keys: str) -> str:
    current: object = data
    for key in keys:
        if not isinstance(current, dict) or key not in current:
            return ""
        current = current[key]
    if isinstance(current, float):
        return f"{current:.4f}"
    return str(current)


def fixture_name(fixture: Path, fixture_root: Path) -> str:
    try:
        relative = fixture.relative_to(fixture_root)
    except ValueError:
        relative = fixture.name
    if isinstance(relative, Path) and len(relative.parts) > 1:
        return "_".join(part for part in relative.with_suffix("").parts)
    return fixture.stem


def summarize_row(fixture: Path, fixture_root: Path, item_dir: Path, out_dir: Path) -> dict:
    name = fixture_name(fixture, fixture_root)
    metrics = read_json(item_dir / f"{name}-metrics.json")
    audit = read_json(item_dir / f"{name}-audit.json")
    retained_oracle = read_json(item_dir / f"{name}-retained-vs-oracle.json")
    oracle_pw = read_json(item_dir / f"{name}-oracle-vs-playwright.json")
    status = read_json(item_dir / f"{name}-status.json")
    return {
        "name": name,
        "fixture": str(fixture),
        "benchmark_exit": status.get("benchmark_exit", ""),
        "playwright_exit": status.get("playwright_exit", ""),
        "benchmark_elapsed_seconds": status.get("benchmark_elapsed_seconds", ""),
        "playwright_elapsed_seconds": status.get("playwright_elapsed_seconds", ""),
        "playwright_timing_mode": status.get("playwright_timing_mode", ""),
        "standalone_render_timing_mode": metric_value(metrics, "render_timing_diagnostics", "mode"),
        "standalone_advance_and_render_ms": metric_value(metrics, "render_timing_diagnostics", "advance_and_render_ms"),
        "standalone_cpu_raster_replay_ms": metric_value(metrics, "render_timing_diagnostics", "cpu_raster_replay_ms"),
        "standalone_process_elapsed_ms": metric_value(metrics, "render_timing_diagnostics", "process_elapsed_ms"),
        "raw_chunks": metric_value(audit, "raw_chunk_count") or metric_value(audit, "paint_artifact", "raw_chunk_count"),
        "raw_ops": metric_value(audit, "raw_op_histogram") or metric_value(audit, "paint_artifact", "raw_op_histogram"),
        "retained_commands": metric_value(metrics, "retained_command_histogram"),
        "retained_vs_oracle_exact": metric_value(retained_oracle, "exact_pixel_difference_count"),
        "retained_vs_oracle_threshold": metric_value(retained_oracle, "thresholded_changed_percent_full_viewport"),
        "oracle_vs_playwright_exact": metric_value(oracle_pw, "exact_pixel_difference_count"),
        "oracle_vs_playwright_threshold": metric_value(oracle_pw, "thresholded_changed_percent_full_viewport"),
        "diff_classification": metric_value(oracle_pw, "diff_classification"),
        "text_explained_diff_percent": metric_value(oracle_pw, "text_explained_diff_percent"),
        "non_text_diff_percent": metric_value(oracle_pw, "non_text_diff_percent"),
        "edge_diff_percent": metric_value(oracle_pw, "edge_diff_percent"),
        "largest_diff_component_bbox": metric_value(oracle_pw, "diff_classification_metrics", "largest_diff_component_bbox"),
        "largest_diff_component_area": metric_value(oracle_pw, "diff_classification_metrics", "largest_diff_component_area"),
        "large_component_diff_percent": metric_value(oracle_pw, "diff_classification_metrics", "large_component_diff_percent"),
        "small_component_count": metric_value(oracle_pw, "diff_classification_metrics", "small_component_count"),
        "retained": rel(item_dir / f"{name}-retained.bmp", out_dir),
        "oracle": rel(item_dir / f"{name}-oracle.bmp", out_dir),
        "playwright": rel(item_dir / f"{name}-playwright.png", out_dir),
    }


def write_html(out_dir: Path, rows: list[dict]) -> Path:
    rows_sorted = sorted(rows, key=lambda row: (row["benchmark_exit"] not in (0, "0"), row["name"]))
    generated = time.strftime("%Y-%m-%d %H:%M:%S")
    html_rows = []
    for row in rows_sorted:
        item_dir = out_dir / row["name"]
        name = html.escape(row["name"])
        status_class = "ok" if row["benchmark_exit"] == 0 and row["playwright_exit"] == 0 else "bad"
        html_rows.append(
            "<tr>"
            f'<td class="{status_class}"><a href="{name}/">{name}</a></td>'
            f"<td>{html.escape(str(row['benchmark_exit']))}</td>"
            f"<td>{html.escape(str(row['playwright_exit']))}</td>"
            f"<td>{html.escape(str(row['retained_vs_oracle_exact']))}</td>"
            f"<td>{html.escape(str(row['oracle_vs_playwright_exact']))}</td>"
            f"<td>{html.escape(str(row.get('diff_classification', '')))}</td>"
            f"<td>{html.escape(str(row.get('standalone_advance_and_render_ms', '')))}</td>"
            f"<td>{html.escape(str(row.get('playwright_elapsed_seconds', '')))}</td>"
            + image_cell(item_dir / f"{row['name']}-retained.bmp", out_dir, "retained")
            + image_cell(item_dir / f"{row['name']}-oracle.bmp", out_dir, "oracle")
            + image_cell(item_dir / f"{row['name']}-playwright.png", out_dir, "playwright")
            + f'<td><a href="{name}/{name}-audit.json">audit</a> '
            f'<a href="{name}/{name}-metrics.json">metrics</a> '
            f'<a href="{name}/{name}-retained-vs-oracle.json">r/o</a> '
            f'<a href="{name}/{name}-oracle-vs-playwright.json">o/p</a> '
            f'<a href="{name}/{name}-benchmark.log">log</a></td>'
            "</tr>"
        )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>Blink Standalone All Examples Comparison</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  h1 {{ margin: 0 0 4px; font-size: 24px; }}
  .meta {{ margin: 0 0 20px; color: #59636e; }}
  table {{ border-collapse: collapse; width: 100%; background: white; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; vertical-align: top; font-size: 12px; }}
  th {{ position: sticky; top: 0; background: #eef2f6; z-index: 1; }}
  img {{ width: 160px; max-height: 110px; object-fit: contain; image-rendering: auto; background: white; border: 1px solid #d8dee4; }}
  .ok {{ background: #dafbe1; }}
  .bad {{ background: #ffebe9; }}
  .missing {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>Blink Standalone All Examples Comparison</h1>
<p class="meta">Generated {html.escape(generated)}. Columns show benchmark/Playwright exit codes, exact retained-vs-oracle diff, exact oracle-vs-Playwright diff, heuristic diff classification, timing, and image previews.</p>
<table>
  <thead><tr>
    <th>Example</th><th>Bench</th><th>PW</th><th>R/O exact</th><th>O/P exact</th><th>Class</th><th>Standalone render ms</th><th>PW elapsed s</th>
    <th>Retained</th><th>Oracle</th><th>Playwright</th><th>Artifacts</th>
  </tr></thead>
  <tbody>
    {''.join(html_rows)}
  </tbody>
</table>
"""
    index = out_dir / "index.html"
    index.write_text(page, encoding="utf-8")
    (out_dir / "summary.json").write_text(json.dumps(rows_sorted, indent=2), encoding="utf-8")
    return index


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--fixtures", type=Path, default=FIXTURE_DIR)
    parser.add_argument("--recursive", action="store_true")
    parser.add_argument("--out-dir", type=Path, default=ROOT / "build" / "all_examples_comparison")
    parser.add_argument("--viewport", default="320x200")
    parser.add_argument("--timeout", type=int, default=45)
    parser.add_argument("--limit", type=int)
    args = parser.parse_args()

    fixtures = sorted(args.fixtures.rglob("*.html") if args.recursive else args.fixtures.glob("*.html"))
    if args.limit:
        fixtures = fixtures[: args.limit]
    if not fixtures:
        raise SystemExit(f"No fixtures found under {args.fixtures}")
    if not args.benchmark.exists():
        raise SystemExit(f"Benchmark not found: {args.benchmark}")

    args.out_dir.mkdir(parents=True, exist_ok=True)
    rows: list[dict] = []
    for index, fixture in enumerate(fixtures, 1):
        name = fixture_name(fixture, args.fixtures)
        item_dir = args.out_dir / name
        item_dir.mkdir(parents=True, exist_ok=True)
        print(f"[{index}/{len(fixtures)}] {name}", flush=True)

        retained = item_dir / f"{name}-retained.bmp"
        oracle = item_dir / f"{name}-oracle.bmp"
        metrics = item_dir / f"{name}-metrics.json"
        audit = item_dir / f"{name}-audit.json"
        setup = item_dir / f"{name}-standalone-setup.json"
        pw = item_dir / f"{name}-playwright.png"
        crash = item_dir / f"{name}.dmp"
        status = {"fixture": str(fixture), "started": time.time()}

        bench_cmd = [
            str(args.benchmark),
            "--html-file",
            str(fixture),
            "--resource-root",
            str(args.fixtures),
            "--viewport",
            args.viewport,
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
        ]
        status["benchmark_exit"], status["benchmark_elapsed_seconds"] = run(
            bench_cmd, item_dir / f"{name}-benchmark.log", args.timeout
        )

        pw_cmd = [
            "node",
            str(ROOT / "tools" / "playwright_screenshot.cjs"),
            "--html-file",
            str(fixture),
            "--out",
            str(pw),
            "--viewport",
            args.viewport,
        ]
        status["playwright_exit"], status["playwright_elapsed_seconds"] = run(
            pw_cmd, item_dir / f"{name}-playwright.log", args.timeout
        )
        status["playwright_timing_mode"] = "wall_clock_command"
        status["playwright_timing_caveat"] = (
            "elapsed time covers the Playwright screenshot command, not a "
            "Chromium trace phase breakdown"
        )

        if retained.exists() and oracle.exists():
            status["retained_vs_oracle_exit"], status["retained_vs_oracle_elapsed_seconds"] = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(retained),
                    "--playwright",
                    str(oracle),
                    "--out-json",
                    str(item_dir / f"{name}-retained-vs-oracle.json"),
                    "--out-dir",
                    str(item_dir / "retained-vs-oracle-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{name}-retained-vs-oracle.log",
                args.timeout,
            )
        if oracle.exists() and pw.exists():
            status["oracle_vs_playwright_exit"], status["oracle_vs_playwright_elapsed_seconds"] = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(oracle),
                    "--playwright",
                    str(pw),
                    "--out-json",
                    str(item_dir / f"{name}-oracle-vs-playwright.json"),
                    "--out-dir",
                    str(item_dir / "oracle-vs-playwright-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{name}-oracle-vs-playwright.log",
                args.timeout,
            )

        status["finished"] = time.time()
        (item_dir / f"{name}-status.json").write_text(json.dumps(status, indent=2), encoding="utf-8")
        rows.append(summarize_row(fixture, args.fixtures, item_dir, args.out_dir))

    index_path = write_html(args.out_dir, rows)
    print(f"Wrote {index_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
