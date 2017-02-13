set(DIE_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/die.cpp
)

set(DIE_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/die.h
)

add_library(die ${DIE_SOURCE})
install(FILES ${DIE_INCLUDE} DESTINATION include/openrpg)

set(ROLL_PARSER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.cpp
)

set(ROLL_PARSER_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.h
)

add_library(roll-parser ${ROLL_PARSER_SOURCE})
target_link_libraries(roll-parser die)

install(FILES ${ROLL_PARSER_INCLUDE} DESTINATION include/openrpg)

set(R_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

set(R_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.h
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=gnu++11")

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils roll-parser)

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION include/openrpg)
