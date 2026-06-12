#!/usr/bin/env python3
"""Run retained/incremental damage regression cases."""

from __future__ import annotations

import argparse
import html
import json
import subprocess
import sys
import time
from pathlib import Path
from typing import Any


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
DEFAULT_CASES = ROOT / "tools" / "damage_regression_cases.json"
COMPARE_SCRIPT = ROOT / "tools" / "content_aware_compare.py"


Rect = dict[str, int]


def run(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float]:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    start = time.time()
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
    elapsed = time.time() - start
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={code} elapsed={elapsed:.2f}s\n\n{output}",
        encoding="utf-8",
        errors="replace",
    )
    return code, elapsed


def read_json(path: Path) -> dict[str, Any]:
    if not path.exists():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:  # pragma: no cover - diagnostic tooling path.
        return {"_json_error": str(exc)}


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def parse_viewport(value: str) -> tuple[int, int]:
    width, height = value.lower().split("x", 1)
    return int(width), int(height)


def rect_area(rect: Rect) -> int:
    return int(rect.get("width", 0)) * int(rect.get("height", 0))


def normalize_rect(rect: dict[str, Any]) -> Rect:
    return {
        "x": int(rect.get("x", 0)),
        "y": int(rect.get("y", 0)),
        "width": int(rect.get("width", 0)),
        "height": int(rect.get("height", 0)),
    }


def rects_equal(left: dict[str, Any] | None, right: dict[str, Any] | None) -> bool:
    if left is None or right is None:
        return left is right
    return normalize_rect(left) == normalize_rect(right)


def rects_within_viewport(rects: list[Rect], width: int, height: int) -> bool:
    for rect in rects:
        if rect["x"] < 0 or rect["y"] < 0:
            return False
        if rect["x"] + rect["width"] > width:
            return False
        if rect["y"] + rect["height"] > height:
            return False
    return True


def rect_is_full_viewport(rect: Rect, width: int, height: int) -> bool:
    return rect["x"] == 0 and rect["y"] == 0 and rect["width"] == width and rect["height"] == height


def point_near(actual: dict[str, Any] | None, expected: dict[str, Any], tolerance: float = 0.5) -> bool:
    if actual is None:
        return False
    return (
        abs(float(actual.get("x", 0)) - float(expected.get("x", 0))) <= tolerance
        and abs(float(actual.get("y", 0)) - float(expected.get("y", 0))) <= tolerance
    )


def raw_audit(metrics: dict[str, Any]) -> dict[str, Any]:
    payload = metrics.get("render_result", {}).get("raw_paint_artifact_audit_json", {})
    if isinstance(payload, dict):
        return payload
    if isinstance(payload, str) and payload:
        try:
            return json.loads(payload)
        except Exception:
            return {}
    return {}


def has_diagnostic(metrics: dict[str, Any], needle: str) -> bool:
    diagnostics = metrics.get("diagnostics", [])
    render_diagnostics = metrics.get("render_result", {}).get("diagnostics", [])
    return any(needle in str(entry) for entry in diagnostics + render_diagnostics)


def load_manifest(path: Path) -> tuple[dict[str, dict[str, Any]], dict[str, list[str]]]:
    payload = read_json(path)
    cases = {case["name"]: case for case in payload.get("cases", [])}
    return cases, payload.get("sets", {})


def add_attrs(cmd: list[str], flag: str, attrs: list[str] | None) -> None:
    for attr in attrs or []:
        cmd.extend([flag, attr])


def add_scroll(cmd: list[str], x_flag: str, y_flag: str, scroll: dict[str, int] | None) -> None:
    if not scroll:
        return
    cmd.extend([x_flag, str(int(scroll.get("x", 0)))])
    cmd.extend([y_flag, str(int(scroll.get("y", 0)))])


def add_element_scroll(cmd: list[str], flag: str, scrolls: dict[str, dict[str, int]] | None) -> None:
    for element_id, scroll in sorted((scrolls or {}).items()):
        cmd.extend([flag, f"{element_id}:{int(scroll.get('x', 0))},{int(scroll.get('y', 0))}"])


def add_optional_value(cmd: list[str], flag: str, value: str | None) -> None:
    if value:
        cmd.extend([flag, value])


