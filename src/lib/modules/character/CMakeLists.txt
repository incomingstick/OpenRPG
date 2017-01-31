set(CG_SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/character-generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
)

set(CG_INCLUDES
		${CMAKE_CURRENT_SOURCE_DIR}/character.h
)

set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")

add_executable(character-generator ${CG_SOURCES})
target_link_libraries(character-generator utils)

install(TARGETS character-generator DESTINATION bin)
install(FILES ${CG_INCLUDE} DESTINATION lib)