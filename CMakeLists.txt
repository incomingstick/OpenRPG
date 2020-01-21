# require cmake v3.0
message(STATUS "CMake Version is " ${CMAKE_VERSION})
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
include(GenerateExportHeader)
include(InstallRequiredSystemLibraries)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_MACOSX_RPATH 1)

# this is the minimum c++std to require across the whole project
# however each module is built with its own specified std
set(CMAKE_CXX_STANDARD 11)

# Project info
project(OpenRPG)
set(OpenRPG_VERSION_MAJOR 0)
set(OpenRPG_VERSION_MINOR 5)
set(OpenRPG_VERSION_TWEAK 2)
set(OpenRPG_AUTHOR "Nicholas Gaulke")
string(TIMESTAMP YEAR %Y UTC)
string(TIMESTAMP DATE UTC)

# default compiler flags
# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "RELEASE")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(DEFAULT_BUILD_TYPE "DEBUG")
endif()

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none were specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "DEBUG" "RELEASE")
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

if(NOT (MSVC OR WIN32))
    if(NOT DEFINED CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "/usr")
    endif()
    set(LIB_INSTALL_DIR lib/openrpg)
elseif(MSVC OR WIN32)
    if(NOT DEFINED CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "C:/Program Files")
    endif()
    set(WINDOWS_FOLDER_NAME "OpenRPG/")
    set(LIB_INSTALL_DIR lib)
endif(NOT (MSVC OR WIN32))

if(MSVC OR WIN32)
    # if this is a cmake-js build ignore the node.exe link warning
    if (CMAKE_JS_VERSION)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /ignore:4199")
    endif()

    # Force to always compile with W1
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W1" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif()
endif()

message(STATUS "CMAKE_SYSTEM_NAME:\t" ${CMAKE_SYSTEM_NAME})
message(STATUS "CMAKE_CXX_FLAGS:\t" ${CMAKE_CXX_FLAGS})
message(STATUS "DEFAULT_BUILD_TYPE:\t" ${DEFAULT_BUILD_TYPE})
message(STATUS "CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})
message(STATUS "CMAKE_SIZEOF_VOID_P:\t" ${CMAKE_SIZEOF_VOID_P})

set(DATA ${CMAKE_SOURCE_DIR}/data)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)
set(MAN ${CMAKE_SOURCE_DIR}/man)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${LIB_INSTALL_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

message(STATUS "INCLUDE_DIR:\t\t" ${INCLUDE})
message(STATUS "DATA_DIR:\t\t" ${DATA})
message(STATUS "LIB_OUTPUT_DIRECTORY:" ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# used to pass the location to use for data into config.h.in
# conform to Linux filesystem standards
if(CMAKE_BUILD_TYPE MATCHES RELEASE AND NOT (MSVC OR WIN32)) #unix
    set(DATA_INSTALL_DIR share/openrpg)
    set(BIN_INSTALL_DIR bin)
    set(LEGAL_INSTALL_DIR ${DATA_INSTALL_DIR})
    set(MAN_INSTALL_DIR share/man)
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE AND (MSVC OR WIN32)) #windows
    set(DATA_INSTALL_DIR data)
    set(BIN_INSTALL_DIR /)
    set(LEGAL_INSTALL_DIR ${BIN_INSTALL_DIR})
    set(MAN_INSTALL_DIR docs)
else() #other
    set(DATA_INSTALL_DIR data)
    set(BIN_INSTALL_DIR bin)
    set(LEGAL_INSTALL_DIR ${DATA_INSTALL_DIR})
    set(MAN_INSTALL_DIR share/man)
endif()


if(MSVC OR WIN32)
    set(INCLUDE_INSTALL_DIR include)
else()
    set(INCLUDE_INSTALL_DIR include/openrpg)
endif()

message(STATUS "INCLUDE_INSTALL_DIR:\t" ${CMAKE_INSTALL_PREFIX}/${INCLUDE_INSTALL_DIR})
message(STATUS "DATA_INSTALL_DIR:\t" ${CMAKE_INSTALL_PREFIX}/${DATA_INSTALL_DIR})
message(STATUS "LIB_INSTALL_DIR:\t" ${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR})
message(STATUS "BIN_INSTALL_DIR:\t" ${CMAKE_INSTALL_PREFIX}/${BIN_INSTALL_DIR})
message(STATUS "MAN_INSTALL_DIR:\t" ${CMAKE_INSTALL_PREFIX}/${MAN_INSTALL_DIR})

# RPATH stuff here
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# TODO load DLLs and so's internally, rather than via RPATHS
set(CMAKE_INSTALL_RPATH $ORIGIN/../${LIB_INSTALL_DIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# source directories
include_directories("include/")

# source code directory with CMakeLists.txt
add_subdirectory("src/")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${CMAKE_SOURCE_DIR}/include/core/config.h"
)

# install targets
install(DIRECTORY ${DATA}/
    DESTINATION ${DATA_INSTALL_DIR}
    COMPONENT Modules
)

# TODO gzip man pages before installing them
install(DIRECTORY ${MAN}/
    DESTINATION ${MAN_INSTALL_DIR}
    COMPONENT Documentation
)

install(DIRECTORY ${INCLUDE}/
    DESTINATION ${INCLUDE_INSTALL_DIR}
    COMPONENT Headers
    FILES_MATCHING PATTERN "*.h"
)

if(MSVC OR WIN32)
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
        DESTINATION ${LEGAL_INSTALL_DIR}
    )
else()
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
    DESTINATION ${LEGAL_INSTALL_DIR}/licenses
    )
