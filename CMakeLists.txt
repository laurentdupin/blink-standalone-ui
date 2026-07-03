cmake_minimum_required(VERSION 3.26)
project(blink_standalone_ui LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
include(cmake/v8_compat_libcxx_objects.cmake)
option(BLINK_STANDALONE_BUILD_SDL_VIEWER
  "Build the optional SDL3 viewer executables." ON)
option(BLINK_STANDALONE_FETCH_SDL3
  "Fetch SDL3 with CMake when an installed SDL3 package is unavailable." ON)
option(BLINK_STANDALONE_PERF_BUILD
  "Build standalone renderer benchmark targets with release-like perf defines." OFF)
option(BLINK_STANDALONE_RELEASE_LEVEL_VIEWER
  "Build SDL viewer/renderer objects without forced DCHECKs or debug-only size/SIMD restrictions." OFF)
option(BLINK_STANDALONE_OPTIMIZE_CHROMIUM
  "Compile upstream Chromium/Blink/cc/Skia/base sources with release optimization." ON)
option(BLINK_STANDALONE_OPTIMIZE_CODECS
  "Compile third-party image/codec sources with release optimization." ON)
option(BLINK_STANDALONE_OPTIMIZE_BOUNDARY
  "Compile standalone Blink boundary/stub/resource bridge sources with release optimization." ON)
option(BLINK_STANDALONE_OPTIMIZE_APP
  "Compile standalone benchmark/presenter application sources with release optimization." ON)
option(BLINK_STANDALONE_DAWN_D3D12
  "Enable experimental standalone Dawn/D3D12 benchmark wiring." OFF)
option(BLINK_STANDALONE_DAWN_D3D12_AUTO_DETECT
  "Enable Dawn/D3D12 wiring automatically when the repo-local Dawn probe output exists." ON)
option(BLINK_STANDALONE_USE_VCPKG_DEPS
  "Use vcpkg/system packages for libxml2/Iconv/ZLIB instead of only source-owned repository dependencies." ON)
set(BLINK_STANDALONE_DAWN_D3D12_LIBS
  ""
  CACHE STRING
  "Semicolon-separated Dawn static libraries built with D3D12 enabled.")
set(BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR
  ""
  CACHE PATH
  "Path to Dawn generated include directory from the D3D12 Dawn build.")
set(BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR
  ""
  CACHE PATH
  "Path to the Dawn source checkout used for the D3D12 Dawn build.")
set(BLINK_STANDALONE_DAWN_D3D12_BUILDFLAGS_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/upstream/chromium/standalone_renderer/stubs/dawn_d3d12_buildflags
)
if(WIN32 AND NOT BLINK_STANDALONE_DAWN_D3D12 AND
    BLINK_STANDALONE_DAWN_D3D12_AUTO_DETECT)
  set(_blink_standalone_default_dawn_d3d12_build_dir
    "${CMAKE_CURRENT_SOURCE_DIR}/build/dawn_probe/cmake_d3d12")
  set(_blink_standalone_default_dawn_d3d12_source_dir
    "${CMAKE_CURRENT_SOURCE_DIR}/build/dawn_probe/dawn")
  set(_blink_standalone_default_dawn_d3d12_gen_include_dir
    "${_blink_standalone_default_dawn_d3d12_build_dir}/gen/include")
  if(EXISTS "${_blink_standalone_default_dawn_d3d12_gen_include_dir}/dawn/webgpu.h" AND
      EXISTS "${_blink_standalone_default_dawn_d3d12_source_dir}/include/dawn/native/DawnNative.h" AND
      EXISTS "${_blink_standalone_default_dawn_d3d12_build_dir}/src/dawn/native/dawn_native.lib")
    file(GLOB_RECURSE _blink_standalone_default_dawn_d3d12_libs
      CONFIGURE_DEPENDS
      "${_blink_standalone_default_dawn_d3d12_build_dir}/*.lib")
    list(SORT _blink_standalone_default_dawn_d3d12_libs)
    set(BLINK_STANDALONE_DAWN_D3D12 ON CACHE BOOL
      "Enable experimental standalone Dawn/D3D12 benchmark wiring." FORCE)
    set(BLINK_STANDALONE_DAWN_D3D12_LIBS
      "${_blink_standalone_default_dawn_d3d12_libs}"
      CACHE STRING
      "Semicolon-separated Dawn static libraries built with D3D12 enabled."
      FORCE)
    set(BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR
      "${_blink_standalone_default_dawn_d3d12_gen_include_dir}"
      CACHE PATH
      "Path to Dawn generated include directory from the D3D12 Dawn build."
      FORCE)
    set(BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR
      "${_blink_standalone_default_dawn_d3d12_source_dir}"
      CACHE PATH
      "Path to the Dawn source checkout used for the D3D12 Dawn build."
      FORCE)
    message(STATUS
      "Auto-enabled BLINK_STANDALONE_DAWN_D3D12 from repo-local Dawn probe output.")
  endif()
endif()
unset(BLINK_STANDALONE_REQUIRE_PREBUILT_V8_COMPAT CACHE)
option(BLINK_STANDALONE_V8_SYNC_DEPS
  "Allow the V8 compatibility wrapper to run gclient sync in its generated work root." OFF)
option(BLINK_STANDALONE_V8_COMPAT_BUILD
  "Make blink_standalone_v8_compat run gn/ninja instead of only printing the build plan." OFF)
set(BLINK_STANDALONE_V8_COMPAT_ACTION
  auto
  CACHE STRING
  "V8 compatibility wrapper action: auto, plan, prepare, gn-gen, or build. auto preserves BLINK_STANDALONE_V8_COMPAT_BUILD."
)
set_property(CACHE BLINK_STANDALONE_V8_COMPAT_ACTION PROPERTY STRINGS auto plan prepare gn-gen build)

set(BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR
  ${CMAKE_BINARY_DIR}/generated/release_level_buildflags
)
if(BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
  file(MAKE_DIRECTORY
    ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}/base/debug
    ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}/base/allocator/partition_allocator/src/partition_alloc
  )
  file(WRITE
    ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}/base/debug/debugging_buildflags.h
    [=[// Generated by standalone CMake for BLINK_STANDALONE_RELEASE_LEVEL_VIEWER.
#ifndef BASE_DEBUG_DEBUGGING_BUILDFLAGS_H_
#define BASE_DEBUG_DEBUGGING_BUILDFLAGS_H_

#include "build/buildflag.h"  // IWYU pragma: export

#define BUILDFLAG_INTERNAL_DCHECK_IS_CONFIGURABLE() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PROFILING() (0)
#define BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_FRAME_POINTERS() (0)
#define BUILDFLAG_INTERNAL_UNSAFE_DEVELOPER_BUILD() (0)
#define BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_CFI_TABLE() (0)
#define BUILDFLAG_INTERNAL_EXCLUDE_UNWIND_TABLES() (0)
#define BUILDFLAG_INTERNAL_ENABLE_GDBINIT_WARNING() (0)
#define BUILDFLAG_INTERNAL_ENABLE_LLDBINIT_WARNING() (0)
#define BUILDFLAG_INTERNAL_EXPENSIVE_DCHECKS_ARE_ON() (0)
#define BUILDFLAG_INTERNAL_ENABLE_STACK_TRACE_LINE_NUMBERS() (0)
#define BUILDFLAG_INTERNAL_ENABLE_COMMANDLINE_SEQUENCE_CHECKS() (0)
#define BUILDFLAG_INTERNAL_ENABLE_ALLOCATION_STACK_TRACE_RECORDER() (0)
#define BUILDFLAG_INTERNAL_ENABLE_ALLOCATION_TRACE_RECORDER_FULL_REPORTING() (0)
#define BUILDFLAG_INTERNAL_PRINT_UNSYMBOLIZED_STACK_TRACES() (0)
#define BUILDFLAG_INTERNAL_ENABLE_CHECK_ELISION_WARNING() (0)

#endif  // BASE_DEBUG_DEBUGGING_BUILDFLAGS_H_
]=])
  file(WRITE
    ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}/base/allocator/partition_allocator/src/partition_alloc/buildflags.h
    [=[// Generated by standalone CMake for BLINK_STANDALONE_RELEASE_LEVEL_VIEWER.
#ifndef BASE_ALLOCATOR_PARTITION_ALLOCATOR_SRC_PARTITION_ALLOC_BUILDFLAGS_H_
#define BASE_ALLOCATOR_PARTITION_ALLOCATOR_SRC_PARTITION_ALLOC_BUILDFLAGS_H_

#include "partition_alloc/buildflag.h"  // IWYU pragma: export

#define PA_BUILDFLAG_INTERNAL_ENABLE_USER_SPACE_ZERO_SEGMENT() (0)
#define PA_BUILDFLAG_INTERNAL_USER_SPACE_ZERO_SEGMENT_SIZE_MB() (4097)
#define PA_BUILDFLAG_INTERNAL_BACKUP_REF_PTR_EXTRA_OOB_CHECKS() (1)
#define PA_BUILDFLAG_INTERNAL_BACKUP_REF_PTR_POISON_OOB_PTR() (0)
#define PA_BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_FRAME_POINTERS() (0)
#define PA_BUILDFLAG_INTERNAL_CHECKED_SPAN() (0)
#define PA_BUILDFLAG_INTERNAL_DCHECKS_ARE_ON() (0)
#define PA_BUILDFLAG_INTERNAL_DCHECK_IS_CONFIGURABLE() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_AUTO_PARTITIONING() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_BACKUP_REF_PTR_FEATURE_FLAG() (1)
#define PA_BUILDFLAG_INTERNAL_ENABLE_BACKUP_REF_PTR_INSTANCE_TRACER() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_BACKUP_REF_PTR_SLOW_CHECKS() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_BACKUP_REF_PTR_SUPPORT() (1)
#define PA_BUILDFLAG_INTERNAL_ENABLE_DANGLING_RAW_PTR_CHECKS() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_DANGLING_RAW_PTR_FEATURE_FLAG() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_GWP_ASAN_SUPPORT() (1)
#define PA_BUILDFLAG_INTERNAL_ENABLE_PARTITION_LOCK_REENTRANCY_CHECK() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_PARTITION_LOCK_PRIORITY_INHERITANCE() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_PKEYS() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_POINTER_ARITHMETIC_TRAIT_CHECK() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_POINTER_COMPRESSION() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_POINTER_SUBTRACTION_CHECK() (0)
#define PA_BUILDFLAG_INTERNAL_ENABLE_SYSTEM_FREE_FALLBACK() (0)
#define PA_BUILDFLAG_INTERNAL_MOVE_METADATA_OUT_OF_GIGACAGE_FOR_64_BITS_POINTERS() (1)
#define PA_BUILDFLAG_INTERNAL_ENABLE_MOVE_METADATA_OUT_OF_GIGACAGE_TRIAL() (1)
#define PA_BUILDFLAG_INTERNAL_ENABLE_THREAD_ISOLATION() (0)
#define PA_BUILDFLAG_INTERNAL_EXPENSIVE_DCHECKS_ARE_ON() (0)
#define PA_BUILDFLAG_INTERNAL_FORCE_DISABLE_BACKUP_REF_PTR_FEATURE() (0)
#define PA_BUILDFLAG_INTERNAL_FORCE_ENABLE_RAW_PTR_EXCLUSION() (0)
#define PA_BUILDFLAG_INTERNAL_FORWARD_THROUGH_MALLOC() (0)
#define PA_BUILDFLAG_INTERNAL_HAS_64_BIT_POINTERS() (1)
#define PA_BUILDFLAG_INTERNAL_HAS_MEMORY_TAGGING() (0)
#define PA_BUILDFLAG_INTERNAL_IS_ANDROID() (0)
#define PA_BUILDFLAG_INTERNAL_IS_CASTOS() (0)
#define PA_BUILDFLAG_INTERNAL_IS_CHROMEOS() (0)
#define PA_BUILDFLAG_INTERNAL_IS_DEBUG() (0)
#define PA_BUILDFLAG_INTERNAL_IS_HWASAN() (0)
#define PA_BUILDFLAG_INTERNAL_RAW_PTR_ZERO_ON_CONSTRUCT() (1)
#define PA_BUILDFLAG_INTERNAL_RAW_PTR_ZERO_ON_DESTRUCT() (0)
#define PA_BUILDFLAG_INTERNAL_RAW_PTR_ZERO_ON_MOVE() (1)
#define PA_BUILDFLAG_INTERNAL_REALLOC_GROWTH_FACTOR_MITIGATION() (0)
#define PA_BUILDFLAG_INTERNAL_RECORD_ALLOC_INFO() (0)
#define PA_BUILDFLAG_INTERNAL_SHIM_SUPPORTS_ALLOC_TOKEN() (0)
#define PA_BUILDFLAG_INTERNAL_SHIM_SUPPORTS_SIZED_DEALLOC() (1)
#define PA_BUILDFLAG_INTERNAL_SMALLER_PARTITION_COOKIE() (0)
#define PA_BUILDFLAG_INTERNAL_STACK_SCAN_SUPPORTED() (1)
#define PA_BUILDFLAG_INTERNAL_USE_ALLOCATOR_SHIM() (0)
#define PA_BUILDFLAG_INTERNAL_USE_ASAN_BACKUP_REF_PTR() (0)
#define PA_BUILDFLAG_INTERNAL_USE_ASAN_BACKUP_REF_PTR_V2() (0)
#define PA_BUILDFLAG_INTERNAL_USE_FULL_MTE() (0)
#define PA_BUILDFLAG_INTERNAL_USE_LARGE_EMPTY_SLOT_SPAN_RING() (1)
#define PA_BUILDFLAG_INTERNAL_USE_PARTITION_ALLOC() (1)
#define PA_BUILDFLAG_INTERNAL_USE_PARTITION_ALLOC_AS_MALLOC() (0)
#define PA_BUILDFLAG_INTERNAL_USE_PARTITION_COOKIE() (1)
#define PA_BUILDFLAG_INTERNAL_USE_RAW_PTR_ASAN_UNOWNED_IMPL() (0)
#define PA_BUILDFLAG_INTERNAL_USE_RAW_PTR_BACKUP_REF_IMPL() (1)
#define PA_BUILDFLAG_INTERNAL_USE_RAW_PTR_HOOKABLE_IMPL() (0)

#endif  // BASE_ALLOCATOR_PARTITION_ALLOCATOR_SRC_PARTITION_ALLOC_BUILDFLAGS_H_
]=])
endif()

