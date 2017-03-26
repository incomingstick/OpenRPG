set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#
set(UTIL_SOURCE
        ${CMAKE_SOURCE_DIR}/src/utils.cpp
)

set(UTIL_INCLUDE
        ${CMAKE_SOURCE_DIR}/include/utils.h
)

add_library(utils ${UTIL_SOURCE})
install (FILES ${UTIL_INCLUDE} DESTINATION include/openrpg)

# build openrpg here
set(ORPG_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/openrpg.cpp
)

set(ORPG_INCLUDE
    ${CMAKE_SOURCE_DIR}/include/config.h
)

add_executable(openrpg ${ORPG_SOURCES})
target_link_libraries(openrpg utils names roll-parser)

install(TARGETS openrpg DESTINATION bin)
install(FILES ${ORPG_INCLUDE} DESTINATION include/openrpg)

# module directories
add_subdirectory("names")
add_subdirectory("roll")
add_subdirectory("character")
