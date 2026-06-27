# blink-standalone-ui

This repository is an exported source snapshot of the current standalone
HTML/CSS renderer cut from Chromium/Blink.

The upstream Chromium paths are preserved under `upstream/chromium/` so each
file can be compared or refreshed from a Chromium checkout. Third-party text
dependencies that are already external to Chromium are tracked as submodules:

- `upstream/chromium/third_party/freetype/src`
- `upstream/chromium/third_party/harfbuzz/src`
- `upstream/chromium/v8`
- `tools/depot_tools`

SDL3 is not vendored. The CMake build first tries `find_package(SDL3)` and then
fetches SDL3 into the generated build directory when needed. libxml2, Iconv,
and zlib are declared in `vcpkg.json`; configure with `VCPKG_ROOT` pointing at a
vcpkg checkout, or install vcpkg at `C:/vcpkg`.

The current Windows build requires a source-built V8/CppGC compatibility
library and matching Chromium libc++ objects generated from the pinned V8
submodule at `upstream/chromium/v8`. This is an internal Blink Oilpan/runtime
dependency, not a public JavaScript feature. The paths are explicit CMake cache
variables:

- `BLINK_STANDALONE_V8_BUILD_ROOT`
- `BLINK_STANDALONE_V8_COMPAT_OUT_DIR`
- `BLINK_STANDALONE_V8_MONOLITH_LIB`
- `BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR`

The repository includes a source-controlled wrapper target for the V8
compatibility build. By default it runs the `plan` action, which only prints
the generated work-root plan and does not download dependencies, run GN, or
compile V8:

```powershell
cmake --build build\cmake-live-image-png-ninja-vs18 --target blink_standalone_v8_compat
```

Set `BLINK_STANDALONE_V8_COMPAT_ACTION` to `prepare`, `gn-gen`, or `build` to
stop after checkout/args generation, stop after `gn gen`, or build
`v8_monolith`. The default `auto` value preserves the older
`BLINK_STANDALONE_V8_COMPAT_BUILD=ON` behavior as a full build request. Use
`BLINK_STANDALONE_V8_SYNC_DEPS=ON` only when the generated work tree should run
`gclient sync`. Tool lookup uses the declared `tools/depot_tools` submodule as
the pinned source input. For non-plan actions the wrapper clones that checkout
into the generated V8 work root and executes depot_tools from there, so
bootstrap/CIPD payloads, the generated Git cache, and V8 dependencies stay under
the build directory. The wrapper also uses generated tool shims there so Windows
build commands resolve the intended Python/Git tools. The normal renderer link
consumes `BLINK_STANDALONE_V8_MONOLITH_LIB` and Chromium libc++ objects from
that generated compatibility output. Configure can generate build files before
the output exists; renderer targets depend on a validation step that checks the
monolith and expected libc++ objects before link, and waits for
`blink_standalone_v8_compat` first when the selected action is `build`.

## Build

From a fresh clone with vcpkg installed, build the generated V8/CppGC
compatibility output first with the bootstrap ClangCL compiler, then configure a
renderer build that uses the Chromium LLVM toolchain fetched by that generated
V8 stage:

```powershell
git submodule update --init --recursive
cmake --preset x64-Release-GeneratedV8
cmake --build --preset x64-Release-GeneratedV8-v8-compat
cmake --preset x64-Release-GeneratedV8-ChromiumLLVM
cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-sdl-viewer
cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-sdl-viewer-release
cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-c-api
```

The generated V8 work copy, generated depot_tools runtime checkout, CIPD
payloads, LLVM/toolchain downloads, `v8_monolith.lib`, libc++ objects, SDL
FetchContent output, and renderer build products stay under `build/` and are
ignored by Git. The default `x64-Release` preset does not enable V8 dependency
sync; use the `x64-Release-GeneratedV8` preset only when you intend to run the
source-built V8 compatibility flow. The
`x64-Release-GeneratedV8-ChromiumLLVM` preset consumes the generated V8 output
and Chromium LLVM toolchain from that first stage; it is not expected to
configure successfully until `x64-Release-GeneratedV8-v8-compat` has produced
them.

The generated-V8 preset sets `DEPOT_TOOLS_WIN_TOOLCHAIN=0` for local Windows
self-builds. Without that environment value, Chromium depot_tools can try to
download Google's private Windows toolchain package and fail with a GCS 401.

The build has a single renderer path: the live Blink path. On Windows this
uses ClangCL. Visual Studio LLVM remains a bootstrap/compiler fallback for
generating the V8 compatibility output. The validated renderer proof build uses
the generated Chromium LLVM `clang-cl` / `lld-link`, which removes the generated
V8 libc++ Clang-version warning and smoke-tested successfully. This remains an
internal Blink/Oilpan runtime dependency, not a public JavaScript feature.

For a release-level SDL viewer, build:

```powershell
cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-sdl-viewer-release
```

That preset uses Chromium LLVM, Release optimization, disables forced
`DCHECK_ALWAYS_ON`, disables expensive DCHECK buildflags, and removes the old
standalone size/SIMD restrictions.

The recommended C API artifacts for embedders are the DLL and import library.
Build and gather the runtime package with:

```powershell
cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-c-api-package
```

The generated package directory is:

```text
build/cmake-generated-v8-chromium-llvm/package/c_api_runtime/
```

It contains the import library and all runtime sidecars an embedder should copy
beside its executable or DLL load location:

```text
blink_standalone_renderer_c_api.dll
blink_standalone_renderer_c_api.lib
libEGL.dll
libGLESv2.dll
icudtl.dat
blink_standalone_renderer_c_api_link_manifest.json
```

This DLL boundary is the intended Godot-facing package because it seals
Chromium/V8/libc++ implementation details behind the C ABI. The static archive
is still buildable for internal/advanced use as
`blink_standalone_renderer_c_api_static.lib`, but it is not the recommended
Godot artifact: Windows static archives do not fold all transitive static
dependencies and can conflict with the host runtime/STL linkage.

The intended public ABI surface is the `blink_standalone_renderer_*` C API declared in
`renderer_c_api.h`. On Windows, `dumpbin /exports` can also show two
implementation-support exports from Chromium/V8 (`GetHandleVerifier` and
`CrashForExceptionInNonABICompliantCodeRange`). Embedders should treat those as
sealed runtime support details and link only against the import library for the
documented `blink_standalone_renderer_*` API. See `docs/C_API.md` for the
embedder lifecycle, raw output, input, mutation, diagnostics, and form-state
contract.

The generated dependency manifest records both artifacts and the static-link
contract:

```text
build/cmake-generated-v8-chromium-llvm/package/c_api_runtime/blink_standalone_renderer_c_api_link_manifest.json
```

All package files, build products, and fetched SDL sources live under `build/`,
which is generated-only and ignored by Git.

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
