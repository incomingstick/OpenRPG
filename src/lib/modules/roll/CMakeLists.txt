set(TC_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
		${CMAKE_SOURCE_DIR}/lib/utils.cpp
		${MOD}/generator/generator.cpp
)

set(TC_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.h
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(roll ${TC_SOURCES})

install(TARGETS roll DESTINATION bin)
install (FILES ${TC_INCLUDE} DESTINATION include)
install (FILES ${TC_ASSETS} DESTINATION assets)