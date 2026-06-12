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

## SDL demo

When SDL3 is available, build the optional viewer target:

```powershell
cmake --build build\cmake-live-image-png-ninja-vs18 --target blink_standalone_sdl_viewer_skia --parallel 8
```

Run the attribute-toggle demo:

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43f_incremental_attr_property_basic.html --viewport 240x200 --toggle-attr card:data-state=off,on
```

Run the multi-target click/toggle demo:

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43n_sdl_multi_toggle_demo.html --viewport 360x180 --toggle-attr card-a:data-state=off,on --toggle-attr card-b:data-state=off,on --toggle-attr card-c:data-state=off,on
```

Run the resource-backed click/toggle demo:

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43u_sdl_resource_toggle_demo.html --viewport 480x260 --toggle-attr png-card:data-state=off,on --toggle-attr svg-card:data-state=off,on --toggle-attr mask-card:data-state=off,on
```

Run the scroll demo:

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43g_incremental_scroll_basic.html --viewport 240x200 --scroll-step 80
```

Run the resource-backed scroll demo:

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43v_sdl_resource_scroll_demo.html --viewport 360x260 --scroll-step 80
```

Run the resource-backed element-scroll panel demo:

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43aa_incremental_element_scroll_panel_basic.html --resource-root upstream\chromium\standalone_renderer\testdata\paint_audit --viewport 360x240 --scroll-step 80
```

Render deterministic snapshots for the SDL resource demos:

```powershell
python tools\run_sdl_demo_snapshots.py --out-dir build\sdl-demo-snapshots
```

Open `build\sdl-demo-snapshots\index.html` to compare the initial, toggled,
and scrolled states produced by the same standalone render path that the SDL
viewer drives.

Profile the SDL viewer render path by adding `--profile`. Use a viewport of at
least `1280x720` for representative timing runs. The viewer prints a per-frame
line and an exit summary with min/avg/p95/max timings. Use
`--profile-summary-frames` to also print interval summaries. For scroll
profiling without a live manual run, add `--profile-auto-scroll-frames`.
The SDL window starts at the requested `--viewport` size by default; resizing
the window updates the real Blink viewport and recreates the render surface
instead of stretching the old texture.

```powershell
build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43u_sdl_resource_toggle_demo.html --viewport 1280x720 --toggle-attr png-card:data-state=off,on --toggle-attr svg-card:data-state=off,on --toggle-attr mask-card:data-state=off,on --profile --profile-summary-frames 60

build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43aa_incremental_element_scroll_panel_basic.html --resource-root upstream\chromium\standalone_renderer\testdata\paint_audit --viewport 1280x720 --scroll-step 80 --profile --profile-summary-frames 60 --profile-auto-scroll-frames 120

build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\49a_ui_visual_effects_resource_cards.html --resource-root upstream\chromium\standalone_renderer\testdata\paint_audit --viewport 1280x720 --scroll-step 80 --profile --profile-summary-frames 60 --profile-auto-scroll-frames 120

build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\43u_sdl_resource_toggle_demo.html --viewport 1280x720 --profile --profile-summary-frames 2 --profile-resize-to 1440x810
```

Controls:

- `Space` or `T` toggles configured `--toggle-attr` values.
- Left click toggles the configured target matching the hit element id.
- Mouse wheel scrolls the topmost hit scrollable element that can move in the
  wheel direction; otherwise it updates document scroll by `--scroll-step`.
- Arrow keys update document scroll by `--scroll-step`.
- `PageUp` and `PageDown` scroll by the viewport; `Home` returns to the top.
- Resizing the SDL window updates the rendered HTML/CSS viewport at the new
  window size.
- `Esc` or window close exits.
- `--quit-after-ms` exits after a fixed delay for explicit smoke runs.

Current pipeline:

`HTML/CSS input -> live Blink DummyPageHolder/Document/style/layout/paint lifecycle -> PaintArtifact metadata -> retained draw commands -> SDL demo`

Known limitations:

- Text draw payload extraction is not complete; the current SDL path uses live
  PaintArtifact metadata and a transitional text bridge.
- Blink animation time is wired through standalone `FrameInput` for
  deterministic snapshots and SDL animation ticks, but this is still the
  retained Skia CPU path rather than the Chromium compositor animation path.
- The Blink target is still being reduced and may expose additional
  link blockers as more Blink paint/layout code is enabled.

Export provenance is recorded in `manifest/origin_manifest.json` and
`manifest/copied_files.txt`. The export helper is
`tools/export_blink_standalone_ui.py`; build directories are intentionally
generated-only and are not source inputs.
