set(R_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/die.cpp
)

set(R_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/die.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=c++11")

add_executable(roll ${R_SOURCES})
target_link_libraries(roll utils)

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION include/openrpg)