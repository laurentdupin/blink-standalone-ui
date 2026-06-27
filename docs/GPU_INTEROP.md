# Embedder-Owned GPU Target Interop

This note records the current boundary for rendering into an embedder-owned GPU
texture, such as a texture owned by Godot's RenderingDevice. It is a design and
blocker document, not a public ABI contract.

## Goal

The desired GPU interop path is presentation independent:

```text
HTML/CSS -> Blink -> PaintArtifactCompositor -> cc -> Viz/Skia ->
embedder-owned GPU target
```

Blink must not receive or sample host-scene pixels. The CPU raw frame C API
remains the always-available baseline. A GPU target mode must not silently fall
back to CPU output or native-window presentation.

## Target Shape

A future C++ runtime boundary should be backend neutral and should describe the
embedder target explicitly. Suggested internal shape:

```cpp
enum class GpuTargetBackend {
  kNone,
  kVulkan,
  kD3D12,
  kMetal,
};

enum class GpuTargetOwnership {
  kEmbedderOwned,
  kRendererOwned,
};

struct GpuTargetConfig {
  GpuTargetBackend backend;
  GpuTargetOwnership ownership;
  Size logical_size;
  Size physical_size;
  float device_scale_factor;
  uint32_t pixel_format;
  uint32_t alpha_mode;
  uint32_t color_space;
  uint64_t generation;
};

struct VulkanGpuTargetConfig {
  VkInstance instance;
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkQueue queue;
  uint32_t queue_family_index;
  VkImage image;
  VkImageView image_view;
  VkFormat format;
  VkImageLayout initial_layout;
  VkImageLayout final_layout;
  VkSemaphore wait_semaphore;
  uint64_t wait_value;
  VkSemaphore signal_semaphore;
  uint64_t signal_value;
};
```

The MVP should be same-device/same-queue-family Vulkan. It should render or copy
the Chromium/Viz/Skia output into the supplied `VkImage`, leave it in the
requested final layout, and signal completion before the embedder samples it.
D3D12 and Metal should use equivalent backend-specific structs only after real
runtime hosts exist.

## Current Audit

`StandaloneCompositorRuntime` currently exposes two output paths:

- CPU raw/PNG output from Viz `CopyOutputRequest` with
  `ResultDestination::kSystemMemory`.
- Native-window presentation through `VulkanWindowHost`.
- Runtime-internal GPU diagnostics from Viz `CopyOutputRequest` with
  `ResultDestination::kSharedImage`. The benchmark flag
  `--gpu-output-smoke` requests this path and verifies that Viz returns a
  nonzero SharedImage mailbox without falling back to system memory.

`VulkanWindowHost` creates and owns its own Chromium Vulkan instance, device,
graphics/presentation queue, Win32 surface, swapchain, and command pool. Its
`Present()` path acquires a swapchain image, transitions it, calls
`SwapBuffers()`, and reports diagnostics. It does not receive a rendered
`VkImage` from `CompositorFrameResult`, and it has no hook to copy into an
external image.

The standalone direct cc/Viz frame sink can create an offscreen Viz `Display`
and can ask Viz for a copy of the submitted surface. Public raw-frame output
continues to request system memory:

```cpp
viz::CopyOutputRequest::ResultDestination::kSystemMemory
```

The internal GPU-output probe can instead request:

```cpp
viz::CopyOutputRequest::ResultDestination::kSharedImage
```

In the current generated-V8 ChromiumLLVM build this produces a
`CopyOutputSharedImageResult` with a Chromium-owned `gpu::ClientSharedImage`
mailbox. The standalone benchmark reports size, format, mailbox, and sync-token
diagnostics. This proves that the imported Viz/SkiaRenderer path can produce a
GPU texture identity before CPU readback or native-window presentation.

The result is still not an embedder-owned texture. This checkout's
`gpu_shared_image_phase3_bridge.cc` is explicitly a compile-boundary
implementation for client-side SharedImage value ownership; mapping/export
helpers are fail-closed and do not provide a usable cross-engine texture handle.
Imported SharedImage/Vulkan backing code, including
`ExternalVkImageBackingFactory`, is not connected to the standalone runtime in a
way that can target a caller-supplied `VkImage`.

## Why No Public API Yet

A real Godot-owned target path is not implementable in this checkpoint without
additional Chromium runtime wiring:

