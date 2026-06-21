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

Run the compositor benchmark and SDL presentation validation with:

```powershell
python tools\perf\run_standalone_perf_suite.py --limit 8 --out-dir build\perf\compositor-smoke

python tools\perf\run_sdl_profile_benchmark.py --out-dir build\perf\sdl-compositor-smoke

build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --html-file upstream\chromium\standalone_renderer\testdata\paint_audit\00_text_only.html --resource-root upstream\chromium\standalone_renderer\testdata\paint_audit --viewport 320x200 --quit-after-ms 1500
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

`HTML/CSS input -> Blink lifecycle -> PaintArtifactCompositor -> cc -> GPU raster/shared image -> Viz Display/SkiaRenderer GPU -> Vulkan -> SDL HWND`

Known limitations:

- The SDL viewer is host-only: it owns the window, native HWND, input/event
  pump, resize events, and frame scheduling. It does not upload or present
  rendered pixels through SDL textures.
- Benchmark no-HWND mode can exercise Blink, cc, GPU raster, and Viz submit
  diagnostics, but full Viz Display/Skia GPU presentation requires the SDL HWND.
- The Blink target is still being reduced and may expose additional
  link blockers as more Blink paint/layout code is enabled.

Export provenance is recorded in `manifest/origin_manifest.json` and
`manifest/copied_files.txt`. The export helper is
`tools/export_blink_standalone_ui.py`; build directories are intentionally
generated-only and are not source inputs.
