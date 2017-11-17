# require cmake v2.8.4
cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 5)
set(OpenRPG_VERSION_TWEAK 0)
set(OpenRPG_VERSION_SUFFIX "dev")
set(OpenRPG_AUTHOR "Nicholas Gaulke")
string(TIMESTAMP YEAR %Y UTC)
string(TIMESTAMP DATE UTC)

# default compiler flags
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

set(DATA ${CMAKE_SOURCE_DIR}/data)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)

# used to pass the location to use for data into config.h.in
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(DATA_DIR ${DATA})
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE)
    set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/data)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

MESSAGE(STATUS "CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "DATA_DIR:\t\t\t" ${DATA_DIR})

# source directories
include_directories("include/")

# source code directory with CMakeLists.txt
add_subdirectory("src/")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_SOURCE_DIR}/include/core/config.h"
)

install(DIRECTORY ${DATA} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${INCLUDE}/ DESTINATION include/openrpg)

set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("test/" EXCLUDE_FROM_ALL)
