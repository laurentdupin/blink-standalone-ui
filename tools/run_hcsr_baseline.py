#!/usr/bin/env python3
"""Run HCSR standalone-vs-Chromium baseline comparisons.

This tool is intentionally report-oriented. It does not change rendering
behavior; it captures standalone benchmark output, the benchmark paint-record
oracle, and Playwright/Chromium screenshots for top/mid/bottom scroll states.
"""

from __future__ import annotations

import argparse
import html
import json
import re
import subprocess
import sys
import time
from collections import Counter
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BENCHMARK = (
    ROOT
    / "build"
    / "cmake-live-image-png-ninja-vs18"
    / "blink_standalone_render_benchmark_skia.exe"
)
PLAYWRIGHT_SCRIPT = ROOT / "tools" / "playwright_screenshot.cjs"
COMPARE_SCRIPT = ROOT / "tools" / "content_aware_compare.py"
DEFAULT_HCSR_ROOT = Path(r"C:\Repos\UniversalGameEngine\HCSR")


IMAGE_EXTENSIONS = {
    ".bmp": "bmp",
    ".gif": "gif",
    ".jpeg": "jpeg",
    ".jpg": "jpeg",
    ".png": "png",
    ".svg": "svg",
    ".webp": "webp",
}


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


def read_json(path: Path) -> dict[str, Any]:
    if not path.exists():
        return {}
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:  # pragma: no cover - diagnostic script.
        return {"_json_error": str(exc)}
    return payload if isinstance(payload, dict) else {"value": payload}


def read_text(path: Path) -> str:
    if not path.exists():
        return ""
    return path.read_text(encoding="utf-8", errors="replace")


def metric_value(data: dict[str, Any], *keys: str) -> Any:
    current: Any = data
    for key in keys:
        if not isinstance(current, dict) or key not in current:
            return None
        current = current[key]
    return current


def format_metric(value: Any) -> str:
    if value is None:
        return ""
    if isinstance(value, float):
        return f"{value:.3f}"
    return str(value)


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def safe_name(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9_.-]+", "_", name).strip("_") or "case"


def load_examples(hcsr_root: Path) -> list[dict[str, str]]:
    examples_root = hcsr_root / "Examples"
    catalog_path = examples_root / "ExampleCatalog.json"
    if catalog_path.exists():
        payload = json.loads(catalog_path.read_text(encoding="utf-8"))
        examples = payload.get("examples", [])
        return [
            {
                "name": str(example["name"]),
                "relative_path": str(example["relativePath"]),
            }
            for example in examples
        ]
    html_files = sorted(examples_root.rglob("*.html"))
    return [
        {
            "name": html_file.stem,
            "relative_path": html_file.relative_to(examples_root).as_posix(),
        }
        for html_file in html_files
    ]


def referenced_path(base: Path, resource_root: Path, reference: str) -> Path | None:
    clean = reference.strip().strip("'\"")
    if not clean or clean.startswith(("data:", "http:", "https:", "#")):
        return None
    clean = clean.split("#", 1)[0].split("?", 1)[0]
    candidate = (base / clean).resolve()
    try:
        candidate.relative_to(resource_root.resolve())
    except ValueError:
        return None
    return candidate


