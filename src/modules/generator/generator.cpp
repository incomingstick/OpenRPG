/*
 * generator.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: Tumblr
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ctime>
#include "generator.h"

using namespace std;

NameGenerator::NameGenerator(string race, string gender) {
    srand(time(NULL));  

    this->race = race;
    this->gender = gender;
}

NameGenerator::~NameGenerator() {
    // TODO nothing yet. May never be anything TODO.
}

string NameGenerator::get_name() {
    string ret;

    string first = get_first();
    string last = get_last();

    ret = first + " " + last;

    return ret;
}

string NameGenerator::get_first() {
    string loc("assets/names/"+race+"/"+gender);
    
    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(getline(file, line)) lines.push_back(line);

        int select = rand() % lines.size();

        file.close();

        return lines[select];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cerr << loc << " COULD NOT BE OPENED" << endl;
    }

    return "NULL";
}

string NameGenerator::get_last() {
    string loc("assets/names/"+race+"/last");
    
    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(getline(file, line)) lines.push_back(line);

        int select = rand() % lines.size();

        file.close();

        return lines[select];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cerr << loc << " COULD NOT BE OPENED" << endl;
    }

    return "NULL";
}