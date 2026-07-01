set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING
  "vcpkg triplet for blink-standalone-ui dependencies")
get_filename_component(_blink_standalone_repo_root
  "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(VCPKG_MANIFEST_DIR "${_blink_standalone_repo_root}" CACHE PATH
  "Repository root containing vcpkg.json")
set(VCPKG_MANIFEST_MODE ON CACHE BOOL
  "Install dependencies from the repository vcpkg.json manifest")

set(BLINK_STANDALONE_VCPKG_STATE_ROOT
  "${_blink_standalone_repo_root}/build/vcpkg"
  CACHE PATH
  "Repository-local root for vcpkg mutable install/build/cache state.")
set(VCPKG_INSTALLED_DIR
  "${BLINK_STANDALONE_VCPKG_STATE_ROOT}/installed"
  CACHE PATH
  "Repository-local vcpkg installed package root."
  FORCE)
set(_blink_standalone_vcpkg_downloads
  "${BLINK_STANDALONE_VCPKG_STATE_ROOT}/downloads")
set(_blink_standalone_vcpkg_binary_cache
  "${BLINK_STANDALONE_VCPKG_STATE_ROOT}/binary-cache")
set(_blink_standalone_vcpkg_buildtrees
  "${BLINK_STANDALONE_VCPKG_STATE_ROOT}/buildtrees")
set(_blink_standalone_vcpkg_packages
  "${BLINK_STANDALONE_VCPKG_STATE_ROOT}/packages")
file(MAKE_DIRECTORY
  "${VCPKG_INSTALLED_DIR}"
  "${_blink_standalone_vcpkg_downloads}"
  "${_blink_standalone_vcpkg_binary_cache}"
  "${_blink_standalone_vcpkg_buildtrees}"
  "${_blink_standalone_vcpkg_packages}")
set(ENV{VCPKG_DOWNLOADS} "${_blink_standalone_vcpkg_downloads}")
set(ENV{VCPKG_DEFAULT_BINARY_CACHE}
  "${_blink_standalone_vcpkg_binary_cache}")
set(BLINK_STANDALONE_VCPKG_EXTRA_INSTALL_OPTIONS "" CACHE STRING
  "Extra options appended to vcpkg manifest install.")
set(VCPKG_INSTALL_OPTIONS
  "--downloads-root=${_blink_standalone_vcpkg_downloads}"
  "--x-buildtrees-root=${_blink_standalone_vcpkg_buildtrees}"
  "--x-packages-root=${_blink_standalone_vcpkg_packages}"
  ${BLINK_STANDALONE_VCPKG_EXTRA_INSTALL_OPTIONS})
set(VCPKG_INSTALL_OPTIONS "${VCPKG_INSTALL_OPTIONS}" CACHE STRING
  "Additional install options passed to vcpkg manifest install." FORCE)

set(BLINK_STANDALONE_VCPKG_ROOT "" CACHE PATH
  "vcpkg checkout used for toolchain scripts. Mutable state remains under BLINK_STANDALONE_VCPKG_STATE_ROOT.")
if(BLINK_STANDALONE_VCPKG_ROOT AND
   EXISTS "${BLINK_STANDALONE_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
  set(_blink_standalone_vcpkg_toolchain
    "${BLINK_STANDALONE_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
elseif(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(_blink_standalone_vcpkg_toolchain
    "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
elseif(DEFINED ENV{VCPKG_ROOT} AND
   EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
  set(_blink_standalone_vcpkg_toolchain
    "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
  message(FATAL_ERROR
    "vcpkg is required for libxml2/Iconv/ZLIB. Set "
    "BLINK_STANDALONE_VCPKG_ROOT or VCPKG_ROOT to a vcpkg checkout, or "
    "install vcpkg at C:/vcpkg, then reconfigure.")
endif()

include("${_blink_standalone_vcpkg_toolchain}")
