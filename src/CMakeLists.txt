set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(UTIL_SOURCE
        ${CMAKE_SOURCE_DIR}/src/utils.cpp
)

add_library(utils ${UTIL_SOURCE})

# if the utils library needs a higher standard than C++11 please update here
set_property(TARGET utils PROPERTY CXX_STANDARD 11)
set_property(TARGET utils PROPERTY CXX_STANDARD_REQUIRED ON)

# build openrpg here
set(ORPG_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/openrpg.cpp
)

add_executable(openrpg ${ORPG_SOURCES})
target_link_libraries(openrpg utils names roll-parser)

# if the openrpg executable needs a higher standard than C++11 please update here
set_property(TARGET openrpg PROPERTY CXX_STANDARD 11)
set_property(TARGET openrpg PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS openrpg DESTINATION bin)

# module directories
add_subdirectory("names")
add_subdirectory("roll")
add_subdirectory("character")
