# Standalone Renderer Performance Architecture

This is the performance-program architecture audit for the current standalone renderer baseline.

## Active Benchmark And Viewer Path

Verdict: the active benchmark/viewer path uses real Blink `PaintArtifact` output, translates it into the standalone retained `DrawCommandList` path, and rasters through Skia CPU. It does not currently use Blink `PaintArtifactCompositor`, cc layer trees, or GPU compositor presentation.

Evidence:

- `upstream/chromium/standalone_renderer/examples/render_benchmark.cc` creates the live Blink page embedder unconditionally for benchmark runs.
- `upstream/chromium/standalone_renderer/examples/render_benchmark.cc` rejects strict benchmark output unless diagnostics confirm `paint artifact source: real Blink PaintArtifact`.
- `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc` creates the same live Blink page embedder for the SDL viewer path.
- `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc` verifies the linked bridge exposes the expected `DummyPageHolder` and `LocalFrameView` PaintArtifact path before using live paint.
- `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc` enters `TryReplaceWithLivePaintArtifactScene`, which reads live Blink paint chunks, display items, property metadata, hit-test data, scroll data, and exported draw ops.
- `upstream/chromium/standalone_renderer/src/blink_runtime_adapter.cc` records the active source as `paint artifact source: real Blink PaintArtifact; extractor=real_blink_paint_artifact_extractor`.
- `upstream/chromium/standalone_renderer/src/retained_scene.cc` converts `PaintArtifact` chunks into retained scene chunks when working from the standalone `PaintArtifact` package.
- `upstream/chromium/standalone_renderer/src/retained_scene.cc` flattens retained scenes into draw commands for presentation.
- `upstream/chromium/standalone_renderer/src/skia_cpu_renderer.cc` rasters a `RenderResult` with Skia CPU.
- `upstream/chromium/standalone_renderer/examples/render_benchmark.cc` uses `RasterizeRenderResultWithSkiaCpu` unconditionally for benchmark output.
- `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc` uses Skia CPU raster for SDL viewer frames.
- `upstream/chromium/standalone_renderer/examples/sdl_viewer.cc` uploads CPU pixels with `SDL_UpdateTexture`.

## Inactive Or Non-Hot Paths

- The old non-live snapshot renderer has been removed from the configured build. Public benchmark and viewer entrypoints require live Blink `PaintArtifact` extraction and should fail rather than synthesize standalone paint output when that bridge is unavailable.
- Blink `PaintArtifactCompositor` is not active. The linked definitions in `upstream/chromium/standalone_renderer/src/live_link_boundary_stubs.cc` are explicit fail-fast boundary stubs for compositor operations, and no active benchmark/viewer path builds a cc layer tree from `PaintArtifactCompositor`.
- `PaintArtifact::GetPaintRecord` is not available as a real flattened Blink paint-record path. The benchmark documents that the standalone symbol resolves to the empty stub in `upstream/chromium/standalone_renderer/src/live_link_boundary_stubs.cc`.

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
- The post-`8382d99` 262-page baseline records `cold_presented_frame_ms` max 467.94 ms and `cold_process_elapsed_ms` max 656.00 ms. The renderer first-frame boundary still passes, but the conservative in-process process boundary is open on this run and the historical command/process envelope remains a process-envelope metric rather than a renderer cold-load target.
- A persistent benchmark process was not added for this validation pass. The current one-process-per-page corpus keeps stronger page isolation, and the focused offender shard with launch/wait instrumentation showed the failure is outside the renderer timing boundary. A persistent worker should be a separate harness refactor with explicit state-leak checks, not part of the retained raster validation closure.

## Retained CPU Damage Grouping Status

The post-`8382d99` damage-clip grouping work is an interim retained Skia CPU replay optimization. It groups disjoint damage clips only for command replay, keeps copyback on the original clamped damage clips, and records stable diagnostics for clip count, replay group count, command replay counts before/after grouping, raw and coalesced damage area, grouping time, SkRegion clip time, CPU replay time, and copyback time.

This is still the standalone retained `DrawCommandList` path. It is not Chromium PaintArtifactCompositor, not a cc layer tree, and not a retained GPU/tile compositor. The remaining `49d_rounded_shadow_document_scroll` scroll cost is dominated by real Skia CPU replay of expensive static shadow/filter/rounded-clip content; closing that safely likely requires real retained layer/tile/cache metadata or the Chromium compositor path, not a local damage-clip shortcut.

