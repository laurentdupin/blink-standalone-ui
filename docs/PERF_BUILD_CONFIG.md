# Standalone Renderer Performance Build Configuration

This document records the current measurement build and known differences from a Chromium release-like benchmark configuration. It is an audit only; no build settings were changed for this baseline milestone.

## Current Build Target

Primary benchmark target:

- `blink_standalone_render_benchmark_skia`
- Default perf-suite executable path: `build/cmake-live-image-png-ninja-vs18/blink_standalone_render_benchmark_skia.exe`
- Source: `upstream/chromium/standalone_renderer/examples/render_benchmark.cc`
- CMake target: `CMakeLists.txt:168`

Viewer target when SDL is enabled:

- `blink_standalone_sdl_viewer_skia`
- Source: `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc`
- CMake target starts at `CMakeLists.txt:270`

## Current Defines Affecting Measurement

The benchmark and SDL viewer targets currently share several non-release-like or measurement-sensitive defines:

- `HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER=1` at `CMakeLists.txt:216` and `CMakeLists.txt:323`
- `DCHECK_ALWAYS_ON=1` at `CMakeLists.txt:217` and `CMakeLists.txt:324`
- `SK_ENABLE_OPTIMIZE_SIZE=1` at `CMakeLists.txt:233` and `CMakeLists.txt:340`
- `CPU_NO_SIMD=1` at `CMakeLists.txt:236` and `CMakeLists.txt:343`

`CMakePresets.json` defines both Debug and Release presets, but the currently used benchmark path is `build/cmake-live-image-png-ninja-vs18`; inspect its `CMakeCache.txt` when comparing machines or producing publishable numbers.

## Known Measurement Risks

- `DCHECK_ALWAYS_ON=1` adds assertion overhead and can perturb branch/layout behavior.
- `SK_ENABLE_OPTIMIZE_SIZE=1` favors size-oriented Skia compilation rather than peak throughput.
- `CPU_NO_SIMD=1` disables CPU SIMD paths that matter for raster, image decode/conversion, and pixel loops.
- The strict benchmark path requires `--skia-cpu`; non-Skia retained replay is rejected for live Blink retained output.
- The live Blink bridge invalidates its probe cache per render in `TryReplaceWithLivePaintArtifactScene`, so cold and warm timings include extra cache churn.
- The benchmark performs a full lifecycle per render invocation. Warm incremental modes currently build the previous frame inside the same process before the measured frame.
- Benchmark presentation writes BMP files, while SDL viewer presentation includes Skia CPU raster plus CPU texture upload through SDL.
- Process startup in the perf suite is estimated from subprocess wall time minus in-process elapsed time and includes Python orchestration overhead.
- Resource-backed pages depend on the `--resource-root` path passed to the benchmark. The perf suite passes the paint audit root by default.

## Baseline Command Shape

The perf suite builds around this benchmark invocation shape:

```powershell
python tools/perf/run_standalone_perf_suite.py --viewport 1280x720
```

Each page is rendered with:

```text
--html-file <paint_audit_html> --resource-root <paint_audit_root> --viewport 1280x720 --skia-cpu --blink --min-non-white 0
```

The non-white threshold is disabled because `paint_audit` includes intentional all-white/transparent/broken-resource fixtures. Retained-vs-Skia-oracle comparison is the correctness gate for those pages.

The suite writes:

- JSON: `build/perf/standalone_perf_results.json`
- CSV: `build/perf/standalone_perf_results.csv`
- per-page logs/images/audit JSON under `build/perf/pages/`
- generated baseline doc: `docs/PERF_BASELINE.md`

## Release-Like Benchmark Gaps To Close Later

- Add a dedicated release/perf preset with DCHECKs off and optimization flags aligned with the intended deployment baseline.
- Re-enable safe CPU SIMD paths after correctness validation on the benchmark suite.
- Add an SDL/live-session timing harness that separates renderer creation, first present, and warm frame presentation/upload.
- Add direct cc/Skia compositor benchmarking once the real `PaintArtifactCompositor` path is available.
