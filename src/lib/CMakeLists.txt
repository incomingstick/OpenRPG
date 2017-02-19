set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(UTIL_SOURCE
        ${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

set(UTIL_INCLUDE
        ${CMAKE_SOURCE_DIR}/src/lib/utils.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=c++11")

add_library(utils ${UTIL_SOURCE})
install (FILES ${UTIL_INCLUDE} DESTINATION include/openrpg)

# module directory
add_subdirectory("modules")