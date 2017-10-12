set(NAMES_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/names.cpp
)

add_library(names ${NAMES_SOURCE})

# if the names library needs a higher standard than C++11 please update here
set_property(TARGET names PROPERTY CXX_STANDARD 11)
set_property(TARGET names PROPERTY CXX_STANDARD_REQUIRED ON)

set(NG_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/name-generator.cpp  
)

add_executable(name-generator ${NG_SOURCES})
target_link_libraries(name-generator utils names)

# if the name-generator executable needs a higher standard than C++11 please update here
set_property(TARGET name-generator PROPERTY CXX_STANDARD 11)
set_property(TARGET name-generator PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS name-generator DESTINATION bin)
