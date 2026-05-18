cmake_minimum_required(VERSION 3.26)
project(blink_standalone_ui LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
option(BLINK_STANDALONE_BUILD_SDL_VIEWER
  "Build the optional SDL3 viewer executables." ON)
option(BLINK_STANDALONE_FETCH_SDL3
  "Fetch SDL3 with CMake when an installed SDL3 package is unavailable." ON)
option(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG
  "Experimental: link the real Blink PNG image resource/decode path instead of standalone null image stubs." OFF)

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
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/examples/render_benchmark.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/skia_cpu_renderer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/typeface_resource_registry.cc
  ${BLINK_STANDALONE_LIVE_SOURCES}
  ${BLINK_STANDALONE_LIVE_OBJECTS}
)

  target_include_directories(blink_standalone_render_benchmark_skia PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
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
    SKCMS_DISABLE_HSW=1
    SKCMS_DISABLE_SKX=1
    SK_ENABLE_OPTIMIZE_SIZE=1
  )

  if(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
    target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
      HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG=1
    )
    target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
      ole32
      windowscodecs
    )
  endif()

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
  endif()

  target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
    freetype
    harfbuzz
  )

  if(BLINK_STANDALONE_BUILD_SDL_VIEWER AND BLINK_STANDALONE_SDL3_TARGET)
    add_executable(blink_standalone_sdl_viewer_skia
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/examples/sdl_viewer.cc
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/skia_cpu_renderer.cc
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/typeface_resource_registry.cc
      ${BLINK_STANDALONE_LIVE_SOURCES}
      ${BLINK_STANDALONE_LIVE_OBJECTS}
    )

    target_include_directories(blink_standalone_sdl_viewer_skia PRIVATE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
      ${BLINK_STANDALONE_CHROMIUM_ROOT}
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
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
      SKCMS_DISABLE_HSW=1
      SKCMS_DISABLE_SKX=1
      SK_ENABLE_OPTIMIZE_SIZE=1
      SDL_STATIC_LIB=1
    )

    if(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
      target_compile_definitions(blink_standalone_sdl_viewer_skia PRIVATE
        HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG=1
      )
      target_link_libraries(blink_standalone_sdl_viewer_skia PRIVATE
        ole32
        windowscodecs
      )
    endif()

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
      ${BLINK_STANDALONE_SDL3_TARGET}
      kernel32.lib user32.lib gdi32.lib winmm.lib imm32.lib ole32.lib
      oleaut32.lib version.lib uuid.lib advapi32.lib setupapi.lib shell32.lib
      dinput8.lib
    )
  endif()

