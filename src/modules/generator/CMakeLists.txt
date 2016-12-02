set(TC_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
		${CMAKE_SOURCE_DIR}/src/util/utils.cpp
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

add_executable(name-generator ${TC_SOURCES})

install(TARGETS name-generator DESTINATION bin)