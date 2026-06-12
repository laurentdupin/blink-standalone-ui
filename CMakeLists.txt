cmake_minimum_required(VERSION 3.26)
project(blink_standalone_ui LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
option(BLINK_STANDALONE_BUILD_SDL_VIEWER
  "Build the optional SDL3 viewer executables." ON)
option(BLINK_STANDALONE_FETCH_SDL3
  "Fetch SDL3 with CMake when an installed SDL3 package is unavailable." ON)
option(BLINK_STANDALONE_PERF_BUILD
  "Build standalone renderer benchmark targets with release-like perf defines." OFF)
option(BLINK_STANDALONE_OPTIMIZE_CHROMIUM
  "Compile upstream Chromium/Blink/cc/Skia/base sources with release optimization." ON)
option(BLINK_STANDALONE_OPTIMIZE_CODECS
  "Compile third-party image/codec sources with release optimization." ON)
option(BLINK_STANDALONE_OPTIMIZE_BOUNDARY
  "Compile standalone Blink boundary/stub/resource bridge sources with release optimization." ON)
option(BLINK_STANDALONE_OPTIMIZE_APP
  "Compile standalone benchmark/presenter application sources with release optimization." ON)

set(BLINK_STANDALONE_CHROMIUM_ROOT
  ${CMAKE_CURRENT_SOURCE_DIR}/upstream/chromium
)
set(BLINK_STANDALONE_RENDERER_ROOT
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer
)

set(BLINK_STANDALONE_FREETYPE_SOURCE
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/freetype/src
)
set(BLINK_STANDALONE_HARFBUZZ_SOURCE
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/harfbuzz/src
)

if(NOT EXISTS "${BLINK_STANDALONE_FREETYPE_SOURCE}/CMakeLists.txt" OR
   NOT EXISTS "${BLINK_STANDALONE_HARFBUZZ_SOURCE}/CMakeLists.txt")
  message(FATAL_ERROR
    "FreeType/HarfBuzz submodules are missing. Run: git submodule update --init --recursive")
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BROTLI ON CACHE BOOL "" FORCE)
add_subdirectory(${BLINK_STANDALONE_FREETYPE_SOURCE} third_party/freetype EXCLUDE_FROM_ALL)

set(HB_HAVE_CAIRO OFF CACHE BOOL "" FORCE)
set(HB_HAVE_FREETYPE ON CACHE BOOL "" FORCE)
set(HB_HAVE_GRAPHITE2 OFF CACHE BOOL "" FORCE)
set(HB_HAVE_GLIB OFF CACHE BOOL "" FORCE)
set(HB_HAVE_ICU OFF CACHE BOOL "" FORCE)
set(HB_HAVE_GOBJECT OFF CACHE BOOL "" FORCE)
set(HB_HAVE_INTROSPECTION OFF CACHE BOOL "" FORCE)
set(HB_HAVE_INTROSPECTION OFF)
set(HB_HAVE_UNISCRIBE OFF CACHE BOOL "" FORCE)
set(HB_HAVE_GDI OFF CACHE BOOL "" FORCE)
set(HB_HAVE_DIRECTWRITE OFF CACHE BOOL "" FORCE)
set(HB_BUILD_UTILS OFF CACHE BOOL "" FORCE)
set(HB_BUILD_SUBSET OFF CACHE BOOL "" FORCE)
set(HB_BUILD_RASTER OFF CACHE BOOL "" FORCE)
set(HB_BUILD_VECTOR OFF CACHE BOOL "" FORCE)
set(HB_BUILD_GPU OFF CACHE BOOL "" FORCE)
add_subdirectory(${BLINK_STANDALONE_HARFBUZZ_SOURCE} third_party/harfbuzz EXCLUDE_FROM_ALL)

find_package(Iconv REQUIRED)
find_package(Threads REQUIRED)
find_package(ZLIB CONFIG QUIET)
if(NOT ZLIB_FOUND)
  find_package(ZLIB REQUIRED)
endif()
if(TARGET ZLIB::ZLIBSTATIC AND NOT TARGET ZLIB::ZLIB)
  add_library(ZLIB::ZLIB INTERFACE IMPORTED)
  target_link_libraries(ZLIB::ZLIB INTERFACE ZLIB::ZLIBSTATIC)
endif()

