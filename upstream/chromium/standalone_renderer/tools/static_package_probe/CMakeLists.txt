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

function(_blink_static_resolve_path out_var value)
  if(IS_ABSOLUTE "${value}")
    set(${out_var} "${value}" PARENT_SCOPE)
  else()
    set(${out_var} "${BLINK_STANDALONE_STATIC_PACKAGE_DIR}/${value}" PARENT_SCOPE)
  endif()
endfunction()

string(JSON _static_status GET "${_manifest_json}" status)
message(STATUS "Blink static package status: ${_static_status}")

_blink_static_json_array(_required_static_archives required_static_archives)
_blink_static_json_array(_required_import_libraries required_import_libraries)
_blink_static_json_array(_third_party_static_archives third_party_static_archives)
_blink_static_json_array(_whole_archive_candidates whole_archive_candidates_msvc)
_blink_static_json_array(_windows_system_libraries windows_system_libraries)
_blink_static_json_array(_remaining_runtime_sidecars remaining_runtime_sidecars)
_blink_static_json_array(_consumer_compile_definitions consumer_compile_definitions)

set(_resolved_whole_archive_candidates)
foreach(_lib IN LISTS _whole_archive_candidates)
  _blink_static_resolve_path(_resolved_lib "${_lib}")
  list(APPEND _resolved_whole_archive_candidates "${_resolved_lib}")
endforeach()

set(_resolved_static_paths)
foreach(_path IN LISTS _required_static_archives _required_import_libraries
                       _third_party_static_archives _remaining_runtime_sidecars)
  _blink_static_resolve_path(_resolved_path "${_path}")
  if(NOT EXISTS "${_resolved_path}")
    message(FATAL_ERROR "Manifest path does not exist: ${_resolved_path}")
  endif()
  list(APPEND _resolved_static_paths "${_resolved_path}")
endforeach()

set(_normal_libraries)
foreach(_lib IN LISTS _required_static_archives _required_import_libraries
                      _third_party_static_archives)
  _blink_static_resolve_path(_resolved_lib "${_lib}")
  list(FIND _resolved_whole_archive_candidates "${_resolved_lib}" _whole_index)
  if(_whole_index EQUAL -1)
    list(APPEND _normal_libraries "${_resolved_lib}")
  else()
    list(APPEND _normal_libraries "${_resolved_lib}")
  endif()
endforeach()
list(APPEND _normal_libraries ${_windows_system_libraries})

set(_resolved_runtime_sidecars)
foreach(_sidecar IN LISTS _remaining_runtime_sidecars)
  _blink_static_resolve_path(_resolved_sidecar "${_sidecar}")
  list(APPEND _resolved_runtime_sidecars "${_resolved_sidecar}")
endforeach()

function(_blink_static_configure_probe target_name)
  target_include_directories(${target_name} PRIVATE
    "${BLINK_STANDALONE_STATIC_PACKAGE_DIR}/include")
  target_compile_definitions(${target_name} PRIVATE
    ${_consumer_compile_definitions})
  target_link_libraries(${target_name} PRIVATE ${_normal_libraries})
  if(MSVC)
    set_property(TARGET ${target_name} PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded")
    foreach(_lib IN LISTS _resolved_whole_archive_candidates)
      target_link_options(${target_name} BEFORE PRIVATE
        "/WHOLEARCHIVE:${_lib}")
    endforeach()
  endif()
  foreach(_sidecar IN LISTS _resolved_runtime_sidecars)
    add_custom_command(TARGET ${target_name} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${_sidecar}" "$<TARGET_FILE_DIR:${target_name}>/")
  endforeach()
endfunction()

add_executable(blink_static_raw_output_smoke raw_output_smoke.cc)
_blink_static_configure_probe(blink_static_raw_output_smoke)

add_executable(blink_static_gpu_external_target_smoke
  gpu_external_target_smoke.cc)
_blink_static_configure_probe(blink_static_gpu_external_target_smoke)

add_executable(blink_static_host_collision_smoke
  host_collision_smoke.cc)
_blink_static_configure_probe(blink_static_host_collision_smoke)
