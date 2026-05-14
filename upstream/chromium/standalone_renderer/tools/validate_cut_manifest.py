#!/usr/bin/env python3
"""Validate the standalone renderer cut manifest against the local checkout."""

from __future__ import annotations

import argparse
import json
import pathlib
import sys


REQUIRED_TOP_LEVEL_KEYS = {
    "name",
    "runtime_policy",
    "public_boundaries",
    "keep_paths",
    "blocked_surfaces",
    "shim_boundaries",
}

REQUIRED_RUNTIME_POLICIES = {
    "javascript_execution": "blocked",
    "network_access": "blocked",
    "filesystem_resource_loading": "blocked",
    "gpu_presentation": "blocked",
    "browser_process_services": "blocked",
    "resource_loading": "caller_asset_provider_only",
}

REQUIRED_PUBLIC_BOUNDARIES = {
    "RendererCreateInfo",
    "RendererState",
    "FrameInput",
    "AssetProvider",
    "RenderResult",
    "DrawCommandList",
}

REQUIRED_SHIMS = {
    "ChromeClient",
    "LocalFrameClient",
    "DocumentLoader",
    "ResourceFetcher",
    "ScriptController",
    "Scheduler",
    "PaintArtifact",
}


def load_manifest(path: pathlib.Path) -> dict[str, object]:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError as error:
        raise ValueError(f"{path}: invalid JSON: {error}") from error


def validate_manifest(manifest: dict[str, object],
                      chromium_root: pathlib.Path | None) -> list[str]:
    failures: list[str] = []

    missing_keys = REQUIRED_TOP_LEVEL_KEYS - set(manifest)
    for key in sorted(missing_keys):
        failures.append(f"missing top-level key: {key}")

    runtime_policy = manifest.get("runtime_policy", {})
    if not isinstance(runtime_policy, dict):
        failures.append("runtime_policy must be an object")
    else:
        for key, expected in REQUIRED_RUNTIME_POLICIES.items():
            actual = runtime_policy.get(key)
            if actual != expected:
                failures.append(
                    f"runtime_policy.{key} should be {expected!r}, got {actual!r}")

    public_boundaries = set(manifest.get("public_boundaries", []))
    for boundary in sorted(REQUIRED_PUBLIC_BOUNDARIES - public_boundaries):
        failures.append(f"missing public boundary: {boundary}")

    keep_paths = manifest.get("keep_paths", [])
    if not isinstance(keep_paths, list) or not keep_paths:
        failures.append("keep_paths must be a non-empty list")
    elif chromium_root:
        for entry in keep_paths:
            if not isinstance(entry, dict):
                failures.append("keep_paths entries must be objects")
                continue
            path = entry.get("path")
            if not isinstance(path, str):
                failures.append("keep_paths entry is missing string path")
                continue
            if entry.get("required", False) and not (chromium_root / path).exists():
                failures.append(f"required keep path is missing: {path}")

    shim_surfaces = {
        entry.get("surface")
        for entry in manifest.get("shim_boundaries", [])
        if isinstance(entry, dict)
    }
    for shim in sorted(REQUIRED_SHIMS - shim_surfaces):
        failures.append(f"missing shim boundary: {shim}")

    return failures


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", required=True)
    parser.add_argument("--chromium-root")
    args = parser.parse_args()

    manifest_path = pathlib.Path(args.manifest).resolve()
    chromium_root = (
        pathlib.Path(args.chromium_root).resolve()
        if args.chromium_root
        else None
    )

    try:
        manifest = load_manifest(manifest_path)
    except ValueError as error:
        print(error, file=sys.stderr)
        return 1

    failures = validate_manifest(manifest, chromium_root)
    if failures:
        for failure in failures:
            print(failure, file=sys.stderr)
        return 1

    print(f"validated cut manifest: {manifest_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