def benchmark_command(
    benchmark: Path,
    html_path: Path,
    viewport: str,
    out_path: Path,
    json_path: Path,
    *,
    attrs: list[str] | None = None,
    scroll: dict[str, int] | None = None,
    element_scroll: dict[str, dict[str, int]] | None = None,
    hover: str | None = None,
    active: str | None = None,
    previous_attrs: list[str] | None = None,
    previous_scroll: dict[str, int] | None = None,
    previous_element_scroll: dict[str, dict[str, int]] | None = None,
    previous_hover: str | None = None,
    previous_active: str | None = None,
    time_ms: int | float | None = None,
    previous_time_ms: int | float | None = None,
    incremental: bool = False,
    disable_damage_clip_grouping: bool = False,
) -> list[str]:
    cmd = [
        str(benchmark),
        "--html-file",
        str(html_path),
        "--resource-root",
        str(PAINT_AUDIT_ROOT),
        "--viewport",
        viewport,
        "--out",
        str(out_path),
        "--json",
        str(json_path),
        "--min-non-white",
        "0",
    ]
    add_attrs(cmd, "--attr", attrs)
    add_scroll(cmd, "--scroll-x", "--scroll-y", scroll)
    add_element_scroll(cmd, "--scroll-element", element_scroll)
    add_optional_value(cmd, "--hover", hover)
    add_optional_value(cmd, "--active", active)
    if time_ms is not None:
        cmd.extend(["--time-ms", str(time_ms)])
    if incremental:
        add_attrs(cmd, "--previous-attr", previous_attrs)
        add_scroll(cmd, "--previous-scroll-x", "--previous-scroll-y", previous_scroll)
        add_element_scroll(cmd, "--previous-scroll-element", previous_element_scroll)
        add_optional_value(cmd, "--previous-hover", previous_hover)
        add_optional_value(cmd, "--previous-active", previous_active)
        if previous_time_ms is not None:
            cmd.extend(["--previous-time-ms", str(previous_time_ms)])
        cmd.append("--incremental")
    if disable_damage_clip_grouping:
        cmd.append("--disable-damage-clip-grouping")
    return cmd


def compare_command(standalone: Path, reference: Path, out_json: Path, out_dir: Path) -> list[str]:
    return [
        sys.executable,
        str(COMPARE_SCRIPT),
        "--standalone",
        str(standalone),
        "--playwright",
        str(reference),
        "--out-json",
        str(out_json),
        "--out-dir",
        str(out_dir),
    ]


