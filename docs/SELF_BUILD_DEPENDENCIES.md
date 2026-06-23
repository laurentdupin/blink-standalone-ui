# Self-Build Dependency Boundary

This repository is intended to build from tracked source plus declared external
dependencies. The current live Blink renderer still has one temporary
compatibility dependency that is not yet self-built by CMake.

## Declared Repository Inputs

- FreeType submodule:
  `upstream/chromium/third_party/freetype/src`
- HarfBuzz submodule:
  `upstream/chromium/third_party/harfbuzz/src`
- vcpkg manifest packages:
  `libiconv`, `libxml2`, and `zlib`
- SDL3:
  fetched by CMake into the build tree when an installed SDL3 package is not
  found and `BLINK_STANDALONE_FETCH_SDL3=ON`

## Tracked Chromium Source Inputs

These are already present under `upstream/chromium` and should not come from a
generated build directory:

- `third_party/abseil-cpp`
- `third_party/zlib`
- `base/allocator/partition_allocator`
- `third_party/skia`
- `cc`
- `components/viz`
- `gpu`
- `third_party/blink`
- `v8/include`

CMake now builds the tracked Abseil source subset needed by the live renderer
instead of consuming Abseil headers or object code from the V8 build scratch
directory.

## Remaining Non-Self-Built Input

On Windows, the current CMake build still requires a GN-built V8/CppGC
compatibility tree:

- `BLINK_STANDALONE_V8_MONOLITH_LIB`
- `BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR`
- `BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS`

The default compatibility path is:

```text
build/v8_mono2/v8
```

This is not acceptable as the final self-build story because `build/` is
generated and ignored by Git.

## Why V8 Cannot Be Stubbed Out Safely Yet

The no-V8 link probe shows that `v8_monolith.lib` is not only satisfying public
JavaScript execution symbols. It also currently supplies:

- CppGC/Oilpan heap, cage, write-barrier, and liveness symbols
- V8 handle-scope, context, traced-reference, and CppHeap APIs used by Blink

Chromium-prefixed zlib aliases such as `Cr_z_*` and PartitionAlloc support
symbols, plus the Abseil object-code used by the live renderer, are now linked
from tracked Chromium sources by the CMake build instead of being supplied
incidentally by `v8_monolith.lib`.

Blink uses Oilpan object lifetime throughout the live document, layout, style,
paint, and input paths. A local fake CppGC replacement would risk invalid object
lifetime and is not a valid renderer foundation.

## Required Path To Full Self-Build

The next dependency work should replace the compatibility tree with CMake-owned
or explicitly external targets:

1. Build real V8/CppGC from a pinned V8 source dependency with the current
   reduced GN args:

   ```text
   is_debug=false
   target_cpu="x64"
   v8_target_cpu="x64"
   is_component_build=false
   v8_monolithic=true
   v8_static_library=true
   v8_use_external_startup_data=false
   use_lld=true
   is_clang=true
   use_custom_libcxx=true
   enable_safe_libcxx=true
   v8_enable_pointer_compression=true
   v8_enable_pointer_compression_shared_cage=true
   v8_enable_webassembly=false
   v8_enable_i18n_support=false
   v8_enable_v8_checks=false
   v8_enable_temporal_support=false
   enable_rust=false
   use_allocator_shim=false
   use_partition_alloc_as_malloc=false
   symbol_level=1
   ```

2. Make Chromium libc++ a declared source/build input instead of consuming
   object files from `build/v8_mono2`.
3. Keep the tracked-source zlib, PartitionAlloc, and Abseil source targets in
   the normal live renderer build graph while replacing the remaining V8/CppGC
   compatibility library.
4. Keep JavaScript disabled at the renderer API boundary. The V8/CppGC support
   target is currently an internal Blink lifetime/runtime requirement, not a
   public scripting feature.
