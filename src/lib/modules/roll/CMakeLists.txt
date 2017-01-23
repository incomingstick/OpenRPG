set(R_SOURCES
		${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/die.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/roll-scanner.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

set(R_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/die.h
		${CMAKE_CURRENT_SOURCE_DIR}/roll.h
		${CMAKE_CURRENT_SOURCE_DIR}/roll-parser.hpp
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(roll ${R_SOURCES})

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION lib/openrpg)