# Standalone Renderer Performance Architecture

This is the performance-program architecture audit for the current standalone renderer baseline.

## Active Benchmark And Viewer Path

Verdict: the active benchmark/viewer path uses real Blink `PaintArtifact` output, translates it into the standalone retained `DrawCommandList` path, and rasters through Skia CPU. It does not currently use Blink `PaintArtifactCompositor`, cc layer trees, or GPU compositor presentation.

Evidence:

- `upstream/chromium/standalone_renderer/examples/render_benchmark.cc:1468` creates the live Blink page embedder for `--blink` benchmark runs.
- `upstream/chromium/standalone_renderer/examples/render_benchmark.cc:1549` rejects strict benchmark output unless diagnostics confirm `paint artifact source: real Blink PaintArtifact`.
- `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc:2121` and `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc:2512` create the same live Blink page embedder for the SDL viewer path.
- `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc:2964` and `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc:3256` verify the linked bridge exposes the expected `DummyPageHolder` and `LocalFrameView` PaintArtifact path before using live paint.
- `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc:3179` enters `TryReplaceWithLivePaintArtifactScene`, which reads live Blink paint chunks, display items, property metadata, hit-test data, scroll data, and exported draw ops.
- `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc:4325` records the active source as `paint artifact source: real Blink PaintArtifact; extractor=real_blink_paint_artifact_extractor`.
- `upstream/chromium/standalone_renderer/src/retained_scene.cc:1341` converts `PaintArtifact` chunks into retained scene chunks when working from the standalone `PaintArtifact` package.
- `upstream/chromium/standalone_renderer/src/retained_scene.cc:1658` flattens retained scenes into draw commands for presentation.
- `upstream/chromium/standalone_renderer/src/skia_cpu_renderer.cc:1611` rasters a `RenderResult` with Skia CPU.
- `upstream/chromium/standalone_renderer/examples/render_benchmark.cc:1667` uses `RasterizeRenderResultWithSkiaCpu` for benchmark output when `--skia-cpu` is selected.
- `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc:2182`, `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc:2368`, and `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc:2580` use Skia CPU raster for SDL viewer frames.
- `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc:1500` uploads CPU pixels with `SDL_UpdateTexture`.

## Inactive Or Non-Hot Paths

- `StandaloneFrame` is still present as a fallback/snapshot artifact path in `upstream/chromium/standalone_renderer/src/standalone_frame.cc`; its `CollectPaint` output is tagged as `BlinkPaintArtifactSource::kStandaloneSnapshot` at `upstream/chromium/standalone_renderer/src/standalone_frame.cc:228`. The strict benchmark rejects non-real-Blink output, so this is not the hot benchmark path.
- Blink `PaintArtifactCompositor` is not active. The linked definitions in `upstream/chromium/standalone_renderer/src/live_link_boundary_stubs.cc:9347` are stubs, and no active benchmark/viewer path builds a cc layer tree from `PaintArtifactCompositor`.
- `PaintArtifact::GetPaintRecord` is not available as a real flattened Blink paint-record path. The benchmark documents that the standalone symbol resolves to the empty stub at `upstream/chromium/standalone_renderer/examples/render_benchmark.cc:1802`, with the stub in `upstream/chromium/standalone_renderer/src/live_link_boundary_stubs.cc:9599`.

## Timing Boundaries

The current benchmark records coarse executable-side timing in `render_timing_diagnostics`:

- `blink_embedder_create_ms`
- `blink_initialize_ms`
- `advance_and_render_ms`
- `cpu_raster_replay_ms`
- `output_image_write_ms`
- `process_elapsed_ms`

When paint artifact audit JSON is enabled, the raw Blink probe contributes stage timings under `render_result.raw_paint_artifact_audit_json.render_timing_diagnostics`, including document commit, style, layout, prepaint/paint, artifact generation, and artifact extraction where available.

Current gaps:

