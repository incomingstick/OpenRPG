# require cmake v2.8.4
cmake_minimum_required(VERSION 2.8.4)

# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 0)
set(OpenRPG_VERSION_TWEAK 3)
set(OpenRPG_VERSION_SUFFIX "dev")
set(OpenRPG_AUTHOR "Nicholas Gaulke")
string(TIMESTAMP YEAR %Y UTC)
string(TIMESTAMP DATE UTC)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_SOURCE_DIR}/src/lib/config.h"
)

# source directories
include_directories("src" "src/lib")

# module directory with CMakeLists.txt
add_subdirectory("src/lib/modules")

set(SOURCES 
		${CMAKE_SOURCE_DIR}/src/openrpg.cpp
		${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

set(INCLUDE
		${CMAKE_SOURCE_DIR}/src/lib/utils.h
		${CMAKE_SOURCE_DIR}/src/lib/config.h
)

set(ASSETS ${CMAKE_SOURCE_DIR}/src/assets)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(openrpg ${SOURCES})

install (TARGETS openrpg DESTINATION bin)
install (FILES ${INCLUDE} DESTINATION lib)
install (DIRECTORY ${ASSETS} DESTINATION ${CMAKE_INSTALL_PREFIX})

set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("src/tests" EXCLUDE_FROM_ALL)