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

The next target-write checkpoint audited whether the texture CopyOutput result
could be copied into a caller-supplied `VkImage` without adding public ABI. The
answer is no in this checkout. `CopyOutputSharedImageResult` exposes a
`gpu::ClientSharedImage` to the caller, but the standalone probe currently sees
only client-visible metadata: size, format, mailbox, and creation sync token.
The backing `VkImage` is service-side state behind SharedImage representations.
The service-side APIs that can expose `SkiaImageRepresentation` or
`VulkanImageRepresentation` are not wired through `StandaloneCompositorRuntime`.
The client-side bridge remains fail-closed: `ClientSharedImage::Map()`,
`BeginRasterAccess()`, `BeginGLAccessForCopySharedImage()`,
`CreateGLTexture()`, `CloneGpuMemoryBufferHandle()`, and related helpers return
null or empty handles.

Chromium has GPU-side building blocks that could become the target writer:
`gpu::VulkanCommandBuffer` can perform image layout transitions and image/buffer
copies, and Viz/Skia has `BlitRequest` paths that write into SharedImage
destinations. Neither path currently accepts a raw externally supplied
`VkImage` from the standalone runtime. A real implementation needs either a
service-side mailbox-to-Vulkan-image access bridge plus a same-device target
copy command, or a registered external-target SharedImage backing for the
embedder image. The benchmark should not add `--gpu-external-vulkan-target-smoke`
until one of those paths is real.

## Route Audit: External Vulkan Target Writes

The two credible routes from the `--gpu-output-smoke` SharedImage mailbox to an
embedder-owned Vulkan target are both blocked today by missing service-side
SharedImage plumbing. Neither route should be exposed as public C ABI until an
internal smoke proves a real GPU-to-GPU write.

### Route A: Service-Side Mailbox Copy

The CopyOutput result is a `CopyOutputSharedImageResult` containing a
`gpu::ClientSharedImage`. The standalone probe can read client-visible metadata:
size, format, mailbox, and creation sync token. It does not receive the
service-side backing image.

Chromium's direct copy helper is `gpu::CopySharedImageHelper`. It is built
around `gpu::SharedImageRepresentationFactory` and `gpu::SharedContextState`,
and its `CopySharedImage()` path copies from one mailbox to another mailbox.
Internally it produces Skia representations for the source and destination
SharedImages. That is a real GPU-side path, but the destination must already be
a SharedImage mailbox; it does not accept an arbitrary raw `VkImage`.

The lower-level representation layer does contain `VulkanImageRepresentation`
and `ScopedAccess::GetVulkanImage()`, but those are service-side objects reached
through the SharedImage manager/representation factory. They are not exposed
through `StandaloneCompositorRuntime` or through the `ClientSharedImage`
metadata returned by the benchmark.

Route A would require a new runtime-internal GPU-service bridge that keeps
CopyOutput result ownership, accesses its service-side representation, and
submits a same-device copy into a registered destination. Without that bridge,
an external-target smoke would only validate metadata or CPU readback, not
external Vulkan output.

### Route B: Register Target Image as Writable SharedImage

The preferred route for Godot is to make the target texture a writable
SharedImage destination, then reuse Chromium's mailbox-to-mailbox copy/blit
machinery. That keeps external targets inside Chromium's existing SharedImage
lifetime, synchronization, and access model.

The relevant imported classes are `gpu::SharedImageFactory`,
`gpu::ExternalVkImageBackingFactory`, and `gpu::ExternalVkImageBacking`.
`SharedImageFactory` installs `ExternalVkImageBackingFactory` for Vulkan
`SharedContextState`s. The factory can create Chromium-owned external Vulkan
images, initialize from pixel data, or import a `gfx::GpuMemoryBufferHandle`.
It does not expose a path that wraps a borrowed raw `VkImage`.

The lower-level Vulkan helpers match that limitation. `gpu::VulkanImage` can be
created by Chromium or from a `gfx::GpuMemoryBufferHandle`; it does not have a
standalone borrowed-`VkImage` constructor. On the active Windows path,
`VulkanImplementationWin32::CreateImageFromGpuMemoryHandle()` is currently
`NOTIMPLEMENTED()` and returns `nullptr`, so even the GMB import route is not
ready for this Vulkan target use case in the generated Windows build.

