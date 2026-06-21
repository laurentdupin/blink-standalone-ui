# Standalone Renderer Performance Baseline

This baseline covers the single Chromium compositor path:

`Blink lifecycle -> PaintArtifactCompositor -> cc -> GPU raster/shared image -> Viz Display/SkiaRenderer GPU -> Vulkan`

The removed retained Skia CPU renderer is not an active benchmark baseline or
regression gate.

## Current Baseline

Generated on 2026-06-20 from:

`build/perf/content-fix/suite_full_262_after_textarea_fix/standalone_perf_results.json`

| Metric | Result |
| --- | ---: |
| Corpus pages | 262 |
| Failures | 0 |
| GPU submission pages | 262 |
| Wall time p50 | 434.07 ms |
| Wall time p95 | 477.61 ms |
| Wall time max | 862.00 ms |
| Process elapsed p50 | 336.74 ms |
| Process elapsed p95 | 375.66 ms |
| Advance frame p50 | 334.70 ms |
| Advance frame p95 | 373.42 ms |
| Initialize p50 | 0.03 ms |
| Initialize p95 | 0.04 ms |

## Validation Commands

Build:

```powershell
ninja -C build\cmake-live-image-png-ninja-vs18 -j8 -k 0 blink_standalone_render_benchmark_skia blink_standalone_sdl_viewer_skia
```

Full corpus:

```powershell
python tools\perf\run_standalone_perf_suite.py --benchmark build\cmake-live-image-png-ninja-vs18\blink_standalone_render_benchmark_skia.exe --out-dir build\perf\content-fix\suite_full_262_after_textarea_fix --timeout 30
```

Non-GUI compositor smoke:

```powershell
python tools\perf\run_standalone_perf_suite.py --benchmark build\cmake-live-image-png-ninja-vs18\blink_standalone_render_benchmark_skia.exe --filter 00_text_only --out-dir build\smoke\compositor-runtime\content_clusters_final_benchmark_smoke --timeout 30 --trace-stages
```

SDL HWND/Vulkan smoke:

```powershell
python tools\perf\run_sdl_profile_benchmark.py --viewer build\cmake-live-image-png-ninja-vs18\blink_standalone_sdl_viewer_skia.exe --out-dir build\smoke\compositor-runtime\content_clusters_final_sdl_smoke --viewport 320x200 --quit-after-ms 300 --timeout 30
```

Benchmark mode validates Blink, cc, GPU raster, and Viz submit without an HWND.
SDL smoke/profile mode validates Viz Display, Skia GPU, and Vulkan HWND
presentation.
