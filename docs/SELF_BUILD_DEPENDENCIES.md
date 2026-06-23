# Self-Build Dependency Boundary

This repository is intended to build from tracked source plus declared external
dependencies. The current live Blink renderer still has one temporary
compatibility dependency that is not yet self-built by CMake.

## Declared Repository Inputs

- FreeType submodule:
  `upstream/chromium/third_party/freetype/src`
- HarfBuzz submodule:
  `upstream/chromium/third_party/harfbuzz/src`
- V8 submodule:
  `upstream/chromium/v8` at
  `d169ad0897a003432b64510f216f0b8365c78957`, from Chromium DEPS
  `v8_revision` at Chromium commit
  `e78920c00cfbfae3856eb6369ad339a4fb2b804e`
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

CMake now builds the tracked Abseil source subset needed by the live renderer
instead of consuming Abseil headers or object code from the V8 build scratch
directory. The old tracked `v8/include` header subset was removed because it
reported V8 14.9 while the working Blink/V8 compatibility boundary is V8 15.1.

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

The V8 source dependency is now explicit as a submodule, but this compatibility
tree is still not acceptable as the final self-build story because the
`v8_monolith.lib` and Chromium libc++ objects are generated under `build/` and
ignored by Git. The next build-system step is to make CMake invoke or depend on
the pinned V8 GN build instead of assuming this scratch tree already exists.

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

1. Build real V8/CppGC from the pinned V8 submodule with the current reduced
   GN args:

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
