/*
name-generator - names.h
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_GENERATOR_H_
#define SRC_GENERATOR_H_

#ifdef _WIN32
#   ifndef names_EXPORTS
#       define names_EXPORTS
#   endif
#   include "exports/names_exports.h"
#else
#   define NAMES_EXPORT
#endif

namespace ORPG {
    namespace Names {
        /**
         * @desc prints the version info when -V or --version is an argument to the command.
         * This adhears to the GNU standard for version printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void NAMES_EXPORT print_version_flag();

        /**
         * @desc prints the version info when -V or --version is an argument to the command.
         * This adhears to the GNU standard for version printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void NAMES_EXPORT print_help_flag();

        /**
         * @desc prints the version info when version, ver, v, or V are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void NAMES_EXPORT print_basic_version();

        /**
         * @desc prints the help info when help, h, or H are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void NAMES_EXPORT print_basic_help();
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
    bool NAMES_EXPORT race_has_last(std::string race);

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
    bool NAMES_EXPORT race_is_gendered(std::string race);

    /**
     * A NameGenerator allows for the random generation of names. A name is
     * determined by a given race and optionally a gender and produces a name
     * with both a first and last name by calling make_name(). You can get an
     * independant first and last name by calling make_first() and make_last()
     * respectively.
     **/
    class NAMES_EXPORT NameGenerator {
    private:
        /* The toplevel location to use when building our namelist, and may
            contain user input data */
        std::string location;

        /* The race to use when selecting our namelist, and may contain
            user input data */
        std::string race;

        /* The cannonical name of the race file. raceFile will always
            derrive from race */
        std::string raceFile;

        /* The gender to use when selecting our namelist, and may contain
            user input data */
        std::string gender;

        /**
         * @desc Initialization for a NameGenerator that is passed no
         * arguments. Initialize cleans up some of the data passed to
         * NameGenerator to ensure we conform to the naming of know races
         **/
        void Initialize();
    public:
        /**
         * @desc Constructor for NameGenerator that is passed two optional
         * arguments. It sets race equal to _race and sets gender to _gender.
         *
         * @param string _race = "dwarf" - the race to use. defaults to dwarf
         * @param string _gender = "" - the gender of our race. defaults to
         * empty
         **/
        NameGenerator(std::string _race = "dwarf", std::string _gender = "");

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
         *      "/usr/local/data/openrpg"
         * Because of this, it attempts to check a folder that has not been installed
         * yet, and we need a way for NameGenerator to use our source data folder.
         *
         * @param string _race - the race to use
         * @param string _gender - the gender of our race
         * @param string _location - the toplevel location to check for lst files.
         * note that /names will be appended to this location
         **/
        NameGenerator(std::string _race, std::string _gender, std::string _location);

        /**
         * @desc Deconstructor for AbilityScore that is passed no arguments.
         * Currently does nothing, and the compiler handles deconstruction.
         **/
        ~NameGenerator(){};

        /**
         * @desc Getter function for the race string of the NameGenerator
         * class
         *
         * @return std::string - the current race string
         **/
        std::string get_race() { return race; };

        /**
         * @desc Getter function for the gender string of the NameGenerator
         * class
         *
         * @return std::string - the current gender string
         **/
        std::string get_gender() { return gender; };

        /**
         * @desc Setter function for the race string of the NameGenerator
         * class
         *
         * @param std::string newRaceStr - a string to set as the new race
         **/
        void set_race(std::string newRaceStr);

        /**
         * @desc Setter function for the gender string of the NameGenerator
         * class
         *
         * @param std::string newRaceStr - a string to set as the new race
         **/
        void set_gender(std::string setGenderStr);

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
        std::string make_name();

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
        std::string make_first();

        /**
         * @desc Generates a random last name by reading from a random namelist
         * in the given location with the given race. If no name can be generated
         * this function will return an empty string
         *
         * @return string - a string containing a last name. If no name could be
         * produced it will return an empty string.
         **/
        std::string make_last();
    };
}

#endif /* SRC_GENERATOR_H_ */
