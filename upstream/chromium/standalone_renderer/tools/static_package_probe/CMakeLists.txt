cmake_minimum_required(VERSION 3.26)
project(blink_standalone_static_package_probe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BLINK_STANDALONE_STATIC_PACKAGE_DIR "" CACHE PATH
  "Path to build/cmake-generated-v8-chromium-llvm/package/c_api_static.")
if(NOT BLINK_STANDALONE_STATIC_PACKAGE_DIR)
  message(FATAL_ERROR
    "Set BLINK_STANDALONE_STATIC_PACKAGE_DIR to the generated c_api_static package.")
endif()

set(_manifest
  "${BLINK_STANDALONE_STATIC_PACKAGE_DIR}/blink_standalone_renderer_c_api_static_link_manifest.json")
if(NOT EXISTS "${_manifest}")
  message(FATAL_ERROR "Static link manifest not found: ${_manifest}")
endif()

file(READ "${_manifest}" _manifest_json)

function(_blink_static_json_array out_var field)
  string(JSON _length ERROR_VARIABLE _json_error LENGTH "${_manifest_json}" "${field}")
  if(_json_error)
    message(FATAL_ERROR "Manifest field '${field}' is missing or not an array: ${_json_error}")
  endif()
  set(_values)
  if(_length GREATER 0)
    math(EXPR _last "${_length} - 1")
    foreach(_index RANGE 0 ${_last})
      string(JSON _value GET "${_manifest_json}" "${field}" ${_index})
      list(APPEND _values "${_value}")
    endforeach()
  endif()
  set(${out_var} "${_values}" PARENT_SCOPE)
endfunction()

string(JSON _static_archive GET "${_manifest_json}" static_archive)
string(JSON _static_status GET "${_manifest_json}" status)
message(STATUS "Blink static package status: ${_static_status}")

_blink_static_json_array(_required_static_archives required_static_archives)
_blink_static_json_array(_required_import_libraries required_import_libraries)
_blink_static_json_array(_third_party_static_archives third_party_static_archives)
_blink_static_json_array(_whole_archive_candidates whole_archive_candidates_msvc)
_blink_static_json_array(_windows_system_libraries windows_system_libraries)
_blink_static_json_array(_remaining_runtime_sidecars remaining_runtime_sidecars)

foreach(_path IN LISTS _required_static_archives _required_import_libraries
                       _third_party_static_archives _remaining_runtime_sidecars)
  if(NOT EXISTS "${_path}")
    message(FATAL_ERROR "Manifest path does not exist: ${_path}")
  endif()
endforeach()

add_executable(blink_static_raw_output_smoke raw_output_smoke.cc)
target_include_directories(blink_static_raw_output_smoke PRIVATE
  "${BLINK_STANDALONE_STATIC_PACKAGE_DIR}/include")
target_compile_definitions(blink_static_raw_output_smoke PRIVATE
  BLINK_STANDALONE_RENDERER_C_API_STATIC=1)
if(MSVC)
  set_property(TARGET blink_static_raw_output_smoke PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()

set(_normal_libraries)
foreach(_lib IN LISTS _required_static_archives _required_import_libraries
                      _third_party_static_archives _windows_system_libraries)
  list(FIND _whole_archive_candidates "${_lib}" _whole_index)
  if(_whole_index EQUAL -1)
    list(APPEND _normal_libraries "${_lib}")
  else()
    list(APPEND _normal_libraries "${_lib}")
  endif()
endforeach()
target_link_libraries(blink_static_raw_output_smoke PRIVATE ${_normal_libraries})

if(MSVC)
  foreach(_lib IN LISTS _whole_archive_candidates)
    target_link_options(blink_static_raw_output_smoke BEFORE PRIVATE
      "/WHOLEARCHIVE:${_lib}")
  endforeach()
endif()

foreach(_sidecar IN LISTS _remaining_runtime_sidecars)
  add_custom_command(TARGET blink_static_raw_output_smoke POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${_sidecar}" "$<TARGET_FILE_DIR:blink_static_raw_output_smoke>/")
endforeach()
