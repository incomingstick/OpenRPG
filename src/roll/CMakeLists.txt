set(ROLL_PARSER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.cpp
)

set(ROLL_PARSER_INCLUDE
    ${CMAKE_SOURCE_DIR}/include/roll-parser.h
    ${CMAKE_SOURCE_DIR}/include/die.h
)

add_library(roll-parser ${ROLL_PARSER_SOURCE})
target_link_libraries(roll-parser)

install(FILES ${ROLL_PARSER_INCLUDE} DESTINATION include/openrpg)

set(R_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

set(R_INCLUDES
		${CMAKE_SOURCE_DIR}/include/roll.h
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils roll-parser)

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION include/openrpg)