def evaluate_damage(
    expected: dict[str, Any],
    metrics: dict[str, Any],
    compare: dict[str, Any],
    viewport: str,
) -> tuple[bool, list[str], dict[str, Any]]:
    failures: list[str] = []
    width, height = parse_viewport(viewport)
    render_result = metrics.get("render_result", {})
    damage_rects = [normalize_rect(rect) for rect in render_result.get("damage_rects", [])]
    damage_bounds = normalize_rect(render_result.get("damage_bounds", {}))
    requires_full_redraw = bool(render_result.get("requires_full_redraw", False))
    exact = bool(compare.get("exact_pixel_identical", False))
    scrollable_entries = render_result.get("scrollable_element_entries", [])
    scrollable_by_id = {
        str(entry.get("element_id", "")): entry
        for entry in scrollable_entries
        if entry.get("element_id")
    }
    audit = raw_audit(metrics)

    if exact != bool(expected.get("exact_pixel_identical", True)):
        failures.append(f"exact_pixel_identical={exact}")
    if requires_full_redraw != bool(expected.get("requires_full_redraw", False)):
        failures.append(f"requires_full_redraw={requires_full_redraw}")

    expected_bounds = expected.get("damage_bounds")
    if expected_bounds is not None and not rects_equal(damage_bounds, expected_bounds):
        failures.append(f"damage_bounds={damage_bounds}")

    damage_class = str(expected.get("damage_class", "local"))
    if damage_class == "none":
        if damage_rects:
            failures.append(f"expected no damage, got {damage_rects}")
        if rect_area(damage_bounds) != 0:
            failures.append(f"expected empty damage bounds, got {damage_bounds}")
    else:
        if not damage_rects:
            failures.append("expected non-empty damage_rects")
        if not rects_within_viewport(damage_rects, width, height):
            failures.append(f"damage_rects outside viewport: {damage_rects}")
        if damage_class != "broad" and any(
            rect_is_full_viewport(rect, width, height) for rect in damage_rects
        ):
            failures.append(f"damage_rects include full viewport: {damage_rects}")
        if damage_class == "exposed_band":
            horizontal_band = any(rect["width"] == width and rect["height"] < height for rect in damage_rects)
            vertical_band = any(rect["height"] == height and rect["width"] < width for rect in damage_rects)
            if not (horizontal_band or vertical_band):
                failures.append(f"expected exposed band damage, got {damage_rects}")

    expected_document_scroll = expected.get("document_scroll")
    if expected_document_scroll:
        document_scroll = audit.get("document_scroll_diagnostics", {})
        expected_applied = expected_document_scroll.get("applied", {})
        fast_path_scroll = (
            has_diagnostic(metrics, "document scroll-only fast path reused retained scene")
            and point_near(
                metrics.get("render_timing_diagnostics", {}).get("scroll_input"),
                expected_applied,
            )
        )
        if not fast_path_scroll:
            if not point_near(document_scroll.get("applied"), expected_applied):
                failures.append(f"document_scroll.applied={document_scroll.get('applied')}")
            if not document_scroll.get("applied_to_blink", False):
                failures.append("document_scroll.applied_to_blink=false")

    expected_scrollables = expected.get("scrollable_elements", {})
    for element_id in expected_scrollables.get("present", []):
        if element_id not in scrollable_by_id:
            failures.append(f"missing scrollable_element_entry={element_id}")
    for element_id in expected_scrollables.get("absent", []):
        if element_id in scrollable_by_id:
            failures.append(f"unexpected scrollable_element_entry={element_id}")
    for element_id, expected_offset in expected_scrollables.get("scroll_offsets", {}).items():
        entry = scrollable_by_id.get(element_id)
        if not entry or not point_near(entry.get("scroll_offset"), expected_offset):
            failures.append(f"scrollable[{element_id}].scroll_offset={entry.get('scroll_offset') if entry else None}")
    for element_id, expected_max in expected_scrollables.get("max_scroll_offsets", {}).items():
        entry = scrollable_by_id.get(element_id)
        if not entry or not point_near(entry.get("max_scroll_offset"), expected_max):
            failures.append(f"scrollable[{element_id}].max_scroll_offset={entry.get('max_scroll_offset') if entry else None}")
    for element_id, expected_bounds in expected_scrollables.get("bounds", {}).items():
        entry = scrollable_by_id.get(element_id)
        if not entry or not rects_equal(entry.get("bounds"), expected_bounds):
            failures.append(f"scrollable[{element_id}].bounds={entry.get('bounds') if entry else None}")
    for element_id, expected_can_scroll in expected_scrollables.get("can_scroll", {}).items():
        entry = scrollable_by_id.get(element_id)
        if not entry:
            failures.append(f"scrollable[{element_id}].can_scroll=missing")
            continue
        if bool(entry.get("can_scroll_x", False)) != bool(expected_can_scroll.get("x", False)):
            failures.append(f"scrollable[{element_id}].can_scroll_x={entry.get('can_scroll_x')}")
        if bool(entry.get("can_scroll_y", False)) != bool(expected_can_scroll.get("y", False)):
            failures.append(f"scrollable[{element_id}].can_scroll_y={entry.get('can_scroll_y')}")

    details = {
        "exact_pixel_identical": exact,
        "exact_pixel_difference_count": compare.get("exact_pixel_difference_count"),
        "requires_full_redraw": requires_full_redraw,
        "damage_class": damage_class,
        "damage_bounds": damage_bounds,
        "damage_rects": damage_rects,
        "scrollable_element_entries": scrollable_entries,
    }
    return not failures, failures, details