set(BLINK_STANDALONE_COMPILER_IS_CLANG_CL OFF)
set(BLINK_STANDALONE_COMPILER_IS_MSVC_CL OFF)
if(MSVC AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(BLINK_STANDALONE_COMPILER_IS_CLANG_CL ON)
elseif(MSVC AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(BLINK_STANDALONE_COMPILER_IS_MSVC_CL ON)
endif()
if(BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
  enable_language(ASM_MASM)
endif()

if(MSVC)
  # Keep the Windows renderer and generated V8 compatibility output on the same
  # static CRT boundary.
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "" FORCE)
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:C>:/utf-8>"
    "$<$<COMPILE_LANGUAGE:CXX>:/utf-8>"
  )
endif()
if(BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/Zc:preprocessor>")
endif()

if(NOT DEFINED BLINK_STANDALONE_V8_TOOLCHAIN)
  if(BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
    set(_blink_standalone_default_v8_toolchain msvc)
  else()
    set(_blink_standalone_default_v8_toolchain chromium-clang)
  endif()
  set(BLINK_STANDALONE_V8_TOOLCHAIN
    ${_blink_standalone_default_v8_toolchain}
    CACHE STRING
    "V8/CppGC compatibility toolchain: chromium-clang or msvc."
  )
else()
  set(BLINK_STANDALONE_V8_TOOLCHAIN
    ${BLINK_STANDALONE_V8_TOOLCHAIN}
    CACHE STRING
    "V8/CppGC compatibility toolchain: chromium-clang or msvc."
  )
endif()
set_property(CACHE BLINK_STANDALONE_V8_TOOLCHAIN PROPERTY STRINGS
  chromium-clang msvc)
if(NOT BLINK_STANDALONE_V8_TOOLCHAIN MATCHES "^(chromium-clang|msvc)$")
  message(FATAL_ERROR
    "BLINK_STANDALONE_V8_TOOLCHAIN must be chromium-clang or msvc.")
endif()

set(BLINK_STANDALONE_USE_CHROMIUM_LIBCXX OFF)
if(BLINK_STANDALONE_V8_TOOLCHAIN STREQUAL "chromium-clang")
  set(BLINK_STANDALONE_USE_CHROMIUM_LIBCXX ON)
endif()

set(BLINK_STANDALONE_PLATFORM_COMPILE_DEFINITIONS)
set(BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES)
set(BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS)
set(BLINK_STANDALONE_PLATFORM_LINK_OPTIONS)
set(BLINK_STANDALONE_PLATFORM_LINK_LIBS)
set(BLINK_STANDALONE_SDL_PLATFORM_LINK_LIBS)
if(WIN32)
  list(APPEND BLINK_STANDALONE_PLATFORM_COMPILE_DEFINITIONS
    VK_USE_PLATFORM_WIN32_KHR=1
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_NONSTDC_NO_WARNINGS
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_DEPRECATE
    _WINSOCK_DEPRECATED_NO_WARNINGS
    UNICODE
    _UNICODE
  )
  list(APPEND BLINK_STANDALONE_PLATFORM_LINK_LIBS
    d3d11
    d3d12
    dcomp
    dwmapi
    dxcore
    dxgi
    kernel32
    mincore
    ole32
    oleaut32
    propsys
    runtimeobject
    shell32
    shcore
    winmm
    windowscodecs
    wbemuuid
    advapi32
    dbghelp
    ntdll
    psapi
    setupapi
    shlwapi
    ws2_32
    delayimp
  )
  list(APPEND BLINK_STANDALONE_SDL_PLATFORM_LINK_LIBS
    kernel32.lib
    user32.lib
    gdi32.lib
    winmm.lib
    imm32.lib
    ole32.lib
    oleaut32.lib
    version.lib
    uuid.lib
    advapi32.lib
    setupapi.lib
    shell32.lib
    dbghelp.lib
    dinput8.lib
    ntdll.lib
    psapi.lib
    shlwapi.lib
    ws2_32.lib
  )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(Threads REQUIRED)
  find_package(X11 REQUIRED COMPONENTS xcb)
  foreach(_blink_standalone_x11_include_dir IN ITEMS
      "${X11_INCLUDEDIR}"
      "${X11_X11_INCLUDE_PATH}"
      "${X11_xcb_INCLUDE_PATH}")
    if(_blink_standalone_x11_include_dir AND
       EXISTS "${_blink_standalone_x11_include_dir}")
      list(APPEND BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES
        "${_blink_standalone_x11_include_dir}")
    endif()
  endforeach()
  list(REMOVE_DUPLICATES BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES)
  list(APPEND BLINK_STANDALONE_PLATFORM_COMPILE_DEFINITIONS
    VK_USE_PLATFORM_XCB_KHR=1
    USE_OZONE=1
  )
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    list(APPEND BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS
      -fPIC
      -pthread
      -fvisibility=hidden
      -fvisibility-inlines-hidden
    )
    list(APPEND BLINK_STANDALONE_PLATFORM_LINK_OPTIONS
      -fPIC
      -pthread
      -Wl,-z,noexecstack
      -Wl,-z,relro
    )
  endif()
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS
      -Wno-nullability-completeness
      -Wno-nontrivial-memcall
    )
    get_filename_component(_blink_standalone_clang_bin_dir
      "${CMAKE_CXX_COMPILER}" DIRECTORY)
    if(EXISTS "${_blink_standalone_clang_bin_dir}/ld.lld")
      execute_process(
        COMMAND "${_blink_standalone_clang_bin_dir}/ld.lld" --version
        RESULT_VARIABLE _blink_standalone_lld_result
        OUTPUT_QUIET
        ERROR_QUIET)
      if(_blink_standalone_lld_result EQUAL 0)
        list(APPEND BLINK_STANDALONE_PLATFORM_LINK_OPTIONS
          -fuse-ld=lld
        )
      endif()
    endif()
  endif()
  list(APPEND BLINK_STANDALONE_PLATFORM_LINK_LIBS
    Threads::Threads
    X11::X11
    X11::xcb
    atomic
    dl
    m
  )
endif()

set(BLINK_STANDALONE_CHROMIUM_ROOT
  ${CMAKE_CURRENT_SOURCE_DIR}/upstream/chromium
)
set(BLINK_STANDALONE_RENDERER_ROOT
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer
)
set(BLINK_STANDALONE_DEPOT_TOOLS_ROOT
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/depot_tools
  CACHE PATH
  "Pinned depot_tools checkout used by optional source-built V8/CppGC compatibility orchestration."
)
set(BLINK_STANDALONE_V8_SOURCE_ROOT
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/v8
  CACHE PATH
  "Pinned V8 source checkout used to create the generated V8/CppGC compatibility build."
)
set(_blink_standalone_default_v8_compat_work_root
  ${CMAKE_BINARY_DIR}/v8_compat
)
set(BLINK_STANDALONE_V8_COMPAT_WORK_ROOT
  ${_blink_standalone_default_v8_compat_work_root}
  CACHE PATH
  "Generated work root for the V8/CppGC compatibility build. gclient sync, if enabled, runs only here."
)
set(BLINK_STANDALONE_V8_COMPAT_OUT_NAME
  chromium_static
  CACHE STRING
  "GN output directory name for the generated V8/CppGC compatibility build."
)
set(_blink_standalone_default_v8_compat_out_dir
  ${_blink_standalone_default_v8_compat_work_root}/src/v8/out/${BLINK_STANDALONE_V8_COMPAT_OUT_NAME}
)
set(BLINK_STANDALONE_V8_COMPAT_OUT_DIR
  ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8/out/${BLINK_STANDALONE_V8_COMPAT_OUT_NAME}
  CACHE PATH
  "GN output directory for the generated V8/CppGC compatibility build."
)
file(TO_CMAKE_PATH "${_blink_standalone_default_v8_compat_work_root}" _blink_standalone_default_v8_compat_work_root_normalized)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}" _blink_standalone_v8_compat_work_root_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_v8_compat_out_dir}" _blink_standalone_default_v8_compat_out_dir_normalized)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}" _blink_standalone_v8_compat_out_dir_normalized)
if(WIN32)
  set(_blink_standalone_v8_gn_names gn.bat gn.cmd gn.exe gn)
  set(_blink_standalone_v8_gclient_names gclient.bat gclient.cmd gclient.exe gclient gclient.py)
else()
  if(BLINK_STANDALONE_V8_GN_EXECUTABLE MATCHES "\\.(bat|cmd|exe)$")
    unset(BLINK_STANDALONE_V8_GN_EXECUTABLE CACHE)
  endif()
  if(BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE MATCHES "\\.(bat|cmd|exe)$")
    unset(BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE CACHE)
  endif()
  set(_blink_standalone_v8_gn_names gn gn.py)
  set(_blink_standalone_v8_gclient_names gclient gclient.py)
endif()

if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_v8_compat_out_dir_normalized STREQUAL _blink_standalone_default_v8_compat_out_dir_normalized)
  message(STATUS "Updating BLINK_STANDALONE_V8_COMPAT_OUT_DIR to match BLINK_STANDALONE_V8_COMPAT_WORK_ROOT.")
  set(BLINK_STANDALONE_V8_COMPAT_OUT_DIR
    ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8/out/${BLINK_STANDALONE_V8_COMPAT_OUT_NAME}
    CACHE PATH
    "GN output directory for the generated V8/CppGC compatibility build."
    FORCE
  )
endif()
find_program(BLINK_STANDALONE_V8_GN_EXECUTABLE
  NAMES ${_blink_standalone_v8_gn_names}
  HINTS ${BLINK_STANDALONE_DEPOT_TOOLS_ROOT}
  NO_DEFAULT_PATH
  DOC "GN executable for the optional V8/CppGC compatibility build target."
)
if(NOT BLINK_STANDALONE_V8_GN_EXECUTABLE)
  find_program(BLINK_STANDALONE_V8_GN_EXECUTABLE
    NAMES ${_blink_standalone_v8_gn_names}
    DOC "GN executable for the optional V8/CppGC compatibility build target."
  )
endif()
find_program(BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE
  NAMES ${_blink_standalone_v8_gclient_names}
  HINTS ${BLINK_STANDALONE_DEPOT_TOOLS_ROOT}
  NO_DEFAULT_PATH
  DOC "gclient executable for the optional V8/CppGC compatibility dependency sync."
)
if(NOT BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE)
  find_program(BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE
    NAMES ${_blink_standalone_v8_gclient_names}
    DOC "gclient executable for the optional V8/CppGC compatibility dependency sync."
  )
endif()
set(_blink_standalone_v8_gn_executable "${BLINK_STANDALONE_V8_GN_EXECUTABLE}")
set(_blink_standalone_v8_gclient_executable "${BLINK_STANDALONE_V8_GCLIENT_EXECUTABLE}")
if(WIN32)
  if(_blink_standalone_v8_gn_executable AND
     EXISTS "${_blink_standalone_v8_gn_executable}.bat")
    set(_blink_standalone_v8_gn_executable "${_blink_standalone_v8_gn_executable}.bat")
  endif()
  if(_blink_standalone_v8_gclient_executable AND
     EXISTS "${_blink_standalone_v8_gclient_executable}.bat")
    set(_blink_standalone_v8_gclient_executable "${_blink_standalone_v8_gclient_executable}.bat")
  endif()
endif()
set(BLINK_STANDALONE_V8_NINJA_EXECUTABLE
  ${CMAKE_MAKE_PROGRAM}
  CACHE FILEPATH
  "Ninja executable for the optional V8/CppGC compatibility build target."
)
set(BLINK_STANDALONE_V8_CLANG_BASE_PATH
  ""
  CACHE PATH
  "Chromium clang base path passed to the optional V8/CppGC compatibility GN build. Empty lets GN/depot_tools resolve clang."
)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_CLANG_BASE_PATH}" _blink_standalone_v8_clang_base_path_normalized)
if(_blink_standalone_v8_clang_base_path_normalized MATCHES "/build/v8_mono2/chromium_clang$")
  message(STATUS "Clearing legacy auto-derived BLINK_STANDALONE_V8_CLANG_BASE_PATH; leave empty to let V8/GN resolve clang.")
  set(BLINK_STANDALONE_V8_CLANG_BASE_PATH
    ""
    CACHE PATH
    "Chromium clang base path passed to the optional V8/CppGC compatibility GN build. Empty lets GN/depot_tools resolve clang."
    FORCE
  )
endif()
set(BLINK_STANDALONE_V8_COMPAT_JOBS
  ""
  CACHE STRING
  "Optional -j value for the V8/CppGC compatibility ninja build."
)
set(_blink_standalone_legacy_v8_build_root
  ${CMAKE_CURRENT_SOURCE_DIR}/build/v8_mono2/v8
)
set(_blink_standalone_default_v8_build_root
  ${_blink_standalone_default_v8_compat_work_root}/src/v8
)
set(_blink_standalone_default_v8_generated_source_root
  ${_blink_standalone_default_v8_compat_work_root}/src
)
set(_blink_standalone_default_v8_include_dir
  ${_blink_standalone_default_v8_build_root}/include
)
set(BLINK_STANDALONE_V8_BUILD_ROOT
  ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8
  CACHE PATH
  "Generated V8 work copy used by the V8/CppGC compatibility build."
)
set(BLINK_STANDALONE_V8_GENERATED_SOURCE_ROOT
  ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src
  CACHE PATH
  "Generated V8 compatibility source root used for Chromium-style v8/include/... includes."
)
set(BLINK_STANDALONE_V8_INCLUDE_DIR
  ${BLINK_STANDALONE_V8_BUILD_ROOT}/include
  CACHE PATH
  "Patched V8 public include root from the generated V8 compatibility work copy."
)
file(TO_CMAKE_PATH "${_blink_standalone_default_v8_build_root}" _blink_standalone_default_v8_build_root_normalized)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_BUILD_ROOT}" _blink_standalone_v8_build_root_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_v8_generated_source_root}" _blink_standalone_default_v8_generated_source_root_normalized)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_GENERATED_SOURCE_ROOT}" _blink_standalone_v8_generated_source_root_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_v8_include_dir}" _blink_standalone_default_v8_include_dir_normalized)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_INCLUDE_DIR}" _blink_standalone_v8_include_dir_normalized)
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_v8_build_root_normalized STREQUAL _blink_standalone_default_v8_build_root_normalized)
  message(STATUS "Updating BLINK_STANDALONE_V8_BUILD_ROOT to match BLINK_STANDALONE_V8_COMPAT_WORK_ROOT.")
  set(BLINK_STANDALONE_V8_BUILD_ROOT
    ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8
    CACHE PATH
    "Generated V8 work copy used by the V8/CppGC compatibility build."
    FORCE
  )
endif()
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_v8_generated_source_root_normalized STREQUAL _blink_standalone_default_v8_generated_source_root_normalized)
  message(STATUS "Updating BLINK_STANDALONE_V8_GENERATED_SOURCE_ROOT to match BLINK_STANDALONE_V8_COMPAT_WORK_ROOT.")
  set(BLINK_STANDALONE_V8_GENERATED_SOURCE_ROOT
    ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src
    CACHE PATH
    "Generated V8 compatibility source root used for Chromium-style v8/include/... includes."
    FORCE
  )
endif()
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_v8_include_dir_normalized STREQUAL _blink_standalone_default_v8_include_dir_normalized)
  message(STATUS "Updating BLINK_STANDALONE_V8_INCLUDE_DIR to match BLINK_STANDALONE_V8_BUILD_ROOT.")
  set(BLINK_STANDALONE_V8_INCLUDE_DIR
    ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8/include
    CACHE PATH
    "Patched V8 public include root from the generated V8 compatibility work copy."
    FORCE
  )
endif()
set(_blink_standalone_default_icu_source_root
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu
)
if(EXISTS "${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/icu/source/common/unicode/uvernum.h")
  set(_blink_standalone_default_icu_source_root
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/icu
  )
endif()
set(BLINK_STANDALONE_ICU_SOURCE_ROOT
  ${_blink_standalone_default_icu_source_root}
  CACHE PATH
  "ICU source root used by the standalone renderer. Generated V8 ICU is preferred when present so compiled ICU and icudtl.dat versions match."
)
set(_blink_standalone_v8_icu_data_file
  ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/icu/common/icudtl.dat
)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu" _blink_standalone_chromium_icu_source_root_normalized)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_ICU_SOURCE_ROOT}" _blink_standalone_icu_source_root_normalized)
if(EXISTS "${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/icu/source/common/unicode/uvernum.h" AND
   _blink_standalone_icu_source_root_normalized STREQUAL _blink_standalone_chromium_icu_source_root_normalized)
  message(STATUS "Updating BLINK_STANDALONE_ICU_SOURCE_ROOT and BLINK_STANDALONE_ICU_DATA_FILE to match the generated V8 ICU checkout.")
  set(BLINK_STANDALONE_ICU_SOURCE_ROOT
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/icu
    CACHE PATH
    "ICU source root used by the standalone renderer. Generated V8 ICU is preferred when present so compiled ICU and icudtl.dat versions match."
    FORCE
  )
  set(BLINK_STANDALONE_ICU_DATA_FILE
    ${_blink_standalone_v8_icu_data_file}
    CACHE FILEPATH
    "ICU data sidecar matching BLINK_STANDALONE_ICU_SOURCE_ROOT."
    FORCE
  )
endif()
set(BLINK_STANDALONE_ICU_DATA_FILE
  ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/common/icudtl.dat
  CACHE FILEPATH
  "ICU data sidecar matching BLINK_STANDALONE_ICU_SOURCE_ROOT."
)
if(NOT EXISTS "${BLINK_STANDALONE_ICU_DATA_FILE}")
  if(EXISTS "${_blink_standalone_v8_icu_data_file}")
    message(STATUS "Updating BLINK_STANDALONE_ICU_DATA_FILE to the generated V8 ICU data bundle.")
    set(BLINK_STANDALONE_ICU_SOURCE_ROOT
      ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/icu
      CACHE PATH
      "ICU source root used by the standalone renderer. Generated V8 ICU is preferred when present so compiled ICU and icudtl.dat versions match."
      FORCE
    )
    set(BLINK_STANDALONE_ICU_DATA_FILE
      ${_blink_standalone_v8_icu_data_file}
      CACHE FILEPATH
      "ICU data sidecar matching BLINK_STANDALONE_ICU_SOURCE_ROOT."
      FORCE
    )
  elseif(BLINK_STANDALONE_ICU_SOURCE_ROOT STREQUAL
         "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu")
    message(STATUS "Using generated V8 ICU data bundle path; the V8 compatibility build will create it.")
    set(BLINK_STANDALONE_ICU_DATA_FILE
      ${_blink_standalone_v8_icu_data_file}
      CACHE FILEPATH
      "ICU data sidecar matching the generated V8 compatibility build."
      FORCE
    )
  endif()
endif()
file(TO_CMAKE_PATH "${BLINK_STANDALONE_ICU_DATA_FILE}" _blink_standalone_icu_data_file_normalized)
if(_blink_standalone_icu_data_file_normalized MATCHES "/out/.*/icudtl\\.dat$")
  message(STATUS "Migrating BLINK_STANDALONE_ICU_DATA_FILE from generated out dir to the matching ICU source data bundle.")
  set(BLINK_STANDALONE_ICU_DATA_FILE
    ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/common/icudtl.dat
    CACHE FILEPATH
    "ICU data sidecar matching BLINK_STANDALONE_ICU_SOURCE_ROOT."
    FORCE
  )
endif()
if(WIN32)
  set(_blink_standalone_v8_monolith_lib_relative
    obj/v8_monolith.lib)
  set(_blink_standalone_packaged_v8_monolith_name
    v8_monolith.lib)
else()
  set(_blink_standalone_v8_monolith_lib_relative
    obj/libv8_monolith.a)
  set(_blink_standalone_packaged_v8_monolith_name
    libv8_monolith.a)
