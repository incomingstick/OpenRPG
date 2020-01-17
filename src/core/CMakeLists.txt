set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CORE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/core/)

set(CORE_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xml.cpp
)

if(MSVC OR WIN32)
    GENERATE_EXPORT_HEADER(core           
        EXPORT_FILE_NAME ${CORE_INCLUDE_DIR}/exports/core_exports.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
    )

    set(CORE_SOURCE
        ${CORE_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/win32.cpp
    )
elseif(UNIX)
    set(CORE_SOURCE
        ${CORE_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/unix.cpp
    )
elseif(APPLE)
    set(CORE_SOURCE
        ${CORE_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/osx.cpp
    )
endif()

add_library(core SHARED ${CORE_SOURCE})

# if the core library needs a higher standard than C++17 please update here
set_property(TARGET core PROPERTY CXX_STANDARD 17)
set_property(TARGET core PROPERTY CXX_STANDARD_REQUIRED ON)

if(NOT (MSVC OR WIN32))
    target_link_libraries(core "stdc++fs")
endif(NOT (MSVC OR WIN32))

install(TARGETS core 
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT Modules
)
