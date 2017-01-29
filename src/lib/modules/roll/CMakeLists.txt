find_package(BISON)
find_package(FLEX)

BISON_TARGET(R_PARSER roll-parser.y ${CMAKE_CURRENT_BINARY_DIR}/roll-parser.cpp)
FLEX_TARGET(R_SCANNER roll-scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/roll-scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(R_SCANNER R_PARSER)

set(R_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/die.cpp
		${BISON_R_PARSER_OUTPUTS}
    	${FLEX_R_SCANNER_OUTPUTS}
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

set(R_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/die.h
		${CMAKE_CURRENT_SOURCE_DIR}/roll.h
		${BISON_R_PARSER_OUTPUTS}
    	${FLEX_R_SCANNER_OUTPUTS}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=gnu++11")

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils)

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION include/openrpg)
