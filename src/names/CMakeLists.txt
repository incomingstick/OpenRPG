set(NAMES_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/names.cpp
)

set(NAMES_INCLUDE
        ${CMAKE_SOURCE_DIR}/include/names.h
)

add_library(names ${NAMES_SOURCE})
install (FILES ${NAMES_INCLUDE} DESTINATION include/openrpg)

set(NG_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/name-generator.cpp  
)

add_executable(name-generator ${NG_SOURCES})
target_link_libraries(name-generator utils names)

install(TARGETS name-generator DESTINATION bin)
install(FILES ${NG_INCLUDE} DESTINATION include/openrpg)
