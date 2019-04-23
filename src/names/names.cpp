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

namespace ORPG {
    namespace Names {
        void print_version_flag() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        void print_help_flag() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: name-generator [options] [RACE | SUBRACE] [GENDER]\n"
                        "\t-h --help                   Print this help screen\n"
                        "\t-v --version                Print version info\n"
                        "\t-V --verbose                Verbose program output\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        void print_basic_version() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
        }

        void print_basic_help() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: name-generator [RACE | SUBRACE] [GENDER]\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
        }
    }

    NameGenerator::NameGenerator(string _race):
        NameGenerator(_race, "")    
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

            const int select = randomInt(0, lines.size() - 1);

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

            const int select = randomInt(0, lines.size() - 1);

            file.close();

            return lines[select];
        } else {
            // TODO: Raise an exception here, if an asset file
            // cannot be opened then something serious has gone wrong
            cerr << "unable to open file " << loc << endl;
        }
        
        return "NULL";
    }
}
