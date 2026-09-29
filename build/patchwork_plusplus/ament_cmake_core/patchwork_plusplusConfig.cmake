# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_patchwork_plusplus_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED patchwork_plusplus_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(patchwork_plusplus_FOUND FALSE)
  elseif(NOT patchwork_plusplus_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(patchwork_plusplus_FOUND FALSE)
  endif()
  return()
endif()
set(_patchwork_plusplus_CONFIG_INCLUDED TRUE)

# output package information
if(NOT patchwork_plusplus_FIND_QUIETLY)
  message(STATUS "Found patchwork_plusplus: 0.0.0 (${patchwork_plusplus_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'patchwork_plusplus' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${patchwork_plusplus_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(patchwork_plusplus_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake;ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_libraries-extras.cmake")
foreach(_extra ${_extras})
  include("${patchwork_plusplus_DIR}/${_extra}")
endforeach()