Route B needs one real addition before a target smoke can exist:

- an importable platform memory-handle contract from the embedder, wired through
  `gfx::GpuMemoryBufferHandle` and `ExternalVkImageBackingFactory`; or
- a service-side SharedImage backing that explicitly wraps a borrowed `VkImage`,
  records that Chromium must not destroy it, handles layout/sync ownership, and
  exposes Skia/Vulkan write access through the normal representation APIs.

Route B is the better product architecture because a Godot-owned target becomes
a first-class SharedImage destination. Route A may still be useful as an
internal stepping stone, but it would otherwise create a separate raw-image copy
bridge beside Chromium's existing SharedImage access model.

### Borrowed `VkImage` Backing Audit

The next bounded audit checked whether Route B could be prototyped by adding a
small internal `SharedImageBacking` that wraps a caller-owned `VkImage`.

The useful existing write path is Viz `BlitRequest`. A `CopyOutputRequest` with
`ResultDestination::kSharedImage`, `result_selection`, and a `BlitRequest`
will make `SkiaOutputSurfaceImplOnGpu::CopyOutputRGBAInTexture()` look up the
destination mailbox through `SharedImageManager::ProduceSkia()` with
`SHARED_IMAGE_USAGE_DISPLAY_WRITE`, begin a Skia write access, and render the
CopyOutput result into that destination surface. This is the right path for
Godot because it writes into a destination SharedImage rather than returning a
separate Chromium-owned output mailbox.

The missing piece is a valid destination SharedImage backing for a borrowed
raw Vulkan image. The current Vulkan backings are not a small fit:

- `ExternalVkImageBackingFactory` creates Chromium-owned Vulkan images through
  `ExternalVkImageBacking::Create()`, or imports a platform
  `gfx::GpuMemoryBufferHandle` through `CreateFromGMB()`. It has no raw
  borrowed-`VkImage` constructor.
- `ExternalVkImageBacking` stores `TextureHolderVk` entries containing
  `std::unique_ptr<gpu::VulkanImage>`. Its destructor schedules those
  `VulkanImage` objects for cleanup through `VulkanFenceHelper`, so using this
  class directly would transfer destruction ownership to Chromium.
- `gpu::VulkanImage::Create(device_queue, VkImage, VkDeviceMemory, ...)` can
  wrap existing handles, but it is still an owning wrapper: `Destroy()` calls
  `vkDestroyImage()` and destroys the wrapped `VkDeviceMemory`, and the
  destructor DCHECKs that cleanup has happened. It is not safe for a
  Godot-owned image without a new non-owning mode.
- `CreateGrVkImageInfo()` fills Skia's `GrVkImageInfo` from
  `gpu::VulkanImage`, including `fAlloc.fMemory`, allocation size, memory type,
  usage flags, tiling, queue family, and layout. Godot's reviewed handle set
  exposes `VkImage`/`VkImageView`/format, but not `VkDeviceMemory`, allocation
  size, or memory type. A borrowed backing must either require that extra
  allocation metadata or prove that the active Skia/Vulkan path can safely wrap
  the image without it.
- The existing `ExternalVkImageSkiaImageRepresentation` is coupled to
  `ExternalVkImageBacking` synchronization state, promise textures, external
  semaphore pool, and GL/Vulkan interop behavior. A borrowed backing would need
  its own Skia representation and explicit layout/semaphore contract rather
  than reusing that class unchanged.
- On the active Windows Vulkan build, `VulkanImplementationWin32::
  CreateImageFromGpuMemoryHandle()` remains `NOTIMPLEMENTED()`, so the
  `GpuMemoryBufferHandle` import route is not currently a shortcut around raw
  image wrapping.

The imported Chromium tree contains `viz::VulkanInProcessContextProvider`,
`SkiaOutputDeviceVulkan`, and `SkiaOutputDeviceVulkanSecondaryCB`, and they are
buildable in the generated Windows build. The benchmark smoke
`--gpu-vulkan-ganesh-context-smoke` proves the context-only piece: it creates a
`viz::VulkanInProcessContextProvider`, constructs an offscreen
`gpu::SharedContextState` with `GrContextType::kVulkan`, and initializes a
Vulkan Ganesh `GrDirectContext` without an SDL window, HWND, surface, or
swapchain.

