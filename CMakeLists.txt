# require cmake v2.8.4
cmake_minimum_required(VERSION 2.8.4)

# project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 0)
set(OpenRPG_VERSION_TWEAK 4)
set(OpenRPG_VERSION_SUFFIX "shiny")
set(OpenRPG_AUTHOR "Nicholas Gaulke")
add_definitions(-DVERSION_STR="v${OpenRPG_VERSION_MAJOR}.${OpenRPG_VERSION_MINOR}.${OpenRPG_VERSION_TWEAK}-${OpenRPG_VERSION_SUFFIX}")
string(TIMESTAMP YEAR %Y UTC)
string(TIMESTAMP DATE UTC)

# set build source directory
set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_SOURCE_DIR}/lib/config.h"
)

# source directories
include_directories("src" "src/lib")

# module directory with CMakeLists.txt
add_subdirectory("src/lib/modules")

# set variables
set(SOURCES 
		${CMAKE_SOURCE_DIR}/openrpg.cpp
		${CMAKE_SOURCE_DIR}/lib/utils.cpp
)

set(INCLUDE
		${CMAKE_SOURCE_DIR}/lib/config.h
)

set(ASSETS ${CMAKE_SOURCE_DIR}/assets)

set(CMAKE_CXX_FLAGS "-Wall --std=c++11")

# create executable from sources
add_executable(openrpg ${SOURCES})

# after building, copy assets folder and contents to root directory of build
add_custom_command(TARGET openrpg POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:openrpg>/assets
)

install (TARGETS openrpg DESTINATION bin)
install (FILES ${INCLUDE} DESTINATION lib)
install (DIRECTORY ${ASSETS} DESTINATION @CMAKE_INSTALL_PREFIX@)

set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("src/tests" EXCLUDE_FROM_ALL)