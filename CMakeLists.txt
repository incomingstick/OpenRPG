# require cmake v3.0
cmake_minimum_required(VERSION 3.0)

# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 0)
set(OpenRPG_VERSION_TWEAK 3)
set(OpenRPG_VERSION_SUFFIX "dev")
set(OpenRPG_AUTHOR "Nicholas Gaulke")
string(TIMESTAMP YEAR %Y UTC)

# Git build options
set(USE_GIT_VERSIONING true CACHE BOOL "Determines whether to use git versioning if available.")

find_package(Git)
if(${GIT_FOUND} AND ${USE_GIT_VERSIONING})
		add_definitions(-DWITH_GIT_INFO=1)
		# The following execute_process stolen from http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/
		# thanks, bud.
		# Get the latest abbreviated commit hash of the working branch
		execute_process(
			COMMAND git log -1 --format=%h
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE GIT_COMMIT_HASH
			OUTPUT_STRIP_TRAILING_WHITESPACE
		)

		add_definitions(-DGIT_COMMIT_STR="${GIT_COMMIT_HASH}")
endif(${GIT_FOUND} AND ${USE_GIT_VERSIONING})

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

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

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