`--gpu-output-vulkan-smoke` wires that context provider into the actual
standalone offscreen runtime path. It proves the Viz frame path reaches
`vk_context_provider=1`, `is_vulkan=1`, `viz_display=1`, `skia_gpu=1`, and still
produces a Chromium-owned SharedImage mailbox.

`--gpu-borrowed-vkimage-backing-smoke` is the first borrowed target proof on
that Vulkan-backed runtime path. It creates a local `VkImage` on the Chromium
Vulkan device as an external-image stand-in, registers a standalone
`SharedImageBacking` that borrows the image without owning it, writes known
content through a Skia Ganesh representation, verifies the result with CPU
readback, releases the backing, and only then explicitly destroys the target
image. The write path under test is GPU-backed; readback is verification only.
The smoke must run the borrowed SharedImage setup on the Vulkan context's owner
sequence because `SharedContextState` is sequence checked.

This smoke is intentionally Skia direct-write only. It does not prove copying
the rendered Viz output into the borrowed target.

`--gpu-output-vulkan-pixel-smoke` narrows the next blocker. It requests the same
offscreen Vulkan SharedImage CopyOutput as `--gpu-output-vulkan-smoke`, then
reads that source mailbox back through the GPU-service Skia representation. The
submitted cc frame is not empty: the diagnostic frame dump shows damage, a
non-transparent root background, three quads, and the expected `#123456` color
quad. The Vulkan CopyOutput source SharedImage still reads back as fully
transparent (`nontransparent_pixels=0`, background and box samples
`00000000`).

`--gpu-borrowed-vkimage-render-copy-smoke` is the next render-output attempt. It
prepares the same borrowed `VkImage` backing as a writable SharedImage
destination, passes it to `CopyOutputRequest::set_blit_request()`, and lets Viz
write into the target through the Vulkan offscreen runtime path. That proves the
borrowed target can be registered as the BlitRequest destination without the
earlier client `ClientSharedImage` sequence/lifetime DCHECK, and the smoke
releases the backing before explicitly destroying the stand-in `VkImage`.

The render-copy smoke is still blocked as a rendered-output proof because it
inherits the transparent source. `SkiaOutputSurfaceImplOnGpu::CopyOutputRGBAInTexture()`
is reached, but the `SkSurface*` supplied to that texture CopyOutput path does
not contain the rendered cc content in this standalone offscreen Vulkan
configuration. The current blocker is therefore not
borrowed target ownership or BlitRequest destination registration; it is the
offscreen Vulkan SkiaOutputSurface/CopyOutput source surface integration between
Viz's submitted cc frame and `CopyOutputRGBAInTexture()`.

The next focused audit narrowed that blocker further. Instrumentation showed
that `SkiaOutputSurfaceImplOnGpu::FinishPaintCurrentFrame()` reaches the Vulkan
path and `scoped_output_device_paint_->Draw(ddl)` returns success, but an
immediate readback of the same source `SkSurface` used by
`CopyOutputRGBAInTexture()` is still fully transparent before the SharedImage
copy starts. This rules out the borrowed destination, BlitRequest destination
registration, and texture-copy destination write as the first content-loss
point.

The standalone cc frame sink still creates its compositor and worker raster
providers through `StandaloneInProcessRasterContextProvider`, and frame-sink
creation forces the in-process GPU holder's `gr_context_type` to
`gpu::GrContextType::kGL`. The opt-in offscreen output surface is Vulkan-only,
so the current diagnostic path mixes a GL command-buffer/raster content path
with a separate Vulkan Ganesh output surface. A bounded test that changed that
GPU holder preference to `gpu::GrContextType::kVulkan` failed earlier:
`gpu::RasterInProcessContext` could not create its `SharedContextState`
(`GrContext creation failed`), the `LayerTreeFrameSink` did not initialize, and
no Viz `Display` or SharedImage CopyOutput was produced. That makes the next
missing integration step explicit: the standalone runtime needs a coherent
Vulkan-capable cc/raster command-buffer context provider, or a real
Chromium-supported SharedImage interop bridge between the existing GL raster
resources and the Vulkan Skia output surface. Flipping the existing GL holder
to Vulkan is not sufficient in this checkout.

