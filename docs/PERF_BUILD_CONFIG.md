# Standalone Renderer Performance Build Configuration

This document records the checked/current build and the dedicated perf benchmark preset. The perf preset is intended to move the benchmark closer to a Chromium release benchmark build without changing renderer behavior.

## Build Presets

### Checked/current

- Preset/path: existing local build under `build/cmake-live-image-png-ninja-vs18`
- Benchmark: `build/cmake-live-image-png-ninja-vs18/blink_standalone_render_benchmark_skia.exe`
- CMake cache observed in this workspace: `CMAKE_BUILD_TYPE=Debug`
- Target: `blink_standalone_render_benchmark_skia`
- Source: `upstream/chromium/standalone_renderer/examples/compositor_benchmark.cc`
- Purpose: correctness and development checks.

The checked/current benchmark keeps the historical measurement-hostile defines:

- `DCHECK_ALWAYS_ON=1`
- `SK_ENABLE_OPTIMIZE_SIZE=1`
- `CPU_NO_SIMD=1`
- `SKCMS_DISABLE_HSW=1`
- `SKCMS_DISABLE_SKX=1`

### Perf

- Preset: `x64-Perf`
- Build preset: `cmake --build --preset x64-Perf --target blink_standalone_render_benchmark_skia`
- Build directory: `build/cmake-live-image-png-ninja-vs18-perf`
- Benchmark: `build/cmake-live-image-png-ninja-vs18-perf/blink_standalone_render_benchmark_skia.exe`
- CMake build type: `Release`
- CMake option: `BLINK_STANDALONE_PERF_BUILD=ON`
- SDL viewer: disabled for this preset with `BLINK_STANDALONE_BUILD_SDL_VIEWER=OFF`

Current post-`1640521e` cache check after the Release crash-boundary matrix:

- `BLINK_STANDALONE_OPTIMIZE_CHROMIUM=ON`
- `BLINK_STANDALONE_OPTIMIZE_CODECS=ON`
- `BLINK_STANDALONE_OPTIMIZE_BOUNDARY=ON`
- `BLINK_STANDALONE_OPTIMIZE_APP=ON`

The perf preset removes these forced benchmark-hostile defines from the benchmark target:

- `SK_ENABLE_OPTIMIZE_SIZE=1`
- `CPU_NO_SIMD=1`
- `SKCMS_DISABLE_HSW=1`
- `SKCMS_DISABLE_SKX=1`

The perf preset still keeps `DCHECK_ALWAYS_ON=1`.

### Release-level SDL viewer

- Build preset: `cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-sdl-viewer-release`
- CMake option: `BLINK_STANDALONE_RELEASE_LEVEL_VIEWER=ON`
- CMake build type: `Release`
- Compiler/linker: generated Chromium LLVM `clang-cl` / `lld-link`
- Output directory: `build/cmake-generated-v8-chromium-llvm-viewer-release`

This viewer preset is the no-DCHECK, release-level SDL viewer path. It disables
forced `DCHECK_ALWAYS_ON`, overrides generated debugging buildflags so expensive
DCHECKs are off, and removes the standalone size/SIMD restrictions
(`SK_ENABLE_OPTIMIZE_SIZE`, `CPU_NO_SIMD`, `SKCMS_DISABLE_HSW`,
`SKCMS_DISABLE_SKX`). It also includes the Skia/skcms optimized and utility
sources required when those restrictions are removed.

## Chromium Comparison Notes

The comparison below is based on the Chromium sources vendored under `upstream/chromium`.

- `upstream/chromium/build/config/dcheck_always_on.gni` keeps DCHECKs on by default for non-official Chromium builds. A release-like benchmark should eventually make this an explicit choice instead of forcing `DCHECK_ALWAYS_ON` in the benchmark target.
- `upstream/chromium/third_party/skia/gn/skia.gni` controls `skia_enable_optimize_size`; it is not a blanket requirement for release benchmarking. The perf preset removes the standalone forced `SK_ENABLE_OPTIMIZE_SIZE=1`.
- `upstream/chromium/third_party/skia/modules/skcms/BUILD.gn` compiles skcms HSW/SKX x86 paths for supported x64 builds instead of defining `SKCMS_DISABLE_HSW` and `SKCMS_DISABLE_SKX`. The perf preset follows that direction by adding the skcms HSW/SKX translation units with the corresponding clang AVX flags.
- `upstream/chromium/third_party/zlib/BUILD.gn` only defines `CPU_NO_SIMD` when x86/x64 and ARM optimizations are unavailable. The perf preset removes the standalone forced `CPU_NO_SIMD=1`.
- `upstream/chromium/third_party/skia/gn/core.gni` includes Skia optimized and optional source groups that are omitted by the size-optimized standalone build. The perf preset adds the Skia opt/utility sources required to link when `SK_ENABLE_OPTIMIZE_SIZE` is not forced.

