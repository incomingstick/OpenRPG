/*
 * generator.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: Nick Gaulke
 */
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <functional>
#include <random>
#include "config.h"
#include "utils.h"
#include "generator.h"

using namespace std;

NameGenerator::NameGenerator(string race, string gender)
    :race(race),
     gender(gender) {
    location = ASSET_LOC;
    location += "/names";
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
        cerr << loc << " COULD NOT BE OPENED" << endl;
    }

    return "NULL";
}

string NameGenerator::make_last() {
    string loc(location+"/"+race+"/last");

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
        cerr << loc << " COULD NOT BE OPENED" << endl;
    }

    return "NULL";
}

int NameGenerator::random(int min, int max) {
    default_random_engine generator;

    generator.seed(time(NULL));

    uniform_int_distribution<int> dist(min, max);
    auto fn_rand = std::bind(dist, generator);

    for(int i = 0; i < fn_rand(); i++) fn_rand();

    return fn_rand();
}