The remaining implementation steps before public ABI are:

1. Define the external target metadata and synchronization contract: at minimum
   image size, format, usage, current/final layout, queue family, and wait/signal
   synchronization; likely also `VkDeviceMemory`, allocation size, and memory
   type unless Skia validation proves those can be omitted.
2. Extend the borrowed backing beyond the smoke path with explicit
   acquire/release layout and semaphore handling, still without destroying
   borrowed `VkImage`, memory, image views, semaphores, or fences.
3. Make the offscreen Vulkan CopyOutput/BlitRequest path produce rendered HTML
   pixels, not just a SharedImage mailbox. The current pixel-content smoke
   shows the cc frame has content but the Vulkan CopyOutput source SharedImage
   is transparent. Root DDL replay reports success, but the source
   `SkSurface` is already transparent before CopyOutput. The current standalone
   gap is a coherent Vulkan cc/raster context path, or equivalent
   Chromium-owned GL-to-Vulkan SharedImage interop, for the offscreen runtime.
4. Once CopyOutput content is non-empty, keep the destination as a service-side
   SharedImage and validate either direct Viz `BlitRequest` into the borrowed
   target or a service-side SharedImage-to-SharedImage copy into it. Only after
   that should public C ABI be added.

## Why No Public API Yet

A real Godot-owned target path is not yet ready for public ABI because the
rendered-output copy step and embedder synchronization contract are still
missing:

- The current runtime can prove a Chromium-owned SharedImage mailbox for the
  final submitted Viz frame, a Skia Ganesh direct-write into a borrowed stand-in
  `VkImage`, and a Viz BlitRequest targeted at that borrowed backing. It does
  not yet prove rendered HTML pixels in that target because the offscreen Vulkan
  CopyOutput/BlitRequest source is currently transparent.
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
5. Add an internal smoke that copies rendered Viz output into an external-like
   `VkImage`, with a hard failure if the path cannot write the image. Only after
   that should a public C ABI be added.

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

The current audit found no direct Ganesh-D3D12 route analogous to the working
Vulkan Ganesh path. `gpu::GrContextType` only has `kGL`, `kVulkan`, and
`kGraphiteDawn`; `gpu::SharedContextState::InitializeGanesh()` handles GL and
Vulkan, then CHECKs that the non-GL Ganesh path is Vulkan. Skia's Ganesh D3D
headers are present in `third_party/skia/include/gpu/ganesh/d3d`, but this
standalone Chromium integration does not expose a `GrContextType::kD3D` or a
Viz `SkiaOutputSurface` path using those headers.

Chromium's current D3D12 compositor direction in this checkout is
Graphite/Dawn:

- `gpu::DawnContextProvider` can create Dawn contexts and exposes
  `GetD3D12CommandQueue()` on Windows.
- `viz::SkiaOutputDeviceDawn` can present through a Dawn surface and uses a
  child HWND for D3D swapchains on Windows.
- D3D/DXGI SharedImage classes exist, including `D3DImageBackingFactory`,
  `D3DImageBacking`, `DXGISharedHandleManager`, and Dawn/Graphite
  representations.

Those pieces are not active in the standalone build. The relevant Chromium
paths are explicitly gated out under `HTML_CSS_RENDERER_STANDALONE`:

- `gpu::SharedContextState::InitializeGraphite()` only calls
  `DawnContextProvider::InitializeGraphiteContext()` under
  `BUILDFLAG(SKIA_USE_DAWN) && !defined(HTML_CSS_RENDERER_STANDALONE)`.
- `viz::CompositorGpuThread` only carries a shared Dawn provider under the same
  non-standalone gate.
- `viz::SkiaOutputSurfaceImplOnGpu::InitializeForDawn()` is also compiled out
  for standalone.
- `viz::GpuServiceImpl` removes its Dawn provider and D3D factory setup from
  the standalone path.
- The standalone runtime dependency currently returns `nullptr` from
  `StandaloneSkiaOutputSurfaceDependency::GetDawnContextProvider()`.

