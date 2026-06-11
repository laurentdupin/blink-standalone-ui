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
- Warm incremental measurements in the perf suite still pay previous-frame setup inside one benchmark process. They are useful for baseline comparison and correctness smoke, but not yet isolated live-session frame timings.
- Process startup is estimated by subprocess wall time minus benchmark `process_elapsed_ms`; this includes Python orchestration overhead and is not as precise as an in-process launcher probe.

## Intended Direction

The next performance architecture step should move toward Chromium/Blink/cc reuse instead of adding custom semantics:

1. Preserve real Blink lifecycle and `PaintArtifact` correctness as the source of truth.
2. Prefer enabling the real `PaintArtifactCompositor`/cc path and Skia-backed compositor primitives over expanding custom retained heuristics.
3. Keep the existing retained DrawCommandList path as a measurable baseline and compatibility path until cc-backed output is correct.
4. Improve instrumentation before optimization: isolate renderer create, page init, commit, style, layout, prepaint, paint, PaintArtifact extraction, translation/composition, raster, upload/present, and warm live-frame timing.
