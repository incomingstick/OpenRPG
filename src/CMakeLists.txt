set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# build openrpg here
set(ORPG_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/openrpg.cpp
)

add_executable(openrpg ${ORPG_SOURCES})
target_link_libraries(openrpg core names roll-parser)

# if the openrpg executable needs a higher standard than C++11 please update here
set_property(TARGET openrpg PROPERTY CXX_STANDARD 11)
set_property(TARGET openrpg PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS openrpg DESTINATION bin)

# module directories
add_subdirectory("character")
add_subdirectory("core")
add_subdirectory("names")
add_subdirectory("roll")
