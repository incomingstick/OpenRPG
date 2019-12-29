/*
generator-test.cpp - Test program for name-generator
Created on: Dec 1, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>

#include "names/names.h"

using namespace ORPG;

int main(int argc, char* argv[]) {
    std::string race;
    std::string gender;

    if(argc == 3) {
        race = argv[1];
        gender = argv[2];
    } else {
        race = argv[1];
        gender = "";
    }

    NameGenerator gen(race, gender, TESTING_ASSET_LOC);

    std::string first;
    std::string last;
    std::string full;

    for(int i = 0; i < 10000; i++) {
        first = gen.make_first();
        last = gen.make_last();
        full = gen.make_name();

        // Check first name function
        if(first.empty()) return 1;

        // Check last name function
        if(last.empty() && race_has_last(race)) return 1;

        // Check full name function
        if(full.empty()) return 1;
    }

    return 0;
}