#!/usr/bin/env python3
"""Obsolete SDL snapshot runner for the removed renderer.

Use `tools/perf/run_sdl_profile_benchmark.py` for the current SDL HWND,
Viz Display, Skia GPU, and Vulkan presentation gate.
"""

from __future__ import annotations

import sys


def main() -> int:
    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
