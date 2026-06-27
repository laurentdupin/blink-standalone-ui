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

`VulkanWindowHost` creates and owns its own Chromium Vulkan instance, device,
graphics/presentation queue, Win32 surface, swapchain, and command pool. Its
`Present()` path acquires a swapchain image, transitions it, calls
`SwapBuffers()`, and reports diagnostics. It does not receive a rendered
`VkImage` from `CompositorFrameResult`, and it has no hook to copy into an
external image.

The standalone direct cc/Viz frame sink can create an offscreen Viz `Display`
and can ask Viz for a copy of the submitted surface. That request is currently
hardwired to system memory:

```cpp
viz::CopyOutputRequest::ResultDestination::kSystemMemory
```

Chromium's `CopyOutputResult` supports `kSharedImage`, and this checkout imports
SharedImage/Vulkan backing code, including `ExternalVkImageBackingFactory`.
However, that is not yet connected to the standalone runtime in a way that can
target a caller-supplied `VkImage`.

## Why No Public API Yet

A real Godot-owned target path is not implementable in this checkpoint without
additional Chromium runtime wiring:

- The current runtime does not expose a GPU texture or SharedImage for the final
  submitted Viz frame.
- `VulkanWindowHost` uses a Chromium-owned device and swapchain; it cannot adopt
  Godot's `VkDevice`, `VkQueue`, or `VkImage`.
- The offscreen CopyOutput path returns CPU memory, not a SharedImage, mailbox,
  or Vulkan image.
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
2. Teach the standalone Viz output path to produce a GPU result that can be
   copied or rendered into another Vulkan image. The likely starting point is a
   texture-backed `CopyOutputRequest` or a custom output device that exposes the
   Skia/Vulkan backend texture.
3. Add a Vulkan target writer that can operate on the same `VkDevice`/queue
   family as the target, perform layout transitions, copy/resolve the rendered
   image, and signal completion.
4. Decide whether the runtime can consume an embedder-created device directly or
   whether the embedder must provide an importable memory handle instead of a
   raw `VkImage`.
5. Add an internal smoke using an external-like `VkImage`, with a hard failure
   if the path cannot write the image. Only after that should a public C ABI be
   added.

## Current Status

- SDL Vulkan native-window presentation remains supported and validated through
  `VulkanWindowHost`.
- C API raw CPU output remains supported and is the portable fallback selected
  explicitly by embedders.
- Embedder-owned Vulkan `VkImage` targeting is blocked pending the runtime
  wiring above.
- D3D12 GPU target support is design-only until a real Chromium D3D12/DXGI/Dawn
  host exists in the standalone runtime.
