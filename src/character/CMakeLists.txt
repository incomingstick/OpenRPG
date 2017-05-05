set(CHARACTER_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/races.cpp
)

set(CHARACTER_INCLUDE
        ${CMAKE_SOURCE_DIR}/include/character.h
        ${CMAKE_SOURCE_DIR}/include/races.h
)

add_library(character ${CHARACTER_SOURCE})
target_link_libraries(character)

set(CG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
)

set(CG_INCLUDES
        ${CHARACTER_INCLUDE}
)

add_executable(character-generator ${CG_SOURCES})
target_link_libraries(character-generator utils character roll-parser names)

install(TARGETS character-generator DESTINATION bin)
