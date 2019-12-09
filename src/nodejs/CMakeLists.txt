set(ROLL_ADDON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/roll/)

set(ROLL_ADDON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/nodeAddon.cpp
    ${CMAKE_SOURCE_DIR}/src/roll/rollWrapper.cpp
)

add_library(orpgNode SHARED ${ROLL_ADDON_SOURCES} ${CMAKE_JS_SRC})
set_target_properties(orpgNode PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(orpgNode ${CMAKE_JS_LIB} roll-parser)

# if the roll executable needs a higher standard than C++11 please update here
set_property(TARGET orpgNode PROPERTY CXX_STANDARD 11)
set_property(TARGET orpgNode PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS orpgNode DESTINATION ${LIB_INSTALL_DIR})
