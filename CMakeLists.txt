# require cmake v2.8.4
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 3)
set(OpenRPG_VERSION_TWEAK 0)
set(OpenRPG_VERSION_SUFFIX "dev")
set(OpenRPG_AUTHOR "Nicholas Gaulke")
string(TIMESTAMP YEAR %Y UTC)
string(TIMESTAMP DATE UTC)

# default compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=c++11")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_SOURCE_DIR}/include/config.h"
)

# source directories
include_directories("include/")

# source code directory with CMakeLists.txt
add_subdirectory("src/")

set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("test/" EXCLUDE_FROM_ALL)