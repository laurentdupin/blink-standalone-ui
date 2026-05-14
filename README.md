# blink-standalone-ui

This repository is an exported source snapshot of the current standalone
HTML/CSS renderer cut from Chromium/Blink.

The upstream Chromium paths are preserved under `upstream/chromium/` so each
file can be compared or refreshed from a Chromium checkout. Third-party text
dependencies that are already external to Chromium are tracked as submodules:

- `upstream/chromium/third_party/freetype/src`
- `upstream/chromium/third_party/harfbuzz/src`

SDL3 is not vendored. The CMake build first tries `find_package(SDL3)` and then
fetches SDL3 into the generated build directory when needed.

## Build

From a fresh clone:

```powershell
git submodule update --init --recursive
cmake --preset x64-Release
cmake --build --preset x64-Release -- /m:8
```

The build has a single renderer path: the live Blink path. On Windows this
requires the Visual Studio Clang toolset. Visual Studio should pick up the
checked-in `CMakePresets.json` or legacy `CMakeSettings.json` configurations;
use `x64-Debug` or `x64-Release`. If configuring manually without presets, use
a ClangCL environment/toolset.

All build products and fetched SDL sources live under `build/`, which is
generated-only and ignored by Git.

Current pipeline:

`HTML/CSS input -> live Blink DummyPageHolder/Document/style/layout/paint lifecycle -> PaintArtifact metadata -> retained draw commands -> SDL demo`

Known limitations:

- Text draw payload extraction is not complete; the current SDL path uses live
  PaintArtifact metadata and a transitional text bridge.
- Blink animation time is not wired to standalone `FrameInput` yet.
- The Blink target is still being reduced and may expose additional
  link blockers as more Blink paint/layout code is enabled.

Export provenance is recorded in `manifest/origin_manifest.json` and
`manifest/copied_files.txt`. The export helper is
`tools/export_blink_standalone_ui.py`; build directories are intentionally
generated-only and are not source inputs.