## Measurement Risks

- `DCHECK_ALWAYS_ON=1` remains active in checked/current and perf builds, so assertion overhead can still perturb benchmark numbers. Use the release-level SDL viewer preset when measuring the interactive viewer without forced DCHECKs.
- The perf preset is optimized (`Release`, clang-cl `/O2`) but does not claim Chromium official-build parity: no PGO, no LTO audit, no component/official-build GN equivalence, and no full Chromium allocator/process configuration match.
- The standalone CMake source manifest is still manually maintained rather than generated from GN target graphs.
- The strict benchmark path uses the Chromium compositor runtime: Blink lifecycle, PaintArtifactCompositor, cc, GPU raster/shared image, and Viz submission.
- The benchmark performs a full lifecycle and one compositor frame submission per invocation.
- The benchmark has no HWND and therefore does not create a Viz Display. The SDL viewer presents through Viz Display/SkiaRenderer GPU and Vulkan using the SDL HWND; SDL texture upload is not part of the production path.
- `wall_ms` is the Python command/process envelope around `subprocess.Popen(...).communicate()`. It includes process creation, Windows executable image load, static initialization before benchmark `main`, benchmark work, stdout/stderr draining, and process exit/teardown.
- `process_elapsed_ms` starts at benchmark `main` and excludes Python orchestration.
- `advance_frame_ms` covers the measured Chromium compositor `AdvanceFrame` call.
- Resource-backed pages depend on the `--resource-root` path passed to the benchmark. The perf suite passes the paint audit root by default.
- The retained-renderer corpus numbers that used `cold_presented_frame_ms` and CPU replay timings are historical only. The compositor corpus should be regenerated from `process_elapsed_ms` and `advance_frame_ms`.

## Diagnostic Optimization Matrix

The Release crash-boundary validation temporarily rebuilt `x64-Perf` with one optimization group disabled at a time:

- `BLINK_STANDALONE_OPTIMIZE_BOUNDARY=OFF`
- `BLINK_STANDALONE_OPTIMIZE_CODECS=OFF`
- `BLINK_STANDALONE_OPTIMIZE_CHROMIUM=OFF`

Those `/Od` variants are diagnostic boundaries only. They are not accepted performance solutions and the primary `x64-Perf` build was restored to all optimization groups enabled after the matrix.

## Commands

Configure and build the checked/current benchmark:

```powershell
cmake --build build\cmake-live-image-png-ninja-vs18 --target blink_standalone_render_benchmark_skia --config Release
```

Configure and build the perf benchmark:

```powershell
cmake --preset x64-Perf
cmake --build --preset x64-Perf --target blink_standalone_render_benchmark_skia
```

Run the perf suite against the perf preset:

```powershell
python tools\perf\run_standalone_perf_suite.py --benchmark build\cmake-live-image-png-ninja-vs18-perf\blink_standalone_render_benchmark_skia.exe --out-dir build\perf\x64-Perf --build-config-name x64-Perf
```

For long corpus runs under command time limits, run deterministic shards:

```powershell
python tools\perf\run_standalone_perf_suite.py --benchmark build\cmake-live-image-png-ninja-vs18-perf\blink_standalone_render_benchmark_skia.exe --out-dir build\perf\x64-Perf-shard0 --build-config-name x64-Perf --shard-index 0 --shard-count 8
```

The suite writes JSON, CSV, and per-page benchmark artifacts for the selected benchmark path. Use `--write-baseline-doc` only after running the intended baseline corpus; subset runs should stay in `build/perf/...`.
