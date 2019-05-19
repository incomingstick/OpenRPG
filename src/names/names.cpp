/*
name-generator - names.cpp
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
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

/**
 * TODO: test what location we are looking for to ensure it is a valid list
 * 
 * NOTE(incomingstick): For security reasons we likely should look at
 * setting some form of fallback location in the event that we cannot
 * fix the given location.
 **/
string make_valid_location(const string baseLoc, string nameList, string raceFolder = "") {
    string ret = baseLoc + "/";

    if(!raceFolder.empty()) {
        ret += raceFolder + "/";
    }

    ret += nameList + ".lst";

    return ret;
}

/**
 * @desc this function takes in a string value representing a race and checks
 * against a hard coded list of races without last names, to determine if it
 * would have a last name list in our data folder.
 * 
 * NOTE(incomingstick): Is is worth putting this in a header and making it a
 * part of the public lib?
 * 
 * @param string race - the race to check if it would have a last name list
 * @return bool - a boolean value containing weather the given race would
 *                  have a last name list
 **/
bool race_has_last(string race) {
    if(race == "aarakocra")     return false;
    if(race == "changeling")    return false;
    if(race == "kor")           return false;
    if(race == "warforged")     return false;
    else return true;
}

/**
 * @desc this function takes in a string value representing a race and checks
 * against a hard coded list of races with gendered lists, to determine if it
 * would have a gendered name list in our data folder.
 * 
 * NOTE(incomingstick): Is is worth putting this in a header and making it a
 * part of the public lib?
 * 
 * @param string race - the race to check if it would have a gendered name list
 * @return bool - a boolean value containing weather the given race would
 *                  have a gendered name list
 **/
bool race_is_gendered(string race) {
    if(race == "dwarf")     return true;
    if(race == "goliath")   return true;
    if(race == "halfling")  return true;
    if(race == "human")     return true;
    if(race == "kor")       return true;
    if(race == "minotaur")  return true;
    if(race == "tiefling")  return true;
    else return false;
}

namespace ORPG {
    namespace Names {
        void print_version_flag() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        void print_help_flag() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: name-generator [options] [RACE | SUBRACE] [GENDER]\n"
                        "\t-h --help                   Print this help screen\n"
                        "\t-v --version                Print version info\n"
                        "\t-V --verbose                Verbose program output\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: <https://www.openrpg.io>\n"
                "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        void print_basic_version() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
        }

        void print_basic_help() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: name-generator [RACE | SUBRACE] [GENDER]\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: <https://www.openrpg.io>\n"
                "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
        }
    }

    NameGenerator::NameGenerator(string _race, string _gender)
        :location(ASSET_LOC), race(_race), gender(_gender) {
        transform(race.begin(), race.end(), race.begin(), ::tolower);
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
        location += "/names";
    }

    /**
     * CAUTION(incomingstick): By creating this constructor we are allowing an
     * end user to specify the location the namelist we will read from. It is
     * extremely important we explore this further. I do think this could prove
     * a beneficial feature, if we allow end users to specify namelists.
     *
     * NOTE(incomingstick): I am creating this function specifically to help
     * the test suite. When testing on a fresh system, we are built before we
     * test, but the release builds defines ASSET_LOC as:
     *      "/usr/local/data/openrpg"
     * Because of this, it attempts to check a folder that has not been installed
     * yet, and we need a way for NameGenerator to use our source data folder.
     **/
    NameGenerator::NameGenerator(string _race, string _gender, string location)
        :location(location), race(_race), gender(_gender) {
        transform(race.begin(), race.end(), race.begin(), ::tolower);
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
        location += "/names";
    }

    string NameGenerator::make_name() {
        string ret;

        auto first = make_first();
        if(first != "NULL") {
            ret += first;
            ret += " ";
        }

        auto last = make_last();
        if(last != "NULL") {
            ret += last;
        }
        
        if(ret.empty()) {
            return NULL;
        } else return ret;
    }

    /* returns "NULL" if the file doesn't exist */
    string NameGenerator::make_first() {
        if(race_is_gendered(race) && gender.empty()) {
            if(randomBool()) gender = "female";
            else gender = "male";
        }

        string loc;

        if(gender.empty()) {
            loc = make_valid_location(location, race);
        } else {
            loc = make_valid_location(location, gender, race);
        }

        ifstream file(loc.c_str());

        if(file.is_open()) {
            string line;
            vector<string> lines;

            while(safeGetline(file, line)) {
                if(!line.empty())
                    lines.push_back(line);
            }

            file.close();

            return lines[randomInt(0, lines.size() - 1)];
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
        if(!race_has_last(race)) {
            return "NULL";
        }

        string loc = make_valid_location(location, "last", race);

        ifstream file(loc.c_str());

        if(file.is_open()) {
            string line;
            vector<string> lines;

            while(safeGetline(file, line)) {
                if(!line.empty())
                    lines.push_back(line);
            }

            file.close();

            return lines[randomInt(0, lines.size() - 1)];
        } else {
            // TODO: Raise an exception here, if an asset file
            // cannot be opened then something serious has gone wrong
            cerr << "unable to open file " << loc << endl;
        }

        return "NULL";
    }
}