- The current runtime can prove a Chromium-owned SharedImage mailbox for the
  final submitted Viz frame, but it does not expose ownership, exportable memory,
  or an external-image copy/import path suitable for an embedder.
- `VulkanWindowHost` uses a Chromium-owned device and swapchain; it cannot adopt
  Godot's `VkDevice`, `VkQueue`, or `VkImage`.
- Imported SharedImage/Vulkan code creates Chromium-owned images or imports
  platform `GpuMemoryBufferHandle` objects. Godot's reviewed contract exposes
  raw device/queue/image/view handles, not a Chromium `GpuMemoryBufferHandle`
  or a registered SharedImage mailbox.
- There is no synchronization contract in the standalone API for external
  wait/signal semaphores or timeline values.
- The D3D12 path has no active standalone host equivalent to `VulkanWindowHost`.

Adding C ABI entry points now would either return unsupported for every call or
silently route through CPU/native-window paths. Both would be misleading.

## Required Implementation Steps

The smallest real Vulkan implementation should start by adding runtime-internal
plumbing, not public C ABI:

1. Add a presentation-independent `GpuTargetConfig` boundary to
   `StandaloneCompositorRuntime`.
2. Promote the current benchmark-only SharedImage CopyOutput diagnostic into a
   runtime-internal GPU result object with explicit ownership and release
   semantics. This is still Chromium-owned.
3. Add a Vulkan target writer that can operate on the same `VkDevice`/queue
   family as the target, perform layout transitions, copy/resolve the rendered
   image, and signal completion.
4. Decide whether the runtime can consume an embedder-created device directly or
   whether the embedder must provide an importable memory handle instead of a
   raw `VkImage`.
5. Add an internal smoke using an external-like `VkImage`, with a hard failure
  if the path cannot write the image. Only after that should a public C ABI be
  added.

## Same-Device Embedder Targets

Godot can expose backend-native resources such as `VkInstance`,
`VkPhysicalDevice`, `VkDevice`, `VkQueue`, queue family index, `VkImage`,
`VkImageView`, and matching D3D12 device/queue/resource handles. That is the
right product direction for a stable Godot-owned target: Godot owns the texture
and Blink writes into it. The current standalone checkout cannot do this yet
without new Chromium-side ownership plumbing.

### Vulkan

The active SDL Vulkan path is still Chromium-owned. `VulkanWindowHost` calls:

```text
gpu::CreateVulkanImplementation(false)
VulkanImplementation::InitializeVulkanInstance(true)
gpu::CreateVulkanDeviceQueue(... GRAPHICS | PRESENTATION ...)
VulkanImplementation::CreateViewSurface(hwnd)
VulkanSurface::Initialize/Reshape
```

That path creates a Chromium `VkInstance`, `VkDevice`, graphics/presentation
queue, Win32 surface, swapchain, and command pool. It is correct for native
window presentation, but it is not a same-device embedder path.

Chromium's `gpu::VulkanDeviceQueue` has non-owning initialization helpers:
`InitializeForWebView()` and `InitializeForCompositorGpuThread()` can reference
externally supplied `VkPhysicalDevice`, `VkDevice`, and `VkQueue` handles
without destroying the device. Those helpers are not enough by themselves for
Godot because the standalone runtime still needs:

- a `VulkanImplementation`/`VulkanInstance` wrapper around the externally
  supplied `VkInstance`, with function pointers, Vulkan version, physical-device
  info, Skia feature queries, and platform external-sync helpers initialized;
- validation that the externally supplied physical device and queue match the
  device used for the target `VkImage`;
- an extension/feature contract matching the active Chromium/Skia path;
- queue locking and lifetime rules for work submitted on an embedder-owned
  queue;
- a no-swapchain render/copy path from the Chromium SharedImage result into the
  supplied `VkImage`.

The benchmark flag `--gpu-external-vulkan-device-smoke` is an internal proof for
the first piece only. It creates a normal Chromium Vulkan device, borrows its
raw handles into a second non-owning `gpu::VulkanDeviceQueue` via
`InitializeForWebView()`, creates a command pool through the borrowed wrapper,
and tears the wrapper down without destroying the original device. This proves
the basic lifetime model can be used in the standalone build. It does not prove
that arbitrary Godot handles can be accepted yet, because that still requires an
external `VulkanImplementation`/`VulkanInstance` adapter and feature/extension
validation around the supplied instance.