find_package(libxml2 CONFIG QUIET)
if(TARGET LibXml2::LibXml2)
  set(LibXml2_FOUND ON)
endif()
if(NOT LibXml2_FOUND)
  find_package(LibXml2 REQUIRED)
endif()

if(BLINK_STANDALONE_BUILD_SDL_VIEWER)
  find_package(SDL3 CONFIG QUIET)
  if(NOT SDL3_FOUND AND BLINK_STANDALONE_FETCH_SDL3)
    set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_AUDIO OFF CACHE BOOL "" FORCE)
    set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
    set(SDL_DIALOG OFF CACHE BOOL "" FORCE)
    set(SDL_GPU OFF CACHE BOOL "" FORCE)
    set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
    set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
    set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
    set(SDL_TRAY OFF CACHE BOOL "" FORCE)
    set(SDL_RENDER ON CACHE BOOL "" FORCE)
    set(SDL_VIDEO ON CACHE BOOL "" FORCE)
    FetchContent_Declare(
      SDL3
      URL https://github.com/libsdl-org/SDL/releases/download/release-3.4.4/SDL3-3.4.4.tar.gz
      URL_HASH SHA256=ee712dbe6a89bb140bbfc2ce72358fb5ee5cc2240abeabd54855012db30b3864
    )
    FetchContent_MakeAvailable(SDL3)
  endif()
  if(TARGET SDL3::SDL3-static)
    set(BLINK_STANDALONE_SDL3_TARGET SDL3::SDL3-static)
  elseif(TARGET SDL3::SDL3)
    set(BLINK_STANDALONE_SDL3_TARGET SDL3::SDL3)
  elseif(TARGET SDL3::SDL3-shared)
    set(BLINK_STANDALONE_SDL3_TARGET SDL3::SDL3-shared)
  endif()
endif()

if(MSVC AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message(FATAL_ERROR
    "blink-standalone-ui requires clang-cl on Windows. Configure with the "
    "Visual Studio Clang toolset, for example: cmake -S . -B build/cmake "
    "-T ClangCL")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/live_blink_sources.cmake)

set(BLINK_STANDALONE_LIBPNG_ZLIB_C_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/png.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngerror.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngget.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngmem.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngpread.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngread.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngrio.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngrtran.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngrutil.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngset.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngtrans.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwutil.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/intel/filter_sse2_intrinsics.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/intel/intel_init.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/adler32.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/crc32.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/infback.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inffast.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inflate.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inftrees.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/zutil.c
)
set_source_files_properties(${BLINK_STANDALONE_LIBPNG_ZLIB_C_SOURCES}
  PROPERTIES LANGUAGE CXX)

if(BLINK_STANDALONE_PERF_BUILD)
  set(BLINK_STANDALONE_PERF_SKIA_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmapProcState_opts_ssse3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitMask_opts_ssse3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitRow_opts_ml3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMemset_opts_avx.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMemset_opts_erms.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSwizzler_opts_ml3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSwizzler_opts_ssse3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkGaussianColorFilter.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkPolyUtils.cpp
  )
  set(BLINK_STANDALONE_PERF_SKCMS_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformHsw.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformSkx.cc
  )
  list(APPEND BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_PERF_SKIA_SOURCES}
    ${BLINK_STANDALONE_PERF_SKCMS_SOURCES}
  )
  if(MSVC)
    set_property(SOURCE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformHsw.cc
      APPEND PROPERTY COMPILE_OPTIONS
        /clang:-mavx2
        /clang:-mf16c
        /clang:-ffp-contract=off
    )
    set_property(SOURCE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformSkx.cc
      APPEND PROPERTY COMPILE_OPTIONS
        /clang:-mavx512f
        /clang:-mavx512dq
        /clang:-mavx512cd
        /clang:-mavx512bw
        /clang:-mavx512vl
        /clang:-ffp-contract=off
    )
  endif()
endif()

