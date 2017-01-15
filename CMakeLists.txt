# require cmake v3.0
cmake_minimum_required(VERSION 2.8.4)

# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 0)
set(OpenRPG_VERSION_TWEAK 2)
set(OpenRPG_VERSION_SUFFIX "dev")
add_definitions(-DVERSION_STR="v${OpenRPG_VERSION_MAJOR}.${OpenRPG_VERSION_MINOR}.${OpenRPG_VERSION_TWEAK}-${OpenRPG_VERSION_SUFFIX}")

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

set(SOURCES 
		${CMAKE_SOURCE_DIR}/main.cpp
		${CMAKE_SOURCE_DIR}/lib/utils.cpp
)

set(INCLUDE
		${CMAKE_SOURCE_DIR}/lib/utils.cpp
		${CMAKE_SOURCE_DIR}/lib/config.h
)

set(ASSETS ${CMAKE_SOURCE_DIR}/assets)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(openrpg ${SOURCES})

add_custom_command(TARGET openrpg POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:openrpg>/assets
)

install (TARGETS openrpg DESTINATION bin)
install (FILES ${INCLUDE} DESTINATION lib)
install (DIRECTORY ${ASSETS} DESTINATION ${CMAKE_INSTALL_PREFIX})

set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("src/tests" EXCLUDE_FROM_ALL)