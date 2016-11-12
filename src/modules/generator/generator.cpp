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
#include "generator.h"

using namespace std;

NameGenerator::NameGenerator(string race, string gender) {
    this->race = race;
    this->gender = gender;
}

NameGenerator::~NameGenerator() {
    // TODO nothing yet. May never be anything TODO.
}

string NameGenerator::get_name() {
    string first = get_first();
    string last = get_last();

    return first + " " + last;
}

string NameGenerator::get_first() {
    string ret = "";
    string loc("assets/names/"+race+"/"+gender);
    
    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(getline(file, line)) lines.push_back(line);

        int select = rand() % lines.size();

        cout << "CALLED GET_FIRST()" << endl;

        ret = lines[select];

        file.close();
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cerr << loc << " COULD NOT BE OPENED" << endl;
    }
    
    return ret;
}

string NameGenerator::get_last() {
    string ret = "";
    string loc("assets/names/"+race+"/last");
    
    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(getline(file, line)) lines.push_back(line);

        int select = rand() % lines.size();

        cout << "CALLED GET_LAST()" << endl;

        ret = lines[select];

        file.close();
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cerr << loc << " COULD NOT BE OPENED" << endl;
    }
    
    return ret;
}