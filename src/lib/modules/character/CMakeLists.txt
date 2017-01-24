set(CG_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
        ${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

set(CG_INCLUDES
		
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(character-generator ${CG_SOURCES})

install(TARGETS character-generator DESTINATION bin)
install(FILES ${CG_INCLUDE} DESTINATION lib)