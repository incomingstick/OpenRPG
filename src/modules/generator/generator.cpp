/*
 * generator.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: Tumblr
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include "generator.h"

using namespace std;

NameGenerator::NameGenerator(string race, string gender)
    :race(race),
     gender(gender) {
}

NameGenerator::~NameGenerator() {
    // TODO nothing yet. May never be anything TODO.
}

string NameGenerator::make_name() {
    string ret;

    string first = make_first();
    string last = make_last();

    ret = first + " " + last;

    return ret;
}

string NameGenerator::make_first() {
    string loc("assets/names/"+race+"/"+gender);
    
    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(getline(file, line)) lines.push_back(line);

        uniform_int_distribution<int> dist(0, lines.size());
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

        while(getline(file, line)) lines.push_back(line);

        uniform_int_distribution<int> dist(0, lines.size());
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