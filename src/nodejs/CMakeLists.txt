set(ROLL_ADDON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/roll/)

set(ROLL_ADDON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/roll/rollAddon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/roll/rollWrapper.cpp
)

add_library(openrpgAddon SHARED ${ROLL_ADDON_SOURCES} ${CMAKE_JS_SRC})
set_target_properties(openrpgAddon PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(openrpgAddon ${CMAKE_JS_LIB} roll-parser)

# if the roll executable needs a higher standard than C++11 please update here
set_property(TARGET openrpgAddon PROPERTY CXX_STANDARD 11)
set_property(TARGET openrpgAddon PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS openrpgAddon DESTINATION ${LIB_INSTALL_DIR})
