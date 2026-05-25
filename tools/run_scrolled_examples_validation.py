#!/usr/bin/env python3
"""Capture first/scrolled Playwright views and standalone scroll support status."""

from __future__ import annotations

import argparse
import html
import json
import subprocess
import sys
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BENCHMARK = (
    ROOT / "build" / "milestone58-nosdl" / "blink_standalone_render_benchmark_skia.exe"
)
COMPARE_SCRIPT = ROOT / "tools" / "content_aware_compare.py"


def run(cmd: list[str], log_path: Path, timeout: int) -> int:
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
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={code} elapsed={time.time() - started:.2f}s\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return code


def fixture_name(path: Path) -> str:
    return path.stem


def read_json(path: Path) -> dict:
    if not path.exists():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:
        return {"_json_error": str(exc)}


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def metric_value(path: Path, key: str) -> str:
    value = read_json(path).get(key)
    if isinstance(value, float):
        return f"{value:.4f}"
    return "" if value is None else str(value)


def image_cell(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<td class="missing">missing</td>'
    relative = html.escape(rel(path, out_dir))
    return (
        "<td>"
        f'<a href="{relative}"><img src="{relative}" alt="{html.escape(label)}"></a>'
        "</td>"
    )


def write_html(out_dir: Path, rows: list[dict]) -> Path:
    generated = time.strftime("%Y-%m-%d %H:%M:%S")
    html_rows = []
    for row in rows:
        item_dir = out_dir / row["name"]
        name = html.escape(row["name"])
        status_class = "ok" if row["benchmark_exit"] == 0 and row["playwright_first_exit"] == 0 else "bad"
        html_rows.append(
            "<tr>"
            f'<td class="{status_class}">{name}</td>'
            f"<td>{row['benchmark_exit']}</td>"
            f"<td>{row['playwright_first_exit']}</td>"
            f"<td>{row['playwright_scrolled_exit']}</td>"
            f"<td>{html.escape(str(row['first_viewport']['retained_vs_oracle_threshold']))}</td>"
            f"<td>{html.escape(str(row['first_viewport']['oracle_vs_playwright_threshold']))}</td>"
            f"<td>{html.escape(str(row['requested_scroll']['y']))}</td>"
            f"<td>{html.escape(str(row['actual_scroll'].get('scrollY', '')))}</td>"
            f"<td>{html.escape(row['standalone_scrolled_viewport_status'])}</td>"
            + image_cell(item_dir / f"{row['name']}-standalone-first-viewport.bmp", out_dir, "standalone first viewport")
            + image_cell(item_dir / f"{row['name']}-oracle-first-viewport.bmp", out_dir, "oracle first viewport")
            + image_cell(item_dir / f"{row['name']}-playwright-first-viewport.png", out_dir, "Playwright first viewport")
            + image_cell(item_dir / f"{row['name']}-playwright-scroll-y-{row['requested_scroll']['y']}.png", out_dir, "Playwright scrolled viewport")
            + f'<td><a href="{name}/{name}-audit.json">audit</a> '
            f'<a href="{name}/{name}-playwright-scroll-y-{row["requested_scroll"]["y"]}.json">scroll</a> '
            f'<a href="{name}/{name}-standalone-scroll-y-{row["requested_scroll"]["y"]}-status.json">status</a></td>'
            "</tr>"
        )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>Scrolled Examples Validation</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  h1 {{ margin: 0 0 4px; font-size: 24px; }}
  .meta {{ margin: 0 0 20px; color: #59636e; }}
  table {{ border-collapse: collapse; width: 100%; background: white; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; vertical-align: top; font-size: 12px; }}
  th {{ position: sticky; top: 0; background: #eef2f6; z-index: 1; }}
  img {{ width: 160px; max-height: 110px; object-fit: contain; background: white; border: 1px solid #d8dee4; }}
  .ok {{ background: #dafbe1; }}
  .bad {{ background: #ffebe9; }}
  .missing {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>Scrolled Examples Validation</h1>
<p class="meta">Generated {html.escape(generated)}. First-viewport metrics are real standalone/oracle/Playwright comparisons. Scrolled rows currently capture Playwright scroll state and explicitly report whether standalone can render that scroll state.</p>
<table>
  <thead><tr>
    <th>Example</th><th>Bench</th><th>PW first</th><th>PW scrolled</th>
    <th>First R/O %</th><th>First O/P %</th><th>Requested Y</th><th>Actual Y</th><th>Standalone scrolled status</th>
    <th>Standalone first</th><th>Oracle first</th><th>PW first</th><th>PW scrolled</th><th>Artifacts</th>
  </tr></thead>
  <tbody>{''.join(html_rows)}</tbody>
</table>
"""
    index = out_dir / "index.html"
    index.write_text(page, encoding="utf-8")
    return index


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--fixtures", type=Path, required=True)
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--viewport", default="1366x768")
    parser.add_argument("--scroll-y", type=int, required=True)
    parser.add_argument("--scroll-x", type=int, default=0)
    parser.add_argument("--timeout", type=int, default=90)
    args = parser.parse_args()

    fixtures = sorted(args.fixtures.glob("*.html"))
    if not fixtures:
        raise SystemExit(f"No fixtures found under {args.fixtures}")

    args.out_dir.mkdir(parents=True, exist_ok=True)
    rows = []
    for index, fixture in enumerate(fixtures, 1):
        name = fixture_name(fixture)
        print(f"[{index}/{len(fixtures)}] {name}", flush=True)
        item_dir = args.out_dir / name
        item_dir.mkdir(parents=True, exist_ok=True)
        retained = item_dir / f"{name}-standalone-first-viewport.bmp"
        oracle = item_dir / f"{name}-oracle-first-viewport.bmp"
        audit = item_dir / f"{name}-audit.json"
        setup = item_dir / f"{name}-setup.json"
        playwright_first = item_dir / f"{name}-playwright-first-viewport.png"
        playwright_scrolled = item_dir / f"{name}-playwright-scroll-y-{args.scroll_y}.png"
        playwright_scroll_state = item_dir / f"{name}-playwright-scroll-y-{args.scroll_y}.json"

        benchmark_exit = run(
            [
                str(args.benchmark),
                "--html-file",
                str(fixture),
                "--resource-root",
                str(args.fixtures),
                "--viewport",
                args.viewport,
                "--out",
                str(retained),
                "--dump-paint-artifact",
                str(audit),
                "--dump-page-setup",
                str(setup),
                "--paint-oracle=skia-paint-record",
                "--oracle-out",
                str(oracle),
                "--debug-command-coverage",
                "--strict-text-blob-typefaces",
                "--skia-cpu",
            ],
            item_dir / f"{name}-benchmark.log",
            args.timeout,
        )
        first_exit = run(
            [
                "node",
                str(ROOT / "tools" / "playwright_screenshot.cjs"),
                "--html-file",
                str(fixture),
                "--out",
                str(playwright_first),
                "--viewport",
                args.viewport,
            ],
            item_dir / f"{name}-playwright-first.log",
            args.timeout,
        )
        scrolled_exit = run(
            [
                "node",
                str(ROOT / "tools" / "playwright_screenshot.cjs"),
                "--html-file",
                str(fixture),
                "--out",
                str(playwright_scrolled),
                "--viewport",
                args.viewport,
                "--scroll-x",
                str(args.scroll_x),
                "--scroll-y",
                str(args.scroll_y),
                "--out-json",
                str(playwright_scroll_state),
            ],
            item_dir / f"{name}-playwright-scroll-y-{args.scroll_y}.log",
            args.timeout,
        )
        retained_oracle = item_dir / f"{name}-retained-vs-oracle-first-viewport.json"
        oracle_playwright = item_dir / f"{name}-oracle-vs-playwright-first-viewport.json"
        retained_oracle_exit = None
        oracle_playwright_exit = None
        if retained.exists() and oracle.exists():
            retained_oracle_exit = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(retained),
                    "--playwright",
                    str(oracle),
                    "--out-json",
                    str(retained_oracle),
                    "--out-dir",
                    str(item_dir / "retained-vs-oracle-first-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{name}-retained-vs-oracle-first-viewport.log",
                args.timeout,
            )
        if oracle.exists() and playwright_first.exists():
            oracle_playwright_exit = run(
                [
                    sys.executable,
                    str(COMPARE_SCRIPT),
                    "--standalone",
                    str(oracle),
                    "--playwright",
                    str(playwright_first),
                    "--out-json",
                    str(oracle_playwright),
                    "--out-dir",
                    str(item_dir / "oracle-vs-playwright-first-crops"),
                    "--compare-background",
                    "auto-corners",
                ],
                item_dir / f"{name}-oracle-vs-playwright-first-viewport.log",
                args.timeout,
            )
        standalone_scroll_status = {
            "standalone_scrolled_viewport_supported": False,
            "standalone_scrolled_viewport_status": "unsupported_missing_real_blink_scroll_offset_input",
            "requested_scroll": {"x": args.scroll_x, "y": args.scroll_y},
            "reason": (
                "render_benchmark and the live Blink PaintArtifact probe do not expose a "
                "real document scroll-offset input before lifecycle/paint. Comparing an "
                "unscrolled standalone bitmap or a crop against scrolled Playwright would "
                "not validate Blink scroll state."
            ),
            "next_real_fix": (
                "plumb scroll offsets into the standalone Blink frame/view before style, "
                "layout, prepaint, and paint, then compare the resulting viewport artifact"
            ),
        }
        standalone_scroll_path = item_dir / f"{name}-standalone-scroll-y-{args.scroll_y}-status.json"
        standalone_scroll_path.write_text(json.dumps(standalone_scroll_status, indent=2), encoding="utf-8")
        actual_scroll = read_json(playwright_scroll_state)
        row = {
            "name": name,
            "fixture": str(fixture),
            "viewport": args.viewport,
            "requested_scroll": {"x": args.scroll_x, "y": args.scroll_y},
            "actual_scroll": actual_scroll,
            "benchmark_exit": benchmark_exit,
            "playwright_first_exit": first_exit,
            "playwright_scrolled_exit": scrolled_exit,
            "retained_vs_oracle_first_exit": retained_oracle_exit,
            "oracle_vs_playwright_first_exit": oracle_playwright_exit,
            "first_viewport": {
                "retained_vs_oracle_threshold": metric_value(
                    retained_oracle, "thresholded_changed_percent_full_viewport"
                ),
                "oracle_vs_playwright_threshold": metric_value(
                    oracle_playwright, "thresholded_changed_percent_full_viewport"
                ),
            },
            **standalone_scroll_status,
            "artifacts": {
                "standalone_first_viewport": str(retained.relative_to(args.out_dir)),
                "oracle_first_viewport": str(oracle.relative_to(args.out_dir)),
                "playwright_first_viewport": str(playwright_first.relative_to(args.out_dir)),
                "playwright_scrolled_viewport": str(playwright_scrolled.relative_to(args.out_dir)),
                "playwright_scroll_state": str(playwright_scroll_state.relative_to(args.out_dir)),
                "standalone_scroll_status": str(standalone_scroll_path.relative_to(args.out_dir)),
            },
        }
        rows.append(row)

    summary = args.out_dir / "summary.json"
    summary.write_text(json.dumps(rows, indent=2), encoding="utf-8")
    index = write_html(args.out_dir, rows)
    print(f"Wrote {summary}")
    print(f"Wrote {index}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
