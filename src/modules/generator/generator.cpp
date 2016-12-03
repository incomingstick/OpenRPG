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
#include "utils.h"
#include "generator.h"

using namespace std;

NameGenerator::NameGenerator(string race, string gender)
    :race(race),
     gender(gender) {
    
    generator.seed(time(NULL));
}

NameGenerator::~NameGenerator() {
    // TODO nothing yet. May never be anything TODO.
}

string NameGenerator::make_name() {
    string ret(make_first() + " " + make_last());

    return ret;
}

string NameGenerator::make_first() {
    string loc("assets/names/"+race+"/"+gender);
    
    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(safeGetline(file, line)) lines.push_back(line);
        while(lines[lines.size()-1].empty()) lines.pop_back();

        uniform_int_distribution<int> dist(0, lines.size() - 1);
        int select = dist(generator);

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
    string loc("assets/names/"+race+"/last");

    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(safeGetline(file, line)) lines.push_back(line);
        while(lines[lines.size()-1].empty()) lines.pop_back();

        uniform_int_distribution<int> dist(0, lines.size() - 1);
        int select = dist(generator); // TODO (fix) only generating a static number
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