# SDL Viewer GPU Backends

The SDL viewer is a sample host for the standalone Chromium compositor path.
It owns the native window and event pump; Blink, PaintArtifactCompositor, cc,
Viz, Skia, ANGLE, and GPU infrastructure own rendering.

## Backend Selection

Use:

```powershell
blink_standalone_sdl_viewer_skia.exe --gpu-backend=vulkan --html-file page.html
```

Supported values:

- `vulkan`: default. Uses the standalone `VulkanWindowHost` and Chromium Vulkan
  surface/swapchain plumbing. A frame is accepted only when diagnostics prove
  `viz_display=1`, `skia_gpu=1`, and `vulkan_present=1`.
- `cpu-texture`: explicit legacy/debug mode. Uses the public C API raw CPU frame
  output and uploads it to an SDL texture. This is not the default and is not a
  fallback for GPU modes.
- `dx12`: blocked. The checkout currently has some D3D/DXGI/Dawn headers and
  imported Chromium source, but the standalone viewer has no DX12 host
  equivalent to `VulkanWindowHost`. The mode fails visibly instead of falling
  back to Vulkan or CPU.

## Vulkan Status

The active Vulkan path is:

```text
HTML/CSS -> Blink lifecycle -> PaintArtifactCompositor -> cc ->
Viz Display/SkiaRenderer GPU -> Chromium Vulkan surface/swapchain -> SDL HWND
```

The noninteractive smoke shape is:

```powershell
build\cmake-generated-v8-chromium-llvm\blink_standalone_sdl_viewer_skia.exe `
  --gpu-backend=vulkan `
  --html "<!doctype html><style>body{margin:0;background:#123456}</style>" `
  --viewport 320x200 `
  --quit-after-ms 300
```

Expected diagnostics include:

- `GPU backend initialized: selected=vulkan actual=vulkan`
- `viz_display=1`
- `skia_gpu=1`
- `vulkan_present=1`
- `Chromium Vulkan swap result: SWAP_ACK`

## DX12 Blocker

A real DX12 backend should be a second native-window presentation host parallel
to `VulkanWindowHost`, not a command-line alias or CPU fallback. The missing
pieces are:

- A standalone D3D12/DXGI/Dawn/Skia/Viz native-window host that can initialize a
  swapchain for the SDL Win32 HWND.
- Runtime backend abstraction in `StandaloneCompositorRuntime` so native
  presentation can dispatch to Vulkan or DX12 hosts.
- CMake source and library wiring for the selected Chromium D3D12/DXGI/Dawn
  path, including any required generated Dawn/Graphite objects.
- Diagnostics equivalent to Vulkan that prove the actual D3D12/DXGI/Dawn path
  presented, rather than silently routing through Vulkan or CPU.

Until those pieces exist, `--gpu-backend=dx12` is intentionally a hard failure.