def scan_example_features(example_dir: Path,
                          html_path: Path,
                          resource_root: Path) -> dict[str, Any]:
    local_extension_counts: Counter[str] = Counter()
    referenced_extension_counts: Counter[str] = Counter()
    svg_text_assets: list[str] = []
    combined_text = ""
    for path in sorted(example_dir.rglob("*")):
        if not path.is_file():
            continue
        suffix = path.suffix.lower()
        if suffix in IMAGE_EXTENSIONS:
            local_extension_counts[IMAGE_EXTENSIONS[suffix]] += 1

    text_paths: list[Path] = [html_path]
    text_paths.extend(sorted(example_dir.glob("*.css")))
    text_paths.extend(sorted(example_dir.glob("*.svg")))
    visited: set[Path] = set()
    ref_pattern = re.compile(
        r"""(?:src|href)\s*=\s*["']([^"']+)["']|url\(\s*["']?([^"')]+)["']?\s*\)""",
        re.I,
    )
    index = 0
    while index < len(text_paths):
        path = text_paths[index].resolve()
        index += 1
        if path in visited or not path.exists():
            continue
        visited.add(path)
        text = read_text(path)
        combined_text += "\n" + text.lower()
        if path.suffix.lower() == ".svg" and re.search(r"<\s*text\b", text, re.I):
            svg_text_assets.append(path.name)
        for match in ref_pattern.finditer(text):
            reference = match.group(1) or match.group(2) or ""
            target = referenced_path(path.parent, resource_root, reference)
            if not target:
                continue
            suffix = target.suffix.lower()
            if suffix in IMAGE_EXTENSIONS:
                referenced_extension_counts[IMAGE_EXTENSIONS[suffix]] += 1
                if suffix == ".svg" and target.exists():
                    svg_text = read_text(target)
                    if re.search(r"<\s*text\b", svg_text, re.I):
                        svg_text_assets.append(target.name)
            elif suffix == ".css" and target not in visited:
                text_paths.append(target)
    extension_counts = local_extension_counts + referenced_extension_counts
    return {
        "image_extension_counts": dict(sorted(extension_counts.items())),
        "local_image_extension_counts": dict(sorted(local_extension_counts.items())),
        "referenced_image_extension_counts": dict(
            sorted(referenced_extension_counts.items())
        ),
        "uses_jpeg": extension_counts.get("jpeg", 0) > 0,
        "uses_bmp": extension_counts.get("bmp", 0) > 0,
        "uses_webp": extension_counts.get("webp", 0) > 0,
        "uses_svg": extension_counts.get("svg", 0) > 0,
        "svg_text_assets": svg_text_assets,
        "uses_svg_text": bool(svg_text_assets),
        "uses_native_controls": bool(
            re.search(r"<\s*(input|select|textarea)\b", combined_text)
        ),
        "uses_sticky": "position: sticky" in combined_text
        or "position:sticky" in combined_text,
        "uses_filter": "filter:" in combined_text
        or "backdrop-filter" in combined_text,
        "uses_mask_or_clip": "clip-path" in combined_text or "mask-" in combined_text,
    }


def scroll_positions_from_state(state: dict[str, Any]) -> list[tuple[str, int]]:
    inner_height = int(state.get("innerHeight") or 720)
    document_height = int(state.get("documentHeight") or inner_height)
    max_y = max(0, document_height - inner_height)
    if max_y <= 0:
        return [("top", 0)]
    mid_y = max_y // 2
    near_bottom_y = max_y
    positions: list[tuple[str, int]] = [("top", 0)]
    if mid_y > 0:
        positions.append(("mid", mid_y))
    if near_bottom_y not in {y for _, y in positions}:
        positions.append(("bottom", near_bottom_y))
    return positions