The current Win32 Vulkan implementation requires these instance extensions when
it creates Chromium's instance:

```text
VK_KHR_external_memory_capabilities
VK_KHR_external_semaphore_capabilities
VK_KHR_surface
VK_KHR_win32_surface
```

It currently requires `VK_KHR_swapchain` at device creation because the active
host is a window/swapchain presenter. It also requests these optional device
extensions:

```text
VK_KHR_external_memory
VK_KHR_external_memory_win32
VK_KHR_external_semaphore
VK_KHR_external_semaphore_win32
```

Skia may add further extensions and physical-device features through
`VulkanInstance::skia_features()` at runtime. A future offscreen same-device
target should not blindly require `VK_KHR_swapchain`, but it must derive and
verify the actual Skia/Viz/SharedImage requirements from the active build before
accepting Godot handles.

Copying the `--gpu-output-smoke` SharedImage result into a Godot-owned image
requires a real Vulkan target writer, not just the mailbox diagnostic. The
writer must acquire or otherwise access the Chromium-owned source image, wait on
the source sync token, transition the source to a transfer-readable layout,
transition the Godot image from its declared current layout to
`VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL` or a renderable equivalent, copy/blit or
render-resolve with compatible format and extent, transition the Godot image to
the requested final layout, and signal the embedder-provided semaphore/timeline
value before Godot samples it. The API also needs resize/generation and no-reuse
rules so the target image is not destroyed or reused while Chromium work is in
flight.

So the Vulkan answer is: same-device is technically plausible in Chromium, and
this checkout has useful internal pieces, but it is not implementable as a
public API today. The minimum credible prototype is an internal external-device
adapter that can initialize Chromium's Vulkan/Skia state around supplied handles
or prove why that fails, followed by an internal smoke that copies a
Chromium-owned SharedImage into an external-like `VkImage` without any window or
swapchain fallback.

### D3D12

D3D12 is further away than Vulkan in this standalone checkout. The tree contains
Chromium code for D3D/DXGI, Dawn/Graphite, and D3D SharedImage plumbing, but
there is no active standalone D3D12 host equivalent to `VulkanWindowHost`. The
SDL viewer intentionally rejects `--gpu-backend=dx12` rather than falling back
to Vulkan or CPU.

A real D3D12 target path would first need a Chromium-owned D3D12/DXGI/Dawn or
Skia/Viz host for standalone rendering. Only after that exists can the same
device question be answered by code. The expected shape is an adapter around an
externally supplied `ID3D12Device*` and `ID3D12CommandQueue*`, a copy or render
path into a supplied `ID3D12Resource*`, explicit resource-state transitions, and
fence wait/signal ownership. The checkout does not currently expose that layer,
so same-device D3D12 is design-only.

### Future ABI Direction

The future public ABI should stay presentation-independent and should not
mention SDL, HWND, or swapchains. A backend enum, common logical/physical target
config, Vulkan external device/target structs, and D3D12 external device/target
structs match the right direction. Before exposing them publicly, a real backend
must prove at least one of these operations:

- initialize Chromium's GPU/Skia/Viz path from externally supplied device and
  queue handles; or
- copy a Chromium-owned GPU result into an externally supplied target resource
  on the same device with explicit synchronization.

Until then, adding C ABI entry points would only create a dead API surface.

## Current Status

- SDL Vulkan native-window presentation remains supported and validated through
  `VulkanWindowHost`.
- C API raw CPU output remains supported and is the portable fallback selected
  explicitly by embedders.
- `--gpu-output-smoke` validates an internal Chromium-owned SharedImage
  CopyOutput result: Viz/SkiaRenderer can produce a GPU mailbox for the rendered
  frame.
- `--gpu-external-vulkan-device-smoke` validates that a non-owning
  `gpu::VulkanDeviceQueue` wrapper can borrow existing Vulkan device/queue
  handles inside this standalone build and create Chromium helper state without
  double-destroying the borrowed device.
- Embedder-owned Vulkan `VkImage` targeting is blocked pending the runtime
  ownership, same-device, copy, and synchronization wiring above.
- D3D12 GPU target support is design-only until a real Chromium D3D12/DXGI/Dawn
  host exists in the standalone runtime.
