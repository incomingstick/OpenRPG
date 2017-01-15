set(TC_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/roll.cpp
)

set(TC_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/roll.h
)

set(CMAKE_CXX_FLAGS "-Wall --std=c++11")

add_executable(roll ${TC_SOURCES})

install(TARGETS roll DESTINATION bin)