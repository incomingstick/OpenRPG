# source directories
include_directories("${CMAKE_SOURCE_DIR}/src/lib")

set(TEST_COMMON_SRC
        ${CMAKE_SOURCE_DIR}/src/lib/utils.cpp
)

# this flag allows mdoules to understand we are in a testing mode
# #define TESTING_FLAG
add_definitions(-DTESTING_FLAG)

add_definitions(-DTESTING_ASSET_LOC="${CMAKE_SOURCE_DIR}/src/assets")

# start name-generator testing here
set(CUR_TEST generator-test)

set(CUR_TEST_SRC
        ${CUR_TEST}.cpp
        ${CMAKE_SOURCE_DIR}/src/lib/modules/names/generator.cpp
)

add_executable(${CUR_TEST} ${TEST_COMMON_SRC} ${CUR_TEST_SRC})

macro(do_test test arg1 arg2)
  add_test(${test}-${arg1}-${arg2} ${test} ${arg1} ${arg2})
  add_dependencies(check ${test})
endmacro(do_test)

do_test(${CUR_TEST} dwarf male)
do_test(${CUR_TEST} dwarf female)