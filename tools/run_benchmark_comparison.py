#!/usr/bin/env python3
"""Manifest-driven standalone/oracle/Playwright comparison runner."""

from __future__ import annotations

import argparse
import html
import json
import re
import subprocess
import sys
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
PAINT_AUDIT_ROOT = (
    ROOT / "upstream" / "chromium" / "standalone_renderer" / "testdata" / "paint_audit"
)
DEFAULT_BENCHMARK = (
    ROOT
    / "build"
    / "cmake-live-image-png-ninja-vs18"
    / "blink_standalone_render_benchmark_skia.exe"
)
DEFAULT_CASES = ROOT / "tools" / "benchmark_comparison_cases.json"
PLAYWRIGHT_SCRIPT = ROOT / "tools" / "playwright_screenshot.cjs"
COMPARE_SCRIPT = ROOT / "tools" / "content_aware_compare.py"


def run(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float, str]:
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
    return code, elapsed, output


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def read_json(path: Path) -> dict:
    if not path.exists():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:  # pragma: no cover - tooling diagnostics.
        return {"_json_error": str(exc)}


def read_text(path: Path) -> str:
    if not path.exists():
        return ""
    return path.read_text(encoding="utf-8", errors="replace")


def metric_value(data: dict, *keys: str) -> str:
    current: object = data
    for key in keys:
        if not isinstance(current, dict) or key not in current:
            return ""
        current = current[key]
    if isinstance(current, float):
        return f"{current:.4f}"
    return str(current)


def fallback_scalar_from_text(text: str, key: str) -> str:
    match = re.search(rf'"{re.escape(key)}"\s*:\s*([0-9]+(?:\.[0-9]+)?)', text)
    if not match:
        return ""
    value = match.group(1)
    return value[:-2] if value.endswith(".0") else value


def unsupported_css_diagnostics(metrics_json: dict) -> tuple[int, str]:
    diagnostics = metrics_json.get("diagnostics", [])
    if not isinstance(diagnostics, list):
        return 0, ""
    matches = [
        str(diagnostic)
        for diagnostic in diagnostics
        if "unsupported CSS" in str(diagnostic)
    ]
    return len(matches), matches[0] if matches else ""


def add_scroll_args(cmd: list[str], scroll: dict | None) -> None:
    if not scroll:
        return
    cmd.extend(["--scroll-x", str(int(scroll.get("x", 0)))])
    cmd.extend(["--scroll-y", str(int(scroll.get("y", 0)))])


def add_element_scroll_args(cmd: list[str], scrolls: dict | None) -> None:
    for element_id, offset in sorted((scrolls or {}).items()):
        cmd.extend(
            [
                "--scroll-element",
                f"{element_id}:{int(offset.get('x', 0))},{int(offset.get('y', 0))}",
            ]
        )


