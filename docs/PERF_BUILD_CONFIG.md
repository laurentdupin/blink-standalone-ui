# Standalone Renderer Performance Build Configuration

This document records the checked/current build and the dedicated perf benchmark preset. The perf preset is intended to move the benchmark closer to a Chromium release benchmark build without changing renderer behavior.

## Build Presets

### Checked/current

- Preset/path: existing local build under `build/cmake-live-image-png-ninja-vs18`
- Benchmark: `build/cmake-live-image-png-ninja-vs18/blink_standalone_render_benchmark_skia.exe`
- CMake cache observed in this workspace: `CMAKE_BUILD_TYPE=Debug`
- Target: `blink_standalone_render_benchmark_skia`
- Source: `upstream/chromium/standalone_renderer/examples/render_benchmark.cc`
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

The perf preset removes these forced benchmark-hostile defines from the benchmark target:

- `SK_ENABLE_OPTIMIZE_SIZE=1`
- `CPU_NO_SIMD=1`
- `SKCMS_DISABLE_HSW=1`
- `SKCMS_DISABLE_SKX=1`

The perf preset still keeps `DCHECK_ALWAYS_ON=1`. A no-DCHECK build is not wired yet: testing the perf preset without that define in this workspace fails while compiling `upstream/chromium/standalone_renderer/src/live_link_boundary_stubs.cc` because `base::subtle::RefCountedBase::CalledOnValidSequence` and the out-of-line `RefCountedBase` destructor no longer match declarations when debug-only declarations are compiled out. Removing that define safely requires a separate narrow compatibility pass, not broad Blink-core edits during this configuration milestone.

## Chromium Comparison Notes

The comparison below is based on the Chromium sources vendored under `upstream/chromium`.

- `upstream/chromium/build/config/dcheck_always_on.gni` keeps DCHECKs on by default for non-official Chromium builds. A release-like benchmark should eventually make this an explicit choice instead of forcing `DCHECK_ALWAYS_ON` in the benchmark target.
- `upstream/chromium/third_party/skia/gn/skia.gni` controls `skia_enable_optimize_size`; it is not a blanket requirement for release benchmarking. The perf preset removes the standalone forced `SK_ENABLE_OPTIMIZE_SIZE=1`.
- `upstream/chromium/third_party/skia/modules/skcms/BUILD.gn` compiles skcms HSW/SKX x86 paths for supported x64 builds instead of defining `SKCMS_DISABLE_HSW` and `SKCMS_DISABLE_SKX`. The perf preset follows that direction by adding the skcms HSW/SKX translation units with the corresponding clang AVX flags.
- `upstream/chromium/third_party/zlib/BUILD.gn` only defines `CPU_NO_SIMD` when x86/x64 and ARM optimizations are unavailable. The perf preset removes the standalone forced `CPU_NO_SIMD=1`.
- `upstream/chromium/third_party/skia/gn/core.gni` includes Skia optimized and optional source groups that are omitted by the size-optimized standalone build. The perf preset adds the Skia opt/utility sources required to link when `SK_ENABLE_OPTIMIZE_SIZE` is not forced.

## Measurement Risks

- `DCHECK_ALWAYS_ON=1` remains active in both checked/current and perf builds, so assertion overhead can still perturb benchmark numbers.
- The perf preset is optimized (`Release`, clang-cl `/O2`) but does not claim Chromium official-build parity: no PGO, no LTO audit, no component/official-build GN equivalence, and no full Chromium allocator/process configuration match.
- The standalone CMake source manifest is still manually maintained rather than generated from GN target graphs.
- The strict benchmark path requires `--skia-cpu`; non-Skia retained replay is rejected for live Blink retained output.
- The live Blink bridge invalidates its probe cache per render in `TryReplaceWithLivePaintArtifactScene`, so cold and warm timings include extra cache churn.
- The benchmark performs a full lifecycle per render invocation. Warm incremental modes currently build the previous frame inside the same process before the measured frame.
- Benchmark presentation writes BMP files, while SDL viewer presentation includes Skia CPU raster plus CPU texture upload through SDL.
- Process startup in the perf suite is estimated from subprocess wall time minus in-process elapsed time and includes Python orchestration overhead.
- Resource-backed pages depend on the `--resource-root` path passed to the benchmark. The perf suite passes the paint audit root by default.

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

For long corpus runs under command time limits, run deterministic shards and merge the JSON reports:

```powershell
python tools\perf\run_standalone_perf_suite.py --benchmark build\cmake-live-image-png-ninja-vs18-perf\blink_standalone_render_benchmark_skia.exe --out-dir build\perf\x64-Perf-shard0 --build-config-name x64-Perf --shard-index 0 --shard-count 8 --skip-warm-modes --playwright-top 0 --retries 1 --no-docs
python tools\perf\run_standalone_perf_suite.py --out-dir build\perf\x64-Perf-merged --merge-json build\perf\x64-Perf-shard0\standalone_perf_results.json --merge-json build\perf\x64-Perf-shard1\standalone_perf_results.json
```

`--retries` only retries benchmark child processes after a timeout. The JSON preserves per-attempt logs and marks recovered timeout cases as `flaky_timeout_recovered`; unrecovered timeouts remain failures.

The suite writes JSON, CSV, page artifacts, and a generated `docs/PERF_BASELINE.md` summary for the selected benchmark path.