def image_cell(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<td class="missing">missing</td>'
    escaped = html.escape(rel(path, out_dir))
    return (
        "<td>"
        f'<a href="{escaped}"><img src="{escaped}" alt="{html.escape(label)}"></a>'
        "</td>"
    )


def classify_row(row: dict[str, Any]) -> str:
    views = row.get("views", [])
    if any(view.get("benchmark_exit") not in (0, None) for view in views):
        return "benchmark_fail"
    if any(view.get("playwright_exit") not in (0, None) for view in views):
        return "playwright_fail"
    features = row.get("features", {})
    if features.get("uses_bmp") or features.get("uses_webp"):
        return "known_gap_image_format"
    if features.get("uses_svg_text"):
        return "known_gap_svg_text"
    if features.get("uses_native_controls"):
        return "native_control_or_text_gap"
    classifications = [view.get("diff_classification", "") for view in views]
    if all(item in {"exact_or_threshold_match", "mostly_edge_aa", ""} for item in classifications):
        return "pass_or_aa"
    if any(item == "missing_resource_or_large_region" for item in classifications):
        return "large_region_mismatch"
    return "needs_review"


def write_html(out_dir: Path, rows: list[dict[str, Any]], report: dict[str, Any]) -> Path:
    generated = time.strftime("%Y-%m-%d %H:%M:%S")
    summary_rows = []
    for classification, count in sorted(report["classification_counts"].items()):
        summary_rows.append(
            f"<tr><td>{html.escape(classification)}</td><td>{count}</td></tr>"
        )

    table_rows = []
    for row in rows:
        item_dir = out_dir / safe_name(row["name"])
        feature_bits = []
        features = row.get("features", {})
        for key in [
            "uses_jpeg",
            "uses_bmp",
            "uses_webp",
            "uses_svg_text",
            "uses_native_controls",
            "uses_sticky",
            "uses_filter",
            "uses_mask_or_clip",
        ]:
            if features.get(key):
                feature_bits.append(key.replace("uses_", ""))
        worst_view = row.get("worst_view", {})
        top_timing = row.get("top_timing", {})
        table_rows.append(
            "<tr>"
            f"<td>{html.escape(row['name'])}</td>"
            f"<td>{html.escape(row.get('classification', ''))}</td>"
            f"<td>{html.escape(', '.join(feature_bits))}</td>"
            f"<td>{html.escape(str(row.get('scroll_positions', '')))}</td>"
            f"<td>{html.escape(format_metric(worst_view.get('diff_exact')))}</td>"
            f"<td>{html.escape(str(worst_view.get('diff_classification', '')))}</td>"
            f"<td>{html.escape(format_metric(top_timing.get('process_elapsed_ms')))}</td>"
            f"<td>{html.escape(format_metric(top_timing.get('blink_initialize_ms')))}</td>"
            f"<td>{html.escape(format_metric(top_timing.get('advance_and_render_ms')))}</td>"
            f"<td>{html.escape(format_metric(row.get('max_missing_resource_count')))}</td>"
            + image_cell(item_dir / f"{safe_name(row['name'])}-top-standalone.bmp", out_dir, "top standalone")
            + image_cell(item_dir / f"{safe_name(row['name'])}-top-playwright.png", out_dir, "top playwright")
            + f'<td><a href="{html.escape(rel(item_dir, out_dir))}/">artifacts</a></td>'
            "</tr>"
        )

    page = f"""<!doctype html>
<meta charset="utf-8">
<title>HCSR Baseline</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  h1 {{ margin: 0 0 4px; font-size: 24px; }}
  table {{ border-collapse: collapse; width: 100%; background: white; margin: 16px 0 28px; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; vertical-align: top; font-size: 12px; }}
  th {{ position: sticky; top: 0; background: #eef2f6; z-index: 1; }}
  img {{ width: 160px; max-height: 110px; object-fit: contain; background: white; border: 1px solid #d8dee4; }}
  .missing {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>HCSR Baseline</h1>
<p>Generated {html.escape(generated)} at viewport {html.escape(str(report['viewport']))}.
Each tall page is compared at top/mid/bottom scroll positions based on Playwright document height.</p>
<h2>Classification Counts</h2>
<table><thead><tr><th>Classification</th><th>Count</th></tr></thead><tbody>
{''.join(summary_rows)}
</tbody></table>
<h2>Examples</h2>
<table>
<thead><tr>
  <th>Example</th><th>Class</th><th>Page Signals</th><th>Scroll Positions</th>
  <th>Worst O/P Exact</th><th>Worst O/P Class</th>
  <th>Process ms</th><th>Blink init ms</th><th>Render ms</th><th>Missing Res</th>
  <th>Top Standalone</th><th>Top Playwright</th><th>Artifacts</th>
</tr></thead>
<tbody>{''.join(table_rows)}</tbody>
</table>
"""
    index = out_dir / "index.html"
    index.write_text(page, encoding="utf-8")
    return index


def write_case_index(item_dir: Path, row: dict[str, Any], out_dir: Path) -> None:
    rows = []
    for view in row.get("views", []):
        name = safe_name(row["name"])
        label = safe_name(view["label"])
        rows.append(
            "<tr>"
            f"<td>{html.escape(view['label'])}</td>"
            f"<td>{view.get('scroll_y', '')}</td>"
            f"<td>{view.get('benchmark_exit', '')}</td>"
            f"<td>{view.get('playwright_exit', '')}</td>"
            f"<td>{html.escape(format_metric(view.get('retained_vs_oracle_exact')))}</td>"
            f"<td>{html.escape(format_metric(view.get('oracle_vs_playwright_exact')))}</td>"
            f"<td>{html.escape(str(view.get('diff_classification', '')))}</td>"
            + image_cell(item_dir / f"{name}-{label}-standalone.bmp", out_dir, "standalone")
            + image_cell(item_dir / f"{name}-{label}-oracle.bmp", out_dir, "oracle")
            + image_cell(item_dir / f"{name}-{label}-playwright.png", out_dir, "playwright")
            + "</tr>"
        )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>{html.escape(row['name'])} HCSR Baseline</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  table {{ border-collapse: collapse; width: 100%; background: white; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; vertical-align: top; font-size: 12px; }}
  img {{ width: 220px; max-height: 150px; object-fit: contain; background: white; border: 1px solid #d8dee4; }}
  .missing {{ color: #8c1818; }}
</style>
<h1>{html.escape(row['name'])}</h1>
<p>Classification: {html.escape(row.get('classification', ''))}</p>
<table><thead><tr>
<th>View</th><th>Scroll Y</th><th>Bench</th><th>PW</th><th>R/O exact</th><th>O/P exact</th><th>Class</th>
<th>Standalone</th><th>Oracle</th><th>Playwright</th>
</tr></thead><tbody>{''.join(rows)}</tbody></table>
"""
    (item_dir / "index.html").write_text(page, encoding="utf-8")


def run_view(
    *,
    benchmark: Path,
    html_path: Path,
    resource_root: Path,
    out_dir: Path,
    case_name: str,
    label: str,
    viewport: str,
    scroll_y: int,
    timeout: int,
) -> dict[str, Any]:
    safe_case = safe_name(case_name)
    safe_label = safe_name(label)
    standalone = out_dir / f"{safe_case}-{safe_label}-standalone.bmp"
    oracle = out_dir / f"{safe_case}-{safe_label}-oracle.bmp"
    metrics = out_dir / f"{safe_case}-{safe_label}-metrics.json"
    audit = out_dir / f"{safe_case}-{safe_label}-audit.json"
    crash = out_dir / f"{safe_case}-{safe_label}.dmp"
    playwright = out_dir / f"{safe_case}-{safe_label}-playwright.png"
    playwright_state = out_dir / f"{safe_case}-{safe_label}-playwright.json"
    retained_oracle = out_dir / f"{safe_case}-{safe_label}-retained-vs-oracle.json"
    oracle_playwright = out_dir / f"{safe_case}-{safe_label}-oracle-vs-playwright.json"

    bench_cmd = [
        str(benchmark),
        "--html-file",
        str(html_path),
        "--resource-root",
        str(resource_root),
        "--viewport",
        viewport,
        "--scroll-y",
        str(scroll_y),
        "--out",
        str(standalone),
        "--json",
        str(metrics),
        "--dump-paint-artifact",
        str(audit),
        "--paint-oracle=skia-paint-record",
        "--oracle-out",
        str(oracle),
        "--crash-dump",
        str(crash),
        "--strict-text-blob-typefaces",
        "--skia-cpu",
    ]
    benchmark_exit, benchmark_elapsed, _ = run(
        bench_cmd, out_dir / f"{safe_case}-{safe_label}-benchmark.log", timeout
    )

    pw_cmd = [
        "node",
        str(PLAYWRIGHT_SCRIPT),
        "--html-file",
        str(html_path),
        "--out",
        str(playwright),
        "--viewport",
        viewport,
        "--scroll-y",
        str(scroll_y),
        "--out-json",
        str(playwright_state),
    ]
    playwright_exit, playwright_elapsed, _ = run(
        pw_cmd, out_dir / f"{safe_case}-{safe_label}-playwright.log", timeout
    )

    retained_oracle_exit = None
    oracle_playwright_exit = None
    if standalone.exists() and oracle.exists():
        retained_oracle_exit, _, _ = run(
            [
                sys.executable,
                str(COMPARE_SCRIPT),
                "--standalone",
                str(standalone),
                "--playwright",
                str(oracle),
                "--out-json",
                str(retained_oracle),
                "--out-dir",
                str(out_dir / f"{safe_case}-{safe_label}-retained-vs-oracle-crops"),
            ],
            out_dir / f"{safe_case}-{safe_label}-retained-vs-oracle.log",
            timeout,
        )
    if oracle.exists() and playwright.exists():
        oracle_playwright_exit, _, _ = run(
            [
                sys.executable,
                str(COMPARE_SCRIPT),
                "--standalone",
                str(oracle),
                "--playwright",
                str(playwright),
                "--out-json",
                str(oracle_playwright),
                "--out-dir",
                str(out_dir / f"{safe_case}-{safe_label}-oracle-vs-playwright-crops"),
                "--compare-background",
                "auto-corners",
            ],
            out_dir / f"{safe_case}-{safe_label}-oracle-vs-playwright.log",
            timeout,
        )

    metrics_json = read_json(metrics)
    retained_oracle_json = read_json(retained_oracle)
    oracle_playwright_json = read_json(oracle_playwright)
    timing = metrics_json.get("render_timing_diagnostics", {})
    return {
        "label": label,
        "scroll_y": scroll_y,
        "benchmark_exit": benchmark_exit,
        "benchmark_elapsed_seconds": benchmark_elapsed,
        "playwright_exit": playwright_exit,
        "playwright_elapsed_seconds": playwright_elapsed,
        "retained_oracle_exit": retained_oracle_exit,
        "oracle_playwright_exit": oracle_playwright_exit,
        "missing_resource_count": metrics_json.get("missing_resource_count"),
        "diagnostic_count": metrics_json.get("diagnostic_count"),
        "unsupported_css_diagnostic_count": len(
            [
                item
                for item in metrics_json.get("diagnostics", [])
                if "unsupported CSS" in str(item)
            ]
        ),
        "process_elapsed_ms": timing.get("process_elapsed_ms"),
        "blink_initialize_ms": timing.get("blink_initialize_ms"),
        "advance_and_render_ms": timing.get("advance_and_render_ms"),
        "cpu_raster_replay_ms": timing.get("cpu_raster_replay_ms"),
        "input_setup_ms": timing.get("input_setup_ms"),
        "retained_vs_oracle_exact": retained_oracle_json.get(
            "exact_pixel_difference_count"
        ),
        "oracle_vs_playwright_exact": oracle_playwright_json.get(
            "exact_pixel_difference_count"
        ),
        "diff_classification": oracle_playwright_json.get("diff_classification"),
        "missing_content_percent": oracle_playwright_json.get(
            "reported_missing_content_percent"
        ),
        "extra_content_percent": oracle_playwright_json.get(
            "reported_extra_content_percent"
        ),
        "standalone": rel(standalone, out_dir),
        "oracle": rel(oracle, out_dir),
        "playwright": rel(playwright, out_dir),
    }


def run_case(
    *,
    benchmark: Path,
    hcsr_root: Path,
    example: dict[str, str],
    out_dir: Path,
    viewport: str,
    timeout: int,
) -> dict[str, Any]:
    examples_root = hcsr_root / "Examples"
    html_path = examples_root / example["relative_path"]
    item_dir = out_dir / safe_name(example["name"])
    item_dir.mkdir(parents=True, exist_ok=True)

    feature_root = html_path.parent if html_path.parent != examples_root else examples_root
    features = scan_example_features(feature_root, html_path, examples_root)

    state_png = item_dir / f"{safe_name(example['name'])}-state-top.png"
    state_json = item_dir / f"{safe_name(example['name'])}-state-top.json"
    state_exit, state_elapsed, _ = run(
        [
            "node",
            str(PLAYWRIGHT_SCRIPT),
            "--html-file",
            str(html_path),
            "--out",
            str(state_png),
            "--viewport",
            viewport,
            "--out-json",
            str(state_json),
        ],
        item_dir / f"{safe_name(example['name'])}-state-top.log",
        timeout,
    )
    state = read_json(state_json)
    scroll_positions = scroll_positions_from_state(state)

    views = []
    for label, scroll_y in scroll_positions:
        print(f"    {label} y={scroll_y}", flush=True)
        views.append(
            run_view(
                benchmark=benchmark,
                html_path=html_path,
                resource_root=examples_root,
                out_dir=item_dir,
                case_name=example["name"],
                label=label,
                viewport=viewport,
                scroll_y=scroll_y,
                timeout=timeout,
            )
        )

    top_timing = {}
    if views:
        top_view = views[0]
        top_timing = {
            "process_elapsed_ms": top_view.get("process_elapsed_ms"),
            "blink_initialize_ms": top_view.get("blink_initialize_ms"),
            "advance_and_render_ms": top_view.get("advance_and_render_ms"),
            "cpu_raster_replay_ms": top_view.get("cpu_raster_replay_ms"),
        }

    worst_view = {}
    for view in views:
        exact = view.get("oracle_vs_playwright_exact")
        if exact is None:
            continue
        if not worst_view or int(exact) > int(worst_view.get("diff_exact", -1)):
            worst_view = {
                "label": view["label"],
                "scroll_y": view["scroll_y"],
                "diff_exact": exact,
                "diff_classification": view.get("diff_classification"),
                "missing_content_percent": view.get("missing_content_percent"),
                "extra_content_percent": view.get("extra_content_percent"),
            }

    max_missing = max(
        [int(view.get("missing_resource_count") or 0) for view in views] or [0]
    )
    row = {
        "name": example["name"],
        "relative_path": example["relative_path"],
        "html_path": str(html_path),
        "state_probe_exit": state_exit,
        "state_probe_elapsed_seconds": state_elapsed,
        "document_height": state.get("documentHeight"),
        "inner_height": state.get("innerHeight"),
        "scroll_positions": scroll_positions,
        "features": features,
        "views": views,
        "top_timing": top_timing,
        "worst_view": worst_view,
        "max_missing_resource_count": max_missing,
    }
    row["classification"] = classify_row(row)
    write_case_index(item_dir, row, out_dir)
    (item_dir / f"{safe_name(example['name'])}-summary.json").write_text(
        json.dumps(row, indent=2), encoding="utf-8"
    )
    return row


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--hcsr-root", type=Path, default=DEFAULT_HCSR_ROOT)
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--viewport", default="1280x720")
    parser.add_argument("--timeout", type=int, default=120)
    parser.add_argument(
        "--examples",
        help="Comma-separated HCSR example names to run. Defaults to all catalog examples.",
    )
    parser.add_argument("--limit", type=int)
    args = parser.parse_args()

    examples = load_examples(args.hcsr_root)
    if args.examples:
        wanted = {item.strip() for item in args.examples.split(",") if item.strip()}
        examples = [example for example in examples if example["name"] in wanted]
    if args.limit:
        examples = examples[: args.limit]
    if not examples:
        raise SystemExit("No HCSR examples selected")
    if not args.benchmark.exists():
        raise SystemExit(f"Benchmark not found: {args.benchmark}")

    args.out_dir.mkdir(parents=True, exist_ok=True)
    rows: list[dict[str, Any]] = []
    for index, example in enumerate(examples, 1):
        print(f"[{index}/{len(examples)}] {example['name']}", flush=True)
        rows.append(
            run_case(
                benchmark=args.benchmark,
                hcsr_root=args.hcsr_root,
                example=example,
                out_dir=args.out_dir,
                viewport=args.viewport,
                timeout=args.timeout,
            )
        )

    classification_counts = Counter(row["classification"] for row in rows)
    report = {
        "viewport": args.viewport,
        "hcsr_root": str(args.hcsr_root),
        "example_count": len(rows),
        "classification_counts": dict(sorted(classification_counts.items())),
        "examples": rows,
    }
    (args.out_dir / "summary.json").write_text(
        json.dumps(report, indent=2), encoding="utf-8"
    )
    index = write_html(args.out_dir, rows, report)
    print(f"Wrote HCSR baseline summary to {index}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
