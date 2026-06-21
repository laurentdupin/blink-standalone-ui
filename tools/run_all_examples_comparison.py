#!/usr/bin/env python3
"""Obsolete pre-compositor example comparison runner.

Use `tools/perf/run_standalone_perf_suite.py` for compositor benchmark
validation.
"""

from __future__ import annotations

import sys


def main() -> int:
    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
