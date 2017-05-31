set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(UTIL_SOURCE
        ${CMAKE_SOURCE_DIR}/src/utils.cpp
)

add_library(utils ${UTIL_SOURCE})

# build openrpg here
set(ORPG_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/openrpg.cpp
)

add_executable(openrpg ${ORPG_SOURCES})
target_link_libraries(openrpg utils names roll-parser)

install(TARGETS openrpg DESTINATION bin)

# module directories
add_subdirectory("names")
add_subdirectory("roll")
add_subdirectory("character")
