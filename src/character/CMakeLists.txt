set(CG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
)

set(CG_INCLUDES
        ${CMAKE_SOURCE_DIR}/include/character.h
)

add_executable(character-generator ${CG_SOURCES})
target_link_libraries(character-generator utils roll-parser names)

install(TARGETS character-generator DESTINATION bin)
install(FILES ${CG_INCLUDE} DESTINATION include/openrpg)