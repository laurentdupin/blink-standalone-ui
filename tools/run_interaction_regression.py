#!/usr/bin/env python3
"""Validate focused Standalone Blink Widget interaction behavior."""

from __future__ import annotations

import argparse
import html
import json
import subprocess
import sys
import time
from pathlib import Path
from typing import Any, Callable


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

FOCUS_HTML = (
    "<!doctype html><style>"
    "body{margin:0}.box{margin:32px;width:100px;height:48px;background:#ccc}"
    ".box:focus{background:rgb(0,255,0)}"
    "</style><div id='target' data-debug-id='target' class='box' tabindex='0'></div>"
)


def base_command(benchmark: Path, case: dict[str, Any], out_bmp: Path, out_json: Path) -> list[str]:
    cmd = [str(benchmark)]
    if "html" in case:
        cmd.extend(["--html", str(case["html"])])
    else:
        cmd.extend(["--html-file", str(PAINT_AUDIT_ROOT / case["html_file"])])
        cmd.extend(["--resource-root", str(PAINT_AUDIT_ROOT)])
    cmd.extend(
        [
            "--viewport",
            str(case["viewport"]),
            "--incremental",
            "--skia-cpu",
            "--out",
            str(out_bmp),
            "--json",
            str(out_json),
        ]
    )
    if pointer := case.get("previous_pointer"):
        cmd.extend(["--previous-pointer", pointer])
    if case.get("previous_pointer_down"):
        cmd.append("--previous-pointer-down")
    if pointer := case.get("pointer"):
        cmd.extend(["--pointer", pointer])
    if case.get("pointer_down"):
        cmd.append("--pointer-down")
    if wheel := case.get("wheel"):
        cmd.extend(["--wheel", wheel])
    return cmd


def run_command(cmd: list[str], log_path: Path, timeout: int) -> tuple[int, float]:
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
        output = exc.stdout if isinstance(exc.stdout, str) else ""
        output += f"\nTIMEOUT after {timeout}s\n"
        code = 124
    elapsed = time.time() - started
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


def audit(payload: dict[str, Any]) -> dict[str, Any]:
    raw = payload.get("render_result", {}).get("raw_paint_artifact_audit_json", {})
    return raw if isinstance(raw, dict) else {}


def pointer(payload: dict[str, Any]) -> dict[str, Any]:
    value = audit(payload).get("pointer_interaction", {})
    return value if isinstance(value, dict) else {}


def wheel(payload: dict[str, Any]) -> dict[str, Any]:
    value = audit(payload).get("wheel_scroll_diagnostics", {})
    return value if isinstance(value, dict) else {}


def document_scroll(payload: dict[str, Any]) -> dict[str, Any]:
    value = audit(payload).get("document_scroll_diagnostics", {})
    return value if isinstance(value, dict) else {}


def controls(payload: dict[str, Any]) -> list[dict[str, Any]]:
    value = audit(payload).get("form_control_diagnostics", {}).get("controls", [])
    if isinstance(value, list):
        return [item for item in value if isinstance(item, dict)]
    if isinstance(value, dict):
        return [value]
    return []


def control_by_debug_id(payload: dict[str, Any], debug_id: str) -> dict[str, Any]:
    for control in controls(payload):
        if control.get("data_debug_id") == debug_id:
            return control
    return {}


def scrollable_entry(payload: dict[str, Any], element_id: str) -> dict[str, Any]:
    entries = payload.get("render_result", {}).get("scrollable_element_entries", [])
    if not isinstance(entries, list):
        return {}
    for entry in entries:
        if isinstance(entry, dict) and entry.get("element_id") == element_id:
            return entry
    return {}


def nested_number(value: dict[str, Any], *path: str) -> float:
    current: Any = value
    for key in path:
        if not isinstance(current, dict):
            return 0.0
        current = current.get(key)
    try:
        return float(current)
    except (TypeError, ValueError):
        return 0.0


def expect_equal(failures: list[str], actual: Any, expected: Any, label: str) -> None:
    if actual != expected:
        failures.append(f"{label}: expected {expected!r}, got {actual!r}")


def expect_true(failures: list[str], actual: Any, label: str) -> None:
    if actual is not True:
        failures.append(f"{label}: expected true, got {actual!r}")


def expect_false(failures: list[str], actual: Any, label: str) -> None:
    if actual is not False:
        failures.append(f"{label}: expected false, got {actual!r}")


def expect_number(
    failures: list[str],
    actual: float,
    expected: float,
    label: str,
    tolerance: float = 0.01,
) -> None:
    if abs(actual - expected) > tolerance:
        failures.append(f"{label}: expected {expected}, got {actual}")