- SDL presentation/upload is not measured by the benchmark executable. Benchmark output writes BMP files, while SDL viewer upload uses CPU raster plus `SDL_UpdateTexture`.
- Warm incremental measurements create the previous frame inside the same benchmark process, then time only the measured incremental `AdvanceAndRender` call. Warm rows also report frame-work counters that show whether lifecycle, PaintArtifact translation, raster, and presentation work ran.
- `cold_presented_frame_ms` is the renderer first-frame boundary: benchmark `advance_and_render_ms` plus CPU raster replay for the measured cold page.
- `cold_process_elapsed_ms` is a conservative in-process document boundary. It starts at the first statement in benchmark `main` and includes argument/file/resource setup, Blink embedder creation and initialization, first-page load, first renderer frame, CPU raster, BMP/audit output, and local Skia PaintRecord oracle work.
- `cold_command_wall_ms` is the Python command/process envelope around `subprocess.Popen(...).communicate()`. It includes Python orchestration, process creation, Windows executable image load, static initialization before benchmark `main`, benchmark work, stdout/stderr draining, and process exit/teardown.
- `cold_command_process_envelope_overhead_ms` is `cold_command_wall_ms - cold_process_elapsed_ms`. The older JSON field `process_startup_overhead_ms` carries the same value for compatibility, but that value is broader than startup alone.
- The post-`1640521e` 262-page baseline meets the 500 ms cold renderer/document boundary by both `cold_presented_frame_ms` (max 274.15 ms) and conservative `cold_process_elapsed_ms` (max 351.24 ms). The historical command/process envelope still fails as a process-envelope metric (max 1357.28 ms).
- A persistent benchmark process was not added for this validation pass. The current one-process-per-page corpus keeps stronger page isolation, and the focused offender shard with launch/wait instrumentation showed the failure is outside the renderer timing boundary. A persistent worker should be a separate harness refactor with explicit state-leak checks, not part of the retained raster validation closure.

## SDL Retained Upload Status

The checked SDL viewer path at `build/cmake-live-image-png-ninja-vs18/blink_standalone_sdl_viewer_skia.exe` now has a focused profile gate in `tools/perf/run_sdl_profile_benchmark.py`.

The post-`1640521e` SDL profile run used the dummy SDL video driver and recorded:

- Static no-change frames: 5/5 with no lifecycle work, no PaintArtifact translation, `damage_pixels=0`, `raster_pixels=0`, `uploaded_pixels=0`, `texture_copy_pixels=0`, `texture_update_rects=0`, and `raster_skipped=1`.
- Retained scroll frames: 5/5 with scroll reuse, partial redraw, `damage_pixels=176640`, `raster_pixels=176640`, `uploaded_pixels=176640`, `texture_copy_pixels=944640`, and two SDL texture update rects per measured frame.
- SDL present timing is reported as `sdl_draw_present_ms`; the latest checked-viewer profile measured scroll p95 at 0.358 ms and static no-change p95 at 0.770 ms. End-to-end profiled frame p95 was 9.521 ms for scroll and 1.566 ms for static no-change.

The SDL texture update control flow keeps the skipped-raster path separate from the incremental-update path. When CPU raster is skipped, the update rect list remains empty instead of falling back to a full texture rect.

## Intended Direction

The next performance architecture step should move toward Chromium/Blink/cc reuse instead of adding custom semantics:

1. Preserve real Blink lifecycle and `PaintArtifact` correctness as the source of truth.
2. Prefer enabling the real `PaintArtifactCompositor`/cc path and Skia-backed compositor primitives over expanding custom retained heuristics.
3. Keep the existing retained DrawCommandList path as a measurable baseline and compatibility path until cc-backed output is correct.
4. Improve instrumentation before optimization: isolate renderer create, page init, commit, style, layout, prepaint, paint, PaintArtifact extraction, translation/composition, raster, upload/present, and warm live-frame timing.
