# require cmake v3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
include(GenerateExportHeader)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_MACOSX_RPATH 1)

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
set(DEFAULT_BUILD_TYPE "RELEASE")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(DEFAULT_BUILD_TYPE "DEBUG")
endif()

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none were specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "DEBUG" "RELEASE")
endif()

if(MSVC OR WIN32)
  set(LIB_DIR lib)

  # Force to always compile with W1
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W1" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(LIB_DIR lib/openrpg)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  endif()
endif()

message(STATUS "CMAKE_CXX_FLAGS:\t" ${CMAKE_CXX_FLAGS})
message(STATUS "DEFAULT_BUILD_TYPE:\t" ${DEFAULT_BUILD_TYPE})
message(STATUS "CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})

set(DATA ${CMAKE_SOURCE_DIR}/data)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)

message(STATUS "INCLUDE:\t\t" ${INCLUDE})

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${LIB_DIR})
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# used to pass the location to use for data into config.h.in
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(DATA_DIR ${DATA})
# better conform to Linux filesystem standards
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE AND NOT (MSVC OR WIN32))
    set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/openrpg)
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE AND (MSVC OR WIN32))
    set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/data)
endif()

message(STATUS "DATA_DIR:\t\t" ${DATA_DIR})
message(STATUS "LIB_DIR:\t\t" ${CMAKE_INSTALL_PREFIX}/${LIB_DIR})

# message( FATAL_ERROR "Exiting.." )

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
install(DIRECTORY ${DATA}/ DESTINATION ${DATA_DIR})
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