def check_focus(payload: dict[str, Any], failures: list[str]) -> None:
    p = pointer(payload)
    expect_equal(failures, p.get("status"), "applied_to_blink_hit_test_target", "pointer status")
    expect_true(failures, p.get("focus_applied_to_blink"), "focus applied")
    expect_equal(failures, p.get("focused_element_id"), "target", "focused element")
    expect_equal(
        failures,
        p.get("focus_status"),
        "applied_to_blink_hit_test_target",
        "focus status",
    )


def check_checkbox_clicked(payload: dict[str, Any], failures: list[str]) -> None:
    p = pointer(payload)
    expect_equal(
        failures,
        p.get("activation_status"),
        "applied_blink_default_activation",
        "activation status",
    )
    expect_true(failures, p.get("activation_applied_to_blink"), "activation applied")
    expect_true(failures, control_by_debug_id(payload, "target").get("checked"), "checkbox checked")


def check_checkbox_mismatch(payload: dict[str, Any], failures: list[str]) -> None:
    p = pointer(payload)
    expect_false(failures, p.get("activation_applied_to_blink"), "activation applied")
    expect_equal(
        failures,
        p.get("activation_status"),
        "no_activation_behavior_at_pointer_up",
        "activation status",
    )
    expect_false(failures, control_by_debug_id(payload, "target").get("checked"), "checkbox checked")


def check_radio_clicked(payload: dict[str, Any], failures: list[str]) -> None:
    p = pointer(payload)
    expect_equal(
        failures,
        p.get("activation_status"),
        "applied_blink_default_activation",
        "activation status",
    )
    expect_false(failures, control_by_debug_id(payload, "radio-a").get("checked"), "radio-a checked")
    expect_true(failures, control_by_debug_id(payload, "radio-b").get("checked"), "radio-b checked")
    expect_true(
        failures,
        control_by_debug_id(payload, "radio-b").get("radio_group_checked"),
        "radio-b group checked",
    )


def check_root_wheel(payload: dict[str, Any], failures: list[str]) -> None:
    w = wheel(payload)
    expect_equal(
        failures,
        w.get("status"),
        "applied_to_frame_scrollable_area_relative_instant",
        "wheel status",
    )
    expect_true(failures, w.get("applied_to_blink"), "wheel applied")
    expect_false(failures, w.get("target_is_element"), "wheel target is element")
    expect_number(failures, nested_number(w, "applied", "y"), 80.0, "wheel applied y")
    expect_number(
        failures,
        nested_number(document_scroll(payload), "applied", "y"),
        80.0,
        "document scroll y",
    )


def check_overflow_wheel(payload: dict[str, Any], failures: list[str]) -> None:
    w = wheel(payload)
    expect_equal(
        failures,
        w.get("status"),
        "applied_to_element_scrollable_area_relative_instant",
        "wheel status",
    )
    expect_true(failures, w.get("applied_to_blink"), "wheel applied")
    expect_true(failures, w.get("target_is_element"), "wheel target is element")
    expect_number(failures, nested_number(w, "applied", "y"), 140.0, "wheel applied y")
    entry = scrollable_entry(payload, "scroll-panel")
    expect_number(
        failures,
        nested_number(entry, "scroll_offset", "y"),
        140.0,
        "scroll-panel offset y",
    )
    expect_number(
        failures,
        nested_number(entry, "max_scroll_offset", "y"),
        250.0,
        "scroll-panel max y",
    )


CaseCheck = Callable[[dict[str, Any], list[str]], None]


CASES: list[dict[str, Any]] = [
    {
        "name": "focus-tabindex-pointer-down",
        "html": FOCUS_HTML,
        "viewport": "180x120",
        "pointer": "60,50",
        "pointer_down": True,
        "check": check_focus,
    },
    {
        "name": "checkbox-default-activation",
        "html_file": "37_checkbox_unchecked.html",
        "viewport": "320x220",
        "previous_pointer": "61,61",
        "previous_pointer_down": True,
        "pointer": "61,61",
        "check": check_checkbox_clicked,
    },
    {
        "name": "checkbox-mismatch-no-activation",
        "html_file": "37_checkbox_unchecked.html",
        "viewport": "320x220",
        "previous_pointer": "61,61",
        "previous_pointer_down": True,
        "pointer": "150,150",
        "check": check_checkbox_mismatch,
    },
    {
        "name": "radio-default-activation",
        "html_file": "37c_radio_pair.html",
        "viewport": "340x220",
        "previous_pointer": "104,63",
        "previous_pointer_down": True,
        "pointer": "104,63",
        "check": check_radio_clicked,
    },
    {
        "name": "root-wheel-scroll",
        "html_file": "43g_incremental_scroll_basic.html",
        "viewport": "240x200",
        "wheel": "120,120,0,80",
        "check": check_root_wheel,
    },
    {
        "name": "overflow-wheel-scroll",
        "html_file": "43aa_incremental_element_scroll_panel_basic.html",
        "viewport": "360x240",
        "wheel": "80,80,0,140",
        "check": check_overflow_wheel,
    },
]