## Chromium Reuse Pivot

The first pivot boundary is to stop exposing product-level renderer switches while the implementation still uses the transitional retained Skia CPU presenter. Public benchmark and SDL viewer entrypoints now use one path: live Blink `PaintArtifact` input, standalone retained `DrawCommandList` extraction, Skia CPU raster, and SDL/BMP presentation as appropriate.

The long-term single rendering path should replace the standalone retained presenter with Chromium `PaintArtifactCompositor` and cc integration rather than extending local retained-renderer heuristics. Validation-only diagnostics may remain available when they inspect the active path, but they should not imply supported alternate renderers.

## PaintArtifactCompositor Frontier

The first source-list pivot attempted to replace the standalone `PaintArtifactCompositor` no-op definitions with the real upstream implementation:

- `third_party/blink/renderer/platform/graphics/compositing/paint_artifact_compositor.cc`
- adjacent Blink compositor files: `adjust_mask_layer_geometry.cc`, `content_layer_client_impl.cc`, `layers_as_json.cc`, `pending_layer.cc`, and `property_tree_manager.cc`
- immediate supporting sources for the first link boundary: `cc/layers/layer.cc`, `cc/layers/picture_layer.cc`, `cc/trees/property_tree.cc`, Blink `logging_canvas.cc`, `raster_invalidation_tracking.cc`, and `raster_invalidator.cc`

The Blink compositor files compiled, but `cc::PictureLayer` crossed the current standalone build boundary into the real cc host/resource stack. The next compile boundary required `cc::LayerTreeHostImpl`, viz transferable resources, GPU shared-image support, and the missing GPU command-buffer include `gpu/command_buffer/client/shared_image_interface.h`. That is the correct upstream dependency direction, but it is broader than a bounded first CL because it requires deciding the real cc layer-tree host, frame sink/output surface, resource provider, scheduling, and software/GPU presentation integration.

This CL therefore does not add a local compositor replacement. It keeps the active retained Skia CPU presenter buildable while changing the `PaintArtifactCompositor` operational stubs from silent no-ops into explicit fail-fast diagnostics. Reaching those methods now reports that the standalone renderer needs real Blink `PaintArtifactCompositor` + cc integration instead of pretending compositor work succeeded.

## 49d Retained Cache Boundary

The post-`fd752623` architecture boundary for `49d_rounded_shadow_document_scroll` is that the retained scene has enough metadata to explain why CPU replay is expensive, but not enough retained surface state to replace the expensive replay with cached pixels.

Current evidence from `build/perf/post-8382d99-full-shard-04/pages/49d_rounded_shadow_document_scroll/warm-scroll.json`:

- Presented scroll frame: 42.11 ms.
- Skia CPU raster: 41.72 ms, with 38.33 ms in command replay and 0.57 ms in copyback.
- Damage grouping overhead: 0.004 ms, `SkRegion` clip overhead: 0.002 ms.
- Damage: four clamped clips, 383,040 raw/coalesced pixels, grouped into two replay clips.
- Replay work: 175 draw commands per replay group; command executions drop from 700 to 350 after grouping.
- The full retained scene has 10 chunks, 195 scene commands, and 12 finer cache-unit descriptors. Zero finer units are conservative cache candidates.

The expensive command classes are structural, not damage bookkeeping. The warm scroll scene contains 20 rounded-rect clips, 10 save layers, 18 shader fill commands, 10 path fills, 8 rounded-rect fills, and 10 draw-looper shadow draws. The resource summary reports 18 shaders, 10 paths, one filter signal, no images, and no text blobs.

The slow chunks fall into repeatable categories:

| Chunk class | Count | Commands | Damage relation | Current blockers |
| --- | ---: | ---: | --- | --- |
| Document background | 1 | 8 | Intersects all four damage clips; bounds are 1280x982, larger than the viewport | Larger-than-viewport shader content |
| Column/container decoration chunks | 2 | 28 each | Two damage intersections each, 154,560 px each | Save layers, rounded clips, shaders, paths |
| Card background chunks | 6 | 15 each | Full or partial card intersections | Save layers, rounded clips, opacity/effect-style ops, shaders, paths |
| Scrollbar chunk | 1 | 3 | Small intersections only | Trivial candidate, not the bottleneck |

The finer cache-unit metadata from the prior retained-cache commits is present:

