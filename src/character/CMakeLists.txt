set(CG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
)

add_executable(character-generator ${CG_SOURCES})
target_link_libraries(character-generator utils roll-parser names)

install(TARGETS character-generator DESTINATION bin)
