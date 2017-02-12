set(MODULE_DIR "${CMAKE_SOURCE_DIR}/src/lib/modules")

# source directories
include_directories("${MODULE_DIR}/roll"
                    "${MODULE_DIR}/names"
)

set(CG_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
)

set(CG_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/character.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=gnu++11")

add_executable(character-generator ${CG_SOURCES})
target_link_libraries(character-generator utils die names)

install(TARGETS character-generator DESTINATION bin)
install(FILES ${CG_INCLUDE} DESTINATION include/openrpg)