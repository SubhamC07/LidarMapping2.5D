#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fastdem::fastdem" for configuration "Release"
set_property(TARGET fastdem::fastdem APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fastdem::fastdem PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfastdem.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fastdem::fastdem )
list(APPEND _IMPORT_CHECK_FILES_FOR_fastdem::fastdem "${_IMPORT_PREFIX}/lib/libfastdem.a" )

# Import target "fastdem::nanoGrid" for configuration "Release"
set_property(TARGET fastdem::nanoGrid APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fastdem::nanoGrid PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libnanoGrid.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fastdem::nanoGrid )
list(APPEND _IMPORT_CHECK_FILES_FOR_fastdem::nanoGrid "${_IMPORT_PREFIX}/lib/libnanoGrid.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
