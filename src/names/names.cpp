/*
names - names.cpp
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
using namespace ORPG;

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
 * @desc this function takes in a file path as a string, opens an input file
 * stream, and reads a random line from it. If it cannot open the filePath it
 * returns an empty string.
 *
 * NOTE(incomingstick): Is is worth putting this in a header and making it a
 * part of the public lib?
 *
 * @param string filePath - the file path to read a random line from
 * @return string - a string containing the random line read from. If the file
 * could not be opened, it returns an empty string
 **/
string rand_line_from_file(string filePath) {
    ifstream file(filePath.c_str());

    if(file.is_open()) {
        string read;
        vector<string> buff;

        while(Utils::safeGetline(file, read)) {
            if(!read.empty())
                buff.push_back(read);
        }

        file.close();

        return buff[Utils::randomInt(0, buff.size() - 1)];
    } else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cerr << "unable to open file " << filePath << endl;
    }

    file.close();

    return "";
}

namespace ORPG {
    namespace Names {
        void PRINT_VERSION_FLAG() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        void PRINT_HELP_FLAG() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: name-generator [options] \"[RACE | SUBRACE]\" [GENDER]\n"
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

        void PRINT_BASIC_VERSION() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
        }

        void PRINT_BASIC_HELP() {
            fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: name-generator \"[RACE | SUBRACE]\" [GENDER]\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: <https://www.openrpg.io>\n"
                "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
        }
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
        /* NOTE(incomingstsick): lets try and keep this in alphabetical order */
        if(race == "aarakocra")     return false;
        if(race == "changeling")    return false;
        if(race == "half-orc")      return false;
        if(race == "kor")           return false;
        if(race == "shifter")       return false;
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
        /* NOTE(incomingstsick): lets try and keep this in alphabetical order */
        if(race == "aarakocra")     return false;
        if(race == "changeling")    return false;
        if(race == "shifter")       return false;
        if(race == "warforged")     return false;
        else return true;
    }

    /**
     * @desc Constructor for NameGenerator that is passed two optional
     * arguments. It sets race equal to _race and sets gender to _gender.
     *
     * @param string _race = "dwarf" - the race to use. defaults to dwarf
     * @param string _gender = "" - the gender of our race. defaults to empty
     **/
    NameGenerator::NameGenerator(string _race, string _gender)
        :location(Core::DATA_LOCATION()), race(_race), raceFile(_race), gender(_gender) {
        location += "/names";

        Initialize();
    }

    /**
     * @desc Constructor for NameGenerator that is passed three arguments.
     * It sets race equal to _race, gender to _gender, and location to
     * _location
     *
     * CAUTION(incomingstick): By creating this constructor we are allowing an
     * end user to specify the location the namelist we will read from. It is
     * extremely important we explore this further. I do think this could prove
     * a beneficial feature, if we allow end users to specify namelists.
     *
     * NOTE(incomingstick): I am creating this function specifically to help
     * the test suite. When testing on a fresh system, we are built before we
     * test, but the release builds defines ASSET_LOC as:
     *      *nix systems: "/usr/local/data/openrpg"
     *      Windows systems: TODO(incomingstick)
     * Because of this, it attempts to check a folder that has not been installed
     * yet, and we need a way for NameGenerator to use our source data folder.
     *
     * @param string _race - the race to use
     * @param string _gender - the gender of our race
     * @param string _location - the toplevel location to check for lst files.
     * note that /names will be appended to this location
     **/
    NameGenerator::NameGenerator(string _race, string _gender, string _location)
        :location(_location), race(_race), raceFile(_race), gender(_gender) {

        if(location.empty()) {
            location = Core::DATA_LOCATION();
        }

        location += "/names";

        Initialize();
    }

    /**
     * @desc Setter function for the race string of the NameGenerator
     * class
     *
     * @param std::string newRaceStr - a string to set as the new race
     **/
    void NameGenerator::set_race(std::string newRaceStr) {
        race = newRaceStr;
        raceFile = newRaceStr;

        Initialize();
    }

    /**
     * @desc Setter function for the gender string of the NameGenerator
     * class
     *
     * @param std::string newRaceStr - a string to set as the new race
     **/
    void NameGenerator::set_gender(std::string setGenderStr) {
        gender = setGenderStr;

        Initialize();
    }

    /**
     * @desc Initialization for a NameGenerator that is passed no arguments.
     * Initialize cleans up some of the data passed to NameGenerator to ensure
     * we conform to the naming of know races
     **/
    void NameGenerator::Initialize() {
        transform(raceFile.begin(), raceFile.end(), raceFile.begin(), ::tolower);
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);

        /**
         * TODO(incomingstick): improve this logic so it scales, and by doing it this
         * way we are preventing someone from using their own provided "hill dwarf"
         * or "high elf" namelists
         *
         * NOTE(incomingstsick): lets try and keep this in alphabetical order
         **/
        if(raceFile == "half orc")      raceFile = "half-orc";
        if(raceFile == "hill dwarf")    raceFile = "dwarf";
        if(raceFile == "high elf")      raceFile = "elf";

        if(raceFile == "half-elf" || raceFile == "half elf") {
            if(Utils::randomBool()) raceFile = "human";
            else             raceFile = "elf";
        }
    }

    /**
     * @desc Generates a random full name by calling make_first and make_last,
     * checking their outputs, and concatenating a string together. If either
     * make_first or make_last return an emprt string it added to the full
     * name. If the string would be empty, this function returns an empty
     * string
     *
     * @return string - a concatenated string containing a full name. If no
     * string could be produced it will return an empty string
     **/
    string NameGenerator::make_name() {
        string ret;

        auto first = make_first();
        if(!first.empty()) {
            ret += first;
        }

        auto last = make_last();
        if(!last.empty()) {
            ret += " ";
            ret += last;
        }

        if(ret.empty()) {
            return "";
        } else return ret;
    }

    /**
     * @desc Generates a random first name by reading from a random namelist
     * in the given location with the given race. If the race is gendered, but
     * no gender is currently set, we will randomly set gender to either female
     * or male. If no name can be generated this function will return an empty
     * string
     *
     * @return string - a string containing a first name. If no name could be
     * produced it will return an empty string.
     **/
    string NameGenerator::make_first() {
        bool gendered = race_is_gendered(raceFile);
        if(gendered && gender.empty()) {
            if(Utils::randomBool()) gender = "female";
            else gender = "male";
        } else if(!gendered) {
            gender = "";
        }

        string loc;

        if(gender.empty()) {
            loc = make_valid_location(location, raceFile);
        } else {
            loc = make_valid_location(location, gender, raceFile);
        }

        return rand_line_from_file(loc);
    }

    /**
     * @desc Generates a random last name by reading from a random namelist
     * in the given location with the given race. If no name can be generated
     * this function will return an empty string
     *
     * @return string - a string containing a last name. If no name could be
     * produced it will return an empty string.
     **/
    string NameGenerator::make_last() {
        if(!race_has_last(raceFile)) {
            return "";
        }

        auto loc = make_valid_location(location, "last", raceFile);

        return rand_line_from_file(loc);
    }
}
