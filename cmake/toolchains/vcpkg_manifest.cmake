set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING
  "vcpkg triplet for blink-standalone-ui dependencies")
get_filename_component(_blink_standalone_repo_root
  "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(VCPKG_MANIFEST_DIR "${_blink_standalone_repo_root}" CACHE PATH
  "Repository root containing vcpkg.json")
set(VCPKG_MANIFEST_MODE ON CACHE BOOL
  "Install dependencies from the repository vcpkg.json manifest")

if(DEFINED ENV{VCPKG_ROOT} AND
   EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
  set(_blink_standalone_vcpkg_toolchain
    "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
elseif(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(_blink_standalone_vcpkg_toolchain
    "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
  message(FATAL_ERROR
    "vcpkg is required for libxml2/Iconv/ZLIB. Set VCPKG_ROOT to a vcpkg checkout "
    "or install vcpkg at C:/vcpkg, then reconfigure.")
endif()

include("${_blink_standalone_vcpkg_toolchain}")
