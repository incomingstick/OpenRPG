cmake_minimum_required(VERSION 3.0)
# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 0)
set(OpenRPG_VERSION_TWEAK 1)
set(OpenRPG_VERSION_SUFFIX "dev")
add_definitions(-DVERSION_STR="v${OpenRPG_VERSION_MAJOR}.${OpenRPG_VERSION_MINOR}.${OpenRPG_VERSION_TWEAK}-${OpenRPG_VERSION_SUFFIX}")

set(USE_GIT_VERSIONING true CACHE BOOL "Determines whether to use git versioning if available.")
# Git build options
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

include_directories("src" "src/modules" "src/modules/lib")
set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

set(TC_SOURCES 
		${CMAKE_SOURCE_DIR}/src/main.cpp
		${CMAKE_SOURCE_DIR}/src/modules/lib/utils.cpp
)

add_executable(OpenRPG ${TC_SOURCES})