The generated CMake target also does not wire the Dawn/D3D implementation files
needed for a real D3D12 smoke, including `dawn_context_provider.cc`,
`dawn_instance.cc`, `dawn_platform.cc`, `skia_output_device_dawn.cc`,
`d3d_image_backing.cc`, `d3d_image_backing_factory.cc`,
`dxgi_shared_handle_manager.cc`, `wrapped_graphite_texture_backing.cc`, and
`skia_graphite_dawn_image_representation.cc`. The repository includes many of
those source files, but they are not part of the standalone generated-V8
ChromiumLLVM target.

Therefore a bounded `--gpu-output-d3d12-smoke` is not currently honest: the
runtime cannot create a D3D12-backed `SharedContextState`, cannot hand Dawn to
Viz, and cannot produce a D3D12 texture-backed CopyOutput source. A real D3D12
checkpoint should first add an internal Graphite/Dawn bootstrap for standalone:

1. Enable/build the required Dawn/Graphite/D3D source files and generated Dawn
   libraries for the standalone target.
2. Add a standalone `DawnContextProvider` owner analogous to the Vulkan
   provider owner, with an opt-in `GrContextType::kGraphiteDawn` runtime flag.
3. Return that provider from
   `StandaloneSkiaOutputSurfaceDependency::GetDawnContextProvider()`.
4. Prove `SharedContextState::IsGraphiteDawnD3D()` and a non-null Graphite
   context in an offscreen smoke.
5. Only then add a pixel-bearing D3D12 CopyOutput smoke and, later, a borrowed
   `ID3D12Resource`/DXGI shared-handle target proof with explicit resource
   states and fence wait/signal ownership.

The first implementation retry after the Vulkan pixel-bearing checkpoint added
`--gpu-output-d3d12-pixel-smoke` as an explicit diagnostic gate. In the current
generated standalone checkout it reports blocked before runtime because:

- `generated/blink_live/gen/skia/buildflags.h` sets `SKIA_USE_DAWN` to `0`.
- `generated/blink_live/gen/ui/gl/buildflags.h` sets `USE_DAWN` to `0`.
- `third_party/dawn/include` is present, but `third_party/dawn/src` is not
  present in this checkout and the active build tree contains no Dawn native
  libraries.

The next implementation retry proved the first part of that blocker is
recoverable. `standalone_renderer/tools/build_dawn_d3d12_native.py` fetches the
Skia-pinned Dawn revision into the build tree, syncs Dawn's own native
dependencies with Dawn's depot-tools-free fetch helper, configures Dawn with
D3D12 enabled and the other native backends disabled, and builds:

- `webgpu_headers_gen`
- `dawn_proc`
- `dawn_native`

That produces generated Dawn/WebGPU headers plus `dawn_native.lib` and
`dawn_proc.lib` under the selected build directory. The experimental
`BLINK_STANDALONE_DAWN_D3D12` CMake option can consume those headers and
libraries for the benchmark target. With that option enabled,
`--gpu-output-d3d12-pixel-smoke` now proves a real Dawn D3D12 GPU path by
creating a D3D12 adapter/device, clearing an `RGBA8Unorm` texture, copying it to
a readback buffer, and validating deterministic pixels. This is a D3D12 texture
pixel proof, not yet a standalone HTML/Viz output proof.

The next implementation step moved from the Dawn texture proof to Chromium's
Graphite/Viz path. The opt-in compile surface behind
`BLINK_STANDALONE_DAWN_D3D12`: standalone Dawn buildflag overrides, a scoped
`BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER` guard, and the minimum
Dawn/Graphite/D3D source files. The following objects compile in the benchmark
target:
`dawn_context_provider`, `dawn_instance`, `dawn_platform`,
`skia_output_device_dawn`, `image_context_impl`,
`wrapped_graphite_texture_backing`, `skia_graphite_dawn_image_representation`,
`dawn_fallback_image_representation`, `d3d_image_backing`,
`d3d_image_backing_factory`, `d3d_image_representation`, `d3d_image_utils`,
`dxgi_shared_handle_manager`, and the SharedImage Dawn utility objects.

`--gpu-output-d3d12-render-pixel-smoke` now initializes a standalone Dawn D3D12
provider, creates a Graphite-backed `SharedContextState`, drives Viz/SkiaRenderer
for deterministic HTML/CSS content, obtains a D3D12-backed CopyOutput
SharedImage, then performs a system-memory CopyOutput readback from the same
runtime and verifies the expected CSS background and box colors. This is a
pixel-bearing rendered HTML proof for the internal D3D12 Graphite/Viz path.

