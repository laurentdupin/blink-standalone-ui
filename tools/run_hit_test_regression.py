#!/usr/bin/env python3
"""Validate standalone hit-test entries for SDL-style interaction fixtures."""

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


CASES: list[dict[str, Any]] = [
    {
        "name": "43z-initial-hit-tests",
        "html": "43z_hover_active_hit_test_resource_basic.html",
        "viewport": "640x340",
        "points": [
            {
                "name": "overlap-topmost",
                "x": 112,
                "y": 86,
                "expected": "overlap-front",
                "note": "overlap should pick the visually top SVG resource card",
            },
            {
                "name": "overlap-back-only",
                "x": 42,
                "y": 42,
                "expected": "overlap-back",
                "note": "non-overlap area should still pick the back PNG resource card",
            },
            {
                "name": "nested-child",
                "x": 334,
                "y": 92,
                "expected": "nested-child",
                "note": "nested child should win over its id-bearing parent",
            },
            {
                "name": "nested-parent-only",
                "x": 292,
                "y": 44,
                "expected": "nested-parent",
                "note": "parent-only area should pick the parent",
            },
            {
                "name": "clipped-visible",
                "x": 36,
                "y": 248,
                "expected": "clipped-card",
                "note": "visible clipped child region should remain hittable",
            },
            {
                "name": "clipped-hidden",
                "x": 10,
                "y": 248,
                "expected": "",
                "note": "offscreen child area outside overflow clip should not hit",
            },
            {
                "name": "masked-visible",
                "x": 300,
                "y": 250,
                "expected": "masked-card",
                "note": "masked resource card should expose its visible layout bounds",
            },
            {
                "name": "svg-image",
                "x": 444,
                "y": 244,
                "expected": "svg-image",
                "note": "non-text external SVG image should be hittable",
            },
        ],
    },
    {
        "name": "43z-hover-overlap-front",
        "html": "43z_hover_active_hit_test_resource_basic.html",
        "viewport": "640x340",
        "hover": "overlap-front",
        "expected_hover": "overlap-front",
        "points": [
            {
                "name": "hovered-overlap-topmost",
                "x": 112,
                "y": 86,
                "expected": "overlap-front",
                "note": "hover styling should not disturb overlap target order",
            }
        ],
    },
    {
        "name": "43z-active-nested-child",
        "html": "43z_hover_active_hit_test_resource_basic.html",
        "viewport": "640x340",
        "hover": "nested-child",
        "active": "nested-child",
        "expected_hover": "nested-child",
        "expected_active": "nested-child",
        "points": [
            {
                "name": "active-nested-child",
                "x": 334,
                "y": 92,
                "expected": "nested-child",
                "note": "active styling should keep the child above the parent",
            }
        ],
    },
]


def run(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float]:
    start = time.time()
    completed = subprocess.run(
        cmd,
        cwd=ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        timeout=timeout,
    )
    elapsed = time.time() - start
    log_path.write_text(
        f"$ {' '.join(cmd)}\nexit={completed.returncode} elapsed={elapsed:.2f}s\n\n"
        f"{completed.stdout}",
        encoding="utf-8",
        errors="replace",
    )
    return completed.returncode, elapsed


def read_json(path: Path) -> dict[str, Any]:
    if not path.exists():
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as exc:  # pragma: no cover - diagnostic tooling path.
        return {"_json_error": str(exc)}


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


def contains(bounds: dict[str, Any], x: float, y: float) -> bool:
    left = float(bounds.get("x", 0.0))
    top = float(bounds.get("y", 0.0))
    width = float(bounds.get("width", 0.0))
    height = float(bounds.get("height", 0.0))
    return x >= left and y >= top and x < left + width and y < top + height


def hit_test(entries: list[dict[str, Any]], x: float, y: float) -> str:
    for entry in reversed(entries):
        if contains(entry.get("bounds", {}), x, y):
            return str(entry.get("element_id", ""))
    return ""


def benchmark_command(
    benchmark: Path,
    case: dict[str, Any],
    out_bmp: Path,
    out_json: Path,
) -> list[str]:
    cmd = [
        str(benchmark),
        "--html-file",
        str(PAINT_AUDIT_ROOT / case["html"]),
        "--resource-root",
        str(PAINT_AUDIT_ROOT),
        "--viewport",
        str(case["viewport"]),
        "--out",
        str(out_bmp),
        "--json",
        str(out_json),
        "--min-non-white",
        "0",
        "--skia-cpu",
    ]
    if case.get("hover"):
        cmd.extend(["--hover", str(case["hover"])])
    if case.get("active"):
        cmd.extend(["--active", str(case["active"])])
    return cmd


