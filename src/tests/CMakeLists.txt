macro(do_test test arg1 arg2)
  add_test(${test}-${arg2} ${test} ${arg1} ${arg2})
  add_dependencies(check ${test})
endmacro(do_test)

set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# source directories
include_directories("${CMAKE_SOURCE_DIR}"
                    "${CMAKE_SOURCE_DIR}/util"
                    "${CMAKE_SOURCE_DIR}/modules/generator"
)

set(TEST_COMMON_SRC
        ${CMAKE_SOURCE_DIR}/util/utils.cpp
        ${CMAKE_SOURCE_DIR}/modules/generator/generator.cpp
)

set(CUR_TEST generator-test)

add_executable(${CUR_TEST} ${TEST_COMMON_SRC} ${CUR_TEST}.cpp)

do_test(${CUR_TEST} dwarf male)
do_test(${CUR_TEST} dwarf female)