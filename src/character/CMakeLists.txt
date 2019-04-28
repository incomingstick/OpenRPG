set(CHARACTER_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/races.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
)

set(CHARACTER_INCLUDE
        ${CMAKE_SOURCE_DIR}/include/ability-scores.h
        ${CMAKE_SOURCE_DIR}/include/races.h
        ${CMAKE_SOURCE_DIR}/include/skills.h
        ${CMAKE_SOURCE_DIR}/include/character.h
)

add_library(character SHARED ${CHARACTER_SOURCE})
target_link_libraries(character utils roll-parser names)

# if the character library needs a higher standard than C++11 please update here
set_property(TARGET character PROPERTY CXX_STANDARD 11)
set_property(TARGET character PROPERTY CXX_STANDARD_REQUIRED ON)

set(CG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
)

add_executable(character-generator ${CG_SOURCES})
target_link_libraries(character-generator utils character roll-parser names)

# if the character-generator executable needs a higher standard than C++11 please update here
set_property(TARGET character-generator PROPERTY CXX_STANDARD 11)
set_property(TARGET character-generator PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS character-generator DESTINATION bin)
install(TARGETS character DESTINATION lib/openrpg)