def render_case(
    case: dict[str, Any],
    benchmark: Path,
    out_dir: Path,
    timeout: int,
) -> dict[str, Any]:
    item_dir = out_dir / case["name"]
    item_dir.mkdir(parents=True, exist_ok=True)
    out_bmp = item_dir / f"{case['name']}.bmp"
    out_json = item_dir / f"{case['name']}.json"
    log_path = item_dir / "benchmark.log"
    code, elapsed = run(benchmark_command(benchmark, case, out_bmp, out_json), log_path, timeout)
    payload = read_json(out_json)
    render_result = payload.get("render_result", {})
    entries = render_result.get("hit_test_entries", [])
    snapshot = render_result.get("successor_snapshot", {})
    failures: list[str] = []
    checks: list[dict[str, Any]] = []
    if code != 0:
        failures.append(f"benchmark exit={code}")
    if not isinstance(entries, list):
        failures.append("hit_test_entries missing or invalid")
        entries = []

    expected_hover = case.get("expected_hover")
    if expected_hover is not None and snapshot.get("hovered_element_id") != expected_hover:
        failures.append(f"hovered_element_id={snapshot.get('hovered_element_id')!r}")
    expected_active = case.get("expected_active")
    if expected_active is not None and snapshot.get("active_element_id") != expected_active:
        failures.append(f"active_element_id={snapshot.get('active_element_id')!r}")

    for point in case.get("points", []):
        actual = hit_test(entries, float(point["x"]), float(point["y"]))
        expected = str(point.get("expected", ""))
        passed = actual == expected
        if not passed:
            failures.append(
                f"{point['name']} expected {expected!r} at "
                f"({point['x']},{point['y']}), got {actual!r}"
            )
        checks.append(
            {
                "name": point["name"],
                "x": point["x"],
                "y": point["y"],
                "expected": expected,
                "actual": actual,
                "passed": passed,
                "note": point.get("note", ""),
            }
        )

    return {
        "name": case["name"],
        "passed": not failures,
        "failures": failures,
        "elapsed_seconds": elapsed,
        "output": rel(out_bmp, out_dir),
        "json": rel(out_json, out_dir),
        "log": rel(log_path, out_dir),
        "hit_test_entries": entries,
        "checks": checks,
        "hovered_element_id": snapshot.get("hovered_element_id", ""),
        "active_element_id": snapshot.get("active_element_id", ""),
    }


def image_cell(path: Path, out_dir: Path, label: str) -> str:
    if not path.exists():
        return '<td class="missing">missing</td>'
    target = html.escape(rel(path, out_dir))
    return f'<td><a href="{target}"><img src="{target}" alt="{html.escape(label)}"></a></td>'


def write_report(out_dir: Path, rows: list[dict[str, Any]]) -> None:
    passed = sum(1 for row in rows if row["passed"])
    summary = {
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "passed": passed,
        "failed": len(rows) - passed,
        "total": len(rows),
        "rows": rows,
        "limitations": [
            "hit testing uses exported layout/clip rectangles and paint order",
            "mask alpha is not currently represented as per-pixel hit geometry",
        ],
    }
    (out_dir / "summary.json").write_text(
        json.dumps(summary, indent=2),
        encoding="utf-8",
    )

    parts = [
        "<!doctype html><meta charset=\"utf-8\"><title>Hit-test regression</title>",
        "<style>body{font-family:sans-serif;margin:24px}"
        "table{border-collapse:collapse;width:100%}td,th{border:1px solid #ddd;padding:6px;vertical-align:top}"
        "img{max-width:220px;image-rendering:auto}.pass{color:#087f4f}.fail{color:#b42318}"
        ".mono{font-family:ui-monospace,Menlo,Consolas,monospace;font-size:12px}</style>",
        f"<h1>Hit-test regression: {passed}/{len(rows)} passed</h1>",
        "<p>Limitations: mask alpha is not exported as per-pixel hit geometry; masked controls are validated through their visible layout bounds.</p>",
        "<table><thead><tr><th>case</th><th>result</th><th>state</th><th>checks</th><th>image</th><th>artifacts</th></tr></thead><tbody>",
    ]
    for row in rows:
        cls = "pass" if row["passed"] else "fail"
        checks = "<br>".join(
            html.escape(
                f"{check['name']}: expected={check['expected'] or '<none>'} actual={check['actual'] or '<none>'}"
            )
            for check in row["checks"]
        )
        failures = "<br>".join(html.escape(item) for item in row["failures"])
        state = html.escape(
            f"hover={row.get('hovered_element_id', '') or '<none>'} "
            f"active={row.get('active_element_id', '') or '<none>'}"
        )
        image_path = out_dir / row["output"]
        artifacts = (
            f"<a href=\"{html.escape(row['json'])}\">json</a><br>"
            f"<a href=\"{html.escape(row['log'])}\">log</a>"
        )
        parts.append(
            f"<tr><td>{html.escape(row['name'])}</td><td class=\"{cls}\">"
            f"{'pass' if row['passed'] else 'fail'}"
            f"{('<br>' + failures) if failures else ''}</td><td class=\"mono\">{state}</td>"
            f"<td class=\"mono\">{checks}</td>{image_cell(image_path, out_dir, row['name'])}"
            f"<td>{artifacts}</td></tr>"
        )
    parts.append("</tbody></table>")
    (out_dir / "index.html").write_text("\n".join(parts), encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Run SDL-style hit-test regression cases against benchmark output."
    )
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--timeout", type=int, default=60)
    args = parser.parse_args()

    out_dir = args.out_dir
    out_dir.mkdir(parents=True, exist_ok=True)
    if not args.benchmark.exists():
        print(f"missing benchmark binary: {args.benchmark}", file=sys.stderr)
        return 2

    rows = [render_case(case, args.benchmark, out_dir, args.timeout) for case in CASES]
    write_report(out_dir, rows)
    passed = sum(1 for row in rows if row["passed"])
    print(f"hit-test regression: {passed}/{len(rows)} passed")
    for row in rows:
        status = "PASS" if row["passed"] else "FAIL"
        print(f"{status} {row['name']} hover={row.get('hovered_element_id') or '<none>'} active={row.get('active_element_id') or '<none>'}")
        for failure in row["failures"]:
            print(f"  {failure}")
    return 0 if passed == len(rows) else 1


if __name__ == "__main__":
    raise SystemExit(main())