endif()
set(_blink_standalone_default_v8_monolith_lib
  ${_blink_standalone_default_v8_compat_out_dir}/${_blink_standalone_v8_monolith_lib_relative}
)
set(_blink_standalone_current_v8_monolith_lib
  ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}/${_blink_standalone_v8_monolith_lib_relative}
)
set(BLINK_STANDALONE_V8_MONOLITH_LIB
  ${_blink_standalone_current_v8_monolith_lib}
  CACHE FILEPATH
  "Source-built V8/CppGC compatibility library for the live Blink renderer."
)
set(BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS
  ${BLINK_STANDALONE_V8_BUILD_ROOT}/buildtools/third_party/libc++
  ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/libc++/src/include
  ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/libc++abi/src/include
  CACHE STRING
  "Chromium libc++ include roots used for ABI compatibility with the V8/CppGC library."
)
set(_blink_standalone_default_libcxx_include_dirs
  ${_blink_standalone_default_v8_build_root}/buildtools/third_party/libc++
  ${_blink_standalone_default_v8_build_root}/third_party/libc++/src/include
  ${_blink_standalone_default_v8_build_root}/third_party/libc++abi/src/include
)
set(BLINK_STANDALONE_V8_ABSEIL_INCLUDE_DIR
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
  CACHE PATH
  "Abseil source include root. Defaults to the tracked Chromium copy."
)
set(BLINK_STANDALONE_CHROMIUM_LIBCXX_DEFINES
  _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE
  _LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS
  _LIBCPP_NO_AUTO_LINK
  _LIBCPP_INSTRUMENTED_WITH_ASAN=0
  CR_LIBCXX_REVISION=5abc7f839700f0f17338434e1c1c6a8c87c00c11
  ABSL_ALLOCATOR_NOTHROW=1
  _HAS_NODISCARD
)
set(BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR
  ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}/obj/buildtools/third_party/libc++/libc++
  CACHE PATH
  "Directory containing Chromium libc++ object files built with the V8/CppGC compatibility library."
)
set(_blink_standalone_default_libcxx_object_dir
  ${_blink_standalone_default_v8_compat_out_dir}/obj/buildtools/third_party/libc++/libc++
)
set(_blink_standalone_default_libcxx_lib
  ${_blink_standalone_default_v8_compat_out_dir}/obj/buildtools/third_party/libc++/libc++.a
)
set(_blink_standalone_default_libcxxabi_lib
  ${_blink_standalone_default_v8_compat_out_dir}/obj/buildtools/third_party/libc++abi/libc++abi.a
)
set(_blink_standalone_current_libcxx_lib
  ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}/obj/buildtools/third_party/libc++/libc++.a
)
set(_blink_standalone_current_libcxxabi_lib
  ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}/obj/buildtools/third_party/libc++abi/libc++abi.a
)
set(BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB
  ${_blink_standalone_current_libcxx_lib}
  CACHE FILEPATH
  "Chromium libc++ static library built with the V8/CppGC compatibility library."
)
set(BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB
  ${_blink_standalone_current_libcxxabi_lib}
  CACHE FILEPATH
  "Chromium libc++abi static library built with the V8/CppGC compatibility library."
)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_BUILD_ROOT}" _blink_standalone_v8_build_root_normalized)
if(_blink_standalone_v8_build_root_normalized MATCHES "/build/v8_mono2/v8$")
  message(STATUS "Migrating legacy BLINK_STANDALONE_V8_BUILD_ROOT cache value to the generated V8 compatibility work root.")
  set(BLINK_STANDALONE_V8_BUILD_ROOT
    ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}/src/v8
    CACHE PATH
    "Generated V8 work copy used by the V8/CppGC compatibility build."
    FORCE
  )
endif()
set(_blink_standalone_legacy_v8_monolith_lib
  ${_blink_standalone_legacy_v8_build_root}/out/chromium_static/obj/v8_monolith.lib
)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_V8_MONOLITH_LIB}" _blink_standalone_v8_monolith_lib_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_v8_monolith_lib}" _blink_standalone_default_v8_monolith_lib_normalized)
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_v8_monolith_lib_normalized STREQUAL _blink_standalone_default_v8_monolith_lib_normalized)
  message(STATUS "Updating BLINK_STANDALONE_V8_MONOLITH_LIB to match BLINK_STANDALONE_V8_COMPAT_OUT_DIR.")
  set(BLINK_STANDALONE_V8_MONOLITH_LIB
    ${_blink_standalone_current_v8_monolith_lib}
    CACHE FILEPATH
    "Source-built V8/CppGC compatibility library for the live Blink renderer."
    FORCE
  )
endif()
if(_blink_standalone_v8_monolith_lib_normalized MATCHES "/build/v8_mono2/v8/out/chromium_static/obj/v8_monolith\\.lib$")
  message(STATUS "Migrating legacy BLINK_STANDALONE_V8_MONOLITH_LIB cache value to the generated V8 compatibility output.")
  set(BLINK_STANDALONE_V8_MONOLITH_LIB
    ${_blink_standalone_current_v8_monolith_lib}
    CACHE FILEPATH
    "Source-built V8/CppGC compatibility library for the live Blink renderer."
    FORCE
  )
endif()
if(NOT WIN32 AND _blink_standalone_v8_monolith_lib_normalized MATCHES "/obj/v8_monolith\\.lib$")
  message(STATUS "Migrating BLINK_STANDALONE_V8_MONOLITH_LIB to the Linux GN archive name.")
  set(BLINK_STANDALONE_V8_MONOLITH_LIB
    ${_blink_standalone_current_v8_monolith_lib}
    CACHE FILEPATH
    "Source-built V8/CppGC compatibility library for the live Blink renderer."
    FORCE
  )
endif()
set(_blink_standalone_legacy_libcxx_object_dir
  ${_blink_standalone_legacy_v8_build_root}/out/chromium_static/obj/buildtools/third_party/libc++/libc++
)
file(TO_CMAKE_PATH "${BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR}" _blink_standalone_libcxx_object_dir_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_libcxx_object_dir}" _blink_standalone_default_libcxx_object_dir_normalized)
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_libcxx_object_dir_normalized STREQUAL _blink_standalone_default_libcxx_object_dir_normalized)
  message(STATUS "Updating BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR to match BLINK_STANDALONE_V8_COMPAT_OUT_DIR.")
  set(BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR
    ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}/obj/buildtools/third_party/libc++/libc++
    CACHE PATH
    "Directory containing Chromium libc++ object files built with the V8/CppGC compatibility library."
    FORCE
  )
endif()
if(_blink_standalone_libcxx_object_dir_normalized MATCHES "/build/v8_mono2/v8/out/chromium_static/obj/buildtools/third_party/libc\\+\\+/libc\\+\\+$")
  message(STATUS "Migrating legacy BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR cache value to the generated V8 compatibility output.")
  set(BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR
    ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}/obj/buildtools/third_party/libc++/libc++
    CACHE PATH
    "Directory containing Chromium libc++ object files built with the V8/CppGC compatibility library."
    FORCE
  )
endif()
file(TO_CMAKE_PATH "${BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB}" _blink_standalone_libcxx_lib_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_libcxx_lib}" _blink_standalone_default_libcxx_lib_normalized)
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_libcxx_lib_normalized STREQUAL _blink_standalone_default_libcxx_lib_normalized)
  message(STATUS "Updating BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB to match BLINK_STANDALONE_V8_COMPAT_OUT_DIR.")
  set(BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB
    ${_blink_standalone_current_libcxx_lib}
    CACHE FILEPATH
    "Chromium libc++ static library built with the V8/CppGC compatibility library."
    FORCE
  )
endif()
file(TO_CMAKE_PATH "${BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB}" _blink_standalone_libcxxabi_lib_normalized)
file(TO_CMAKE_PATH "${_blink_standalone_default_libcxxabi_lib}" _blink_standalone_default_libcxxabi_lib_normalized)
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_libcxxabi_lib_normalized STREQUAL _blink_standalone_default_libcxxabi_lib_normalized)
  message(STATUS "Updating BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB to match BLINK_STANDALONE_V8_COMPAT_OUT_DIR.")
  set(BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB
    ${_blink_standalone_current_libcxxabi_lib}
    CACHE FILEPATH
    "Chromium libc++abi static library built with the V8/CppGC compatibility library."
    FORCE
  )
endif()
set(_blink_standalone_legacy_libcxx_include_dirs
  ${_blink_standalone_legacy_v8_build_root}/buildtools/third_party/libc++
  ${_blink_standalone_legacy_v8_build_root}/third_party/libc++/src/include
)
set(_blink_standalone_libcxx_include_dirs_normalized "${BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS}")
string(REPLACE "\\" "/" _blink_standalone_libcxx_include_dirs_normalized "${_blink_standalone_libcxx_include_dirs_normalized}")
set(_blink_standalone_default_libcxx_include_dirs_normalized "${_blink_standalone_default_libcxx_include_dirs}")
string(REPLACE "\\" "/" _blink_standalone_default_libcxx_include_dirs_normalized "${_blink_standalone_default_libcxx_include_dirs_normalized}")
if(NOT _blink_standalone_v8_compat_work_root_normalized STREQUAL _blink_standalone_default_v8_compat_work_root_normalized AND
   _blink_standalone_libcxx_include_dirs_normalized STREQUAL _blink_standalone_default_libcxx_include_dirs_normalized)
  message(STATUS "Updating BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS to match BLINK_STANDALONE_V8_BUILD_ROOT.")
  set(BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/buildtools/third_party/libc++
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/libc++/src/include
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/libc++abi/src/include
    CACHE STRING
    "Chromium libc++ include roots used for ABI compatibility with the V8/CppGC library."
    FORCE
  )
endif()
string(FIND "${_blink_standalone_libcxx_include_dirs_normalized}" "build/v8_mono2/v8" _blink_standalone_legacy_libcxx_include_pos)
if(NOT _blink_standalone_legacy_libcxx_include_pos EQUAL -1)
  message(STATUS "Migrating legacy BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS cache value to the generated V8 compatibility work root.")
  set(BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/buildtools/third_party/libc++
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/libc++/src/include
    ${BLINK_STANDALONE_V8_BUILD_ROOT}/third_party/libc++abi/src/include
    CACHE STRING
    "Chromium libc++ include roots used for ABI compatibility with the V8/CppGC library."
    FORCE
  )
endif()
set(BLINK_STANDALONE_STL_INCLUDE_DIRS)
set(BLINK_STANDALONE_STL_DEFINES)
if(BLINK_STANDALONE_USE_CHROMIUM_LIBCXX)
  set(BLINK_STANDALONE_STL_INCLUDE_DIRS
    ${BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS}
  )
  set(BLINK_STANDALONE_STL_DEFINES
    ${BLINK_STANDALONE_CHROMIUM_LIBCXX_DEFINES}
  )
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND BLINK_STANDALONE_USE_CHROMIUM_LIBCXX)
  list(PREPEND BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES
    ${BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS}
  )
  list(REMOVE_DUPLICATES BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS
      "$<$<COMPILE_LANGUAGE:CXX>:-nostdinc++>"
    )
    list(APPEND BLINK_STANDALONE_PLATFORM_LINK_OPTIONS
      -nostdlib++
    )
  endif()
endif()
set(BLINK_STANDALONE_V8_ABI_DEFINES
  V8_COMPRESS_POINTERS
  V8_COMPRESS_POINTERS_IN_SHARED_CAGE
  V8_31BIT_SMIS_ON_64BIT_ARCH
  V8_STATIC_ROOTS
  V8_USE_ZLIB
  CPPGC_CAGED_HEAP
  CPPGC_YOUNG_GENERATION
  CPPGC_POINTER_COMPRESSION
  CPPGC_ENABLE_LARGER_CAGE
  CPPGC_SLIM_WRITE_BARRIER
)
if(NOT BLINK_STANDALONE_V8_TOOLCHAIN STREQUAL "msvc")
  list(APPEND BLINK_STANDALONE_V8_ABI_DEFINES
    V8_ENABLE_PARTITION_ALLOC
    V8_ENABLE_SANDBOX
  )
endif()
set(BLINK_STANDALONE_PRIVATE_ICU_DEFINES
  U_LIB_SUFFIX_C_NAME=_blink_standalone
)

set(_blink_standalone_v8_compat_command
  ${Python3_EXECUTABLE}
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/v8/build_v8_monolith.py
  --toolchain ${BLINK_STANDALONE_V8_TOOLCHAIN}
  --source-v8-root ${BLINK_STANDALONE_V8_SOURCE_ROOT}
  --work-root ${BLINK_STANDALONE_V8_COMPAT_WORK_ROOT}
  --out-name ${BLINK_STANDALONE_V8_COMPAT_OUT_NAME}
  --out-dir ${BLINK_STANDALONE_V8_COMPAT_OUT_DIR}
  --ninja ${BLINK_STANDALONE_V8_NINJA_EXECUTABLE}
)
if(EXISTS "${BLINK_STANDALONE_DEPOT_TOOLS_ROOT}")
  list(APPEND _blink_standalone_v8_compat_command
    --depot-tools ${BLINK_STANDALONE_DEPOT_TOOLS_ROOT}
  )
endif()
if(_blink_standalone_v8_gn_executable)
  list(APPEND _blink_standalone_v8_compat_command
    --gn ${_blink_standalone_v8_gn_executable}
  )
endif()
if(_blink_standalone_v8_gclient_executable)
  list(APPEND _blink_standalone_v8_compat_command
    --gclient ${_blink_standalone_v8_gclient_executable}
  )
endif()
if(BLINK_STANDALONE_V8_CLANG_BASE_PATH)
  list(APPEND _blink_standalone_v8_compat_command
    --clang-base-path ${BLINK_STANDALONE_V8_CLANG_BASE_PATH}
  )
endif()
if(BLINK_STANDALONE_V8_COMPAT_JOBS)
  list(APPEND _blink_standalone_v8_compat_command
    --jobs ${BLINK_STANDALONE_V8_COMPAT_JOBS}
  )
endif()
if(BLINK_STANDALONE_V8_SYNC_DEPS)
  list(APPEND _blink_standalone_v8_compat_command --sync-deps)
else()
  list(APPEND _blink_standalone_v8_compat_command --no-sync-deps)
endif()
set(_blink_standalone_v8_compat_action "${BLINK_STANDALONE_V8_COMPAT_ACTION}")
if(_blink_standalone_v8_compat_action STREQUAL "" OR
   _blink_standalone_v8_compat_action STREQUAL "auto")
  if(BLINK_STANDALONE_V8_COMPAT_BUILD)
    set(_blink_standalone_v8_compat_action build)
  elseif(BLINK_STANDALONE_V8_TOOLCHAIN STREQUAL "msvc")
    # Native cl.exe compiles renderer objects against the generated V8 public
    # headers, so the V8 MSVC patch queue must be applied even when reusing an
    # existing v8_monolith.lib.
    set(_blink_standalone_v8_compat_action prepare)
  else()
    set(_blink_standalone_v8_compat_action plan)
  endif()
endif()
if(NOT _blink_standalone_v8_compat_action MATCHES "^(plan|prepare|gn-gen|build)$")
  message(FATAL_ERROR
    "BLINK_STANDALONE_V8_COMPAT_ACTION must be one of auto, plan, prepare, gn-gen, or build.")
endif()
list(APPEND _blink_standalone_v8_compat_command --action ${_blink_standalone_v8_compat_action})
if(_blink_standalone_v8_compat_action STREQUAL "build")
  set(_blink_standalone_v8_compat_comment "V8/CppGC compatibility full build")
elseif(_blink_standalone_v8_compat_action STREQUAL "gn-gen")
  set(_blink_standalone_v8_compat_comment "V8/CppGC compatibility GN generation")
elseif(_blink_standalone_v8_compat_action STREQUAL "prepare")
  set(_blink_standalone_v8_compat_comment "V8/CppGC compatibility prepare")
else()
  set(_blink_standalone_v8_compat_comment "V8/CppGC compatibility build plan")
endif()
set(_blink_standalone_v8_compat_byproducts
  ${BLINK_STANDALONE_V8_MONOLITH_LIB}
  ${BLINK_STANDALONE_ICU_DATA_FILE}
)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND BLINK_STANDALONE_USE_CHROMIUM_LIBCXX)
  list(APPEND _blink_standalone_v8_compat_byproducts
    ${BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB}
    ${BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB}
  )
endif()
set(_blink_standalone_v8_compat_stamp
  ${CMAKE_BINARY_DIR}/CMakeFiles/blink_standalone_v8_compat.stamp
)
add_custom_command(
  OUTPUT ${_blink_standalone_v8_compat_stamp}
  COMMAND ${_blink_standalone_v8_compat_command}
  COMMAND ${CMAKE_COMMAND} -E touch ${_blink_standalone_v8_compat_stamp}
  BYPRODUCTS ${_blink_standalone_v8_compat_byproducts}
  USES_TERMINAL
  COMMENT "${_blink_standalone_v8_compat_comment}"
  VERBATIM
)
add_custom_target(blink_standalone_v8_compat
  DEPENDS ${_blink_standalone_v8_compat_stamp}
)

function(blink_standalone_add_v8_compat_dependency target_name)
  if(TARGET blink_standalone_v8_compat_validate)
    add_dependencies(${target_name} blink_standalone_v8_compat_validate)
  endif()
endfunction()

function(blink_standalone_copy_icu_data target_name)
  add_custom_command(TARGET ${target_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_ICU_DATA_FILE}"
      "$<TARGET_FILE_DIR:${target_name}>/icudtl.dat"
    COMMENT "Copying ICU data sidecar for ${target_name}"
  )
endfunction()

