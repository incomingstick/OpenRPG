set(ROLL_PARSER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.cpp
)

add_library(roll-parser ${ROLL_PARSER_SOURCE})
target_link_libraries(roll-parser)

set(R_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils roll-parser)

install(TARGETS roll DESTINATION bin)
