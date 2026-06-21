#!/usr/bin/env python3
"""Obsolete pre-compositor animation comparison runner.

Animation timing must be revalidated against the Chromium compositor path.
Use `tools/perf/run_standalone_perf_suite.py` as the current validation entry.
"""

from __future__ import annotations

import sys


def main() -> int:
    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
