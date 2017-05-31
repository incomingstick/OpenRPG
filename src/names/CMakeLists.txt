set(NAMES_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/names.cpp
)

add_library(names ${NAMES_SOURCE})

set(NG_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/name-generator.cpp  
)

add_executable(name-generator ${NG_SOURCES})
target_link_libraries(name-generator utils names)

install(TARGETS name-generator DESTINATION bin)
