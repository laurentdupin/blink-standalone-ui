#!/usr/bin/env python3
"""Obsolete damage-regression runner for the removed renderer.

The active path is Chromium cc/GPU/Viz submission.  New damage validation
should consume compositor diagnostics instead of pixel upload metrics.
"""

from __future__ import annotations

import sys


def main() -> int:
    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
