/*
name-generator - names.cpp
Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <functional>
#include <random>

#include "config.h"
#include "utils.h"
#include "names.h"

using namespace std;

#ifdef TESTING_FLAG
#undef ASSET_LOC
#define ASSET_LOC TESTING_ASSET_LOC
#endif

NameGenerator::NameGenerator(string race, string gender)
    :race(race),
     gender(gender) {
    location = ASSET_LOC;
    location += "/names";
    output("top location: "+location, VB_CODE);
    output("NameGenerator with "+race+" "+gender+" created", VB_CODE);
}

NameGenerator::~NameGenerator() {
    // TODO nothing yet. May never be anything TODO.
}

string NameGenerator::make_name() {
    string ret(make_first() + " " + make_last());

    return ret;
}

string NameGenerator::make_first() {
    string loc(location+"/"+race+"/"+gender);
    
    output("opening location: "+loc, VB_CODE);

    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(safeGetline(file, line)) lines.push_back(line);
        while(lines[lines.size()-1].empty()) lines.pop_back();

        int select = random(0, lines.size() - 1);

        file.close();

        return lines[select];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        output(loc + " could not be opened", EXIT_FAILURE);
    }

    return "NULL";
}

string NameGenerator::make_last() {
    string loc(location+"/"+race+"/last");

    output("opening location: "+ loc, VB_CODE);

    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(safeGetline(file, line)) lines.push_back(line);
        while(lines[lines.size()-1].empty()) lines.pop_back();

        int select = random(0, lines.size() - 1);   // TODO (fix) only generating a static number
                                                    // it appears to be system specific

        file.close();

        return lines[select];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        output(loc + " could not be opened", EXIT_FAILURE);
    }

    return "NULL";
}