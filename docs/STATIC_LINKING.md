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

`blink_standalone_renderer_c_api_static_package` is the first packaged static C
API target. It exports:

- the renderer static archive;
- the public C API header;
- a package-relative static-link manifest;
- package-local V8, Freetype, HarfBuzz, libxml2, ANGLE import libraries, and
  selected generated Dawn libraries when enabled;
- runtime sidecars that are still required by the current build.

The manifest intentionally reports `static_link_complete_by_itself: false`.
The MSVC package has an isolated external raw-output proof that consumes only
the package manifest, package-local files, public C header, and Windows system
libraries. It renders deterministic HTML/CSS raw pixels, verifies hit metadata,
and checks that `blink_standalone_renderer_c_api.dll` is not loaded. This proves
isolated external consumption of the static C API package metadata. It does not
prove that the full Godot editor/export binary can link this monolithic archive.

Godot static consumption is currently blocked by duplicate third-party symbols
when linking against the full editor, even without `/WHOLEARCHIVE`. The current
renderer archive folds Chromium/Blink/Skia object files and third-party source
objects into one archive, including libpng, ICU, zlib, VMA, and Abseil-style
global symbols that Godot can also own. Do not use `/FORCE:MULTIPLE` as product
behavior; it is diagnostic only.

The static manifest therefore reports `full_host_static_link_supported: false`
and `full_host_static_link_blocker:
monolithic_renderer_archive_exports_chromium_third_party_symbols`. The isolated
static probes validate package metadata and the C ABI, but they do not prove
that the full Godot editor/export binary can safely link the archive.

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
- packaged Vulkan headers and Vulkan loader expectations for static GPU
  consumers;
- CRT/STL/toolchain assumptions;
- required runtime sidecars and data files.
- CRT/STL compatibility fields. MSVC consumers must match the package CRT
  family, architecture, configuration, and `_ITERATOR_DEBUG_LEVEL`.

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
- Full Godot static linking needs symbol isolation or a validated dependency
  ownership split before it can be considered product-supported. The isolated
  static probe is necessary package validation, not proof that the full Godot
  binary can safely consume the archive.

## Full Host Static Link Blocker

The current monolithic archive is collision-prone by construction. It contains
object files that define globally visible third-party symbols such as libpng
`png_*`, ICU `u_*`/`icu_*`, Chromium zlib `Cr_z_*`, Abseil, and Chromium
libc++-style symbols. A full host like Godot can already define some of those
families before Blink is linked, so normal archive member extraction is enough
to produce `LNK2005`; removing broad `/WHOLEARCHIVE` does not solve the
underlying ownership collision.

Vulkan Memory Allocator is the first isolated family. In standalone builds,
Blink includes `standalone_renderer/src/private_vma_symbol_prefix.h` before
`vk_mem_alloc.h` in the Skia VMA implementation and Chromium VMA users. The
MSVC object-level proof verifies that `vmaCreateAllocator` is absent and
`blink_standalone_vmaCreateAllocator` is present in the bundled VMA
implementation object. This removes the known VMA collision family, but it does
not make full-host static linking product-supported until the remaining
third-party families are isolated or otherwise proven safe.

The preferred product fix is symbol isolation for Blink-owned third-party
dependencies in the static package. Candidate work:

- build Blink's bundled libpng/zlib/ICU/Abseil-facing objects with private
  symbol prefixes or private namespaces where the upstream dependency supports
  that;
- keep V8, Skia, Blink, Dawn, ANGLE, and ICU data coupled to the exact
  dependency revisions and defines they were built with;
- update the static manifest to report private/renamed third-party ownership
  only after a full Godot editor/export link and the isolated static probes pass.

A granular dependency split is only safe if each dependency is proven
ABI/config-compatible with Chromium/Skia/V8 expectations. Reusing Godot-owned
ICU, libpng, zlib, VMA, or Abseil by default is high risk and is not currently a
supported package contract.

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
5. Extend validation to Vulkan and D3D12 external target smokes. This remains
   open for the MSVC package: the isolated GPU probe links, but the package does
   not yet ship Vulkan headers for the probe and D3D12 does not reach a ready
   LayerTreeFrameSink in that static run.
6. Only after those pass, mark the static package as link-complete for the
   validated toolchain.

## First Acceptance Checkpoint

The raw-output checkpoint is complete for the MSVC Windows package when the
static probe is run from `upstream/chromium/standalone_renderer/tools/static_package_probe`.
The package remains a "static C API package with runtime sidecars", not a
fully sidecar-free static renderer. OpenGL3 remains unsupported because no
caller-owned GL/ANGLE texture or FBO producer proof exists.

For seamless Godot builds, consume the promoted static package archive under
`prebuilt/windows-x86_64-msvc-static/` rather than generating V8 or the static
package during the normal Godot build. The extracted package manifest is the
authoritative link contract; the unpacked package directory remains generated
output.
