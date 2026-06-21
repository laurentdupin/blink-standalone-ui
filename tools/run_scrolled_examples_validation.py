#!/usr/bin/env python3
"""Obsolete pre-compositor scrolled-example validation runner.

Scroll/toggle validation must be rebuilt on top of the Chromium compositor
metrics.  Use `tools/perf/run_standalone_perf_suite.py` for current smoke
coverage.
"""

from __future__ import annotations

import sys


def main() -> int:
    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