add_library(blink_standalone_v8_monolith STATIC IMPORTED GLOBAL)
set_target_properties(blink_standalone_v8_monolith PROPERTIES
  IMPORTED_LOCATION "${BLINK_STANDALONE_V8_MONOLITH_LIB}"
  INTERFACE_COMPILE_DEFINITIONS "${BLINK_STANDALONE_STL_DEFINES};${BLINK_STANDALONE_V8_ABI_DEFINES}"
)
set(_blink_standalone_libcxx_object_list
  ${CMAKE_BINARY_DIR}/v8_compat_libcxx_objects.txt
)
set(_blink_standalone_v8_compat_validation_command
  ${Python3_EXECUTABLE}
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/v8/validate_v8_compat_output.py
  --monolith-lib ${BLINK_STANDALONE_V8_MONOLITH_LIB}
  --toolchain ${BLINK_STANDALONE_V8_TOOLCHAIN}
  --v8-include-dir ${BLINK_STANDALONE_V8_INCLUDE_DIR}
)
add_library(blink_standalone_chromium_libcxx INTERFACE)
if(BLINK_STANDALONE_USE_CHROMIUM_LIBCXX)
  if(WIN32)
    blink_standalone_resolve_libcxx_objects(
      BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECTS
      "${BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR}"
    )
    set_source_files_properties(${BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECTS}
      PROPERTIES
        GENERATED TRUE
        EXTERNAL_OBJECT TRUE
    )
    file(WRITE "${_blink_standalone_libcxx_object_list}" "")
    foreach(_blink_standalone_libcxx_object_name IN LISTS BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_NAMES)
      file(APPEND "${_blink_standalone_libcxx_object_list}" "${_blink_standalone_libcxx_object_name}\n")
    endforeach()
    list(APPEND _blink_standalone_v8_compat_validation_command
      --libcxx-object-dir ${BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR}
      --object-list ${_blink_standalone_libcxx_object_list}
    )
    target_sources(blink_standalone_chromium_libcxx INTERFACE
      ${BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECTS}
    )
    add_library(blink_standalone_chromium_libcxx_static STATIC
      ${BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECTS}
    )
    set_target_properties(blink_standalone_chromium_libcxx_static PROPERTIES
      LINKER_LANGUAGE CXX
      OUTPUT_NAME chromium_libcxx
    )
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND _blink_standalone_v8_compat_validation_command
      --required-path ${BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB}
      --required-path ${BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB}
    )
    target_link_libraries(blink_standalone_chromium_libcxx INTERFACE
      "${BLINK_STANDALONE_CHROMIUM_LIBCXX_LIB}"
      "${BLINK_STANDALONE_CHROMIUM_LIBCXXABI_LIB}"
    )
  endif()
endif()
set(_blink_standalone_v8_compat_validate_stamp
  ${CMAKE_BINARY_DIR}/CMakeFiles/blink_standalone_v8_compat_validate.stamp
)
add_custom_command(
  OUTPUT ${_blink_standalone_v8_compat_validate_stamp}
  COMMAND ${_blink_standalone_v8_compat_validation_command}
  COMMAND ${CMAKE_COMMAND} -E touch ${_blink_standalone_v8_compat_validate_stamp}
  DEPENDS
    ${BLINK_STANDALONE_V8_MONOLITH_LIB}
    ${_blink_standalone_v8_compat_stamp}
  COMMENT "Validate V8/CppGC compatibility link outputs"
  VERBATIM
)
add_custom_target(blink_standalone_v8_compat_validate
  DEPENDS ${_blink_standalone_v8_compat_validate_stamp}
)
if(_blink_standalone_v8_compat_action STREQUAL "build")
  add_dependencies(blink_standalone_v8_compat_validate blink_standalone_v8_compat)
endif()

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

find_package(Threads REQUIRED)
if(BLINK_STANDALONE_USE_VCPKG_DEPS)
  find_package(Iconv REQUIRED)
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
else()
  if(NOT TARGET ZLIB::ZLIB)
    add_library(blink_standalone_chromium_zlib_headers INTERFACE)
    target_include_directories(blink_standalone_chromium_zlib_headers
      INTERFACE
        ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib
    )
    add_library(ZLIB::ZLIB ALIAS blink_standalone_chromium_zlib_headers)
  endif()

  set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_CATALOG OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_HTTP OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_ICONV OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_ICU OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_LZMA OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_MODULES OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_PROGRAMS OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_PYTHON OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_TESTS OFF CACHE BOOL "" FORCE)
  set(LIBXML2_WITH_ZLIB OFF CACHE BOOL "" FORCE)
  add_subdirectory(
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/src
    third_party/libxml
    EXCLUDE_FROM_ALL)
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

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/live_blink_sources.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/angle_runtime.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/abseil_sources.cmake)
if(NOT BLINK_STANDALONE_V8_TOOLCHAIN STREQUAL "msvc")
  list(APPEND BLINK_STANDALONE_ABSEIL_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp/absl/base/internal/hardening.cc
  )
endif()

set(BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES)
if(BLINK_STANDALONE_DAWN_D3D12)
  set(BLINK_STANDALONE_DAWN_D3D12_ADDED_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/image_context_impl.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/skia_output_device_dawn.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/dawn_context_provider.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/dawn_instance.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/dawn_platform.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/dxgi_shared_handle_manager.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/d3d_image_backing.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/d3d_image_backing_factory.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/d3d_image_representation.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/d3d_image_utils.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/d3d11_image_same_adapter_copy_strategy.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/dawn_copy_strategy.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/dawn_fallback_image_representation.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/dawn_shared_texture_cache.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/gl_texture_passthrough_fallback_image_representation.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/skia_graphite_dawn_image_representation.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/wrapped_graphite_texture_backing.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnBackendTexture.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnQueueManager.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnSharedContext.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnTextureInfo.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnGraphiteUtils.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/dxgi_helpers.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnCaps.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnBuffer.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnCommandBuffer.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnComputePipeline.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnErrorChecker.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnGraphicsPipeline.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnResourceProvider.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnSampler.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/dawn/DawnTexture.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/codegen/SkSLWGSLCodeGenerator.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/buffer_usage_util.cc
  )
  list(APPEND BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_DAWN_D3D12_ADDED_SOURCES}
  )
  set(BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES
    ${BLINK_STANDALONE_DAWN_D3D12_ADDED_SOURCES}
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/compositor_gpu_thread.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/compositor_gpu_thread.h
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/skia_output_surface_dependency_impl.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/skia_output_surface_impl_on_gpu.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/in_process_gpu_thread_holder.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_context_state.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/shared_image_backing.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/shared_image_backing.h
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/shared_image_format_service_utils.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/shared_image_format_service_utils.h
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/shared_image_representation.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/shared_image_representation.h
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/wrapped_sk_image_backing_factory.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/standalone_live_frame_bridge_probe.cc
  )
  list(REMOVE_ITEM BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES}
  )
endif()

if(NOT BLINK_STANDALONE_ICU_SOURCE_ROOT STREQUAL
   "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu")
  set(_blink_standalone_rebased_live_sources)
  foreach(source IN LISTS BLINK_STANDALONE_LIVE_SOURCES)
    string(REPLACE
      "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/"
      "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/"
      rebased_source
      "${source}"
    )
    list(APPEND _blink_standalone_rebased_live_sources "${rebased_source}")
  endforeach()
  set(BLINK_STANDALONE_LIVE_SOURCES
    ${_blink_standalone_rebased_live_sources}
  )
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/third_party/icu/source/common/fixedstring\\.cpp$")
endif()

set(BLINK_STANDALONE_ZLIB_C_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/adler32.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/compress.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/crc32.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/deflate.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/infback.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inffast.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inflate.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inftrees.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/trees.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/uncompr.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/zutil.c
)

set(BLINK_STANDALONE_PARTITION_ALLOC_BASE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/check.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/cpu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/debug/alias.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/debug/stack_trace.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/debug/stack_trace_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/log_message.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/logging.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/memory/page_size_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/memory/ref_counted.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/process/process_handle_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/rand_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/rand_util_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/scoped_clear_last_error_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/strings/cstring_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/strings/safe_sprintf.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/strings/string_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/strings/stringprintf.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/threading/platform_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/threading/platform_thread_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/time/time.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/time/time_override.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_base/time/time_win.cc
)

set(BLINK_STANDALONE_PARTITION_ALLOC_CORE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/address_pool_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/address_pool_manager_bitmap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/address_space_randomization.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/allocation_guard.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/allocator_config.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/bounds_checks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/compressed_pointer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/dangling_raw_ptr_checks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/gwp_asan_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/in_slot_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/internal_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/memory_reclaimer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/oom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/oom_callback.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/page_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_address_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc_hooks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_bucket.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_cookie.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_dcheck_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_freelist_entry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_oom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_page.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_stats.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_tls_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/random.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/reservation_offset_table.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/scheduler_loop_quarantine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/scheduler_loop_quarantine_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/slot_address_and_size.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/slot_start.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/spinning_mutex.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/stack/stack.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/tagging.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/thread_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/thread_isolation/pkey.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/thread_isolation/thread_isolation.cc
)
if(NOT BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
  list(APPEND BLINK_STANDALONE_PARTITION_ALLOC_CORE_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/stack/asm/x64/push_registers_asm.cc
  )
endif()

set(BLINK_STANDALONE_LIBPNG_C_SOURCES
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
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwio.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwrite.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwtran.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwutil.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/intel/filter_sse2_intrinsics.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/intel/intel_init.c
)
set(BLINK_STANDALONE_LIBPNG_ZLIB_C_SOURCES
  ${BLINK_STANDALONE_LIBPNG_C_SOURCES}
  ${BLINK_STANDALONE_ZLIB_C_SOURCES}
)
set_source_files_properties(${BLINK_STANDALONE_LIBPNG_ZLIB_C_SOURCES}
  PROPERTIES LANGUAGE CXX)
set_source_files_properties(${BLINK_STANDALONE_PARTITION_ALLOC_BASE_SOURCES}
  PROPERTIES COMPILE_DEFINITIONS IS_PARTITION_ALLOC_BASE_IMPL=1)
set_source_files_properties(${BLINK_STANDALONE_PARTITION_ALLOC_CORE_SOURCES}
  PROPERTIES COMPILE_DEFINITIONS IS_PARTITION_ALLOC_IMPL=1)
list(APPEND BLINK_STANDALONE_LIVE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/i18n/icu_util.cc
  ${BLINK_STANDALONE_ZLIB_C_SOURCES}
)
if(EXISTS "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/stubdata/stubdata.cpp")
  list(APPEND BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/stubdata/stubdata.cpp
  )
endif()
# Source-built v8_monolith contains the real PartitionAlloc implementation used
# by V8/CppGC. Do not link the tracked implementation objects into the normal
# V8-backed renderer as well, or lld reports duplicate PartitionAlloc symbols.
if(BLINK_STANDALONE_V8_TOOLCHAIN STREQUAL "msvc")
  list(APPEND BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_PARTITION_ALLOC_BASE_SOURCES}
    ${BLINK_STANDALONE_PARTITION_ALLOC_CORE_SOURCES}
  )
endif()

