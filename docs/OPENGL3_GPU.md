# OpenGL3 Compatibility GPU Plan

This document tracks the Blink-side work needed before Godot Compatibility /
OpenGL3 can expose explicit GPU output for the standalone HTML/CSS renderer.

CPU raw output remains the supported Compatibility fallback. Explicit OpenGL3
GPU mode must not be exposed until Blink has a real GPU producer proof. A
readback followed by a Godot texture upload is CPU fallback, not OpenGL3 GPU
interop.

## Current State

The public GPU C ABI supports:

- CPU raw output;
- Vulkan external targets;
- D3D12 external targets.

There is no public OpenGL backend enum or external GL target struct today.

The current standalone build includes ANGLE `libEGL` and `libGLESv2` runtime
targets, but the configured ANGLE runtime is not a proven Godot OpenGL texture
interop path. The existing validated GPU target writers are Vulkan and D3D12.

The existing offscreen OpenGL path is Chromium-owned. `gpu::InProcessGpuThreadHolder`
creates the GL `SharedContextState`, and `viz::SkiaOutputDeviceOffscreen`
allocates and owns its own `GrBackendTexture`/`SkSurface`. That path can produce
Chromium-owned output, but it does not borrow or wrap an embedder texture.

Chromium also has a useful service-side copy primitive:
`gpu::CopySharedImageHelper::CopySharedImageToGLTexture()`. It can copy a
SharedImage mailbox into a destination OpenGL texture id by wrapping that
texture with `CreateSkSurfaceWrappingGLTexture()`. In this checkout it is only
usable when the destination texture is a valid service texture in Chromium's GL
context/share group. It is not currently a public standalone path for a Godot
texture or FBO.

## Candidate Producer Paths

### Native OpenGL Texture Or FBO

Blink would write into an embedder-owned GL texture or FBO while Godot owns the
OpenGL context. This is the most direct Compatibility backend shape, but it
requires a clear current-context and synchronization contract.

### ANGLE/EGL Texture Interop

Blink could render through ANGLE and share an EGL/GL texture with Godot if both
sides can establish compatible context sharing. This needs a Windows proof; it
must not be assumed from ANGLE being present in the build.

### SharedImage GL Backing

Chromium has GL SharedImage concepts, but this standalone cut has not proven a
service-side GL SharedImage target that wraps a caller-owned Godot texture. This
is likely the right Chromium-shaped architecture if the necessary GL factory and
access stream can be wired.

The imported GL SharedImage pieces are not enough yet:

- `gpu::WrappedSkImageBackingFactory` allocates Chromium-owned GL/Skia backing
  storage. It rejects non-empty GPU-memory-buffer handles and has no raw
  `GLuint`/FBO borrow path.
- `gpu::SharedImageManager::ProduceGLTexture()` and
  `ProduceGLTexturePassthrough()` need an existing registered backing; they do
  not register an arbitrary caller-owned texture by themselves.
- `gpu::ClientSharedImage::CreateGLTexture()` and
  `BeginGLAccessForCopySharedImage()` are fail-closed in
  `gpu_shared_image_phase3_bridge.cc`, so the standalone client cannot use
  client-side mailbox GL access as a workaround.

### Readback Then Upload

This remains CPU fallback and should stay behind CPU/default modes. It is not an
explicit OpenGL3 GPU solution.

## Likely Public ABI Shape

A future OpenGL target API would need:

- a new `BLINK_STANDALONE_GPU_BACKEND_OPENGL` backend value;
- renderer-level context configuration, including context/share-group identity
  and platform handles if required;
- target metadata for texture id or FBO id;
- texture target, internal format, width, height, device scale factor, alpha
  mode, and color space;
- ownership and generation fields;
- rules for which thread/context must be current during calls;
- synchronous completion or `GLsync` wait/signal fields;
- resize and target destruction lifetime rules.

## Required Smokes

Before exposing a Godot-facing ABI, Blink needs standalone smokes that:

1. create or borrow a GL context compatible with the intended path;
2. render deterministic HTML pixels into a caller-owned GL texture or FBO;
3. verify repeated frames without CPU raw fallback;
4. verify resize/recreate behavior;
5. verify click/action hit metadata still appears on GPU frames;
6. prove no CPU raw readback/upload is being used as the product path.

## Current Blocker

The blocker is not Godot API shape alone. Blink first needs a service-side
OpenGL/ANGLE/SharedImage producer that can write to a caller-owned GL target.
Until that smoke exists, explicit OpenGL3 GPU should return unsupported and
Godot should continue using CPU raw/default output for Compatibility.

The precise missing pieces are:

1. A standalone renderer hook to adopt or share with the embedder's OpenGL
   context/share group on the correct GPU sequence, or an ANGLE/EGL equivalent
   with a proven Windows and Godot Compatibility contract.
2. A borrowed GL target registration path, either a new SharedImage backing for
   caller-owned `GLuint` texture/FBO targets or a service-texture registration
   layer that makes the caller target valid for
   `CopySharedImageHelper::CopySharedImageToGLTexture()`.
3. A lifetime and synchronization contract. Blink must know when the caller's
   texture/FBO is alive, which context owns it, whether the texture target and
   internal format are compatible, and whether completion is synchronous or
   signaled through `GLsync`.
4. A pixel-bearing smoke that renders deterministic HTML through Viz/Skia into
   that caller-owned GL target, then verifies repeated frames and resize without
   CPU raw fallback.

The smallest useful implementation step is an internal-only GL copy smoke that
creates a texture in Chromium's service GL context and uses
`CopySharedImageHelper::CopySharedImageToGLTexture()` to copy the rendered
SharedImage mailbox into it. That would prove the service copy primitive, but it
would still not be a Godot/OpenGL3 producer proof until the texture is genuinely
caller-owned or shareable with the caller's context.
