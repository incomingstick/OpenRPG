set(NG_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
		${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

set(NG_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/generator.h
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++14")

add_executable(name-generator ${NG_SOURCES})

install(TARGETS name-generator DESTINATION bin)
install(FILES ${NG_INCLUDE} DESTINATION lib)