set(BLINK_STANDALONE_APP_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/examples/render_benchmark.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/skia_cpu_renderer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/typeface_resource_registry.cc
)
set(BLINK_STANDALONE_SDL_APP_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/examples/sdl_viewer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/skia_cpu_renderer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/typeface_resource_registry.cc
)
set(BLINK_STANDALONE_BOUNDARY_SOURCES)
set(BLINK_STANDALONE_CODEC_SOURCES ${BLINK_STANDALONE_LIBPNG_ZLIB_C_SOURCES})
set(BLINK_STANDALONE_CHROMIUM_SOURCES)
foreach(source IN LISTS BLINK_STANDALONE_LIVE_SOURCES)
  if(source MATCHES "/standalone_renderer/src/")
    list(APPEND BLINK_STANDALONE_BOUNDARY_SOURCES ${source})
  elseif(source MATCHES "/third_party/skia/src/codec/" OR
         source MATCHES "/third_party/skia/third_party/externals/libpng/" OR
         source MATCHES "/third_party/libyuv/" OR
         source MATCHES "/third_party/zlib/")
    list(APPEND BLINK_STANDALONE_CODEC_SOURCES ${source})
  else()
    list(APPEND BLINK_STANDALONE_CHROMIUM_SOURCES ${source})
  endif()
endforeach()
list(REMOVE_DUPLICATES BLINK_STANDALONE_CODEC_SOURCES)
list(REMOVE_DUPLICATES BLINK_STANDALONE_BOUNDARY_SOURCES)
list(REMOVE_DUPLICATES BLINK_STANDALONE_CHROMIUM_SOURCES)

function(blink_standalone_apply_optimization_group group_name optimize)
  if(NOT MSVC OR NOT CMAKE_BUILD_TYPE MATCHES "^(Release|RelWithDebInfo)$")
    return()
  endif()
  if(${optimize})
    set(group_compile_options)
  else()
    set(group_compile_options /Od /Ob0 /Oy-)
  endif()
  foreach(source IN LISTS ARGN)
    if(group_compile_options)
      set_property(SOURCE ${source} APPEND PROPERTY COMPILE_OPTIONS
        ${group_compile_options}
      )
    endif()
    set_property(SOURCE ${source} PROPERTY BLINK_STANDALONE_COMPILE_GROUP ${group_name})
  endforeach()
endfunction()

blink_standalone_apply_optimization_group(
  chromium BLINK_STANDALONE_OPTIMIZE_CHROMIUM ${BLINK_STANDALONE_CHROMIUM_SOURCES})
blink_standalone_apply_optimization_group(
  codecs BLINK_STANDALONE_OPTIMIZE_CODECS ${BLINK_STANDALONE_CODEC_SOURCES})
blink_standalone_apply_optimization_group(
  boundary BLINK_STANDALONE_OPTIMIZE_BOUNDARY ${BLINK_STANDALONE_BOUNDARY_SOURCES})
blink_standalone_apply_optimization_group(
  app BLINK_STANDALONE_OPTIMIZE_APP ${BLINK_STANDALONE_APP_SOURCES} ${BLINK_STANDALONE_SDL_APP_SOURCES})

function(blink_standalone_json_source_list out_var group_name optimize)
  set(items "")
  foreach(source IN LISTS ARGN)
    file(RELATIVE_PATH rel_source "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
    string(REPLACE "\\" "/" rel_source "${rel_source}")
    string(APPEND items
      "    {\"source\":\"${rel_source}\",\"object\":\"\",\"group\":\"${group_name}\","
      "\"optimization\":\"$<IF:$<BOOL:${${optimize}}>,inherited Release /O2,/Od /Ob0 /Oy->\","
      "\"runtime_library\":\"${CMAKE_MSVC_RUNTIME_LIBRARY}\","
      "\"forced_includes\":[\"${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs/standalone_network_namespace_forwards.h\"]},\n")
  endforeach()
  set(${out_var} "${items}" PARENT_SCOPE)
endfunction()

blink_standalone_json_source_list(compile_group_chromium chromium BLINK_STANDALONE_OPTIMIZE_CHROMIUM ${BLINK_STANDALONE_CHROMIUM_SOURCES})
blink_standalone_json_source_list(compile_group_codecs codecs BLINK_STANDALONE_OPTIMIZE_CODECS ${BLINK_STANDALONE_CODEC_SOURCES})
blink_standalone_json_source_list(compile_group_boundary boundary BLINK_STANDALONE_OPTIMIZE_BOUNDARY ${BLINK_STANDALONE_BOUNDARY_SOURCES})
blink_standalone_json_source_list(compile_group_app app BLINK_STANDALONE_OPTIMIZE_APP ${BLINK_STANDALONE_APP_SOURCES})
set(compile_groups_json "${compile_group_chromium}${compile_group_codecs}${compile_group_boundary}${compile_group_app}")
string(REGEX REPLACE ",\n$" "\n" compile_groups_json "${compile_groups_json}")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/perf")
file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/build/perf/compile_groups.json"
  "{\n"
  "  \"schema_version\": 1,\n"
  "  \"build_dir\": \"${CMAKE_BINARY_DIR}\",\n"
  "  \"cmake_build_type\": \"${CMAKE_BUILD_TYPE}\",\n"
  "  \"options\": {\n"
  "    \"BLINK_STANDALONE_OPTIMIZE_CHROMIUM\": \"${BLINK_STANDALONE_OPTIMIZE_CHROMIUM}\",\n"
  "    \"BLINK_STANDALONE_OPTIMIZE_CODECS\": \"${BLINK_STANDALONE_OPTIMIZE_CODECS}\",\n"
  "    \"BLINK_STANDALONE_OPTIMIZE_BOUNDARY\": \"${BLINK_STANDALONE_OPTIMIZE_BOUNDARY}\",\n"
  "    \"BLINK_STANDALONE_OPTIMIZE_APP\": \"${BLINK_STANDALONE_OPTIMIZE_APP}\"\n"
  "  },\n"
  "  \"sources\": [\n"
  "${compile_groups_json}"
  "  ]\n"
  "}\n")

