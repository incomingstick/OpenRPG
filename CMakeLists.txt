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
# Set a default build type if none was specified
set(default_build_type "RELEASE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "DEBUG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()
 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "DEBUG" "RELEASE")
endif()

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
    message("debug mode")
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")

set(DATA ${CMAKE_SOURCE_DIR}/data)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib/openrpg)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# used to pass the location to use for data into config.h.in
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(DATA_DIR ${DATA})
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE)
    set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/data/openrpg)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

MESSAGE(STATUS "CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "DATA_DIR:\t\t" ${DATA_DIR})

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

# install targets
install(DIRECTORY ${DATA}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/data/openrpg)
install(DIRECTORY ${INCLUDE}/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/openrpg)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()


set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("test/" EXCLUDE_FROM_ALL)
