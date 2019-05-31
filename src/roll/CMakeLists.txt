set(ROLL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/roll/)

set(ROLL_PARSER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.cpp
)

add_library(roll-parser SHARED ${ROLL_PARSER_SOURCE})
GENERATE_EXPORT_HEADER(roll-parser           
    EXPORT_FILE_NAME ${ROLL_INCLUDE_DIR}/exports/parser_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)

target_link_libraries(roll-parser utils)

# if the roll-parser library needs a higher standard than C++11 please update here
set_property(TARGET roll-parser PROPERTY CXX_STANDARD 11)
set_property(TARGET roll-parser PROPERTY CXX_STANDARD_REQUIRED ON)

set(R_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

add_executable(roll ${R_SOURCES})
target_link_libraries(roll roll-parser utils)

# if the roll executable needs a higher standard than C++11 please update here
set_property(TARGET roll PROPERTY CXX_STANDARD 11)
set_property(TARGET roll PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS roll DESTINATION bin)
install(TARGETS roll-parser
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT library
)
