set(TC_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
		${CMAKE_SOURCE_DIR}/lib/utils.cpp
)

set(TC_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/generator.h
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(name-generator ${TC_SOURCES})

install(TARGETS name-generator DESTINATION bin)
install (FILES ${TC_INCLUDE} DESTINATION include)
install (FILES ${TC_ASSETS} DESTINATION assets)
