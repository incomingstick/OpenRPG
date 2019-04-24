set(ROLL_PARSER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.cpp
)

add_library(roll-parser SHARED ${ROLL_PARSER_SOURCE})
target_link_libraries(roll-parser utils)

# if the roll-parser library needs a higher standard than C++11 please update here
set_property(TARGET roll-parser PROPERTY CXX_STANDARD 11)
set_property(TARGET roll-parser PROPERTY CXX_STANDARD_REQUIRED ON)

set(R_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils roll-parser)

# if the roll executable needs a higher standard than C++11 please update here
set_property(TARGET roll PROPERTY CXX_STANDARD 11)
set_property(TARGET roll PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS roll DESTINATION bin)
install(TARGETS roll-parser DESTINATION lib/openrpg)
