# Static C API Package Plan

This document tracks the Blink-side work needed before Godot can consume the
standalone renderer as a static library instead of the C API runtime DLL.

The supported embedder API remains the `blink_standalone_renderer_*` C ABI. A
static package changes the link and deployment model only; it must not expose
Chromium, Blink, V8, Skia, Dawn, ANGLE, or Viz C++ internals to Godot.

## Current State

`blink_standalone_renderer_c_api` builds a static archive, but it is not yet a
complete static package. The archive does not fold all transitive static
dependencies, object files, whole-archive needs, sidecars, or toolchain
assumptions.

`blink_standalone_renderer_c_api_static_package` is the first evaluation target.
It exports:

- the renderer static archive;
- the public C API header;
- a static-link manifest;
- runtime sidecars that are still required by the current build.

The manifest intentionally reports `static_link_complete_by_itself: false`.
The external static proof now closes for raw output; static linking is not yet
product-supported until GPU external-target smokes pass from the same package
metadata.

## Required Package Contract

A supported static package must enumerate:

- renderer static archive path;
- V8 monolith path;
- Chromium libc++ object list when the selected toolchain needs it;
- Dawn D3D12 static libraries when D3D12 is enabled;
- third-party libraries or package targets, including Freetype, HarfBuzz, XML,
  zlib/libpng, Abseil, ICU, Skia, ANGLE, Dawn, and PartitionAlloc pieces;
- Windows system libraries;
- required `/WHOLEARCHIVE` or equivalent linker flags;
- public include roots and required consumer defines;
- CRT/STL/toolchain assumptions;
- required runtime sidecars and data files.

## Sidecars That Remain

Static linking does not remove all runtime files. The current package still
expects:

- `icudtl.dat`;
- `libEGL.dll` and `libGLESv2.dll` unless a static ANGLE package is added and
  validated separately;
- D3D shader compiler sidecars such as `d3dcompiler_47.dll`, and optionally
  `dxcompiler.dll` / `dxil.dll` when the Dawn build requires them;
- platform GPU runtimes and drivers, including Vulkan and D3D system runtimes.

## Hazards

- Chromium, Skia, ICU, ANGLE, Dawn, and V8-adjacent state includes process-global
  singletons.
- Godot and Blink must agree on CRT and STL boundaries. Godot must not free
  renderer-owned memory.
- Registration-heavy Chromium/Viz/GPU objects may need whole-archive linking.
- Static linking can expose duplicate symbols that DLL packaging hides.
- Link time, PDB size, and final binary size will increase materially.
- Shutdown ordering must still destroy renderer instances before global runtime
  teardown.
- Link `v8_monolith.lib` normally, not as `/WHOLEARCHIVE`; whole-archiving V8
  duplicates Chromium zlib symbols such as `Cr_z_inflateReset`.
- Do not add the Chromium libc++ object list separately when linking the
  renderer static archive. The archive currently folds those objects, and adding
  them again duplicates `std::__Cr` symbols such as `bad_any_cast::what` and
  `__atomic_wait_global_table`.

## Milestones

1. Build `blink_standalone_renderer_c_api_static_package` from a clean generated
   V8 configuration.
2. Add a tiny external CMake or command-line link proof that consumes only the
   package manifest and public header.
3. Make the link proof create and destroy a renderer. Done for the generated-V8
   ChromiumLLVM package: the proof links when only the renderer archive is
   whole-archived, V8 is linked normally, the manifest third-party archive list
   is included, and sidecars are deployed beside the proof executable.
4. Extend the proof to a CPU raw `--c-api-smoke` equivalent. Done by
   `upstream/chromium/standalone_renderer/tools/static_package_probe`, which
   consumes the generated static package manifest and public header, renders
   deterministic HTML/CSS, verifies raw output dimensions/stride/pixels/dirty
   rects, and verifies hit metadata.
5. Extend validation to Vulkan and D3D12 external target smokes.
6. Only after those pass, mark the static package as link-complete for the
   validated toolchain.

## First Acceptance Checkpoint

The raw-output checkpoint is complete. The remaining first product blocker is
GPU external-target smoke coverage from an external static executable, not CPU
raw-output link closure.
