#!/usr/bin/env python3
"""Render deterministic SDL demo states for manual visual review."""

from __future__ import annotations

import argparse
import html
import json
import subprocess
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
        "name": "43u-initial",
        "title": "43u initial",
        "html": "43u_sdl_resource_toggle_demo.html",
        "viewport": "480x260",
        "attrs": [],
        "scroll": None,
        "note": "Initial resource-backed SDL toggle page.",
    },
    {
        "name": "43u-png-on",
        "title": "43u PNG card on",
        "html": "43u_sdl_resource_toggle_demo.html",
        "viewport": "480x260",
        "attrs": ["png-card:data-state=on"],
        "scroll": None,
        "note": "Equivalent to clicking the PNG card once.",
    },
    {
        "name": "43u-svg-on",
        "title": "43u SVG card on",
        "html": "43u_sdl_resource_toggle_demo.html",
        "viewport": "480x260",
        "attrs": ["svg-card:data-state=on"],
        "scroll": None,
        "note": "Equivalent to clicking the clipped SVG card once.",
    },
    {
        "name": "43u-mask-on",
        "title": "43u mask card on",
        "html": "43u_sdl_resource_toggle_demo.html",
        "viewport": "480x260",
        "attrs": ["mask-card:data-state=on"],
        "scroll": None,
        "note": "Equivalent to clicking the masked SVG card once.",
    },
    {
        "name": "43u-all-on",
        "title": "43u all cards on",
        "html": "43u_sdl_resource_toggle_demo.html",
        "viewport": "480x260",
        "attrs": [
            "png-card:data-state=on",
            "svg-card:data-state=on",
            "mask-card:data-state=on",
        ],
        "scroll": None,
        "note": "Equivalent to clicking all configured cards.",
    },
    {
        "name": "43v-scroll-0",
        "title": "43v scroll 0",
        "html": "43v_sdl_resource_scroll_demo.html",
        "viewport": "360x260",
        "attrs": [],
        "scroll": {"x": 0, "y": 0},
        "note": "Initial resource-backed SDL scroll page.",
    },
    {
        "name": "43v-scroll-160",
        "title": "43v scroll 160",
        "html": "43v_sdl_resource_scroll_demo.html",
        "viewport": "360x260",
        "attrs": [],
        "scroll": {"x": 0, "y": 160},
        "note": "Equivalent to two 80px SDL wheel/key scroll steps.",
    },
    {
        "name": "43v-scroll-320",
        "title": "43v scroll 320",
        "html": "43v_sdl_resource_scroll_demo.html",
        "viewport": "360x260",
        "attrs": [],
        "scroll": {"x": 0, "y": 320},
        "note": "Equivalent to four 80px SDL wheel/key scroll steps.",
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
    html_path = PAINT_AUDIT_ROOT / case["html"]
    cmd = [
        str(benchmark),
        "--html-file",
        str(html_path),
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
    for attr in case.get("attrs", []):
        cmd.extend(["--attr", attr])
    scroll = case.get("scroll")
    if scroll:
        cmd.extend(["--scroll-x", str(int(scroll.get("x", 0)))])
        cmd.extend(["--scroll-y", str(int(scroll.get("y", 0)))])

    exit_code, elapsed = run(cmd, item_dir / f"{case['name']}.log", timeout)
    metrics = read_json(out_json)
    return {
        "name": case["name"],
        "title": case["title"],
        "note": case["note"],
        "fixture": str(html_path),
        "viewport": case["viewport"],
        "attrs": case.get("attrs", []),
        "scroll": scroll or {"x": 0, "y": 0},
        "exit": exit_code,
        "elapsed_seconds": round(elapsed, 3),
        "output": str(out_bmp),
        "json": str(out_json),
        "log": str(item_dir / f"{case['name']}.log"),
        "non_white_pixels": metrics.get("non_white_pixels", ""),
        "unique_color_sample": metrics.get("unique_color_sample", ""),
        "missing_resource_count": metrics.get("missing_resource_count", ""),
        "diagnostic_count": metrics.get("diagnostic_count", ""),
    }


def write_report(out_dir: Path, rows: list[dict[str, Any]]) -> None:
    summary = {
        "case_count": len(rows),
        "failed_count": sum(1 for row in rows if row["exit"] != 0),
        "cases": rows,
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    cards = []
    for row in rows:
        image = html.escape(rel(Path(row["output"]), out_dir))
        json_path = html.escape(rel(Path(row["json"]), out_dir))
        log_path = html.escape(rel(Path(row["log"]), out_dir))
        status = "ok" if row["exit"] == 0 else "bad"
        cards.append(
            "<article>"
            f"<h2>{html.escape(row['title'])}</h2>"
            f'<a href="{image}"><img src="{image}" alt="{html.escape(row["title"])}"></a>'
            f"<p>{html.escape(row['note'])}</p>"
            f'<p class="{status}">exit={row["exit"]} '
            f"non_white={html.escape(str(row['non_white_pixels']))} "
            f"unique={html.escape(str(row['unique_color_sample']))} "
            f"missing={html.escape(str(row['missing_resource_count']))}</p>"
            f'<p><a href="{json_path}">metrics</a> <a href="{log_path}">log</a></p>'
            "</article>"
        )
    page = f"""<!doctype html>
<meta charset="utf-8">
<title>SDL Demo Snapshots</title>
<style>
  body {{ font-family: system-ui, Segoe UI, sans-serif; margin: 24px; background: #f6f8fa; color: #1f2328; }}
  h1 {{ margin: 0 0 8px; font-size: 24px; }}
  .meta {{ color: #59636e; margin-bottom: 20px; }}
  main {{ display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 16px; }}
  article {{ background: white; border: 1px solid #d0d7de; padding: 12px; }}
  h2 {{ margin: 0 0 10px; font-size: 16px; }}
  img {{ width: 100%; height: auto; border: 1px solid #d8dee4; background: white; image-rendering: auto; }}
  p {{ font-size: 13px; }}
  .ok {{ color: #116329; }}
  .bad {{ color: #8c1818; }}
  a {{ color: #0969da; text-decoration: none; }}
</style>
<h1>SDL Demo Snapshots</h1>
<p class="meta">Deterministic benchmark renders for SDL demo states. These are the same host-provided attr and scroll states the viewer sends to Blink; manual SDL click/wheel testing is still separate.</p>
<main>{''.join(cards)}</main>
"""
    (out_dir / "index.html").write_text(page, encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--benchmark", type=Path, default=DEFAULT_BENCHMARK)
    parser.add_argument(
        "--out-dir",
        type=Path,
        default=ROOT / "build" / "sdl-demo-snapshots",
    )
    parser.add_argument("--timeout", type=int, default=90)
    args = parser.parse_args()

    if not args.benchmark.exists():
        raise SystemExit(f"Benchmark not found: {args.benchmark}")

    args.out_dir.mkdir(parents=True, exist_ok=True)
    rows: list[dict[str, Any]] = []
    for index, case in enumerate(CASES, 1):
        print(f"[{index}/{len(CASES)}] {case['name']}", flush=True)
        rows.append(render_case(case, args.benchmark, args.out_dir, args.timeout))
    write_report(args.out_dir, rows)
    failed = [row for row in rows if row["exit"] != 0]
    print(f"sdl_demo_snapshots passed={len(rows) - len(failed)} failed={len(failed)} out={args.out_dir}")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
