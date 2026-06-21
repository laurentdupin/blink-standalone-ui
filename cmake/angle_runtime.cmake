set(BLINK_STANDALONE_ANGLE_ROOT
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle)
set(BLINK_STANDALONE_ANGLE_SRC
  ${BLINK_STANDALONE_ANGLE_ROOT}/src)

set(BLINK_STANDALONE_ANGLE_ZLIB_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/adler32.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/compress.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/cpu_features.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/crc32.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/crc_folding.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/deflate.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/infback.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inffast.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inflate.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/inftrees.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/trees.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/uncompr.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/zutil.c
)
set_source_files_properties(${BLINK_STANDALONE_ANGLE_ZLIB_SOURCES}
  PROPERTIES LANGUAGE CXX)

set_source_files_properties(
  ${BLINK_STANDALONE_ANGLE_SRC}/third_party/volk/volk.c
  PROPERTIES LANGUAGE CXX)

set(BLINK_STANDALONE_ANGLE_COMMON_RUNTIME_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/common/CompiledShaderState.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/Float16ToFloat32.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/MemoryBuffer.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/PackedEGLEnums_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/PackedEnums.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/PackedGLEnums_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/PoolAlloc.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/SimpleMutex.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/WorkerThread.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/aligned_memory.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/android_util.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/angle_version_info.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/angleutils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/backtrace_utils_noop.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/base/anglebase/sha1.cc
  ${BLINK_STANDALONE_ANGLE_SRC}/common/debug.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/entry_points_enum_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/event_tracer.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/gl_enum_utils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/gl_enum_utils_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/mathutil.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/matrix_utils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/platform_helpers.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/string_utils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/system_utils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/system_utils_win.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/system_utils_win32.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/tls.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/uniform_type_info_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/utilities.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/third_party/xxhash/xxhash.c
  ${BLINK_STANDALONE_ANGLE_SRC}/common/vulkan/libvulkan_loader.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/vulkan/vulkan_icd.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/third_party/volk/volk.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/angle_vma_implementation.cc
  ${BLINK_STANDALONE_ANGLE_ZLIB_SOURCES}
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/google/compression_utils_portable.cc
)

set(BLINK_STANDALONE_ANGLE_IMAGE_RUNTIME_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/AstcDecompressorNoOp.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/copyimage.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/imageformats.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/loadimage.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/loadimage_astc.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/loadimage_etc.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/loadimage_paletted.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/image_util/storeimage_paletted.cpp
)

set(BLINK_STANDALONE_ANGLE_GPU_INFO_RUNTIME_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/gpu_info_util/SystemInfo.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/gpu_info_util/SystemInfo_win.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/gpu_info_util/SystemInfo_vulkan.cpp
)