def image_cell(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<td class="missing">missing</td>'
    relative = html.escape(rel(path, out_dir))
    return (
        "<td>"
        f'<a href="{relative}"><img src="{relative}" alt="{html.escape(label)}"></a>'
        "</td>"
    )


def load_manifest(path: Path) -> tuple[dict[str, dict], dict[str, list[str]]]:
    payload = json.loads(path.read_text(encoding="utf-8"))
    cases = {case["name"]: case for case in payload.get("cases", [])}
    return cases, payload.get("sets", {})


def build_report(selected_names: list[str], rows: list[dict], *, case_set: str,
                 has_playwright: bool, playwright_detail: str,
                 has_pillow: bool, pillow_detail: str) -> dict:
    classification_counts: dict[str, int] = {}
    benchmark_ok = 0
    playwright_ok = 0
    for row in rows:
        if row.get("benchmark_exit") == 0:
            benchmark_ok += 1
        if row.get("playwright_exit") == 0:
            playwright_ok += 1
        classification = str(row.get("diff_classification") or "unclassified")
        classification_counts[classification] = classification_counts.get(classification, 0) + 1
    return {
        "case_set": case_set,
        "case_count": len(selected_names),
        "benchmark_success_count": benchmark_ok,
        "playwright_success_count": playwright_ok,
        "classification_counts": classification_counts,
        "dependencies": {
            "playwright_available": has_playwright,
            "playwright_detail": playwright_detail,
            "pillow_available": has_pillow,
            "pillow_detail": pillow_detail,
        },
        "cases": rows,
    }


def playwright_available() -> tuple[bool, str]:
    code, _, output = run(
        ["node", str(PLAYWRIGHT_SCRIPT), "--check-only"],
        ROOT / "build" / "benchmark-comparison" / "playwright-check.log",
        20,
    )
    return code == 0, output.strip()


def pillow_available() -> tuple[bool, str]:
    code, _, output = run(
        [sys.executable, "-c", "import PIL; print(PIL.__version__)"],
        ROOT / "build" / "benchmark-comparison" / "pillow-check.log",
        20,
    )
    return code == 0, output.strip()


def resolve_hcsr_example(catalog: dict, example_name: str) -> str:
    for example in catalog.get("examples", []):
        if example.get("name") == example_name:
            return example["relativePath"]
    raise KeyError(f"Unknown HCSR example '{example_name}'")


def resolve_case(case: dict, hcsr_root: Path | None) -> tuple[Path, Path]:
    source = case.get("source", "paint_audit")
    if source == "paint_audit":
      html_path = PAINT_AUDIT_ROOT / case["html"]
      return html_path, PAINT_AUDIT_ROOT
    if source == "hcsr":
      if hcsr_root is None:
          raise ValueError("HCSR case requested without --hcsr-root")
      examples_root = hcsr_root / "Examples"
      if "catalog_name" in case:
          catalog = read_json(examples_root / "ExampleCatalog.json")
          relative = resolve_hcsr_example(catalog, case["catalog_name"])
          return examples_root / relative, examples_root
      return examples_root / case["html"], examples_root
    raise ValueError(f"Unsupported case source '{source}'")


def write_html_summary(out_dir: Path, report: dict) -> Path:
    generated = time.strftime("%Y-%m-%d %H:%M:%S")
    rows = report["cases"]
    html_rows = []
    for row in rows:
        name = html.escape(row["name"])
        item_dir = out_dir / row["name"]
        status_class = "ok" if row["benchmark_exit"] == 0 else "bad"
        note = html.escape(str(row.get("note", "")))
        unsupported_css = html.escape(
            str(row.get("first_unsupported_css_diagnostic", ""))
        )
        html_rows.append(
            "<tr>"
            f'<td class="{status_class}"><a href="{name}/">{name}</a></td>'
            f"<td>{html.escape(str(row['benchmark_exit']))}</td>"
            f"<td>{html.escape(str(row.get('playwright_exit', 'skipped')))}</td>"
            f"<td>{html.escape(str(row.get('non_white_pixels', '')))}</td>"
            f"<td>{html.escape(str(row.get('unique_color_sample', '')))}</td>"
            f"<td>{html.escape(str(row.get('missing_resource_count', '')))}</td>"
            f"<td>{html.escape(str(row.get('diagnostic_count', '')))}</td>"
            f"<td>{html.escape(str(row.get('unsupported_css_diagnostic_count', '')))}"
            f"{('<br>' + unsupported_css) if unsupported_css else ''}</td>"
            f"<td>{html.escape(str(row.get('retained_vs_oracle_exact', '')))}</td>"
            f"<td>{html.escape(str(row.get('oracle_vs_playwright_exact', '')))}</td>"
            f"<td>{html.escape(str(row.get('retained_vs_playwright_exact', '')))}</td>"
            f"<td>{html.escape(str(row.get('playwright_compare_source', 'oracle')))}</td>"
            f"<td>{html.escape(str(row.get('diff_classification', '')))}</td>"
            f"<td>{note}</td>"
            f"<td>{html.escape(str(row.get('standalone_advance_and_render_ms', '')))}</td>"
            f"<td>{html.escape(str(row.get('playwright_elapsed_seconds', '')))}</td>"
            + image_cell(item_dir / f"{row['name']}-retained.bmp", out_dir, "retained")
            + image_cell(item_dir / f"{row['name']}-oracle.bmp", out_dir, "oracle")
            + image_cell(item_dir / f"{row['name']}-playwright.png", out_dir, "playwright")
            + f'<td><a href="{name}/{name}-metrics.json">metrics</a> '
            f'<a href="{name}/{name}-audit.json">audit</a> '
            f'<a href="{name}/{name}-status.json">status</a></td>'
            "</tr>"
        )
    classification_items = "".join(
        f"<li><strong>{html.escape(name)}</strong>: {count}</li>"
        for name, count in sorted(report["classification_counts"].items())
    )
    dependencies = report["dependencies"]
    dep_html = (
        f"<li><strong>Playwright</strong>: {'available' if dependencies['playwright_available'] else 'missing'}"
        f" <span class=\"meta-inline\">{html.escape(str(dependencies['playwright_detail']))}</span></li>"
        f"<li><strong>Pillow</strong>: {'available' if dependencies['pillow_available'] else 'missing'}"
        f" <span class=\"meta-inline\">{html.escape(str(dependencies['pillow_detail']))}</span></li>"
    )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>Blink Standalone Benchmark Comparison</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  h1 {{ margin: 0 0 4px; font-size: 24px; }}
  .meta {{ margin: 0 0 20px; color: #59636e; }}
  .summary {{ display: grid; grid-template-columns: repeat(3, minmax(0, 1fr)); gap: 12px; margin: 0 0 20px; }}
  .summary-card {{ background: white; border: 1px solid #d0d7de; padding: 12px 14px; }}
  .summary-card h2 {{ margin: 0 0 8px; font-size: 14px; }}
  .summary-card ul {{ margin: 0; padding-left: 18px; font-size: 12px; }}
  .meta-inline {{ color: #59636e; }}
  table {{ border-collapse: collapse; width: 100%; background: white; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; vertical-align: top; font-size: 12px; }}
  th {{ position: sticky; top: 0; background: #eef2f6; z-index: 1; }}
  img {{ width: 160px; max-height: 110px; object-fit: contain; image-rendering: auto; background: white; border: 1px solid #d8dee4; }}
  .ok {{ background: #dafbe1; }}
  .bad {{ background: #ffebe9; }}
  .missing {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>Blink Standalone Benchmark Comparison</h1>
<p class="meta">Generated {html.escape(generated)} for case set <strong>{html.escape(str(report['case_set']))}</strong>. This runner compares retained replay, paint-record oracle replay, and optional Playwright Chromium screenshots for manifest-selected cases.</p>
<section class="summary">
  <div class="summary-card">
    <h2>Run</h2>
    <ul>
      <li><strong>Cases</strong>: {report['case_count']}</li>
      <li><strong>Benchmark OK</strong>: {report['benchmark_success_count']}</li>
      <li><strong>Playwright OK</strong>: {report['playwright_success_count']}</li>
    </ul>
  </div>
  <div class="summary-card">
    <h2>Classification Counts</h2>
    <ul>{classification_items}</ul>
  </div>
  <div class="summary-card">
    <h2>Dependencies</h2>
    <ul>{dep_html}</ul>
  </div>
</section>
<table>
  <thead><tr>
    <th>Case</th><th>Bench</th><th>PW</th><th>Non-white</th><th>Unique</th><th>Missing res</th><th>Diag</th><th>Unsupported CSS</th><th>R/O exact</th><th>O/P exact</th><th>R/P exact</th><th>PW source</th><th>Class</th><th>Note</th><th>Standalone render ms</th><th>PW elapsed s</th>
    <th>Retained</th><th>Oracle</th><th>Playwright</th><th>Artifacts</th>
  </tr></thead>
  <tbody>{''.join(html_rows)}</tbody>
</table>
"""
    index = out_dir / "index.html"
    index.write_text(page, encoding="utf-8")
    (out_dir / "summary.json").write_text(json.dumps(rows, indent=2), encoding="utf-8")
    (out_dir / "report.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
    return index


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--cases-file", type=Path, default=DEFAULT_CASES)
    parser.add_argument("--case-set", default="smoke")
    parser.add_argument("--out-dir", type=Path, default=ROOT / "build" / "benchmark-comparison" / "smoke")
    parser.add_argument("--viewport", default="320x200")
    parser.add_argument("--timeout", type=int, default=90)
    parser.add_argument("--hcsr-root", type=Path)
    parser.add_argument("--limit", type=int)
    args = parser.parse_args()

    if not args.benchmark.exists():
        raise SystemExit(f"Benchmark not found: {args.benchmark}")

    cases_by_name, sets = load_manifest(args.cases_file)
    selected_names = sets.get(args.case_set)
    if selected_names is None:
        raise SystemExit(f"Unknown case set '{args.case_set}' in {args.cases_file}")
    if args.limit:
        selected_names = selected_names[: args.limit]

    args.out_dir.mkdir(parents=True, exist_ok=True)
    has_playwright, playwright_detail = playwright_available()
    has_pillow, pillow_detail = pillow_available()

    rows: list[dict] = []
    for index, case_name in enumerate(selected_names, 1):
        case = cases_by_name[case_name]
        html_path, resource_root = resolve_case(case, args.hcsr_root)
        item_dir = args.out_dir / case_name
        item_dir.mkdir(parents=True, exist_ok=True)
        print(f"[{index}/{len(selected_names)}] {case_name}", flush=True)

        retained = item_dir / f"{case_name}-retained.bmp"
        oracle = item_dir / f"{case_name}-oracle.bmp"
        metrics = item_dir / f"{case_name}-metrics.json"
        audit = item_dir / f"{case_name}-audit.json"
        setup = item_dir / f"{case_name}-standalone-setup.json"
        pw = item_dir / f"{case_name}-playwright.png"
        crash = item_dir / f"{case_name}.dmp"
        status = {
            "name": case_name,
            "fixture": str(html_path),
            "resource_root": str(resource_root),
            "started": time.time(),
            "playwright_available": has_playwright,
            "pillow_available": has_pillow,
        }

        viewport = case.get("viewport", args.viewport)
        bench_cmd = [
            str(args.benchmark),
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
        ]
        if case.get("time_ms") is not None:
            bench_cmd.extend(["--time-ms", str(case["time_ms"])])
        for attr in case.get("attrs", []):
            bench_cmd.extend(["--attr", attr])
        add_scroll_args(bench_cmd, case.get("scroll"))
        add_element_scroll_args(bench_cmd, case.get("element_scroll"))
        status["benchmark_exit"], status["benchmark_elapsed_seconds"], _ = run(
            bench_cmd, item_dir / f"{case_name}-benchmark.log", args.timeout
        )

        if has_playwright:
            pw_cmd = [
                "node",
                str(PLAYWRIGHT_SCRIPT),
                "--html-file",
                str(html_path),
                "--out",
                str(pw),
                "--viewport",
                viewport,
            ]
            if case.get("time_ms") is not None:
                pw_cmd.extend(["--time-ms", str(case["time_ms"])])
            for attr in case.get("attrs", []):
                pw_cmd.extend(["--attr", attr])
            add_scroll_args(pw_cmd, case.get("scroll"))
            add_element_scroll_args(pw_cmd, case.get("element_scroll"))
            status["playwright_exit"], status["playwright_elapsed_seconds"], _ = run(
                pw_cmd, item_dir / f"{case_name}-playwright.log", args.timeout
            )
        else:
            status["playwright_exit"] = ""
            status["playwright_skip_reason"] = playwright_detail

        if has_pillow and retained.exists() and oracle.exists():
            status["retained_vs_oracle_exit"], status["retained_vs_oracle_elapsed_seconds"], _ = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(retained),
                    "--playwright",
                    str(oracle),
                    "--out-json",
                    str(item_dir / f"{case_name}-retained-vs-oracle.json"),
                    "--out-dir",
                    str(item_dir / "retained-vs-oracle-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{case_name}-retained-vs-oracle.log",
                args.timeout,
            )
        else:
            status["retained_vs_oracle_exit"] = ""
            if not has_pillow:
                status["compare_skip_reason"] = pillow_detail

        if has_pillow and has_playwright and oracle.exists() and pw.exists():
            status["oracle_vs_playwright_exit"], status["oracle_vs_playwright_elapsed_seconds"], _ = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(oracle),
                    "--playwright",
                    str(pw),
                    "--out-json",
                    str(item_dir / f"{case_name}-oracle-vs-playwright.json"),
                    "--out-dir",
                    str(item_dir / "oracle-vs-playwright-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{case_name}-oracle-vs-playwright.log",
                args.timeout,
            )

        if case.get("time_ms") is not None and has_pillow and has_playwright and retained.exists() and pw.exists():
            status["retained_vs_playwright_exit"], status["retained_vs_playwright_elapsed_seconds"], _ = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(retained),
                    "--playwright",
                    str(pw),
                    "--out-json",
                    str(item_dir / f"{case_name}-retained-vs-playwright.json"),
                    "--out-dir",
                    str(item_dir / "retained-vs-playwright-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{case_name}-retained-vs-playwright.log",
                args.timeout,
            )

        status["finished"] = time.time()
        status_path = item_dir / f"{case_name}-status.json"
        status_path.write_text(json.dumps(status, indent=2), encoding="utf-8")

        metrics_json = read_json(metrics)
        metrics_text = read_text(metrics)
        unsupported_css_count, first_unsupported_css = unsupported_css_diagnostics(
            metrics_json
        )
        retained_oracle = read_json(item_dir / f"{case_name}-retained-vs-oracle.json")
        oracle_pw = read_json(item_dir / f"{case_name}-oracle-vs-playwright.json")
        retained_pw = read_json(item_dir / f"{case_name}-retained-vs-playwright.json")
        playwright_compare = retained_pw if case.get("time_ms") is not None else oracle_pw
        playwright_compare_source = "retained" if case.get("time_ms") is not None else "oracle"
        rows.append(
            {
                "name": case_name,
                "benchmark_exit": status["benchmark_exit"],
                "playwright_exit": status.get("playwright_exit", ""),
                "benchmark_elapsed_seconds": status.get("benchmark_elapsed_seconds", ""),
                "playwright_elapsed_seconds": status.get("playwright_elapsed_seconds", ""),
                "non_white_pixels": metrics_json.get("non_white_pixels", "")
                or fallback_scalar_from_text(metrics_text, "non_white_pixels"),
                "unique_color_sample": metrics_json.get("unique_color_sample", "")
                or fallback_scalar_from_text(metrics_text, "unique_color_sample"),
                "missing_resource_count": metrics_json.get("missing_resource_count", "")
                or fallback_scalar_from_text(metrics_text, "missing_resource_count"),
                "time_ms": case.get("time_ms", ""),
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
                "oracle_vs_playwright_exact": metric_value(
                    oracle_pw, "exact_pixel_difference_count"
                ),
                "retained_vs_playwright_exact": metric_value(
                    retained_pw, "exact_pixel_difference_count"
                ),
                "playwright_compare_source": playwright_compare_source,
                "diff_classification": metric_value(playwright_compare, "diff_classification"),
                "note": case.get("note", ""),
            }
        )

    report = build_report(
        selected_names,
        rows,
        case_set=args.case_set,
        has_playwright=has_playwright,
        playwright_detail=playwright_detail,
        has_pillow=has_pillow,
        pillow_detail=pillow_detail,
    )
    index = write_html_summary(args.out_dir, report)
    print(f"Wrote comparison summary to {index}")
    if not has_playwright:
        print(
            "Playwright unavailable. Install with `npm install --no-save playwright` "
            "then `npx playwright install chromium` from the repo root."
        )
    if not has_pillow:
        print("Pillow unavailable. Install with `python -m pip install pillow`.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