endif()

# CPack Config Stuff goes here
# if we are being called for node we need to build the wrapper
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenRPG")
set(CPACK_PACKAGE_VENDOR "OpenRPG")
set(CPACK_PACKAGE_NAME "OpenRPG")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nick Gaulke") #required
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${OpenRPG_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${OpenRPG_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${OpenRPG_VERSION_TWEAK})
set(CPACK_PACKAGE_CONTACT "contact@openrpg.io")
set(CPACK_PACKAGE_CHECKSUM SHA512)
set(CPACK_COMPONENT_MODULES_REQUIRED ON)
set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
if((MSVC OR WIN32) AND NOT UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "NSIS;TGZ;ZIP")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenRPG")
    set(CPACK_PACKAGE_ICON "")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\openrpg.exe")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Libraries and CLIs")
    set(CPACK_NSIS_HELP_LINK "https:\\\\\\\\openrpg.io")
    set(CPACK_NSIS_URL_INFO_ABOUT "https:\\\\\\\\openrpg.io\\\\about\\\\history")
    set(CPACK_NSIS_CONTACT "@incomingstick 🐥")
    set(CPACK_NSIS_MODIFY_PATH ON)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CPACK_SYSTEM_NAME win64)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(CPACK_SYSTEM_NAME win32)
    else()
        # default to win64 if we cannot use CMAKE_SIZEOF_VOID_P for some reason
        set(CPACK_SYSTEM_NAME win64)
    endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
elseif(UNIX AND NOT (MSVC OR WIN32) AND NOT APPLE)
    set(CPACK_GENERATOR "DEB;STGZ;TGZ;TXZ;TZ")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "cmake (>= 3.7.2-1), gcc (>= 4.8.3.0-1)")
    set(CPACK_DEBIAN_PACKAGE_NAME "openrpg-libs")
    set(CPACK_SET_DESTDIR ON)
elseif(APPLE AND NOT (MSVC OR WIN32) AND NOT UNIX)
    set(CPACK_GENERATOR "OSXX11;PackageMaker;productbuild;TGZ;ZIP")
endif((MSVC OR WIN32) AND NOT UNIX AND NOT APPLE)
if (CMAKE_JS_VERSION)
    set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${OpenRPG_VERSION_MAJOR}.${OpenRPG_VERSION_MINOR}.${OpenRPG_VERSION_TWEAK}-${NODE_RUNTIME}-${NODE_RUNTIMEVERSION}-${CPACK_SYSTEM_NAME})
endif(CMAKE_JS_VERSION)
include(CPack)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()


set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

enable_testing()

# tests directory
add_subdirectory("test/" EXCLUDE_FROM_ALL)