def rel(path: Path, base: Path) -> str:
    return path.relative_to(base).as_posix()


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
    code, elapsed = run_command(base_command(benchmark, case, out_bmp, out_json), log_path, timeout)
    payload = read_json(out_json)
    failures: list[str] = []
    if code != 0:
        failures.append(f"benchmark exit={code}")
    if not audit(payload):
        failures.append("raw Blink audit missing")
    check: CaseCheck = case["check"]
    check(payload, failures)
    return {
        "name": case["name"],
        "passed": not failures,
        "failures": failures,
        "elapsed_seconds": elapsed,
        "output": rel(out_bmp, out_dir),
        "json": rel(out_json, out_dir),
        "log": rel(log_path, out_dir),
        "pointer": pointer(payload),
        "wheel": wheel(payload),
        "controls": controls(payload),
        "document_scroll": document_scroll(payload),
        "scrollable_entries": payload.get("render_result", {}).get("scrollable_element_entries", []),
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
            "validates the current narrow standalone bridge, not full DOM mouse/click/wheel dispatch",
            "Blink-owned focus is asserted from raw pointer audit; successor snapshots still preserve replay fields",
            "details/summary is intentionally excluded because display-lock remains the known boundary",
        ],
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    parts = [
        "<!doctype html><meta charset=\"utf-8\"><title>Interaction regression</title>",
        "<style>body{font-family:sans-serif;margin:24px}"
        "table{border-collapse:collapse;width:100%}td,th{border:1px solid #ddd;padding:6px;vertical-align:top}"
        "img{max-width:220px}.pass{color:#087f4f}.fail{color:#b42318}"
        ".mono{font-family:ui-monospace,Menlo,Consolas,monospace;font-size:12px;white-space:pre-wrap}</style>",
        f"<h1>Interaction regression: {passed}/{len(rows)} passed</h1>",
        "<p>Scope: Blink layout hit-test pointer focus, checkable default activation, and Blink-owned wheel scroll.</p>",
        "<table><thead><tr><th>case</th><th>result</th><th>key audit</th><th>image</th><th>artifacts</th></tr></thead><tbody>",
    ]
    for row in rows:
        cls = "pass" if row["passed"] else "fail"
        failures = "<br>".join(html.escape(item) for item in row["failures"])
        key_audit = {
            "pointer": row["pointer"],
            "wheel": row["wheel"],
            "controls": row["controls"],
            "document_scroll": row["document_scroll"],
            "scrollable_entries": row["scrollable_entries"],
        }
        artifacts = (
            f"<a href=\"{html.escape(row['json'])}\">json</a><br>"
            f"<a href=\"{html.escape(row['log'])}\">log</a>"
        )
        parts.append(
            f"<tr><td>{html.escape(row['name'])}</td>"
            f"<td class=\"{cls}\">{'pass' if row['passed'] else 'fail'}"
            f"{('<br>' + failures) if failures else ''}</td>"
            f"<td class=\"mono\">{html.escape(json.dumps(key_audit, indent=2))}</td>"
            f"{image_cell(out_dir / row['output'], out_dir, row['name'])}"
            f"<td>{artifacts}</td></tr>"
        )
    parts.append("</tbody></table>")
    (out_dir / "index.html").write_text("\n".join(parts), encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Run focused Standalone Blink Widget interaction regressions."
    )
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--timeout", type=int, default=60)
    args = parser.parse_args()

    if not args.benchmark.exists():
        print(f"missing benchmark binary: {args.benchmark}", file=sys.stderr)
        return 2

    args.out_dir.mkdir(parents=True, exist_ok=True)
    rows = [render_case(case, args.benchmark, args.out_dir, args.timeout) for case in CASES]
    write_report(args.out_dir, rows)
    passed = sum(1 for row in rows if row["passed"])
    print(f"interaction regression: {passed}/{len(rows)} passed")
    for row in rows:
        status = "PASS" if row["passed"] else "FAIL"
        print(f"{status} {row['name']}")
        for failure in row["failures"]:
            print(f"  {failure}")
    return 0 if passed == len(rows) else 1


if __name__ == "__main__":
    raise SystemExit(main())
