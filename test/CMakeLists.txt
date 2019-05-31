#
#   TODO: We really should write a solid test suite here to make testing
#           easier and more defined. NOTE: look in to <assert.h>
#
############################################################################

# source directories
include_directories("${CMAKE_SOURCE_DIR}/include/")

# this flag allows mdoules to understand we are in a testing mode
# #define TESTING_FLAG
add_definitions(-DTESTING_FLAG)

add_definitions(-DTESTING_ASSET_LOC="${DATA}")

# start name-generator testing here
set(CUR_TEST name-generator-test)

set(CUR_TEST_SRC
    ${CUR_TEST}.cpp
)

add_executable(${CUR_TEST} ${TEST_COMMON_SRC} ${CUR_TEST_SRC})
target_link_libraries(${CUR_TEST} utils names)

macro(do_test test arg1 arg2)
    add_test(${test}-${arg1}-${arg2} ${test} ${arg1} ${arg2})
    add_dependencies(check ${test})
endmacro(do_test)

# dwarf
do_test(${CUR_TEST} dwarf male)
do_test(${CUR_TEST} dwarf female)

# human
do_test(${CUR_TEST} human male)
do_test(${CUR_TEST} human female)

# start roll-parser testing here
set(CUR_TEST roll-parser-test)

set(CUR_TEST_SRC
    ${CUR_TEST}.cpp
)

add_executable(${CUR_TEST} ${TEST_COMMON_SRC} ${CUR_TEST_SRC})
target_link_libraries(${CUR_TEST} utils roll-parser)

macro(do_test test)
    add_test(${test}-die ${test})
    add_dependencies(check ${test})
endmacro(do_test)

do_test(${CUR_TEST})
