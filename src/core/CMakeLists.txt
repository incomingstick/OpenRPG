set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CORE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/core/)

set(CORE_SOURCE
    ${CMAKE_SOURCE_DIR}/src/core/utils.cpp
    ${CMAKE_SOURCE_DIR}/src/core/xml.cpp
)

add_library(core SHARED ${CORE_SOURCE})
GENERATE_EXPORT_HEADER(core           
    EXPORT_FILE_NAME ${CORE_INCLUDE_DIR}/exports/core_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)

# if the core library needs a higher standard than C++11 please update here
set_property(TARGET core PROPERTY CXX_STANDARD 11)
set_property(TARGET core PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS core 
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT Modules
)
