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
- depot_tools submodule:
  `tools/depot_tools` at
  `ea253a3e3ae7653cafd343be001dc5cbe69b3ad0`
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

## V8 Compatibility Build Wrapper

The repository has a source-controlled wrapper for the V8 compatibility build:

```powershell
cmake --build build\cmake-live-image-png-ninja-vs18 --target blink_standalone_v8_compat
```

In the default configuration this target runs
`tools/v8/build_v8_monolith.py --action plan` only. It reports the pinned V8
submodule revision, generated work root, GN output directory, and reduced GN
arguments without cloning, syncing, running GN, or compiling V8.

Relevant CMake cache variables:

- `BLINK_STANDALONE_V8_SOURCE_ROOT`, default
  `upstream/chromium/v8`
- `BLINK_STANDALONE_V8_COMPAT_WORK_ROOT`, default
  `${CMAKE_BINARY_DIR}/v8_compat`
- `BLINK_STANDALONE_V8_COMPAT_OUT_NAME`, default `chromium_static`
- `BLINK_STANDALONE_V8_COMPAT_OUT_DIR`, default under the generated V8 work
  copy
- `BLINK_STANDALONE_DEPOT_TOOLS_ROOT`, default `tools/depot_tools`
- `BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE`
- `BLINK_STANDALONE_V8_GN_EXECUTABLE`
- `BLINK_STANDALONE_V8_NINJA_EXECUTABLE`
- `BLINK_STANDALONE_V8_CLANG_BASE_PATH`
- `BLINK_STANDALONE_V8_SYNC_DEPS`, default `OFF`
- `BLINK_STANDALONE_V8_COMPAT_BUILD`, default `OFF`
- `BLINK_STANDALONE_V8_COMPAT_ACTION`, default `auto`

`BLINK_STANDALONE_V8_COMPAT_ACTION` selects the wrapper stage:

- `auto`: preserve the older `BLINK_STANDALONE_V8_COMPAT_BUILD` behavior.
- `plan`: print paths, tool resolution, and GN arguments only.
- `prepare`: clone or update the generated V8 work copy, write `.gclient`,
  optionally run `gclient sync`, write `args.gn`, and stop before `gn gen`.
- `gn-gen`: run `prepare`, then run `gn gen`, and stop before Ninja.
- `build`: run `prepare`, `gn gen`, and `ninja v8_monolith`.

When the action reaches `prepare`, the wrapper clones or updates a generated V8
work copy under `${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8` from the pinned
submodule. It also clones or updates a generated depot_tools work copy under
`${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/depot_tools` from the pinned
`tools/depot_tools` submodule. Non-plan actions execute `gclient` and `gn` from
that generated depot_tools copy so bootstrap/CIPD payloads do not dirty the
tracked submodule. The wrapper writes a generated `.gclient` under the V8 work
root, uses a generated Git cache under
`${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/git_cache`, uses generated tool shims
under `${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/tool_shims`, and optionally runs
`gclient sync` if
`BLINK_STANDALONE_V8_SYNC_DEPS=ON`. `gclient` must not run inside
`upstream/chromium`; the generated work root exists specifically to avoid
colliding with tracked Chromium snapshot paths.

`BLINK_STANDALONE_V8_CLANG_BASE_PATH` defaults to empty. Leave it empty to let
V8/GN/depot_tools resolve clang; set it explicitly only when a known Chromium
clang checkout should be forced.

The current renderer link still consumes `BLINK_STANDALONE_V8_MONOLITH_LIB` and
the Chromium libc++ object files from `BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR`.
Those libc++ object filenames are now source-controlled in
`cmake/v8_compat_libcxx_objects.cmake` so the next step can point the link at
the generated compatibility output without relying on a configure-time glob.

`tools/depot_tools` is a declared submodule for locating and pinning
`gclient` and `gn`. The wrapper and CMake target prefer that submodule as the
source input, but generated CIPD payloads from depot_tools must remain
generated-only under the V8 compatibility work root. On Windows, the wrapper may
create generated helper shims such as `git.bat` in the generated depot_tools
copy when the local Git install exposes only `git.exe`, plus `python.bat` and
`python3.bat` under `tool_shims` so generated Ninja files do not pick up the
WindowsApps Python manager launcher. Do not run depot_tools bootstrap or
`gclient sync` inside the tracked source checkout.

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
