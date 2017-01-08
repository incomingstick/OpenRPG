set(R_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/die.cpp
		${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

set(R_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/die.h
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

add_executable(roll ${R_SOURCES})

install(TARGETS roll DESTINATION bin)
install(FILES ${R_INCLUDE} DESTINATION lib)
