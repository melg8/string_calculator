cmake_minimum_required (VERSION 3.5 FATAL_ERROR)
project (string_calculator)
enable_testing ()

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

include ("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ccache.cmake")
include ("${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler_flags.cmake")
include ("${CMAKE_CURRENT_SOURCE_DIR}/cmake/recursive_dirs_macro.cmake")

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/tests")
