if(NOT DEFINED PACKAGE_DIR)
  message(FATAL_ERROR "PACKAGE_DIR is required")
endif()

set(_forbidden_code_sidecars
  blink_standalone_renderer_c_api.dll
  blink_standalone_renderer_c_api.so
  libblink_standalone_renderer_c_api.so
  libblink_standalone_renderer_c_api.dylib
  libEGL.dll
  libEGL.so
  libEGL.dylib
  libGLESv2.dll
  libGLESv2.so
  libGLESv2.dylib
)

set(_found_forbidden)
foreach(_name IN LISTS _forbidden_code_sidecars)
  foreach(_prefix IN ITEMS "" "bin/" "lib/")
    if(EXISTS "${PACKAGE_DIR}/${_prefix}${_name}")
      list(APPEND _found_forbidden "${_prefix}${_name}")
    endif()
  endforeach()
endforeach()

if(_found_forbidden)
  list(REMOVE_DUPLICATES _found_forbidden)
  string(REPLACE ";" ", " _found_forbidden_text "${_found_forbidden}")
  message(FATAL_ERROR
    "Static package contains forbidden Blink/ANGLE code sidecar(s): "
    "${_found_forbidden_text}")
endif()