- `ac7ac005` added chunk-level retained-cache feasibility JSON.
- `3990c22c` added finer retained cache-unit reporting from the Blink bridge.
- `aae576f0` persisted finer cache-unit descriptors through retained frames.
- `0c74cbbb` annotated retained draw commands with source chunk, display item, and finer cache-unit spans.
- `9fce3bf7` recorded cache-unit entry-state metadata.

What remains missing is not another scalar diagnostic. The CPU replay path receives a flattened command list plus damage clips, and replays the list under clip groups. It does not own retained raster surfaces, cache memory, or a compositing graph. A correct cache for 49d needs at least:

- Retained surface or tile storage with explicit allocation, eviction, and invalidation.
- Cache keys that combine chunk/finer-unit stable keys, content hashes, resource-signal hashes, paint property-state hashes, device scale, viewport, and scroll/transform state.
- Complete entry and exit canvas state for cached spans. Current entry summaries can record save depth, transform, clip bounds, and effect depth, but 49d still reports `active_rounded_clip_shape_not_serialized` and `active_save_layer_context_not_serialized` on inner units.
- Layer isolation semantics for save layers, opacity/blend/filter/backdrop state, and unset/full-viewport save-layer bounds.
- Conservative surface bounds and outsets for blur shadows, filters, rounded clips, paths, and shader draws.
- Resource lifetime tracking for shader bytes, path bytes, image/text resources, decoded resource reuse, and invalidation when Blink resource state changes.
- Ordered composition of cached and uncached content in scene order, including interactions between chunks that overlap the same damage region.

Without that model, caching the 49d shadow/card work would have to guess at isolation, clip shape, resource lifetime, or composition ordering. That retained-cache direction is no longer the product path. It may remain useful only as validation-only analysis, not as another renderer implementation. The next implementation step should instead wire the real Chromium `PaintArtifactCompositor`/cc route.

The Chromium-parity path is broader: replace the custom retained replay boundary with a real `PaintArtifactCompositor`/cc layer-tree route. That requires turning the current linked compositor stubs into a working compositor integration, including cc layer tree creation, frame sink/output surface plumbing, resource providers, image/resource upload, scheduling, and software/GPU presentation. That is the correct long-term direction, but it is a separate integration seam from the current standalone `DrawCommandList` renderer.

## SDL Retained Upload Status

The checked SDL viewer path at `build/cmake-live-image-png-ninja-vs18/blink_standalone_sdl_viewer_skia.exe` now has a focused profile gate in `tools/perf/run_sdl_profile_benchmark.py`.

The post-`8382d99` SDL profile run used the dummy SDL video driver and recorded:

- Static no-change frames: 5/5 with no lifecycle work, no PaintArtifact translation, `damage_pixels=0`, `raster_pixels=0`, `uploaded_pixels=0`, `texture_copy_pixels=0`, `texture_update_rects=0`, and `raster_skipped=1`.
- Retained scroll frames: 5/5 with scroll reuse, partial redraw, `damage_pixels=176640`, `raster_pixels=176640`, `uploaded_pixels=176640`, `texture_copy_pixels=944640`, and two SDL texture update rects per measured frame.
- SDL present timing is reported as `sdl_draw_present_ms`; the latest checked-viewer profile measured scroll present p95 at 0.558 ms and static no-change present p95 at 0.804 ms. End-to-end profiled frame p95 was 13.186 ms for scroll and 1.939 ms for static no-change. Scroll CPU replay p95 was 8.272 ms, so the checked SDL viewer still shows the retained Skia CPU replay boundary rather than an SDL upload/present bottleneck.

The SDL texture update control flow keeps the skipped-raster path separate from the incremental-update path. When CPU raster is skipped, the update rect list remains empty instead of falling back to a full texture rect.

## Intended Direction

The next performance architecture step should move toward Chromium/Blink/cc reuse instead of adding custom semantics:

1. Preserve real Blink lifecycle and `PaintArtifact` correctness as the source of truth.
2. Prefer enabling the real `PaintArtifactCompositor`/cc path and Skia-backed compositor primitives over expanding custom retained heuristics.
3. Keep the existing retained DrawCommandList path only as the current transitional presenter while it is being replaced; do not preserve it as a supported fallback once cc-backed output is correct.
4. Improve instrumentation before optimization: isolate renderer create, page init, commit, style, layout, prepaint, paint, PaintArtifact extraction, translation/composition, raster, upload/present, and warm live-frame timing.