`--gpu-borrowed-d3d12-render-copy-smoke` is the matching internal external
target proof. It creates a stand-in `ID3D12Resource` on the active Dawn D3D12
device, registers it as a borrowed SharedImage backing, asks Viz to write the
rendered HTML CopyOutput into that destination through `BlitRequest`, and then
verifies deterministic CSS pixels with a direct D3D12 readback. The backing does
not own or destroy the target resource; the smoke releases the SharedImage
registration before destroying the stand-in resource.

This proves that the standalone D3D12 Graphite/Viz path can write rendered HTML
pixels into a borrowed D3D12 texture destination. The current public C ABI uses
that proven path for an internal stand-in target; real embedder handles are
reserved in the ABI but still return an explicit unsupported status until the
handle-adoption layer is implemented.

### Public ABI Direction

The public GPU ABI is presentation-independent and does not mention SDL, HWND,
or swapchains. The exported surface is:

```c
blink_standalone_renderer_gpu_backend_capabilities(renderer, backend)
blink_standalone_renderer_render_to_gpu_target(renderer, target, result)
```

`blink_standalone_external_gpu_target_t` contains a backend-neutral common
section plus Vulkan and D3D12 target sections. The common section carries
logical size, physical size, device scale factor, pixel format, alpha mode,
color space, generation, and flags. The Vulkan section reserves `VkImage`,
format, extent, current/final layout, queue family, and wait/signal semaphore
metadata. The D3D12 section reserves `ID3D12Device*`, `ID3D12CommandQueue*`,
`ID3D12Resource*`, DXGI format, extent, current/final resource state, and
wait/signal fence metadata.

GPU target mode is explicit opt-in. The C API raw CPU output path remains the
portable default and is selected only through `advance_frame` plus
`get_latest_output`. `render_to_gpu_target` does not silently fall back to CPU
output. Unsupported backends, unavailable platform support, invalid target
metadata, or real external handles that this build cannot yet adopt return
`BLINK_STANDALONE_STATUS_UNSUPPORTED` or another non-OK status with
renderer-local diagnostics.

The current public ABI validation uses
`BLINK_STANDALONE_GPU_TARGET_INTERNAL_TEST_STANDIN`. That flag creates a
stand-in target on the active standalone GPU device and verifies rendered HTML
pixels through the same public C API call:

```text
--c-api-vulkan-external-target-smoke
--c-api-d3d12-external-target-smoke
```

This is a real C ABI boundary and target-writer validation, but it is not yet
the final Godot handle path. The next implementation checkpoint is to replace
the stand-in target with embedder-provided `VkImage` / `ID3D12Resource` handles,
validate device/queue compatibility, and honor the public layout/resource-state
and synchronization fields.

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
- `--gpu-output-vulkan-pixel-smoke` validates pixel-bearing rendered HTML output
  from the offscreen Vulkan CopyOutput source.
- `--gpu-borrowed-vkimage-render-copy-smoke` validates that rendered HTML pixels
  can be written through Viz `BlitRequest` into a borrowed Vulkan `VkImage`
  backing and read back for verification.
- `--gpu-output-d3d12-pixel-smoke` validates a standalone Dawn D3D12 GPU texture
  clear/copy/readback path.
- `--gpu-output-d3d12-render-pixel-smoke` validates pixel-bearing rendered HTML
  output from the D3D12 Graphite/Viz path.
- `--gpu-borrowed-d3d12-render-copy-smoke` validates that rendered HTML pixels
  can be written through Viz `BlitRequest` into a borrowed D3D12
  `ID3D12Resource` backing and read back for verification.
- `--c-api-vulkan-external-target-smoke` validates the public C API GPU target
  call for Vulkan using the internal stand-in target flag.
- `--c-api-d3d12-external-target-smoke` validates the public C API GPU target
  call for D3D12 using the internal stand-in target flag.
- Real embedder-owned native handle adoption is still pending. The ABI reserves
  the required Vulkan and D3D12 metadata, but non-stand-in targets currently
  return explicit unsupported status rather than falling back to CPU.
