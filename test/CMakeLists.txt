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

macro(do_test test arg1)
    set(ExtraMacroArgs ${ARGN})

    # Get the length of the list
    list(LENGTH ExtraMacroArgs NumExtraMacroArgs)

    # Execute the following block only if the length is > 0
    if(NumExtraMacroArgs GREATER 0)
        foreach(ExtraArg ${ExtraMacroArgs})
            add_test(${test}-${arg1}-${ExtraArg} ${test} ${arg1} ${ExtraArg})
        endforeach()
    else()
        add_test(${test}-${arg1} ${test} ${arg1})
    endif()

    add_dependencies(check ${test})
endmacro(do_test)

# NOTE(incomingstick): please keep this alphabetical
# aarakocra
do_test(${CUR_TEST} aarakocra)

# changeling
do_test(${CUR_TEST} changeling)

# dragonborn
do_test(${CUR_TEST} dragonborn male)
do_test(${CUR_TEST} dragonborn female)

# dwarf
do_test(${CUR_TEST} dwarf male)
do_test(${CUR_TEST} dwarf female)

# elf
do_test(${CUR_TEST} elf male)
do_test(${CUR_TEST} elf female)

# gnome
do_test(${CUR_TEST} gnome male)
do_test(${CUR_TEST} gnome female)

# goliath
do_test(${CUR_TEST} goliath male)
do_test(${CUR_TEST} goliath female)

# half-elf
do_test(${CUR_TEST} half-elf male)
do_test(${CUR_TEST} half-elf female)

# half-orc
do_test(${CUR_TEST} half-orc male)
do_test(${CUR_TEST} half-orc female)

# halfling
do_test(${CUR_TEST} halfling male)
do_test(${CUR_TEST} halfling female)

# human
do_test(${CUR_TEST} human male)
do_test(${CUR_TEST} human female)

# kalashtar
do_test(${CUR_TEST} kalashtar male)
do_test(${CUR_TEST} kalashtar female)

# kor
do_test(${CUR_TEST} kor male)
do_test(${CUR_TEST} kor female)

# minotaur
do_test(${CUR_TEST} minotaur male)
do_test(${CUR_TEST} minotaur female)

# shifter
do_test(${CUR_TEST} shifter)

# tiefling
do_test(${CUR_TEST} tiefling male)
do_test(${CUR_TEST} tiefling female)

# warforged
do_test(${CUR_TEST} warforged)

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