if(BLINK_STANDALONE_PERF_BUILD OR BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
  set(BLINK_STANDALONE_PERF_SKIA_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmapProcState_opts_ssse3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitMask_opts_ssse3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitRow_opts_ml3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDistanceFieldGen.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMemset_opts_avx.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMemset_opts_erms.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSwizzler_opts_ml3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSwizzler_opts_ssse3.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkGaussianColorFilter.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/SDFMaskFilter.cpp
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
  if(BLINK_STANDALONE_COMPILER_IS_CLANG_CL)
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
  elseif(BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
    set_property(SOURCE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformHsw.cc
      APPEND PROPERTY COMPILE_OPTIONS
        /arch:AVX2
    )
    set_property(SOURCE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformSkx.cc
      APPEND PROPERTY COMPILE_OPTIONS
        /arch:AVX512
    )
  endif()
endif()

set(BLINK_STANDALONE_APP_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/examples/compositor_benchmark.cc
)
set(BLINK_STANDALONE_SDL_APP_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/examples/compositor_sdl_viewer.cc
)
set(BLINK_STANDALONE_C_API_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/renderer_c_api.cc
)
set(BLINK_STANDALONE_C_API_EXPORTS_DEF
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/renderer_c_api_exports.def
)
set(BLINK_STANDALONE_PRIVATE_SYMBOL_PREFIX_DIR
  ${CMAKE_BINARY_DIR}/generated/standalone_renderer/generated
)
file(MAKE_DIRECTORY "${BLINK_STANDALONE_PRIVATE_SYMBOL_PREFIX_DIR}")

set(BLINK_STANDALONE_PRIVATE_LIBPNG_SYMBOL_PREFIX_HEADER
  ${BLINK_STANDALONE_PRIVATE_SYMBOL_PREFIX_DIR}/private_libpng_symbol_prefix.h
)
set(_blink_standalone_private_libpng_symbols)
file(READ
  "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/png.h"
  _blink_standalone_libpng_public_header
)
string(REGEX REPLACE
  "[\r\n]+[ \t]*" " "
  _blink_standalone_libpng_public_header_flat
  "${_blink_standalone_libpng_public_header}"
)
string(REGEX MATCHALL
  "PNG_([A-Z_]+_)?EXPORTA?\\([^)]*,[^)]*,[ \t]*(png_[A-Za-z0-9_]+)"
  _blink_standalone_libpng_public_matches
  "${_blink_standalone_libpng_public_header_flat}"
)
foreach(match IN LISTS _blink_standalone_libpng_public_matches)
  string(REGEX REPLACE
    "^.*,[ \t]*(png_[A-Za-z0-9_]+).*$" "\\1"
    symbol "${match}"
  )
  list(APPEND _blink_standalone_private_libpng_symbols "${symbol}")
endforeach()
file(READ
  "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngpriv.h"
  _blink_standalone_libpng_private_header
)
string(REGEX REPLACE
  "[\r\n]+[ \t]*" " "
  _blink_standalone_libpng_private_header_flat
  "${_blink_standalone_libpng_private_header}"
)
string(REGEX MATCHALL
  "PNG_INTERNAL_(DATA|FUNCTION|CALLBACK)\\([^)]*,[ \t]*(png_[A-Za-z0-9_]+)"
  _blink_standalone_libpng_private_matches
  "${_blink_standalone_libpng_private_header_flat}"
)
foreach(match IN LISTS _blink_standalone_libpng_private_matches)
  string(REGEX REPLACE
    "^.*,[ \t]*(png_[A-Za-z0-9_]+).*$" "\\1"
    symbol "${match}"
  )
  list(APPEND _blink_standalone_private_libpng_symbols "${symbol}")
endforeach()
file(GLOB_RECURSE _blink_standalone_libpng_symbol_sources
  CONFIGURE_DEPENDS
  "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/*.c"
  "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/*.h"
)
foreach(_blink_standalone_libpng_symbol_source IN LISTS
        _blink_standalone_libpng_symbol_sources)
  file(READ
    "${_blink_standalone_libpng_symbol_source}"
    _blink_standalone_libpng_symbol_source_text
  )
  string(REGEX MATCHALL
    "(^|[^A-Za-z0-9_])(png_[A-Za-z0-9_]+)[ \t\r\n]*\\("
    _blink_standalone_libpng_source_symbol_matches
    "${_blink_standalone_libpng_symbol_source_text}"
  )
  foreach(match IN LISTS _blink_standalone_libpng_source_symbol_matches)
    string(REGEX REPLACE
      "^.*(png_[A-Za-z0-9_]+)[ \t\r\n]*\\($"
      "\\1"
      symbol "${match}"
    )
    list(APPEND _blink_standalone_private_libpng_symbols "${symbol}")
  endforeach()
  string(REGEX MATCHALL
    "(^|[^A-Za-z0-9_])(png_[A-Za-z0-9_]+),[ \t\r\n]*\\("
    _blink_standalone_libpng_comma_symbol_matches
    "${_blink_standalone_libpng_symbol_source_text}"
  )
  foreach(match IN LISTS _blink_standalone_libpng_comma_symbol_matches)
    string(REGEX REPLACE
      "^.*(png_[A-Za-z0-9_]+),[ \t\r\n]*\\($"
      "\\1"
      symbol "${match}"
    )
    list(APPEND _blink_standalone_private_libpng_symbols "${symbol}")
  endforeach()
endforeach()
list(APPEND _blink_standalone_private_libpng_symbols
  png_create_png_struct
)
list(REMOVE_DUPLICATES _blink_standalone_private_libpng_symbols)
list(FILTER _blink_standalone_private_libpng_symbols EXCLUDE REGEX "^png_debug")
list(SORT _blink_standalone_private_libpng_symbols)
set(_blink_standalone_private_libpng_prefix_content "")
string(APPEND _blink_standalone_private_libpng_prefix_content
  "/* Generated by standalone CMake. Do not edit. */\n"
  "#ifndef STANDALONE_RENDERER_GENERATED_PRIVATE_LIBPNG_SYMBOL_PREFIX_H_\n"
  "#define STANDALONE_RENDERER_GENERATED_PRIVATE_LIBPNG_SYMBOL_PREFIX_H_\n\n"
  "/* Keep Blink/Skia's bundled libpng symbols private in static packages. */\n"
)
foreach(symbol IN LISTS _blink_standalone_private_libpng_symbols)
  string(APPEND _blink_standalone_private_libpng_prefix_content
    "#define ${symbol} blink_standalone_${symbol}\n"
  )
endforeach()
string(APPEND _blink_standalone_private_libpng_prefix_content
  "\n#endif  /* STANDALONE_RENDERER_GENERATED_PRIVATE_LIBPNG_SYMBOL_PREFIX_H_ */\n"
)
file(GENERATE
  OUTPUT "${BLINK_STANDALONE_PRIVATE_LIBPNG_SYMBOL_PREFIX_HEADER}"
  CONTENT "${_blink_standalone_private_libpng_prefix_content}"
)

set(BLINK_STANDALONE_PRIVATE_VMA_SYMBOL_PREFIX_GENERATED_HEADER
  ${BLINK_STANDALONE_PRIVATE_SYMBOL_PREFIX_DIR}/private_vma_symbol_prefix_generated.h
)
file(READ
  "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan_memory_allocator/include/vk_mem_alloc.h"
  _blink_standalone_vma_header
)
string(REGEX MATCHALL
  "(^|[^A-Za-z0-9_])(Vma[A-Za-z0-9_]*)"
  _blink_standalone_private_vma_matches
  "${_blink_standalone_vma_header}"
)
set(_blink_standalone_private_vma_symbols)
foreach(match IN LISTS _blink_standalone_private_vma_matches)
  string(REGEX REPLACE
    "^.*(Vma[A-Za-z0-9_]*)$" "\\1"
    symbol "${match}"
  )
  list(APPEND _blink_standalone_private_vma_symbols "${symbol}")
endforeach()
list(REMOVE_DUPLICATES _blink_standalone_private_vma_symbols)
list(SORT _blink_standalone_private_vma_symbols)
set(_blink_standalone_private_vma_prefix_content "")
string(APPEND _blink_standalone_private_vma_prefix_content
  "/* Generated by standalone CMake. Do not edit. */\n"
  "#ifndef STANDALONE_RENDERER_GENERATED_PRIVATE_VMA_SYMBOL_PREFIX_H_\n"
  "#define STANDALONE_RENDERER_GENERATED_PRIVATE_VMA_SYMBOL_PREFIX_H_\n\n"
  "/* Keep VMA's C++ internal symbol names private in static packages. */\n"
)
foreach(symbol IN LISTS _blink_standalone_private_vma_symbols)
  string(APPEND _blink_standalone_private_vma_prefix_content
    "#define ${symbol} blink_standalone_${symbol}\n"
  )
endforeach()
string(APPEND _blink_standalone_private_vma_prefix_content
  "\n#endif  /* STANDALONE_RENDERER_GENERATED_PRIVATE_VMA_SYMBOL_PREFIX_H_ */\n"
)
file(GENERATE
  OUTPUT "${BLINK_STANDALONE_PRIVATE_VMA_SYMBOL_PREFIX_GENERATED_HEADER}"
  CONTENT "${_blink_standalone_private_vma_prefix_content}"
)

file(GLOB_RECURSE _blink_standalone_icu_symbol_sources
  CONFIGURE_DEPENDS
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common/*.c"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common/*.cc"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common/*.cpp"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common/*.h"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/i18n/*.c"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/i18n/*.cc"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/i18n/*.cpp"
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/i18n/*.h"
)
set(_blink_standalone_icu_urename_header
  "${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common/unicode/urename.h")
set(_blink_standalone_icu_urename_text "")
if(EXISTS "${_blink_standalone_icu_urename_header}")
  file(READ "${_blink_standalone_icu_urename_header}"
    _blink_standalone_icu_urename_text)
endif()
set(_blink_standalone_private_icu_symbols)
foreach(_blink_standalone_icu_symbol_source IN LISTS
        _blink_standalone_icu_symbol_sources)
  file(READ "${_blink_standalone_icu_symbol_source}"
    _blink_standalone_icu_symbol_source_text)
  string(REGEX MATCHALL "(^|[^A-Za-z0-9_])(uprv_[A-Za-z0-9_]+)"
    _blink_standalone_icu_symbol_matches
    "${_blink_standalone_icu_symbol_source_text}")
  foreach(match IN LISTS _blink_standalone_icu_symbol_matches)
    string(REGEX REPLACE "^.*(uprv_[A-Za-z0-9_]+)$" "\\1"
      symbol "${match}")
    if(NOT _blink_standalone_icu_urename_text MATCHES
       "(^|\n)[ \t]*#[ \t]*define[ \t]+${symbol}[ \t]")
      list(APPEND _blink_standalone_private_icu_symbols "${symbol}")
    endif()
  endforeach()
endforeach()
list(REMOVE_DUPLICATES _blink_standalone_private_icu_symbols)
list(SORT _blink_standalone_private_icu_symbols)
set(_blink_standalone_private_icu_prefix_content "")
string(APPEND _blink_standalone_private_icu_prefix_content
  "/* Generated by standalone CMake. Do not edit. */\n"
  "#ifndef STANDALONE_RENDERER_GENERATED_PRIVATE_ICU_SYMBOL_PREFIX_H_\n"
  "#define STANDALONE_RENDERER_GENERATED_PRIVATE_ICU_SYMBOL_PREFIX_H_\n\n"
  "/* Keep Blink's bundled ICU internals private in static packages. */\n"
)
foreach(symbol IN LISTS _blink_standalone_private_icu_symbols)
  string(APPEND _blink_standalone_private_icu_prefix_content
    "#ifndef ${symbol}\n"
    "#define ${symbol} blink_standalone_${symbol}\n"
    "#endif\n"
  )
endforeach()
string(APPEND _blink_standalone_private_icu_prefix_content
  "\n#endif  /* STANDALONE_RENDERER_GENERATED_PRIVATE_ICU_SYMBOL_PREFIX_H_ */\n"
)
set(BLINK_STANDALONE_PRIVATE_ICU_SYMBOL_PREFIX_HEADER
  ${BLINK_STANDALONE_PRIVATE_SYMBOL_PREFIX_DIR}/private_icu_symbol_prefix.h
)
file(GENERATE
  OUTPUT "${BLINK_STANDALONE_PRIVATE_ICU_SYMBOL_PREFIX_HEADER}"
  CONTENT "${_blink_standalone_private_icu_prefix_content}"
)

function(blink_standalone_force_include_header header)
  if(MSVC)
    foreach(source IN LISTS ARGN)
      set_property(SOURCE ${source} APPEND PROPERTY COMPILE_OPTIONS
        "/FI${header}"
      )
    endforeach()
  else()
    foreach(source IN LISTS ARGN)
      set_property(SOURCE ${source} APPEND PROPERTY COMPILE_OPTIONS
        "-include" "${header}"
      )
    endforeach()
  endif()
endfunction()

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

set(BLINK_STANDALONE_LIBPNG_PREFIX_SOURCES
  ${BLINK_STANDALONE_LIBPNG_C_SOURCES}
)
foreach(source IN LISTS BLINK_STANDALONE_LIVE_SOURCES)
  if(source MATCHES "/third_party/skia/src/codec/SkPng.*\\.cpp$" OR
     source MATCHES "/third_party/blink/renderer/platform/image-decoders/png/" OR
     source MATCHES "/ui/gfx/codec/png_codec\\.cc$")
    list(APPEND BLINK_STANDALONE_LIBPNG_PREFIX_SOURCES ${source})
  endif()
endforeach()
foreach(source IN LISTS BLINK_STANDALONE_LIVE_SOURCES)
  if(source MATCHES "/third_party/skia/src/encode/SkPng.*\\.cpp$")
    list(APPEND BLINK_STANDALONE_LIBPNG_PREFIX_SOURCES ${source})
  endif()
endforeach()
list(REMOVE_DUPLICATES BLINK_STANDALONE_LIBPNG_PREFIX_SOURCES)
blink_standalone_force_include_header(
  "${BLINK_STANDALONE_PRIVATE_LIBPNG_SYMBOL_PREFIX_HEADER}"
  ${BLINK_STANDALONE_LIBPNG_PREFIX_SOURCES}
)
set_property(SOURCE ${BLINK_STANDALONE_LIBPNG_PREFIX_SOURCES}
  APPEND PROPERTY COMPILE_DEFINITIONS PNG_NO_USE_READ_MACROS
)

set(BLINK_STANDALONE_ICU_PREFIX_SOURCES)
foreach(source IN LISTS BLINK_STANDALONE_LIVE_SOURCES)
  if(source MATCHES "/third_party/icu/source/")
    list(APPEND BLINK_STANDALONE_ICU_PREFIX_SOURCES ${source})
  endif()
endforeach()
list(REMOVE_DUPLICATES BLINK_STANDALONE_ICU_PREFIX_SOURCES)
blink_standalone_force_include_header(
  "${BLINK_STANDALONE_PRIVATE_ICU_SYMBOL_PREFIX_HEADER}"
  ${BLINK_STANDALONE_ICU_PREFIX_SOURCES}
)

if(MSVC)
  set_property(SOURCE ${BLINK_STANDALONE_BOUNDARY_SOURCES}
    APPEND PROPERTY COMPILE_OPTIONS
      /FI${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs/standalone_network_namespace_forwards.h
  )
endif()

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

if(BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
  set_property(GLOBAL APPEND PROPERTY JOB_POOLS blink_standalone_msvc_heap_sensitive=1)
  set(BLINK_STANDALONE_MSVC_HEAP_SENSITIVE_SOURCES
    ${BLINK_STANDALONE_PARTITION_ALLOC_CORE_SOURCES}
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/bounds_checks.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/gwp_asan_support.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/in_slot_metadata.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/internal_allocator.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/memory_reclaimer.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_alloc.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src/partition_alloc/partition_bucket.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editing_utilities.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/text_iterator_text_state.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/ng_flat_tree_shorthands.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/editing_commands_utilities.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/indent_outdent_command.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_into_text_node_command.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_line_break_command.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_object.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/standalone_resource_provider.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/visual_viewport.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_image_element.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_image_fallback_helper.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_image_loader.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/image_loader.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/html_canvas_painter.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/style_commands.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_layer_delegate.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/skia/skia_utils.cc
  )
  list(REMOVE_DUPLICATES BLINK_STANDALONE_MSVC_HEAP_SENSITIVE_SOURCES)
  foreach(source IN LISTS BLINK_STANDALONE_MSVC_HEAP_SENSITIVE_SOURCES)
    set_property(SOURCE ${source} APPEND PROPERTY COMPILE_OPTIONS
      /Od
      /Ob0
      /Oy-
    )
    set_property(SOURCE ${source} PROPERTY JOB_POOL_COMPILE blink_standalone_msvc_heap_sensitive)
  endforeach()
endif()

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

function(blink_standalone_configure_abseil_target target_name)
  target_include_directories(${target_name} BEFORE PRIVATE
    ${BLINK_STANDALONE_STL_INCLUDE_DIRS}
    ${BLINK_STANDALONE_V8_ABSEIL_INCLUDE_DIR}
  )
  target_include_directories(${target_name} PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
  )
  target_compile_definitions(${target_name} PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_NONSTDC_NO_WARNINGS
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_DEPRECATE
    _WINSOCK_DEPRECATED_NO_WARNINGS
    UNICODE
    _UNICODE
    ${BLINK_STANDALONE_STL_DEFINES}
  )
  set_property(TARGET ${target_name} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")
  if(MSVC)
    target_compile_options(${target_name} PRIVATE
      /bigobj
      /permissive-
      /Zc:__cplusplus
      /wd4005
      /wd4068
      /wd4100
      /wd4127
      /wd4267
      /wd4324
      /wd4800
      /wd4996
    )
  endif()
endfunction()

add_library(blink_standalone_abseil_static STATIC
  ${BLINK_STANDALONE_ABSEIL_SOURCES}
)
set_target_properties(blink_standalone_abseil_static PROPERTIES
  OUTPUT_NAME blink_standalone_abseil
)
blink_standalone_configure_abseil_target(blink_standalone_abseil_static)

set(BLINK_STANDALONE_LIVE_OBJECTS
  $<TARGET_OBJECTS:blink_live_modp_b64>
)
if(BLINK_STANDALONE_COMPILER_IS_MSVC_CL)
  add_library(blink_standalone_partition_alloc_masm OBJECT
    ${BLINK_STANDALONE_RENDERER_ROOT}/src/partition_alloc_push_registers_masm.asm
  )
  list(APPEND BLINK_STANDALONE_LIVE_OBJECTS
    $<TARGET_OBJECTS:blink_standalone_partition_alloc_masm>
  )
endif()
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
if(BLINK_STANDALONE_DAWN_D3D12)
  set(_blink_standalone_dawn_render_sources_normalized)
  foreach(source IN LISTS BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES)
    file(TO_CMAKE_PATH "${source}" normalized_source)
    list(APPEND _blink_standalone_dawn_render_sources_normalized
      "${normalized_source}")
  endforeach()
  set(_blink_standalone_live_sources_without_dawn)
  foreach(source IN LISTS BLINK_STANDALONE_LIVE_SOURCES)
    file(TO_CMAKE_PATH "${source}" normalized_source)
    if(NOT normalized_source IN_LIST
        _blink_standalone_dawn_render_sources_normalized)
      list(APPEND _blink_standalone_live_sources_without_dawn "${source}")
    endif()
  endforeach()
  set(BLINK_STANDALONE_LIVE_SOURCES
    ${_blink_standalone_live_sources_without_dawn})
  add_library(blink_standalone_dawn_d3d12_render_objects OBJECT
    ${BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES}
  )
add_dependencies(blink_standalone_dawn_d3d12_render_objects
    blink_angle_libEGL_static
    blink_angle_libGLESv2_static
  )
  blink_standalone_add_v8_compat_dependency(
    blink_standalone_dawn_d3d12_render_objects)
  set_property(TARGET blink_standalone_dawn_d3d12_render_objects PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")
  list(APPEND BLINK_STANDALONE_LIVE_OBJECTS
    $<TARGET_OBJECTS:blink_standalone_dawn_d3d12_render_objects>
  )
endif()

add_library(blink_standalone_live_renderer_objects OBJECT
  ${BLINK_STANDALONE_LIVE_SOURCES}
)
add_dependencies(blink_standalone_live_renderer_objects
  blink_angle_libEGL_static
  blink_angle_libGLESv2_static
)
blink_standalone_add_v8_compat_dependency(blink_standalone_live_renderer_objects)
if(BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
  target_include_directories(blink_standalone_live_renderer_objects BEFORE PRIVATE
    ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}
  )
endif()
set_property(TARGET blink_standalone_live_renderer_objects PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded")

add_executable(blink_standalone_render_benchmark_skia
  ${BLINK_STANDALONE_APP_SOURCES}
  ${BLINK_STANDALONE_C_API_SOURCES}
  $<TARGET_OBJECTS:blink_standalone_live_renderer_objects>
  ${BLINK_STANDALONE_LIVE_OBJECTS}
)
add_dependencies(blink_standalone_render_benchmark_skia
  blink_angle_libEGL_static
  blink_angle_libGLESv2_static
)
blink_standalone_add_v8_compat_dependency(blink_standalone_render_benchmark_skia)

  if(BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
    target_include_directories(blink_standalone_render_benchmark_skia BEFORE PRIVATE
      ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}
    )
  endif()

  target_include_directories(blink_standalone_render_benchmark_skia BEFORE PRIVATE
    ${BLINK_STANDALONE_STL_INCLUDE_DIRS}
    ${BLINK_STANDALONE_V8_INCLUDE_DIR}
    ${BLINK_STANDALONE_V8_GENERATED_SOURCE_ROOT}
    ${BLINK_STANDALONE_V8_ABSEIL_INCLUDE_DIR}
  )
  target_include_directories(blink_standalone_render_benchmark_skia PRIVATE
    ${CMAKE_BINARY_DIR}/generated
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/base
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/third_party/xxhash
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/dawn/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/ipcz/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/khronos
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan-headers/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan_memory_allocator/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/flatbuffers/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/angle
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/v8/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/overrides
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src/quiche/common/platform/default
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/allocator/partition_allocator/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/build_config
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/harfbuzz/src/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/highway/src
    ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common
    ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/i18n
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libwebm/source
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/win32/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/include/third_party/vulkan
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/libpng
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/v8/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
    ${BLINK_STANDALONE_FREETYPE_SOURCE}/include
    ${BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES}
  )
  target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
    BLINK_CORE_IMPLEMENTATION=1
    BLINK_IMPLEMENTATION=1
    INSIDE_BLINK=1
    STANDALONE_RENDERER_GN_PROBE=1
    STANDALONE_RENDERER_NO_RUST=1
    HTML_CSS_RENDERER_STANDALONE=1
    HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT=1
    HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL=1
    HTML_CSS_RENDERER_HAS_REDUCED_BLINK_PLATFORM=1
    HTML_CSS_RENDERER_USE_CHROMIUM_COMPOSITOR=1
    HTML_CSS_RENDERER_ENABLE_WEBGPU=0
    SK_GANESH=1
    SK_VULKAN=1
    VK_NO_PROTOTYPES=1
    BLINK_STANDALONE_PRIVATE_VULKAN_FUNCTION_POINTER_WRAPPERS=1
    SK_GPU_WORKAROUNDS_HEADER=\"gpu/config/gpu_driver_bug_workaround_autogen.h\"
    SK_USE_INTERNAL_VULKAN_HEADERS=1
    WTF_IMPLEMENTATION=1
    USE_AURA=1
    U_STATIC_IMPLEMENTATION
    U_I18N_IMPLEMENTATION
    U_COMMON_IMPLEMENTATION
    ICU_UTIL_DATA_IMPL=ICU_UTIL_DATA_FILE
    ${BLINK_STANDALONE_PRIVATE_ICU_DEFINES}
    PNG_SET_OPTION_SUPPORTED=1
    PNG_WRITE_SUPPORTED=1
    PNG_WRITE_CUSTOMIZE_COMPRESSION_SUPPORTED=1
    PNG_INTEL_SSE=1
    ZLIB_IMPLEMENTATION=1
    ${BLINK_STANDALONE_PLATFORM_COMPILE_DEFINITIONS}
    ${BLINK_STANDALONE_STL_DEFINES}
    ${BLINK_STANDALONE_V8_ABI_DEFINES}
  )
  set_property(TARGET blink_standalone_render_benchmark_skia PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")

  if(NOT BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
    target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
      DCHECK_ALWAYS_ON=1
    )
  endif()

  if(NOT BLINK_STANDALONE_PERF_BUILD AND NOT BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
    target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
      SKCMS_DISABLE_HSW=1
      SKCMS_DISABLE_SKX=1
      SK_ENABLE_OPTIMIZE_SIZE=1
      CPU_NO_SIMD=1
    )
  endif()

  target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
    blink_standalone_abseil_static
    blink_standalone_chromium_libcxx
    blink_standalone_v8_monolith
    ${BLINK_STANDALONE_PLATFORM_LINK_LIBS}
  )

  if(MSVC)
    target_compile_options(blink_standalone_render_benchmark_skia PRIVATE
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
  if(BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS)
    target_compile_options(blink_standalone_render_benchmark_skia PRIVATE
      ${BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS})
  endif()
  if(BLINK_STANDALONE_PLATFORM_LINK_OPTIONS)
    target_link_options(blink_standalone_render_benchmark_skia PRIVATE
      ${BLINK_STANDALONE_PLATFORM_LINK_OPTIONS})
  endif()

  target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
    freetype
    harfbuzz
    LibXml2::LibXml2
  )
  blink_standalone_copy_icu_data(blink_standalone_render_benchmark_skia)

  foreach(property_name IN ITEMS INCLUDE_DIRECTORIES COMPILE_DEFINITIONS
                                 COMPILE_OPTIONS)
    get_target_property(property_value blink_standalone_render_benchmark_skia
      ${property_name})
    if(property_value AND NOT property_value STREQUAL "property_value-NOTFOUND")
      foreach(live_object_target IN ITEMS
          blink_standalone_live_renderer_objects
          blink_standalone_dawn_d3d12_render_objects)
        if(TARGET ${live_object_target})
          if(property_name STREQUAL "INCLUDE_DIRECTORIES")
            target_include_directories(${live_object_target} PRIVATE
              ${property_value})
          elseif(property_name STREQUAL "COMPILE_DEFINITIONS")
            target_compile_definitions(${live_object_target} PRIVATE
              ${property_value})
          elseif(property_name STREQUAL "COMPILE_OPTIONS")
            target_compile_options(${live_object_target} PRIVATE
              ${property_value})
          endif()
        endif()
      endforeach()
    endif()
  endforeach()

  target_compile_definitions(blink_standalone_live_renderer_objects PRIVATE
    LIBXML_STATIC
  )
  target_link_libraries(blink_standalone_live_renderer_objects PRIVATE
    LibXml2::LibXml2
  )
  if(TARGET blink_standalone_dawn_d3d12_render_objects)
    target_compile_definitions(blink_standalone_dawn_d3d12_render_objects
      PRIVATE LIBXML_STATIC)
    target_link_libraries(blink_standalone_dawn_d3d12_render_objects PRIVATE
      LibXml2::LibXml2)
  endif()
  target_compile_definitions(blink_standalone_render_benchmark_skia PRIVATE
    BLINK_STANDALONE_RENDERER_C_API_STATIC=1
  )

  add_library(blink_standalone_renderer_c_api STATIC
    ${BLINK_STANDALONE_C_API_SOURCES}
    $<TARGET_OBJECTS:blink_standalone_live_renderer_objects>
    ${BLINK_STANDALONE_LIVE_OBJECTS}
  )
  add_dependencies(blink_standalone_renderer_c_api
    blink_angle_libEGL_static
    blink_angle_libGLESv2_static
  )
  blink_standalone_add_v8_compat_dependency(blink_standalone_renderer_c_api)
  foreach(property_name IN ITEMS INCLUDE_DIRECTORIES COMPILE_DEFINITIONS
                                 COMPILE_OPTIONS LINK_LIBRARIES)
    get_target_property(property_value blink_standalone_render_benchmark_skia
      ${property_name})
    if(property_value AND NOT property_value STREQUAL "property_value-NOTFOUND")
      if(property_name STREQUAL "INCLUDE_DIRECTORIES")
        target_include_directories(blink_standalone_renderer_c_api PRIVATE
          ${property_value})
      elseif(property_name STREQUAL "COMPILE_DEFINITIONS")
        target_compile_definitions(blink_standalone_renderer_c_api PRIVATE
          ${property_value})
      elseif(property_name STREQUAL "COMPILE_OPTIONS")
        target_compile_options(blink_standalone_renderer_c_api PRIVATE
          ${property_value})
      elseif(property_name STREQUAL "LINK_LIBRARIES")
        if(WIN32 AND TARGET blink_standalone_chromium_libcxx_static)
          list(REMOVE_ITEM property_value blink_standalone_chromium_libcxx)
        endif()
        target_link_libraries(blink_standalone_renderer_c_api PRIVATE
          ${property_value})
      endif()
    endif()
  endforeach()
  target_compile_definitions(blink_standalone_renderer_c_api PRIVATE
    BLINK_STANDALONE_RENDERER_C_API_STATIC=1
    KHRONOS_STATIC=1)
  target_link_libraries(blink_standalone_renderer_c_api PUBLIC
    blink_angle_libEGL_static
    blink_angle_libGLESv2_static)
  set_property(TARGET blink_standalone_renderer_c_api PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")
  set_target_properties(blink_standalone_renderer_c_api PROPERTIES
    OUTPUT_NAME blink_standalone_renderer_c_api_static)

  add_library(blink_standalone_renderer_c_api_dll SHARED
    ${BLINK_STANDALONE_C_API_SOURCES}
    ${BLINK_STANDALONE_C_API_EXPORTS_DEF}
    $<TARGET_OBJECTS:blink_standalone_live_renderer_objects>
    ${BLINK_STANDALONE_ANGLE_IMAGE_UTIL_SOURCES}
    ${BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES}
    ${BLINK_STANDALONE_LIVE_OBJECTS}
  )
  add_dependencies(blink_standalone_renderer_c_api_dll
    blink_angle_libEGL
    blink_angle_libGLESv2
  )
  target_link_libraries(blink_standalone_renderer_c_api_dll PRIVATE
    blink_angle_libEGL
    blink_angle_libGLESv2)
  blink_standalone_add_v8_compat_dependency(blink_standalone_renderer_c_api_dll)
  foreach(property_name IN ITEMS INCLUDE_DIRECTORIES COMPILE_DEFINITIONS
                                 COMPILE_OPTIONS LINK_LIBRARIES)
    get_target_property(property_value blink_standalone_render_benchmark_skia
      ${property_name})
    if(property_value AND NOT property_value STREQUAL "property_value-NOTFOUND")
      if(property_name STREQUAL "INCLUDE_DIRECTORIES")
        target_include_directories(blink_standalone_renderer_c_api_dll PRIVATE
          ${property_value})
      elseif(property_name STREQUAL "COMPILE_DEFINITIONS")
        list(FILTER property_value EXCLUDE REGEX
          "^BLINK_STANDALONE_RENDERER_C_API_STATIC(=|$)")
        target_compile_definitions(blink_standalone_renderer_c_api_dll PRIVATE
          ${property_value})
      elseif(property_name STREQUAL "COMPILE_OPTIONS")
        target_compile_options(blink_standalone_renderer_c_api_dll PRIVATE
          ${property_value})
      elseif(property_name STREQUAL "LINK_LIBRARIES")
        target_link_libraries(blink_standalone_renderer_c_api_dll PRIVATE
          ${property_value})
      endif()
    endif()
  endforeach()
  target_compile_definitions(blink_standalone_renderer_c_api_dll PRIVATE
    BLINK_STANDALONE_RENDERER_C_API_IMPLEMENTATION=1)
  set_property(TARGET blink_standalone_renderer_c_api_dll PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")
  set_target_properties(blink_standalone_renderer_c_api_dll PROPERTIES
    OUTPUT_NAME blink_standalone_renderer_c_api)
  if(BLINK_STANDALONE_PLATFORM_LINK_OPTIONS)
    target_link_options(blink_standalone_renderer_c_api_dll PRIVATE
      ${BLINK_STANDALONE_PLATFORM_LINK_OPTIONS})
  endif()
  if(MSVC)
    target_link_options(blink_standalone_renderer_c_api_dll PRIVATE
      /MAP:${CMAKE_BINARY_DIR}/blink_standalone_renderer_c_api_dll.map
      /DEF:${BLINK_STANDALONE_C_API_EXPORTS_DEF}
    )
  endif()
  target_link_libraries(blink_standalone_render_benchmark_skia PRIVATE
    blink_angle_libEGL_static
    blink_angle_libGLESv2_static)
  if(BLINK_STANDALONE_COMPILER_IS_CLANG_CL)
    target_link_options(blink_standalone_renderer_c_api_dll PRIVATE
      /exclude-all-symbols
      /exclude-symbols:CrashForExceptionInNonABICompliantCodeRange,GetHandleVerifier
    )
  endif()
  blink_standalone_copy_icu_data(blink_standalone_renderer_c_api_dll)

  if(BLINK_STANDALONE_DAWN_D3D12)
    if("${BLINK_STANDALONE_DAWN_D3D12_LIBS}" STREQUAL "")
      message(FATAL_ERROR
        "BLINK_STANDALONE_DAWN_D3D12 requires BLINK_STANDALONE_DAWN_D3D12_LIBS.")
    endif()
    if(NOT EXISTS "${BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR}")
      message(FATAL_ERROR
        "BLINK_STANDALONE_DAWN_D3D12 requires BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR.")
    endif()
    if(NOT EXISTS "${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}")
      message(FATAL_ERROR
        "BLINK_STANDALONE_DAWN_D3D12 requires BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR.")
    endif()
    foreach(dawn_lib IN LISTS BLINK_STANDALONE_DAWN_D3D12_LIBS)
      if(NOT EXISTS "${dawn_lib}")
        message(FATAL_ERROR
          "BLINK_STANDALONE_DAWN_D3D12 library does not exist: ${dawn_lib}")
      endif()
    endforeach()
    set_property(SOURCE ${BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES}
      APPEND PROPERTY INCLUDE_DIRECTORIES
        ${BLINK_STANDALONE_DAWN_D3D12_BUILDFLAGS_DIR}
        ${BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR}
        ${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}
        ${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}/include
    )
    set_property(SOURCE ${BLINK_STANDALONE_DAWN_D3D12_RENDER_SOURCES}
      APPEND PROPERTY COMPILE_DEFINITIONS
        BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER=1
        BLINK_STANDALONE_HAVE_DAWN_D3D12=1
    )
    target_include_directories(blink_standalone_render_benchmark_skia BEFORE PRIVATE
      ${BLINK_STANDALONE_DAWN_D3D12_BUILDFLAGS_DIR}
      ${BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR}
    )
    target_include_directories(blink_standalone_render_benchmark_skia PRIVATE
      ${BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR}
      ${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}
      ${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}/include
    )
    foreach(dawn_api_target IN ITEMS
        blink_standalone_render_benchmark_skia
        blink_standalone_renderer_c_api
        blink_standalone_renderer_c_api_dll)
      target_compile_definitions(${dawn_api_target} PRIVATE
        BLINK_STANDALONE_HAVE_DAWN_D3D12=1
      )
    endforeach()
    if(TARGET blink_standalone_dawn_d3d12_render_objects)
      target_include_directories(
        blink_standalone_dawn_d3d12_render_objects BEFORE PRIVATE
          ${BLINK_STANDALONE_DAWN_D3D12_BUILDFLAGS_DIR}
          ${BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR}
          ${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}
          ${BLINK_STANDALONE_DAWN_D3D12_SOURCE_DIR}/include
      )
      target_compile_definitions(
        blink_standalone_dawn_d3d12_render_objects PRIVATE
          BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER=1
          BLINK_STANDALONE_HAVE_DAWN_D3D12=1
      )
    endif()
    foreach(dawn_link_target IN ITEMS
        blink_standalone_render_benchmark_skia
        blink_standalone_renderer_c_api
        blink_standalone_renderer_c_api_dll)
      target_link_libraries(${dawn_link_target} PRIVATE
        ${BLINK_STANDALONE_DAWN_D3D12_LIBS}
        d3d12
        dxguid
        onecore
        user32
      )
    endforeach()
    if(MSVC)
      target_link_options(blink_standalone_render_benchmark_skia PRIVATE
        /FORCE:MULTIPLE)
    endif()
  endif()

  set(BLINK_STANDALONE_RENDERER_C_API_LINK_MANIFEST
    ${CMAKE_BINARY_DIR}/blink_standalone_renderer_c_api_link_manifest.json
  )
  set(BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR
    ${CMAKE_BINARY_DIR}/package/c_api_runtime
    CACHE PATH
    "Output directory for the embeddable C API DLL/import-library runtime package."
  )
  execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE BLINK_STANDALONE_PACKAGE_GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if(NOT BLINK_STANDALONE_PACKAGE_GIT_COMMIT)
    set(BLINK_STANDALONE_PACKAGE_GIT_COMMIT unknown)
  endif()
  execute_process(
    COMMAND git rev-parse --short=12 HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE BLINK_STANDALONE_PACKAGE_GIT_COMMIT_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if(NOT BLINK_STANDALONE_PACKAGE_GIT_COMMIT_SHORT)
    set(BLINK_STANDALONE_PACKAGE_GIT_COMMIT_SHORT unknown)
  endif()
  if(BLINK_STANDALONE_PACKAGE_GIT_COMMIT STREQUAL "unknown")
    set(_blink_standalone_git_dir "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    set(_blink_standalone_git_actual_dir "")
    if(IS_DIRECTORY "${_blink_standalone_git_dir}")
      set(_blink_standalone_git_actual_dir "${_blink_standalone_git_dir}")
    elseif(EXISTS "${_blink_standalone_git_dir}")
      file(READ "${_blink_standalone_git_dir}" _blink_standalone_git_dir_file)
      string(STRIP "${_blink_standalone_git_dir_file}"
        _blink_standalone_git_dir_file)
      if(_blink_standalone_git_dir_file MATCHES "^gitdir:[ \t]*(.+)$")
        set(_blink_standalone_git_actual_dir "${CMAKE_MATCH_1}")
        if(NOT IS_ABSOLUTE "${_blink_standalone_git_actual_dir}")
          get_filename_component(_blink_standalone_git_actual_dir
            "${_blink_standalone_git_actual_dir}" ABSOLUTE
            BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        endif()
      endif()
    endif()
    if(_blink_standalone_git_actual_dir AND
        EXISTS "${_blink_standalone_git_actual_dir}/HEAD")
      file(READ "${_blink_standalone_git_actual_dir}/HEAD"
        _blink_standalone_git_head)
      string(STRIP "${_blink_standalone_git_head}"
        _blink_standalone_git_head)
      if(_blink_standalone_git_head MATCHES "^ref: (.+)$")
        set(_blink_standalone_git_ref_name "${CMAKE_MATCH_1}")
        set(_blink_standalone_git_ref
          "${_blink_standalone_git_actual_dir}/${_blink_standalone_git_ref_name}")
        if(EXISTS "${_blink_standalone_git_ref}")
          file(READ "${_blink_standalone_git_ref}"
            BLINK_STANDALONE_PACKAGE_GIT_COMMIT)
          string(STRIP "${BLINK_STANDALONE_PACKAGE_GIT_COMMIT}"
            BLINK_STANDALONE_PACKAGE_GIT_COMMIT)
        elseif(EXISTS "${_blink_standalone_git_actual_dir}/packed-refs")
          file(READ "${_blink_standalone_git_actual_dir}/packed-refs"
            _blink_standalone_git_packed_refs)
          if(_blink_standalone_git_packed_refs MATCHES
             "(^|\n)([0-9a-fA-F]{40})[ \t]+${_blink_standalone_git_ref_name}(\n|$)")
            set(BLINK_STANDALONE_PACKAGE_GIT_COMMIT "${CMAKE_MATCH_2}")
          endif()
        endif()
      elseif(_blink_standalone_git_head MATCHES "^[0-9a-fA-F]+$")
        set(BLINK_STANDALONE_PACKAGE_GIT_COMMIT
          "${_blink_standalone_git_head}")
      endif()
      if(NOT BLINK_STANDALONE_PACKAGE_GIT_COMMIT STREQUAL "unknown")
        string(SUBSTRING "${BLINK_STANDALONE_PACKAGE_GIT_COMMIT}" 0 12
          BLINK_STANDALONE_PACKAGE_GIT_COMMIT_SHORT)
      endif()
    endif()
  endif()
  set(BLINK_STANDALONE_RENDERER_C_API_PUBLIC_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/upstream/chromium/standalone_renderer/include/html_css_renderer/renderer_c_api.h
  )
  set(_blink_standalone_package_build_type "${CMAKE_BUILD_TYPE}")
  if(NOT _blink_standalone_package_build_type)
    set(_blink_standalone_package_build_type "$<CONFIG>")
  endif()
  set(_blink_standalone_package_name_base
    "blink-standalone-c-api-runtime-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}-${BLINK_STANDALONE_V8_TOOLCHAIN}-${BLINK_STANDALONE_PACKAGE_GIT_COMMIT_SHORT}"
  )
  string(TOLOWER "${_blink_standalone_package_name_base}"
    _blink_standalone_package_name_base)
  set(BLINK_STANDALONE_RENDERER_C_API_RUNTIME_ARCHIVE
    ${CMAKE_BINARY_DIR}/package/${_blink_standalone_package_name_base}.zip
  )
  set(_blink_standalone_dawn_d3d12_runtime_sidecars)
  set(_blink_standalone_dawn_d3d12_runtime_copy_commands)
  set(_blink_standalone_dawn_d3d12_runtime_sidecars_json)
  set(_blink_standalone_dawn_d3d12_runtime_sidecars_package_json)
  if(BLINK_STANDALONE_DAWN_D3D12 AND BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR)
    set(_blink_standalone_dawn_d3d12_sidecar_search_dirs)
    get_filename_component(
      _blink_standalone_dawn_d3d12_gen_dir
      "${BLINK_STANDALONE_DAWN_D3D12_GEN_INCLUDE_DIR}"
      DIRECTORY
    )
    get_filename_component(
      _blink_standalone_dawn_d3d12_build_dir
      "${_blink_standalone_dawn_d3d12_gen_dir}"
      DIRECTORY
    )
    list(APPEND _blink_standalone_dawn_d3d12_sidecar_search_dirs
      "${_blink_standalone_dawn_d3d12_build_dir}"
    )
    if(DEFINED ENV{SystemRoot})
      list(APPEND _blink_standalone_dawn_d3d12_sidecar_search_dirs
        "$ENV{SystemRoot}/System32"
      )
    endif()
    foreach(_blink_standalone_dawn_lib IN LISTS BLINK_STANDALONE_DAWN_D3D12_LIBS)
      get_filename_component(_blink_standalone_dawn_lib_dir
        "${_blink_standalone_dawn_lib}" DIRECTORY)
      set(_blink_standalone_dawn_candidate_dir
        "${_blink_standalone_dawn_lib_dir}")
      foreach(_blink_standalone_dawn_parent_step RANGE 0 5)
        list(APPEND _blink_standalone_dawn_d3d12_sidecar_search_dirs
          "${_blink_standalone_dawn_candidate_dir}")
        get_filename_component(_blink_standalone_dawn_candidate_dir
          "${_blink_standalone_dawn_candidate_dir}" DIRECTORY)
      endforeach()
    endforeach()
    list(REMOVE_DUPLICATES _blink_standalone_dawn_d3d12_sidecar_search_dirs)
    foreach(_blink_standalone_dawn_sidecar IN ITEMS
        d3dcompiler_47.dll
        dxcompiler.dll
        dxil.dll)
      set(_blink_standalone_dawn_sidecar_path)
      foreach(_blink_standalone_dawn_search_dir IN LISTS
          _blink_standalone_dawn_d3d12_sidecar_search_dirs)
        if(NOT _blink_standalone_dawn_sidecar_path AND
            EXISTS "${_blink_standalone_dawn_search_dir}/${_blink_standalone_dawn_sidecar}")
          set(_blink_standalone_dawn_sidecar_path
            "${_blink_standalone_dawn_search_dir}/${_blink_standalone_dawn_sidecar}"
          )
        endif()
      endforeach()
      if(NOT _blink_standalone_dawn_sidecar_path)
        if(_blink_standalone_dawn_sidecar STREQUAL "d3dcompiler_47.dll")
          message(FATAL_ERROR
            "BLINK_STANDALONE_DAWN_D3D12 is enabled, but "
            "d3dcompiler_47.dll was not found in the generated Dawn build "
            "tree or the Windows runtime. Rebuild the Dawn D3D12 inputs or "
            "install the Windows D3D compiler runtime before packaging the C "
            "API.")
        endif()
        continue()
      endif()
      list(APPEND _blink_standalone_dawn_d3d12_runtime_sidecars
        "${_blink_standalone_dawn_sidecar_path}"
      )
      list(APPEND _blink_standalone_dawn_d3d12_runtime_copy_commands
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${_blink_standalone_dawn_sidecar_path}"
          "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/${_blink_standalone_dawn_sidecar}"
      )
      file(TO_CMAKE_PATH "${_blink_standalone_dawn_sidecar_path}"
        _blink_standalone_dawn_sidecar_manifest_path)
      string(APPEND _blink_standalone_dawn_d3d12_runtime_sidecars_json
        ",\n    \"${_blink_standalone_dawn_sidecar_manifest_path}\""
      )
      string(APPEND _blink_standalone_dawn_d3d12_runtime_sidecars_package_json
        ",\n    \"${_blink_standalone_dawn_sidecar}\""
      )
    endforeach()
  endif()
  if(BLINK_STANDALONE_DAWN_D3D12)
    set(_blink_standalone_dawn_d3d12_enabled_json true)
  else()
    set(_blink_standalone_dawn_d3d12_enabled_json false)
  endif()
  set(_blink_standalone_renderer_c_api_link_manifest_content [=[
{
  "schema_version": 1,
  "package_schema_version": 1,
  "blink_commit": "@BLINK_STANDALONE_PACKAGE_GIT_COMMIT@",
  "package_layout_version": 1,
  "package_target": "blink_standalone_renderer_c_api_runtime_package",
  "package_archive_target": "blink_standalone_renderer_c_api_runtime_archive",
  "package_archive": "@BLINK_STANDALONE_RENDERER_C_API_RUNTIME_ARCHIVE@",
  "platform": {
    "os": "@CMAKE_SYSTEM_NAME@",
    "arch": "@CMAKE_SYSTEM_PROCESSOR@"
  },
  "build": {
    "build_type": "@_blink_standalone_package_build_type@",
    "compiler": "@CMAKE_CXX_COMPILER_ID@",
    "compiler_version": "@CMAKE_CXX_COMPILER_VERSION@",
    "toolchain": "@BLINK_STANDALONE_V8_TOOLCHAIN@",
    "profile": "@BLINK_STANDALONE_V8_TOOLCHAIN@-@CMAKE_CXX_COMPILER_ID@-@_blink_standalone_package_build_type@"
  },
  "link_mode": "dynamic",
  "link_kind": "shared_library",
  "d3d12_external_targets_enabled": @_blink_standalone_dawn_d3d12_enabled_json@,
  "public_header": {
    "package_relative": "include/html_css_renderer/renderer_c_api.h",
    "source": "@BLINK_STANDALONE_RENDERER_C_API_PUBLIC_HEADER@",
    "version": "unversioned-c-abi"
  },
  "artifacts": {
    "dll": "$<TARGET_FILE_NAME:blink_standalone_renderer_c_api_dll>",
    "import_library": "$<TARGET_LINKER_FILE_NAME:blink_standalone_renderer_c_api_dll>"
  },
  "recommended_target": "blink_standalone_renderer_c_api_dll",
  "recommended_artifact": "$<TARGET_FILE:blink_standalone_renderer_c_api_dll>",
  "recommended_import_library": "$<TARGET_LINKER_FILE:blink_standalone_renderer_c_api_dll>",
  "recommended_kind": "shared_library",
  "static_target": "blink_standalone_renderer_c_api",
  "static_archive": "$<TARGET_FILE:blink_standalone_renderer_c_api>",
  "static_link_complete_by_itself": false,
  "contract": "Godot and other external embedders should link the DLL import library, not the static archive. The supported public ABI is the blink_standalone_renderer_* C API. On Windows the DLL export table can also contain Chromium/V8 runtime-support exports such as GetHandleVerifier and CrashForExceptionInNonABICompliantCodeRange; those are sealed implementation details, not supported embedder API. The static archive is internal/advanced because Windows static libraries do not fold all transitive static dependencies and can conflict with the host runtime/STL.",
  "v8_monolith": "@BLINK_STANDALONE_V8_MONOLITH_LIB@",
  "chromium_libcxx_object_dir": "@BLINK_STANDALONE_CHROMIUM_LIBCXX_OBJECT_DIR@",
  "chromium_libcxx_object_list": "@_blink_standalone_libcxx_object_list@",
  "runtime_sidecars": [
    "$<TARGET_FILE:blink_angle_libEGL>",
    "$<TARGET_FILE:blink_angle_libGLESv2>",
    "@BLINK_STANDALONE_ICU_DATA_FILE@"@_blink_standalone_dawn_d3d12_runtime_sidecars_json@
  ],
  "runtime_sidecars_package_relative": [
    "$<TARGET_FILE_NAME:blink_angle_libEGL>",
    "$<TARGET_FILE_NAME:blink_angle_libGLESv2>",
    "icudtl.dat"@_blink_standalone_dawn_d3d12_runtime_sidecars_package_json@
  ],
  "package_files": [
    "$<TARGET_FILE_NAME:blink_standalone_renderer_c_api_dll>",
    "$<TARGET_LINKER_FILE_NAME:blink_standalone_renderer_c_api_dll>",
    "$<TARGET_FILE_NAME:blink_angle_libEGL>",
    "$<TARGET_FILE_NAME:blink_angle_libGLESv2>",
    "icudtl.dat",
    "blink_standalone_renderer_c_api_link_manifest.json",
    "include/html_css_renderer/renderer_c_api.h"@_blink_standalone_dawn_d3d12_runtime_sidecars_package_json@
  ],
  "third_party_targets": [
    "freetype",
    "harfbuzz",
    "LibXml2::LibXml2"
  ],
  "windows_system_libraries": [
    "d3d11",
    "dcomp",
    "dwmapi",
    "dxcore",
    "dxgi",
    "kernel32",
    "mincore",
    "ole32",
    "oleaut32",
    "propsys",
    "runtimeobject",
    "shell32",
    "shcore",
    "winmm",
    "windowscodecs",
    "wbemuuid",
    "advapi32",
    "dbghelp",
    "ntdll",
    "psapi",
    "setupapi",
    "shlwapi",
    "ws2_32",
    "delayimp"
  ],
  "runtime_package_target": "blink_standalone_renderer_c_api_runtime_package",
  "runtime_package_dir": "@BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR@"
}
]=])
  string(CONFIGURE
    "${_blink_standalone_renderer_c_api_link_manifest_content}"
    _blink_standalone_renderer_c_api_link_manifest_content
    @ONLY
  )
  file(GENERATE OUTPUT "${BLINK_STANDALONE_RENDERER_C_API_LINK_MANIFEST}"
    CONTENT "${_blink_standalone_renderer_c_api_link_manifest_content}")
  add_custom_target(blink_standalone_renderer_c_api_link_manifest
    DEPENDS blink_standalone_renderer_c_api_dll
    COMMAND ${CMAKE_COMMAND} -E echo
      "C API link manifest: ${BLINK_STANDALONE_RENDERER_C_API_LINK_MANIFEST}"
  )

  add_custom_target(blink_standalone_renderer_c_api_runtime_package
    DEPENDS
      blink_standalone_renderer_c_api_dll
      blink_standalone_renderer_c_api_link_manifest
      blink_angle_libEGL
      blink_angle_libGLESv2
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/include/html_css_renderer"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_standalone_renderer_c_api_dll>"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/$<TARGET_FILE_NAME:blink_standalone_renderer_c_api_dll>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_LINKER_FILE:blink_standalone_renderer_c_api_dll>"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/$<TARGET_LINKER_FILE_NAME:blink_standalone_renderer_c_api_dll>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_angle_libEGL>"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/$<TARGET_FILE_NAME:blink_angle_libEGL>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_angle_libGLESv2>"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/$<TARGET_FILE_NAME:blink_angle_libGLESv2>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_ICU_DATA_FILE}"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/icudtl.dat"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_RENDERER_C_API_LINK_MANIFEST}"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/blink_standalone_renderer_c_api_link_manifest.json"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_RENDERER_C_API_PUBLIC_HEADER}"
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}/include/html_css_renderer/renderer_c_api.h"
    ${_blink_standalone_dawn_d3d12_runtime_copy_commands}
    COMMAND ${CMAKE_COMMAND} -E echo
      "C API runtime package: ${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}"
  )
  add_custom_target(blink_standalone_renderer_c_api_runtime_archive
    DEPENDS blink_standalone_renderer_c_api_runtime_package
    COMMAND ${CMAKE_COMMAND} -E rm -f
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_ARCHIVE}"
    COMMAND ${CMAKE_COMMAND} -E tar cf
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_ARCHIVE}"
      --format=zip
      .
    WORKING_DIRECTORY
      "${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_PACKAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo
      "C API runtime archive: ${BLINK_STANDALONE_RENDERER_C_API_RUNTIME_ARCHIVE}"
  )

  set(BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR
    ${CMAKE_BINARY_DIR}/package/c_api_static
    CACHE PATH
    "Output directory for the embeddable static C API package."
  )
  set(_blink_standalone_static_package_name_base
    "blink-standalone-c-api-static-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}-${BLINK_STANDALONE_V8_TOOLCHAIN}-${BLINK_STANDALONE_PACKAGE_GIT_COMMIT_SHORT}"
  )
  string(TOLOWER "${_blink_standalone_static_package_name_base}"
    _blink_standalone_static_package_name_base)
  set(BLINK_STANDALONE_RENDERER_C_API_STATIC_ARCHIVE_PACKAGE
    ${CMAKE_BINARY_DIR}/package/${_blink_standalone_static_package_name_base}.zip
  )
  set(BLINK_STANDALONE_RENDERER_C_API_STATIC_LINK_MANIFEST
    ${CMAKE_BINARY_DIR}/blink_standalone_renderer_c_api_static_link_manifest.json
  )

  set(_blink_standalone_static_dawn_libs_json)
  set(_blink_standalone_static_dawn_copy_commands)
  set(_blink_standalone_static_libcxx_libs_json)
  set(_blink_standalone_static_libcxx_copy_commands)
  if(WIN32 AND TARGET blink_standalone_chromium_libcxx_static)
    string(APPEND _blink_standalone_static_libcxx_libs_json
      ",\n    \"lib/$<TARGET_FILE_NAME:blink_standalone_chromium_libcxx_static>\""
    )
    list(APPEND _blink_standalone_static_libcxx_copy_commands
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:blink_standalone_chromium_libcxx_static>"
        "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:blink_standalone_chromium_libcxx_static>"
    )
  endif()
  foreach(_blink_standalone_dawn_lib IN LISTS BLINK_STANDALONE_DAWN_D3D12_LIBS)
    get_filename_component(_blink_standalone_dawn_lib_name
      "${_blink_standalone_dawn_lib}" NAME)
    list(APPEND _blink_standalone_static_dawn_copy_commands
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${_blink_standalone_dawn_lib}"
        "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/dawn/${_blink_standalone_dawn_lib_name}"
    )
    string(APPEND _blink_standalone_static_dawn_libs_json
      ",\n    \"lib/dawn/${_blink_standalone_dawn_lib_name}\""
    )
  endforeach()

  set(_blink_standalone_static_product_supported false)
  set(_blink_standalone_static_full_host_supported false)
  set(_blink_standalone_static_full_host_blocker_json
    "\"monolithic_renderer_archive_exports_chromium_third_party_symbols\"")
  set(_blink_standalone_static_symbol_collision_risk "\"known\"")
  set(_blink_standalone_static_symbol_product_supported false)
  set(_blink_standalone_static_duplicate_prone_families_json
    "\"abseil_template_instantiations\",\n      \"chromium_libcxx\"")
  set(_blink_standalone_static_required_resolution
    "actual Godot editor/static-template link proof or private/prefixed ownership for remaining Abseil template instantiations and Chromium libc++ symbols before full host/editor static linking is product-supported")
  set(_blink_standalone_static_status "raw_output_link_proof_passed")
  set(_blink_standalone_static_manifest_notes
    "The synthetic host collision probe covers prior libpng, ICU, and VMA Godot collision families, but this package still needs a real host/editor link proof before product support can be claimed.")
  set(_blink_standalone_static_known_hazards_json
    "\"This static package is validated by isolated external probes first; full Godot editor/export static linking can still expose duplicate host/Blink third-party symbols until dependency ownership or symbol isolation is solved.\",\n    \"The renderer static archive currently contains globally named Chromium/Skia/V8-adjacent third-party objects. The synthetic host collision probe covers prior libpng, ICU, and VMA Godot collision families, but full host binaries that already link Abseil or Chromium libc++-style symbols can still fail with LNK2005/LNK1169.\"")
  if(WIN32 AND
      CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND
      BLINK_STANDALONE_V8_TOOLCHAIN STREQUAL "msvc" AND
      NOT BLINK_STANDALONE_USE_CHROMIUM_LIBCXX)
    set(_blink_standalone_static_product_supported true)
    set(_blink_standalone_static_full_host_supported true)
    set(_blink_standalone_static_full_host_blocker_json null)
    set(_blink_standalone_static_symbol_collision_risk "\"validated_native_msvc_host_link\"")
    set(_blink_standalone_static_symbol_product_supported true)
    set(_blink_standalone_static_duplicate_prone_families_json "")
    set(_blink_standalone_static_required_resolution
      "Native MSVC/MSVC-STL package validated by static probes plus Godot editor diagnostic static link without forbidden code DLL imports.")
    set(_blink_standalone_static_status "godot_host_static_link_proof_passed")
    set(_blink_standalone_static_manifest_notes
      "Native MSVC/MSVC-STL package validated by static raw-output, D3D12/Vulkan external-target, host-collision probes, and a Godot editor diagnostic static link. Consumers must still match CRT family, architecture, configuration, and iterator debug level.")
    set(_blink_standalone_static_known_hazards_json
      "\"Native MSVC/MSVC-STL static host linking is validated for Godot with matching /MT CRT, architecture, configuration, and iterator debug level. Rebuild this package if the host switches CRT family or configuration.\",\n    \"ChromiumLLVM/libc++ static packages remain unsupported for Godot/MSVC-STL host linking; this support claim applies only to the native MSVC/MSVC-STL package.\"")
  endif()

  set(_blink_standalone_static_package_manifest_content [=[
{
  "schema_version": 1,
  "package_schema_version": 1,
  "blink_commit": "@BLINK_STANDALONE_PACKAGE_GIT_COMMIT@",
  "package_layout_version": 1,
  "package_target": "blink_standalone_renderer_c_api_static_package",
  "package_archive_target": "blink_standalone_renderer_c_api_static_archive",
  "package_archive": "@BLINK_STANDALONE_RENDERER_C_API_STATIC_ARCHIVE_PACKAGE@",
  "platform": {
    "os": "@CMAKE_SYSTEM_NAME@",
    "arch": "@CMAKE_SYSTEM_PROCESSOR@"
  },
  "build": {
    "build_type": "@_blink_standalone_package_build_type@",
    "compiler": "@CMAKE_CXX_COMPILER_ID@",
    "compiler_version": "@CMAKE_CXX_COMPILER_VERSION@",
    "toolchain": "@BLINK_STANDALONE_V8_TOOLCHAIN@",
    "profile": "@BLINK_STANDALONE_V8_TOOLCHAIN@-@CMAKE_CXX_COMPILER_ID@-@_blink_standalone_package_build_type@"
  },
  "link_mode": "static",
  "link_kind": "static_library",
  "package_kind": "static_c_api_no_blink_angle_code_sidecars",
  "static_link_complete_by_itself": false,
  "full_host_static_link_supported": @_blink_standalone_static_full_host_supported@,
  "full_host_static_link_blocker": @_blink_standalone_static_full_host_blocker_json@,
  "product_supported": @_blink_standalone_static_product_supported@,
  "symbol_ownership": {
    "model": "blink_bundled_third_party_symbols_are_public_in_static_archive_with_incremental_private_prefixing",
    "collision_risk": @_blink_standalone_static_symbol_collision_risk@,
    "product_supported": @_blink_standalone_static_symbol_product_supported@,
    "private_prefixed_families": [
      "libpng",
      "icu",
      "vulkan_memory_allocator"
    ],
    "host_collision_probe": {
      "target": "blink_static_host_collision_smoke",
      "covered_families": [
        "libpng",
        "icu",
        "vulkan_memory_allocator"
      ],
      "scope": "synthetic host definitions for the symbol families that previously blocked Godot editor static linking; this does not prove arbitrary Abseil or Chromium libc++ coexistence"
    },
    "duplicate_prone_families": [
      @_blink_standalone_static_duplicate_prone_families_json@
    ],
    "required_resolution": "@_blink_standalone_static_required_resolution@"
  },
  "status": "@_blink_standalone_static_status@",
  "crt": {
    "msvc_runtime_library": "MultiThreaded",
    "required_consumer_match": true,
    "notes": "Consumers must use the same CRT family, architecture, configuration, and iterator debug level as this package. Rebuild the package if the host uses /MD instead of /MT."
  },
  "public_header": {
    "package_relative": "include/html_css_renderer/renderer_c_api.h",
    "source": "@BLINK_STANDALONE_RENDERER_C_API_PUBLIC_HEADER@",
    "version": "unversioned-c-abi"
  },
  "artifacts": {
    "static_archive": "lib/$<TARGET_FILE_NAME:blink_standalone_renderer_c_api>"
  },
  "consumer_compile_definitions": [
    "BLINK_STANDALONE_RENDERER_C_API_STATIC=1"
  ],
  "required_static_archives": [
    "lib/$<TARGET_FILE_NAME:blink_standalone_renderer_c_api>",
    "lib/@_blink_standalone_packaged_v8_monolith_name@"
  ],
  "required_import_libraries": [],
  "third_party_static_archives": [
    "lib/$<TARGET_FILE_NAME:blink_angle_libEGL_static>",
    "lib/$<TARGET_FILE_NAME:blink_angle_libGLESv2_static>",
    "lib/$<TARGET_FILE_NAME:blink_standalone_abseil_static>",
    "lib/$<TARGET_FILE_NAME:freetype>",
    "lib/$<TARGET_FILE_NAME:harfbuzz>",
    "lib/$<TARGET_FILE_NAME:LibXml2::LibXml2>"@_blink_standalone_static_libcxx_libs_json@@_blink_standalone_static_dawn_libs_json@
  ],
  "whole_archive_candidates_msvc": [
    "lib/$<TARGET_FILE_NAME:blink_standalone_renderer_c_api>"
  ],
  "runtime_code_sidecars": [],
  "remaining_runtime_sidecars": [
    "bin/icudtl.dat"
  ],
  "windows_system_libraries": [
    "d3d11.lib",
    "d3d12.lib",
    "dcomp.lib",
    "dwmapi.lib",
    "dxcore.lib",
    "dxgi.lib",
    "kernel32.lib",
    "mincore.lib",
    "ole32.lib",
    "oleaut32.lib",
    "propsys.lib",
    "runtimeobject.lib",
    "shell32.lib",
    "shcore.lib",
    "user32.lib",
    "winmm.lib",
    "windowscodecs.lib",
    "wbemuuid.lib",
    "advapi32.lib",
    "dbghelp.lib",
    "ntdll.lib",
    "psapi.lib",
    "setupapi.lib",
    "shlwapi.lib",
    "ws2_32.lib",
    "delayimp.lib"
  ],
  "known_hazards": [
    @_blink_standalone_static_known_hazards_json@,
    "The static C API archive must be whole-archived on MSVC, but the V8 monolith archive must not be whole-archived.",
    "Static mode must not ship Blink or ANGLE code shared-library sidecars; libEGL/libGLESv2 are packaged as static archives.",
    "icudtl.dat remains a required runtime data sidecar."
  ],
  "package_files": [
    "blink_standalone_renderer_c_api_static_link_manifest.json",
    "include/html_css_renderer/renderer_c_api.h",
    "include/vk_video",
    "include/vulkan",
    "lib/$<TARGET_FILE_NAME:blink_standalone_renderer_c_api>",
    "lib/@_blink_standalone_packaged_v8_monolith_name@",
    "lib/$<TARGET_FILE_NAME:blink_angle_libEGL_static>",
    "lib/$<TARGET_FILE_NAME:blink_angle_libGLESv2_static>",
    "lib/$<TARGET_FILE_NAME:blink_standalone_abseil_static>",
    "lib/$<TARGET_FILE_NAME:freetype>",
    "lib/$<TARGET_FILE_NAME:harfbuzz>",
    "lib/$<TARGET_FILE_NAME:LibXml2::LibXml2>"@_blink_standalone_static_libcxx_libs_json@@_blink_standalone_static_dawn_libs_json@,
    "bin/icudtl.dat"
  ]
}
]=])
  string(CONFIGURE
    "${_blink_standalone_static_package_manifest_content}"
    _blink_standalone_static_package_manifest_content
    @ONLY
  )
  file(GENERATE
    OUTPUT "${BLINK_STANDALONE_RENDERER_C_API_STATIC_LINK_MANIFEST}"
    CONTENT "${_blink_standalone_static_package_manifest_content}"
  )

  add_custom_target(blink_standalone_renderer_c_api_static_link_manifest
    DEPENDS blink_standalone_renderer_c_api
    COMMAND ${CMAKE_COMMAND} -E echo
      "C API static link manifest: ${BLINK_STANDALONE_RENDERER_C_API_STATIC_LINK_MANIFEST}"
  )
  add_custom_target(blink_standalone_renderer_c_api_static_package
    DEPENDS
      blink_standalone_renderer_c_api
      blink_standalone_renderer_c_api_static_link_manifest
      blink_angle_libEGL_static
      blink_angle_libGLESv2_static
      blink_standalone_abseil_static
      freetype
      harfbuzz
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/bin"
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/include/html_css_renderer"
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/include/vk_video"
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/include/vulkan"
    COMMAND ${CMAKE_COMMAND} -E make_directory
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/dawn"
    COMMAND ${CMAKE_COMMAND} -E rm -f
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/bin/$<TARGET_FILE_NAME:blink_angle_libEGL>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/bin/$<TARGET_FILE_NAME:blink_angle_libGLESv2>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_LINKER_FILE_NAME:blink_angle_libEGL>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_LINKER_FILE_NAME:blink_angle_libGLESv2>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_LINK_MANIFEST}"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/blink_standalone_renderer_c_api_static_link_manifest.json"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_RENDERER_C_API_PUBLIC_HEADER}"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/include/html_css_renderer/renderer_c_api.h"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan-headers/src/include/vk_video"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/include/vk_video"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan-headers/src/include/vulkan"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/include/vulkan"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_standalone_renderer_c_api>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:blink_standalone_renderer_c_api>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_V8_MONOLITH_LIB}"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/${_blink_standalone_packaged_v8_monolith_name}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_angle_libEGL_static>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:blink_angle_libEGL_static>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_angle_libGLESv2_static>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:blink_angle_libGLESv2_static>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:blink_standalone_abseil_static>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:blink_standalone_abseil_static>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:freetype>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:freetype>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:harfbuzz>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:harfbuzz>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:LibXml2::LibXml2>"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/lib/$<TARGET_FILE_NAME:LibXml2::LibXml2>"
    ${_blink_standalone_static_libcxx_copy_commands}
    ${_blink_standalone_static_dawn_copy_commands}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${BLINK_STANDALONE_ICU_DATA_FILE}"
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}/bin/icudtl.dat"
    ${_blink_standalone_dawn_d3d12_runtime_copy_commands}
    COMMAND ${CMAKE_COMMAND}
      -DPACKAGE_DIR="${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/verify_static_package_no_code_sidecars.cmake"
    COMMAND ${CMAKE_COMMAND} -E echo
      "C API static package: ${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}"
  )
  if(TARGET blink_standalone_chromium_libcxx_static)
    add_dependencies(blink_standalone_renderer_c_api_static_package
      blink_standalone_chromium_libcxx_static)
  endif()
  add_custom_target(blink_standalone_renderer_c_api_static_archive
    DEPENDS blink_standalone_renderer_c_api_static_package
    COMMAND ${CMAKE_COMMAND} -E rm -f
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_ARCHIVE_PACKAGE}"
    COMMAND ${CMAKE_COMMAND} -E tar cf
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_ARCHIVE_PACKAGE}"
      --format=zip
      .
    WORKING_DIRECTORY
      "${BLINK_STANDALONE_RENDERER_C_API_STATIC_PACKAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo
      "C API static archive: ${BLINK_STANDALONE_RENDERER_C_API_STATIC_ARCHIVE_PACKAGE}"
  )
  if(BLINK_STANDALONE_BUILD_SDL_VIEWER AND BLINK_STANDALONE_SDL3_TARGET)
    add_executable(blink_standalone_sdl_viewer_skia
      ${BLINK_STANDALONE_SDL_APP_SOURCES}
    )
    add_dependencies(blink_standalone_sdl_viewer_skia
      blink_angle_libEGL_static
      blink_angle_libGLESv2_static
      blink_standalone_renderer_c_api
    )
    blink_standalone_add_v8_compat_dependency(blink_standalone_sdl_viewer_skia)
    if(BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
      target_include_directories(blink_standalone_sdl_viewer_skia BEFORE PRIVATE
        ${BLINK_STANDALONE_RELEASE_LEVEL_BUILDFLAGS_DIR}
      )
    endif()

    target_include_directories(blink_standalone_sdl_viewer_skia BEFORE PRIVATE
      ${BLINK_STANDALONE_STL_INCLUDE_DIRS}
      ${BLINK_STANDALONE_V8_INCLUDE_DIR}
      ${BLINK_STANDALONE_V8_GENERATED_SOURCE_ROOT}
      ${BLINK_STANDALONE_V8_ABSEIL_INCLUDE_DIR}
    )
    target_include_directories(blink_standalone_sdl_viewer_skia PRIVATE
      ${BLINK_STANDALONE_CHROMIUM_ROOT}
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/base
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/third_party/xxhash
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/dawn/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/ipcz/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/khronos
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan-headers/src/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan_memory_allocator/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/flatbuffers/src/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/angle
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/v8/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/overrides
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src/quiche/common/platform/default
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/allocator/partition_allocator/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/build_config
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/harfbuzz/src/src
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/highway/src
      ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/common
      ${BLINK_STANDALONE_ICU_SOURCE_ROOT}/source/i18n
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libwebm/source
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/src/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/win32/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/include/third_party/vulkan
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/libpng
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/v8/include
      ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
      ${BLINK_STANDALONE_FREETYPE_SOURCE}/include
      ${BLINK_STANDALONE_PLATFORM_INCLUDE_DIRECTORIES}
    )

    target_compile_definitions(blink_standalone_sdl_viewer_skia PRIVATE
      BLINK_CORE_IMPLEMENTATION=1
      BLINK_IMPLEMENTATION=1
      INSIDE_BLINK=1
      STANDALONE_RENDERER_GN_PROBE=1
      STANDALONE_RENDERER_NO_RUST=1
      HTML_CSS_RENDERER_STANDALONE=1
      HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT=1
      HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL=1
      HTML_CSS_RENDERER_HAS_REDUCED_BLINK_PLATFORM=1
      HTML_CSS_RENDERER_USE_CHROMIUM_COMPOSITOR=1
      HTML_CSS_RENDERER_ENABLE_WEBGPU=0
      SK_GANESH=1
      SK_VULKAN=1
      SK_GPU_WORKAROUNDS_HEADER=\"gpu/config/gpu_driver_bug_workaround_autogen.h\"
      SK_USE_INTERNAL_VULKAN_HEADERS=1
      WTF_IMPLEMENTATION=1
      USE_AURA=1
      U_STATIC_IMPLEMENTATION
      U_I18N_IMPLEMENTATION
      U_COMMON_IMPLEMENTATION
      ICU_UTIL_DATA_IMPL=ICU_UTIL_DATA_FILE
      ${BLINK_STANDALONE_PRIVATE_ICU_DEFINES}
      PNG_SET_OPTION_SUPPORTED=1
      PNG_WRITE_SUPPORTED=1
      PNG_WRITE_CUSTOMIZE_COMPRESSION_SUPPORTED=1
      PNG_INTEL_SSE=1
      ZLIB_IMPLEMENTATION=1
      SDL_STATIC_LIB=1
      BLINK_STANDALONE_RENDERER_C_API_STATIC=1
      KHRONOS_STATIC=1
      ${BLINK_STANDALONE_PLATFORM_COMPILE_DEFINITIONS}
      ${BLINK_STANDALONE_STL_DEFINES}
      ${BLINK_STANDALONE_V8_ABI_DEFINES}
    )
    set_property(TARGET blink_standalone_sdl_viewer_skia PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded")

    if(NOT BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
      target_compile_definitions(blink_standalone_sdl_viewer_skia PRIVATE
        DCHECK_ALWAYS_ON=1
      )
    endif()

    if(NOT BLINK_STANDALONE_PERF_BUILD AND NOT BLINK_STANDALONE_RELEASE_LEVEL_VIEWER)
      target_compile_definitions(blink_standalone_sdl_viewer_skia PRIVATE
        SKCMS_DISABLE_HSW=1
        SKCMS_DISABLE_SKX=1
        SK_ENABLE_OPTIMIZE_SIZE=1
        CPU_NO_SIMD=1
      )
    endif()
    if(BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS)
      target_compile_options(blink_standalone_sdl_viewer_skia PRIVATE
        ${BLINK_STANDALONE_PLATFORM_COMPILE_OPTIONS})
    endif()
    if(BLINK_STANDALONE_PLATFORM_LINK_OPTIONS)
      target_link_options(blink_standalone_sdl_viewer_skia PRIVATE
        ${BLINK_STANDALONE_PLATFORM_LINK_OPTIONS})
    endif()

    target_link_libraries(blink_standalone_sdl_viewer_skia PRIVATE
      blink_standalone_renderer_c_api
      blink_angle_libEGL_static
      blink_angle_libGLESv2_static
      blink_standalone_chromium_libcxx
      blink_standalone_v8_monolith
      ${BLINK_STANDALONE_PLATFORM_LINK_LIBS}
    )

    if(MSVC)
      target_compile_options(blink_standalone_sdl_viewer_skia PRIVATE
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

    target_link_libraries(blink_standalone_sdl_viewer_skia PRIVATE
      freetype
      harfbuzz
      LibXml2::LibXml2
      ${BLINK_STANDALONE_SDL3_TARGET}
      ${BLINK_STANDALONE_SDL_PLATFORM_LINK_LIBS}
    )
    blink_standalone_copy_icu_data(blink_standalone_sdl_viewer_skia)
  endif()
