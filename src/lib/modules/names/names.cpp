/*
name-generator - names.cpp
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
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

NameGenerator::NameGenerator(string race, string gender, string subrace)
    :race(race),
     subrace(subrace),
     gender(gender) {
    location = ASSET_LOC;
    location += "/names";

    if(!subrace.empty()) this->subrace = "/" + subrace;
}

string NameGenerator::make_name() {
    string ret(make_first() + " " + make_last());

    return ret;
}

string NameGenerator::make_first() {
    string loc(location+"/"+ race + subrace +"/"+gender);

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
    }

    return "NULL";
}

string NameGenerator::make_last() {
    string loc(location +"/"+ race + subrace +"/last");

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
        // cannot be opened then something serious has gone wrong
    }

    return "NULL";
}