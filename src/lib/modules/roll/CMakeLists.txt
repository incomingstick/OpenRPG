set(DIE_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/die.cpp
)

set(DIE_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/die.h
)

add_library(die ${DIE_SOURCE})
install(FILES ${DIE_INCLUDE} DESTINATION include/openrpg)

set(R_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

set(R_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.h
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=gnu++11")

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils die)

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION include/openrpg)
