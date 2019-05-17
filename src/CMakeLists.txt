set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CORE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/core/)

set(UTIL_SOURCE
        ${CMAKE_SOURCE_DIR}/src/utils.cpp
)

add_library(utils SHARED ${UTIL_SOURCE})
GENERATE_EXPORT_HEADER(utils           
    EXPORT_FILE_NAME ${CORE_INCLUDE_DIR}/exports/utils_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

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
install(TARGETS utils DESTINATION lib/openrpg)

# module directories
add_subdirectory("names")
add_subdirectory("roll")
add_subdirectory("character")
