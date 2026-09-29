
if(NOT "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-subbuild/nanogrid-populate-prefix/src/nanogrid-populate-stamp/nanogrid-populate-gitinfo.txt" IS_NEWER_THAN "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-subbuild/nanogrid-populate-prefix/src/nanogrid-populate-stamp/nanogrid-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-subbuild/nanogrid-populate-prefix/src/nanogrid-populate-stamp/nanogrid-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/Ikhyeon-Cho/nanoGrid.git" "nanogrid-src"
    WORKING_DIRECTORY "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/Ikhyeon-Cho/nanoGrid.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout main --
  WORKING_DIRECTORY "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'main'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-subbuild/nanogrid-populate-prefix/src/nanogrid-populate-stamp/nanogrid-populate-gitinfo.txt"
    "/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-subbuild/nanogrid-populate-prefix/src/nanogrid-populate-stamp/nanogrid-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/media/subham/85dce0f4-2e29-4540-9a32-801850cfcef6/subham/LidarMapping2.5D/build/fastdem/_deps/nanogrid-subbuild/nanogrid-populate-prefix/src/nanogrid-populate-stamp/nanogrid-populate-gitclone-lastrun.txt'")
endif()