def image_cell(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<td class="missing">missing</td>'
    target = html.escape(rel(path, out_dir))
    return f'<td><a href="{target}"><img src="{target}" alt="{html.escape(label)}"></a></td>'


def write_report(out_dir: Path, rows: list[dict[str, Any]], case_set: str) -> None:
    passed = sum(1 for row in rows if row["passed"])
    class_counts: dict[str, int] = {}
    for row in rows:
        key = str(row.get("damage_class", "unknown"))
        class_counts[key] = class_counts.get(key, 0) + 1
    summary = {
        "case_set": case_set,
        "case_count": len(rows),
        "passed_count": passed,
        "failed_count": len(rows) - passed,
        "damage_class_counts": class_counts,
        "cases": rows,
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    generated = time.strftime("%Y-%m-%d %H:%M:%S")
    class_items = "".join(
        f"<li><strong>{html.escape(name)}</strong>: {count}</li>"
        for name, count in sorted(class_counts.items())
    )
    table_rows = []
    for row in rows:
        name = html.escape(row["name"])
        status_class = "ok" if row["passed"] else "bad"
        item_dir = out_dir / row["name"]
        failures = "; ".join(row.get("failures", []))
        rects = html.escape(json.dumps(row.get("damage_rects", []), separators=(",", ":")))
        table_rows.append(
            "<tr>"
            f'<td class="{status_class}"><a href="{name}/">{name}</a></td>'
            f"<td>{'pass' if row['passed'] else 'fail'}</td>"
            f"<td>{html.escape(row.get('damage_class', ''))}</td>"
            f"<td>{html.escape(str(row.get('exact_pixel_difference_count', '')))}</td>"
            f"<td>{html.escape(str(row.get('requires_full_redraw', '')))}</td>"
            f"<td>{rects}</td>"
            f"<td>{html.escape(failures)}</td>"
            + image_cell(item_dir / "full-current.bmp", out_dir, "full current")
            + image_cell(item_dir / "incremental.bmp", out_dir, "incremental")
            + f'<td><a href="{name}/full-current.json">full json</a> '
            f'<a href="{name}/incremental.json">incremental json</a> '
            f'<a href="{name}/compare.json">compare</a> '
            f'<a href="{name}/incremental.log">log</a></td>'
            "</tr>"
        )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>Standalone Damage Regression</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f7f7f8; color: #1f2328; }}
  h1 {{ margin: 0 0 4px; font-size: 24px; }}
  .meta {{ color: #59636e; margin: 0 0 18px; }}
  .summary {{ display: grid; grid-template-columns: repeat(2, minmax(0, 1fr)); gap: 12px; margin-bottom: 18px; }}
  .card {{ background: white; border: 1px solid #d0d7de; padding: 12px 14px; }}
  .card h2 {{ font-size: 14px; margin: 0 0 8px; }}
  table {{ border-collapse: collapse; width: 100%; background: white; }}
  th, td {{ border: 1px solid #d0d7de; padding: 6px 8px; font-size: 12px; vertical-align: top; }}
  th {{ background: #eef2f6; position: sticky; top: 0; }}
  img {{ width: 140px; max-height: 100px; object-fit: contain; background: white; border: 1px solid #d8dee4; }}
  .ok {{ background: #dafbe1; }}
  .bad {{ background: #ffebe9; }}
  .missing {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>Standalone Damage Regression</h1>
<p class="meta">Generated {html.escape(generated)} for case set <strong>{html.escape(case_set)}</strong>. Each case compares incremental replay against a full current render and checks top-level damage expectations.</p>
<section class="summary">
  <div class="card">
    <h2>Run</h2>
    <ul>
      <li><strong>Cases</strong>: {len(rows)}</li>
      <li><strong>Passed</strong>: {passed}</li>
      <li><strong>Failed</strong>: {len(rows) - passed}</li>
    </ul>
  </div>
  <div class="card">
    <h2>Damage Classes</h2>
    <ul>{class_items}</ul>
  </div>
</section>
<table>
  <thead><tr>
    <th>Case</th><th>Status</th><th>Class</th><th>Exact Diff</th><th>Full Redraw</th><th>Damage Rects</th><th>Failures</th>
    <th>Full Current</th><th>Incremental</th><th>Artifacts</th>
  </tr></thead>
  <tbody>{''.join(table_rows)}</tbody>
</table>
"""
    (out_dir / "index.html").write_text(page, encoding="utf-8")


def run_case(
    case: dict[str, Any],
    benchmark: Path,
    out_dir: Path,
    timeout: int,
    compare_ungrouped: bool,
) -> dict[str, Any]:
    name = case["name"]
    item_dir = out_dir / name
    item_dir.mkdir(parents=True, exist_ok=True)
    viewport = case.get("viewport", "240x200")
    html_path = PAINT_AUDIT_ROOT / case["html"]
    full_bmp = item_dir / "full-current.bmp"
    full_json = item_dir / "full-current.json"
    incremental_bmp = item_dir / "incremental.bmp"
    incremental_json = item_dir / "incremental.json"
    compare_json = item_dir / "compare.json"
    ungrouped_bmp = item_dir / "incremental-ungrouped.bmp"
    ungrouped_json = item_dir / "incremental-ungrouped.json"
    grouped_ungrouped_compare_json = item_dir / "compare-grouped-ungrouped.json"

    current_attrs = case.get("current_attrs")
    previous_attrs = case.get("previous_attrs")
    current_scroll = case.get("current_scroll")
    previous_scroll = case.get("previous_scroll")
    current_element_scroll = case.get("current_element_scroll")
    previous_element_scroll = case.get("previous_element_scroll")
    current_hover = case.get("current_hover")
    previous_hover = case.get("previous_hover")
    current_active = case.get("current_active")
    previous_active = case.get("previous_active")
    current_time_ms = case.get("current_time_ms")
    previous_time_ms = case.get("previous_time_ms")

    full_cmd = benchmark_command(
        benchmark,
        html_path,
        viewport,
        full_bmp,
        full_json,
        attrs=current_attrs,
        scroll=current_scroll,
        element_scroll=current_element_scroll,
        hover=current_hover,
        active=current_active,
        time_ms=current_time_ms,
    )
    full_exit, full_elapsed = run(full_cmd, item_dir / "full-current.log", timeout)

    incremental_cmd = benchmark_command(
        benchmark,
        html_path,
        viewport,
        incremental_bmp,
        incremental_json,
        attrs=current_attrs,
        scroll=current_scroll,
        element_scroll=current_element_scroll,
        hover=current_hover,
        active=current_active,
        previous_attrs=previous_attrs,
        previous_scroll=previous_scroll,
        previous_element_scroll=previous_element_scroll,
        previous_hover=previous_hover,
        previous_active=previous_active,
        time_ms=current_time_ms,
        previous_time_ms=previous_time_ms,
        incremental=True,
    )
    incremental_exit, incremental_elapsed = run(incremental_cmd, item_dir / "incremental.log", timeout)

    compare_cmd = compare_command(incremental_bmp, full_bmp, compare_json, item_dir / "compare-crops")
    compare_exit, compare_elapsed = run(compare_cmd, item_dir / "compare.log", timeout)

    ungrouped_exit = 0
    ungrouped_elapsed = 0.0
    grouped_ungrouped_compare_exit = 0
    grouped_ungrouped_compare: dict[str, Any] = {}
    if compare_ungrouped:
        ungrouped_cmd = benchmark_command(
            benchmark,
            html_path,
            viewport,
            ungrouped_bmp,
            ungrouped_json,
            attrs=current_attrs,
            scroll=current_scroll,
            element_scroll=current_element_scroll,
            hover=current_hover,
            active=current_active,
            previous_attrs=previous_attrs,
            previous_scroll=previous_scroll,
            previous_element_scroll=previous_element_scroll,
            previous_hover=previous_hover,
            previous_active=previous_active,
            time_ms=current_time_ms,
            previous_time_ms=previous_time_ms,
            incremental=True,
            disable_damage_clip_grouping=True,
        )
        ungrouped_exit, ungrouped_elapsed = run(
            ungrouped_cmd, item_dir / "incremental-ungrouped.log", timeout
        )
        grouped_ungrouped_compare_cmd = compare_command(
            incremental_bmp,
            ungrouped_bmp,
            grouped_ungrouped_compare_json,
            item_dir / "compare-grouped-ungrouped-crops",
        )
        grouped_ungrouped_compare_exit, _ = run(
            grouped_ungrouped_compare_cmd,
            item_dir / "compare-grouped-ungrouped.log",
            timeout,
        )
        grouped_ungrouped_compare = read_json(grouped_ungrouped_compare_json)

    metrics = read_json(incremental_json)
    compare = read_json(compare_json)
    passed, failures, details = evaluate_damage(case.get("expected", {}), metrics, compare, viewport)
    if full_exit != 0:
        failures.append(f"full benchmark exit={full_exit}")
    if incremental_exit != 0:
        failures.append(f"incremental benchmark exit={incremental_exit}")
    if compare_exit != 0:
        failures.append(f"compare exit={compare_exit}")
    if compare_ungrouped:
        if ungrouped_exit != 0:
            failures.append(f"ungrouped benchmark exit={ungrouped_exit}")
        if grouped_ungrouped_compare_exit != 0:
            failures.append(f"grouped/ungrouped compare exit={grouped_ungrouped_compare_exit}")
        if not grouped_ungrouped_compare.get("exact_pixel_identical", False):
            failures.append(
                "grouped/ungrouped exact_pixel_identical="
                f"{grouped_ungrouped_compare.get('exact_pixel_identical')}"
            )
    passed = passed and not failures

    return {
        "name": name,
        "html": str(html_path),
        "viewport": viewport,
        "passed": passed,
        "failures": failures,
        "full_current_output": str(full_bmp),
        "incremental_output": str(incremental_bmp),
        "full_current_json": str(full_json),
        "incremental_json": str(incremental_json),
        "compare_json": str(compare_json),
        "ungrouped_output": str(ungrouped_bmp) if compare_ungrouped else "",
        "ungrouped_json": str(ungrouped_json) if compare_ungrouped else "",
        "grouped_ungrouped_compare_json": str(grouped_ungrouped_compare_json) if compare_ungrouped else "",
        "full_exit": full_exit,
        "incremental_exit": incremental_exit,
        "compare_exit": compare_exit,
        "ungrouped_exit": ungrouped_exit if compare_ungrouped else None,
        "grouped_ungrouped_compare_exit": grouped_ungrouped_compare_exit if compare_ungrouped else None,
        "full_elapsed_seconds": round(full_elapsed, 3),
        "incremental_elapsed_seconds": round(incremental_elapsed, 3),
        "ungrouped_elapsed_seconds": round(ungrouped_elapsed, 3) if compare_ungrouped else None,
        "compare_elapsed_seconds": round(compare_elapsed, 3),
        "grouped_ungrouped_exact_pixel_identical": grouped_ungrouped_compare.get("exact_pixel_identical") if compare_ungrouped else None,
        "damage_grouping_metrics": metrics.get("render_timing_diagnostics", {}),
        **details,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--cases-file", type=Path, default=DEFAULT_CASES)
    parser.add_argument("--case-set", default="damage")
    parser.add_argument("--out-dir", type=Path, default=ROOT / "build" / "damage-regression" / "damage")
    parser.add_argument("--timeout", type=int, default=90)
    parser.add_argument(
        "--compare-ungrouped",
        action="store_true",
        help="also compare grouped incremental replay against ungrouped incremental replay",
    )
    args = parser.parse_args()

    if not args.benchmark.exists():
        raise SystemExit(f"Benchmark not found: {args.benchmark}")

    cases_by_name, sets = load_manifest(args.cases_file)
    selected_names = sets.get(args.case_set)
    if not selected_names:
        raise SystemExit(f"Unknown or empty case set '{args.case_set}' in {args.cases_file}")

    args.out_dir.mkdir(parents=True, exist_ok=True)
    rows = []
    for index, name in enumerate(selected_names, 1):
        print(f"[{index}/{len(selected_names)}] {name}", flush=True)
        rows.append(
            run_case(
                cases_by_name[name],
                args.benchmark,
                args.out_dir,
                args.timeout,
                args.compare_ungrouped,
            )
        )
    write_report(args.out_dir, rows, args.case_set)
    failed = [row for row in rows if not row["passed"]]
    print(f"damage_regression passed={len(rows) - len(failed)} failed={len(failed)} out={args.out_dir}")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
