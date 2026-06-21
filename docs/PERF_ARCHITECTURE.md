# Standalone Renderer Performance Architecture

This document records the active standalone renderer architecture after the
Chromium compositor pivot.

## Active Benchmark And Viewer Path

Verdict: the active benchmark and SDL viewer path is a single Chromium
compositor path:

`HTML/CSS input -> Blink lifecycle -> PaintArtifactCompositor -> cc -> GPU raster/shared image -> Viz Display/SkiaRenderer GPU -> Vulkan -> SDL HWND`

The retained `DrawCommandList` presenter, Skia CPU raster path, SDL texture
upload path, and old retained SDL viewer are no longer production surfaces.

Active entrypoints:

- `upstream/chromium/standalone_renderer/examples/compositor_benchmark.cc`
- `upstream/chromium/standalone_renderer/examples/compositor_sdl_viewer.cc`
- `upstream/chromium/standalone_renderer/src/compositor_runtime.cc`
- `upstream/chromium/standalone_renderer/src/vulkan_window_host.cc`
- `upstream/chromium/third_party/blink/renderer/core/standalone_live_frame_bridge_probe.cc`

The SDL viewer is host-only. It owns window creation, input/event pumping,
native HWND lifetime, size changes, and frame scheduling. It does not own a
renderer, texture upload, readback, or pixel presentation path.

## Runtime Boundaries

Supported runtime surface:

- Local HTML/CSS input.
- SDL keyboard, mouse, wheel, resize, and quit events.
- Static images and canvas through the Blink/cc/Viz/GPU path.
- Source-owned ANGLE/Vulkan runtime artifacts built from this checkout.

Unsupported runtime surfaces remain inert or compile-only:

- External network fetching and Network Service runtime.
- Media/video decode, encode, and capture runtime.
- WebGPU/Dawn runtime.
- Browser shell and browser input-on-Viz runtime.

## Current Smoke Milestones

The checked SDL smoke now verifies the first production frame reaches:

- `frame_sink_bound=1`
- `gpu_context=1`
- `raster_context=1`
- `shared_image=1`
- `viz_submit=1`
- `viz_display=1`
- `skia_gpu=1`
- `vulkan_present=1`
- `SWAP_ACK`

The non-GUI benchmark does not have an HWND, so it still reports
`viz_display=0` and `skia_gpu=0` while verifying the Blink, cc, GPU raster, and
Viz submit path through `viz_submit=1`.

## Performance Notes

Historical retained-renderer baseline data is no longer representative of the
production path. New performance work should measure Chromium compositor
boundaries directly:

- Runtime creation and Blink document setup.
- Style/layout/prepaint/paint.
- PaintArtifactCompositor root-layer production.
- cc host attach, commit, raster, and frame-sink submission.
- Shared-image allocation and GPU raster.
- Viz Display/SkiaRenderer draw/swap.
- Vulkan swap/present through the SDL HWND.

Do not add local retained-compositor heuristics or CPU raster shortcuts as
performance fixes. Optimizations should either improve the Chromium-owned path
or clearly document an unsupported optional surface being gated out.
