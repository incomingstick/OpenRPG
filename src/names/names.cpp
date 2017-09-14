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
#include <random>
#include <functional>
#include <algorithm>

#include "core/config.h"
#include "core/utils.h"
#include "names/names.h"

using namespace std;

string make_location_valid(const string& loc) {
    // string ret = loc;

    // TODO: test what location we are looking for
    // to ensure it is a valid list
    
    return loc;
}

NameGenerator::NameGenerator(string race):
    NameGenerator(race, "")    
{
    transform(race.begin(), race.end(), race.begin(), ::tolower);

    // this->race = race;
    // this->gender = "";

    // location = ASSET_LOC;
    // location += "/names";
}

NameGenerator::NameGenerator(string _race, string _gender)
    :location(ASSET_LOC), race(_race), gender(_gender) 
{
    transform(race.begin(), race.end(), race.begin(), ::tolower);
    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    location += "/names";

    // this->race = race;
    // this->gender = gender;
    
    // location = ASSET_LOC;
    // location += "/names";
}

string NameGenerator::make_name() {
    string ret;

    if(!gender.empty()) {
        ret += make_first();

        ret += " ";
    }

    ret += make_last();
    
    return ret;
}

/* returns "NULL" if the file doesn't exist */
string NameGenerator::make_first() {
    string loc;

    if(gender.empty()) {
        loc = make_location_valid(location +"/"+ race +".lst");
    } else {
        loc = make_location_valid(location +"/"+ race +"/"+ gender +".lst");
    }

    ifstream file(loc.c_str());

    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(safeGetline(file, line)) {
            if(!line.empty())
                lines.push_back(line);
        }
        // while(safeGetline(file, line)) lines.push_back(line);
        // while(lines[lines.size()-1].empty()) lines.pop_back();

        const int select = random(0, lines.size() - 1);

        file.close();

        return lines[select];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cerr << "unable to open file " << loc << endl;
    }

    file.close();

    return "NULL";
}

/* returns "NULL" if the file doesn't exist */
string NameGenerator::make_last() {
    string loc = make_location_valid(location +"/"+ race +"/last.lst");

    ifstream file(loc.c_str());
    
    if(file.is_open()) {
        string line;
        vector<string> lines;

        while(safeGetline(file, line)) {
            if(!line.empty())
                lines.push_back(line);
        }

        // while(safeGetline(file, line)) lines.push_back(line);
        // while(lines[lines.size()-1].empty()) lines.pop_back();

        const int select = random(0, lines.size() - 1);

        file.close();

        return lines[select];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong
        cerr << "unable to open file " << loc << endl;
    }
    
    return "NULL";
}
