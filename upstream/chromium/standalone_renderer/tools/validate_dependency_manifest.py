#!/usr/bin/env python3
"""Validates the source dependency manifest used by production builds."""

import argparse
import json
import pathlib
import sys


REQUIRED_DEP_KEYS = {
    "name",
    "role",
    "source_required_for_production",
    "local_path",
    "preferred_build",
}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", required=True)
    args = parser.parse_args()

    manifest_path = pathlib.Path(args.manifest)
    data = json.loads(manifest_path.read_text(encoding="utf-8"))

    errors = []
    if not data.get("policy"):
        errors.append("missing policy")
    if "prototype_binary_packages_allowed" not in data:
        errors.append("missing prototype package policy")

    dependencies = data.get("dependencies")
    if not isinstance(dependencies, list) or not dependencies:
        errors.append("dependencies must be a non-empty list")
    else:
        seen_names = set()
        for index, dependency in enumerate(dependencies):
            if not isinstance(dependency, dict):
                errors.append(f"dependency {index} must be an object")
                continue
            missing = sorted(REQUIRED_DEP_KEYS - dependency.keys())
            if missing:
                errors.append(
                    f"dependency {index} missing keys: {', '.join(missing)}"
                )
            name = dependency.get("name")
            if not isinstance(name, str) or not name:
                errors.append(f"dependency {index} has invalid name")
            elif name in seen_names:
                errors.append(f"duplicate dependency name: {name}")
            else:
                seen_names.add(name)
            if dependency.get("source_required_for_production") is not True:
                errors.append(
                    f"dependency {name or index} must require source for production"
                )

    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
