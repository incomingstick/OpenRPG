set(MODULE_DIR "${CMAKE_SOURCE_DIR}/src/lib/modules")

# source directories
include_directories("${CMAKE_SOURCE_DIR}/src/lib"
                    "${MODULE_DIR}/names"
                    "${MODULE_DIR}/roll"
)

set(TEST_COMMON_SRC
        #${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

# this flag allows mdoules to understand we are in a testing mode
# #define TESTING_FLAG
add_definitions(-DTESTING_FLAG)

add_definitions(-DTESTING_ASSET_LOC="${CMAKE_SOURCE_DIR}/src/assets")

# start name-generator testing here
set(CUR_TEST generator-test)

set(CUR_TEST_SRC
        ${CUR_TEST}.cpp
        ${MODULE_DIR}/names/names.cpp
)

add_executable(${CUR_TEST} ${TEST_COMMON_SRC} ${CUR_TEST_SRC})
target_link_libraries(${CUR_TEST} utils)

macro(do_test test arg1 arg2)
  add_test(${test}-${arg1}-${arg2} ${test} ${arg1} ${arg2})
  add_dependencies(check ${test})
endmacro(do_test)

# should we really test all combinations here?
do_test(${CUR_TEST} dwarf male)
do_test(${CUR_TEST} dwarf female)

# start name-generator testing here
set(CUR_TEST roll-parser-test)

set(CUR_TEST_SRC
        ${CUR_TEST}.cpp
        ${MODULE_DIR}/roll/roll-parser.cpp
)

add_executable(${CUR_TEST} ${TEST_COMMON_SRC} ${CUR_TEST_SRC})
target_link_libraries(${CUR_TEST} utils)

macro(do_test test)
  add_test(${test}-die ${test})
  add_dependencies(check ${test})
endmacro(do_test)

do_test(${CUR_TEST})