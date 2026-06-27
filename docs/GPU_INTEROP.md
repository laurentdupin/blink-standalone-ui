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

## Same-Device Feasibility

Godot can expose backend-native resources such as `VkInstance`,
`VkPhysicalDevice`, `VkDevice`, `VkQueue`, queue family index, `VkImage`,
`VkImageView`, and matching D3D12 device/queue/resource handles. That is the
right product direction for a stable Godot-owned target: Godot owns the texture
and Blink writes into it.

The current standalone Vulkan host does not yet support that model.
`VulkanWindowHost` creates Chromium's own Vulkan implementation, instance,
device queue, Win32 surface, and swapchain. Reusing Godot's Vulkan device would
require a sibling initialization path around externally owned Vulkan handles,
including:

- a Chromium `gpu::VulkanDeviceQueue` or equivalent wrapper that can reference,
  but not destroy, externally owned `VkInstance`, `VkPhysicalDevice`,
  `VkDevice`, and `VkQueue` handles;
- feature/extension validation against the externally supplied device. The
  minimum list must be derived from Chromium's Vulkan/Skia requirements in the
  active build rather than guessed. The renderer will also need transfer/copy
  support, layout transitions, and synchronization primitives compatible with
  the target image;
- explicit wait/signal semaphore or timeline semaphore ownership rules;
- a no-swapchain/offscreen path that copies from the Chromium-owned SharedImage
  result into the supplied `VkImage`.

D3D12 has the same shape but is further away in this checkout. There is no
active standalone D3D12 host equivalent to `VulkanWindowHost`; a real D3D12
target path would need Chromium/Skia/Dawn/Viz initialization around an externally
owned `ID3D12Device*` and `ID3D12CommandQueue*`, plus resource-state and fence
contracts for a supplied `ID3D12Resource*`.

The future public ABI should stay presentation-independent and should not
mention SDL, HWND, or swapchains. The Godot-proposed structs with a backend enum,
common logical/physical target config, Vulkan external device/target handles,
and D3D12 external device/target handles match the right direction. They should
not be added until at least one backend can initialize or copy through a real
Chromium-owned path.

## Current Status

- SDL Vulkan native-window presentation remains supported and validated through
  `VulkanWindowHost`.
- C API raw CPU output remains supported and is the portable fallback selected
  explicitly by embedders.
- `--gpu-output-smoke` validates an internal Chromium-owned SharedImage
  CopyOutput result: Viz/SkiaRenderer can produce a GPU mailbox for the rendered
  frame.
- Embedder-owned Vulkan `VkImage` targeting is blocked pending the runtime
  ownership, same-device, copy, and synchronization wiring above.
- D3D12 GPU target support is design-only until a real Chromium D3D12/DXGI/Dawn
  host exists in the standalone runtime.
