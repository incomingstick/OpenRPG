set(TC_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/gen-main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
)

set(TC_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/generator.h
)

set(CMAKE_CXX_FLAGS "-Wall --std=c++11")

add_executable(generator ${TC_SOURCES})

install(TARGETS generator DESTINATION bin)