add_library(blink_live_modp_b64 OBJECT
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/modp_b64/modp_b64.cc
)
target_include_directories(blink_live_modp_b64 PRIVATE
  ${BLINK_STANDALONE_CHROMIUM_ROOT}
)

set(BLINK_STANDALONE_LIVE_OBJECTS
  $<TARGET_OBJECTS:blink_live_modp_b64>
)
if(NOT MSVC)
  add_library(blink_live_compiler_rt_atomic OBJECT
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/compiler-rt/src/lib/builtins/atomic.c
  )
  target_include_directories(blink_live_compiler_rt_atomic PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/compiler-rt/src/lib/builtins
  )
  list(APPEND BLINK_STANDALONE_LIVE_OBJECTS
    $<TARGET_OBJECTS:blink_live_compiler_rt_atomic>
  )
endif()

add_executable(blink_standalone_render_benchmark_skia
  ${BLINK_STANDALONE_APP_SOURCES}
  ${BLINK_STANDALONE_LIVE_SOURCES}
  ${BLINK_STANDALONE_LIVE_OBJECTS}
)

  target_include_directories(blink_standalone_render_benchmark_skia PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/overrides
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src/quiche/common/platform/default
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/allocator/partition_allocator/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/build_config
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/harfbuzz/src/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/highway/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/win32/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/libpng
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/v8/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/buildtools/third_party/libc++/src/include
    ${BLINK_STANDALONE_FREETYPE_SOURCE}/include
  )

  target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
    BLINK_CORE_IMPLEMENTATION=1
    BLINK_IMPLEMENTATION=1
    INSIDE_BLINK=1
    STANDALONE_RENDERER_GN_PROBE=1
    HTML_CSS_RENDERER_STANDALONE=1
    HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT=1
    HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL=1
    HTML_CSS_RENDERER_HAS_REDUCED_BLINK_PLATFORM=1
    HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER=1
    DCHECK_ALWAYS_ON=1
    WTF_IMPLEMENTATION=1
    USE_AURA=1
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_NONSTDC_NO_WARNINGS
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_DEPRECATE
    _WINSOCK_DEPRECATED_NO_WARNINGS
    UNICODE
    _UNICODE
    U_STATIC_IMPLEMENTATION
    U_I18N_IMPLEMENTATION
    U_COMMON_IMPLEMENTATION
    PNG_SET_OPTION_SUPPORTED=1
    PNG_INTEL_SSE=1
    ZLIB_IMPLEMENTATION=1
  )

  if(NOT BLINK_STANDALONE_PERF_BUILD)
    target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
      SKCMS_DISABLE_HSW=1
      SKCMS_DISABLE_SKX=1
      SK_ENABLE_OPTIMIZE_SIZE=1
      CPU_NO_SIMD=1
    )
  endif()

  target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
    ole32
    windowscodecs
  )

  if(MSVC)
    target_compile_options(blink_standalone_render_benchmark_skia PRIVATE
      /MP8
      /FI${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs/standalone_network_namespace_forwards.h
      /bigobj
      /permissive-
      /Zc:__cplusplus
      /wd4005
      /wd4068
      /wd4100
      /wd4127
      /wd4251
      /wd4267
      /wd4275
      /wd4324
      /wd4800
      /wd4996
    )
    target_link_options(blink_standalone_render_benchmark_skia PRIVATE
      /MAP:${CMAKE_BINARY_DIR}/blink_standalone_render_benchmark_skia.map
    )
  endif()

  target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
    freetype
    harfbuzz
    LibXml2::LibXml2
  )

  if(BLINK_STANDALONE_BUILD_SDL_VIEWER AND BLINK_STANDALONE_SDL3_TARGET)
    add_executable(blink_standalone_sdl_viewer_skia
      ${BLINK_STANDALONE_SDL_APP_SOURCES}
      ${BLINK_STANDALONE_LIVE_SOURCES}
      ${BLINK_STANDALONE_LIVE_OBJECTS}
    )

    target_include_directories(blink_standalone_sdl_viewer_skia PRIVATE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
      ${BLINK_STANDALONE_CHROMIUM_ROOT}
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/overrides
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src/quiche/common/platform/default
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/allocator/partition_allocator/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/build_config
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/harfbuzz/src/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/highway/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/src/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/win32/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/libpng
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/v8/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/buildtools/third_party/libc++/src/include
      ${BLINK_STANDALONE_FREETYPE_SOURCE}/include
    )

    target_compile_definitions(blink_standalone_sdl_viewer_skia PRIVATE
      BLINK_CORE_IMPLEMENTATION=1
      BLINK_IMPLEMENTATION=1
      INSIDE_BLINK=1
      STANDALONE_RENDERER_GN_PROBE=1
      HTML_CSS_RENDERER_STANDALONE=1
      HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT=1
      HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL=1
      HTML_CSS_RENDERER_HAS_REDUCED_BLINK_PLATFORM=1
      HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER=1
      DCHECK_ALWAYS_ON=1
      WTF_IMPLEMENTATION=1
      USE_AURA=1
      NOMINMAX
      WIN32_LEAN_AND_MEAN
      _CRT_NONSTDC_NO_WARNINGS
      _CRT_SECURE_NO_DEPRECATE
      _SCL_SECURE_NO_DEPRECATE
      _WINSOCK_DEPRECATED_NO_WARNINGS
      UNICODE
      _UNICODE
      U_STATIC_IMPLEMENTATION
      U_I18N_IMPLEMENTATION
      U_COMMON_IMPLEMENTATION
      PNG_SET_OPTION_SUPPORTED=1
      PNG_INTEL_SSE=1
      ZLIB_IMPLEMENTATION=1
      SDL_STATIC_LIB=1
    )

    if(NOT BLINK_STANDALONE_PERF_BUILD)
      target_compile_definitions(blink_standalone_sdl_viewer_skia PRIVATE
        SKCMS_DISABLE_HSW=1
        SKCMS_DISABLE_SKX=1
        SK_ENABLE_OPTIMIZE_SIZE=1
        CPU_NO_SIMD=1
      )
    endif()

    target_link_libraries(blink_standalone_sdl_viewer_skia PRIVATE
      ole32
      windowscodecs
    )

    if(MSVC)
      target_compile_options(blink_standalone_sdl_viewer_skia PRIVATE
        /FI${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs/standalone_network_namespace_forwards.h
        /bigobj
        /MP8
        /permissive-
        /Zc:__cplusplus
        /wd4005
        /wd4068
        /wd4100
        /wd4127
        /wd4251
        /wd4267
        /wd4275
        /wd4324
        /wd4800
        /wd4996
      )
    endif()

    target_link_libraries(blink_standalone_sdl_viewer_skia PRIVATE
      freetype
      harfbuzz
      LibXml2::LibXml2
      ${BLINK_STANDALONE_SDL3_TARGET}
      kernel32.lib user32.lib gdi32.lib winmm.lib imm32.lib ole32.lib
      oleaut32.lib version.lib uuid.lib advapi32.lib setupapi.lib shell32.lib
      dinput8.lib
    )
  endif()