file(GLOB BLINK_STANDALONE_ANGLE_LIBANGLE_TOP_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/*.cpp)
list(FILTER BLINK_STANDALONE_ANGLE_LIBANGLE_TOP_SOURCES EXCLUDE REGEX "_unittest\\.cpp$")
list(FILTER BLINK_STANDALONE_ANGLE_LIBANGLE_TOP_SOURCES EXCLUDE REGEX "/CL[^/]*\\.cpp$")
list(FILTER BLINK_STANDALONE_ANGLE_LIBANGLE_TOP_SOURCES EXCLUDE REGEX "/cl_utils\\.cpp$")
list(FILTER BLINK_STANDALONE_ANGLE_LIBANGLE_TOP_SOURCES EXCLUDE REGEX "/validationCL\\.cpp$")

set(BLINK_STANDALONE_ANGLE_RENDERER_CORE_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/BufferImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/ContextImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/DeviceImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/DisplayImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/EGLReusableSync.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/EGLSyncImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/Format_table_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/FramebufferImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/ImageImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/ProgramImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/ProgramPipelineImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/QueryImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/RenderbufferImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/ShaderImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/SurfaceImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/TextureImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/TransformFeedbackImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/VertexArrayImpl.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/driver_utils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/load_functions_table_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/renderer_utils.cpp
)

set(BLINK_STANDALONE_ANGLE_CAPTURE_MOCK_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/capture/FrameCapture_mock.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/capture/serialize_mock.cpp
)

file(GLOB BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/vulkan/*.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/vulkan/win32/*.cpp)
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/CL[^/]*\\.cpp$")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/clspv_utils\\.cpp$")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/vk_cl_utils\\.cpp$")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/android/")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/linux/")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/mac/")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/fuchsia/")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "/null/")
list(FILTER BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES EXCLUDE REGEX "_unittest\\.cpp$")
list(APPEND BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/libANGLE/renderer/vulkan/android/vk_android_utils.cpp)

set(BLINK_STANDALONE_ANGLE_SPIRV_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/common/spirv/spirv_instruction_builder_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/spirv/spirv_instruction_parser_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/spirv/BuildSPIRV.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/spirv/BuiltinsWorkaround.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/spirv/OutputSPIRV.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/spirv/TranslatorSPIRV.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/ClampGLLayer.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/EmulateAdvancedBlendEquations.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/EmulateFragColorData.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/EmulateFramebufferFetch.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/EmulateYUVBuiltIns.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/FlagSamplersWithTexelFetch.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/ReswizzleYUVOps.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/RewriteInterpolateAtOffset.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/RewriteR32fImages.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/compiler/translator/tree_ops/spirv/RewriteSamplerExternalTexelFetch.cpp
)

set(BLINK_STANDALONE_ANGLE_LIBGLESV2_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/egl_ext_stubs.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/egl_stubs.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/egl_stubs_getprocaddress_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_egl_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_egl_ext_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_gles_1_0_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_gles_2_0_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_gles_3_0_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_gles_3_1_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_gles_3_2_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/entry_points_gles_ext_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/global_state.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/libGLESv2_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libGLESv2/libGLESv2_autogen.def
)

set(BLINK_STANDALONE_ANGLE_LIBEGL_SOURCES
  ${BLINK_STANDALONE_ANGLE_SRC}/common/system_utils.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/system_utils_win.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/common/system_utils_win32.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libEGL/egl_loader_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libEGL/libEGL_autogen.cpp
  ${BLINK_STANDALONE_ANGLE_SRC}/libEGL/libEGL_autogen.def
)

set(BLINK_STANDALONE_ANGLE_RUNTIME_SOURCES
  ${BLINK_STANDALONE_ANGLE_COMMON_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_ANGLE_IMAGE_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_ANGLE_GPU_INFO_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_ANGLE_LIBANGLE_TOP_SOURCES}
  ${BLINK_STANDALONE_ANGLE_RENDERER_CORE_SOURCES}
  ${BLINK_STANDALONE_ANGLE_CAPTURE_MOCK_SOURCES}
  ${BLINK_STANDALONE_ANGLE_VULKAN_BACKEND_SOURCES}
  ${BLINK_STANDALONE_ANGLE_SPIRV_SOURCES}
  ${BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES}
)
list(REMOVE_DUPLICATES BLINK_STANDALONE_ANGLE_RUNTIME_SOURCES)

function(blink_standalone_configure_angle_target target_name)
  target_include_directories(${target_name} PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
    ${BLINK_STANDALONE_ANGLE_ROOT}/include
    ${BLINK_STANDALONE_ANGLE_SRC}
    ${BLINK_STANDALONE_ANGLE_SRC}/common/base
    ${BLINK_STANDALONE_ANGLE_SRC}/common/third_party/xxhash
    ${BLINK_STANDALONE_ANGLE_SRC}/third_party/volk
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/angle
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan-headers/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/vulkan_memory_allocator/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/spirv-headers/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/spirv-tools/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/zlib/google
  )
  target_compile_definitions(${target_name} PRIVATE
    ANGLE_ENABLE_CONTEXT_MUTEX=1
    ANGLE_ENABLE_CRC_FOR_PIPELINE_CACHE=1
    ANGLE_ENABLE_ESSL=1
    ANGLE_ENABLE_GLSL=1
    ANGLE_ENABLE_VULKAN=1
    ANGLE_IS_WIN=1
    ANGLE_OUTSIDE_WEBKIT=1
    ANGLE_PLATFORM_WINDOWS=1
    ANGLE_SHARED_LIBVULKAN=1
    ANGLE_USE_CUSTOM_VULKAN_OUTSIDE_RENDER_PASS_CMD_BUFFERS=1
    ANGLE_USE_CUSTOM_VULKAN_RENDER_PASS_CMD_BUFFERS=1
    ANGLE_WINDOWS_NO_FUTEX=1
    EGL_EGL_PROTOTYPES=1
    EGL_EGLEXT_PROTOTYPES=1
    GL_GLES_PROTOTYPES=1
    GL_GLEXT_PROTOTYPES=1
    VK_USE_PLATFORM_WIN32_KHR=1
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_DEPRECATE
    _WINSOCK_DEPRECATED_NO_WARNINGS
    ANGLE_CAPTURE_ENABLED=0
    ANGLE_EGL_LIBRARY_NAME="libEGL"
    ANGLE_GLESV2_LIBRARY_NAME="libGLESv2"
    ANGLE_MESA_EGL_LIBRARY_NAME="mesa/src/egl/libEGL"
    ANGLE_MESA_GLESV2_LIBRARY_NAME="mesa/src/mapi/es2api/libGLESv2"
    ANGLE_VULKAN_SECONDARIES_EGL_LIBRARY_NAME="libEGL_vulkan_secondaries"
    ANGLE_VULKAN_SECONDARIES_GLESV2_LIBRARY_NAME="libGLESv2_vulkan_secondaries"
    ANGLE_VK_MOCK_ICD_JSON="VkICD_mock_icd.json"
    CPU_NO_SIMD=1
    NDEBUG=1
    ZLIB_IMPLEMENTATION=1
  )
  set_property(TARGET ${target_name} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")
  if(MSVC)
    target_compile_options(${target_name} PRIVATE
      /MP8
      /bigobj
      /permissive-
      /Zc:__cplusplus
      /wd4005
      /wd4068
      /wd4100
      /wd4127
      /wd4201
      /wd4251
      /wd4267
      /wd4275
      /wd4324
      /wd4458
      /wd4800
      /wd4996
    )
  endif()
  target_link_libraries(${target_name} PRIVATE
    advapi32
    d3d11
    dxgi
    dxguid
    gdi32
    kernel32
    ole32
    setupapi
    user32
    version
    winmm
    ZLIB::ZLIB
  )
  set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
endfunction()

add_library(blink_angle_libGLESv2 SHARED
  ${BLINK_STANDALONE_ANGLE_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_ANGLE_LIBGLESV2_SOURCES}
)
set_target_properties(blink_angle_libGLESv2 PROPERTIES
  OUTPUT_NAME "libGLESv2")
blink_standalone_configure_angle_target(blink_angle_libGLESv2)
target_compile_definitions(blink_angle_libGLESv2 PRIVATE
  LIBANGLE_IMPLEMENTATION=1
  LIBGLESV2_IMPLEMENTATION=1
)

add_library(blink_angle_libEGL SHARED
  ${BLINK_STANDALONE_ANGLE_LIBEGL_SOURCES}
)
set_target_properties(blink_angle_libEGL PROPERTIES
  OUTPUT_NAME "libEGL")
blink_standalone_configure_angle_target(blink_angle_libEGL)
target_compile_definitions(blink_angle_libEGL PRIVATE
  ANGLE_DISPATCH_LIBRARY="libGLESv2"
  ANGLE_USE_EGL_LOADER=1
  EGLAPI=
  LIBEGL_IMPLEMENTATION=1
)
add_dependencies(blink_angle_libEGL blink_angle_libGLESv2)
