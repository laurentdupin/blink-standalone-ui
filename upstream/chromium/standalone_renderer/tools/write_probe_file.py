#!/usr/bin/env python3
import os
import sys


def main():
    for path in sys.argv[1:]:
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "wb") as handle:
            handle.write(b"\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
