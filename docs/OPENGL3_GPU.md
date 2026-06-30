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

The blocker is not Godot API shape yet. Blink first needs a service-side
OpenGL/ANGLE/SharedImage producer that can write to a caller-owned GL target.
Until that smoke exists, explicit OpenGL3 GPU should return unsupported and
Godot should continue using CPU raw/default output for Compatibility.
