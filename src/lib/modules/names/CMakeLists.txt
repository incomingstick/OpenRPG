set(NAMES_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/names.cpp
)

set(NAMES_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/names.h
)

add_library(names ${NAMES_SOURCE})
install (FILES ${NAMES_INCLUDE} DESTINATION include/openrpg)

set(NG_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/name-generator.cpp  
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=c++11")

add_executable(name-generator ${NG_SOURCES})
target_link_libraries(name-generator utils names)

install(TARGETS name-generator DESTINATION bin)
install(FILES ${NG_INCLUDE} DESTINATION include/openrpg)
