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
        void NAMES_EXPORT print_version_flag();
        void NAMES_EXPORT print_help_flag();
        void NAMES_EXPORT print_basic_version();
        void NAMES_EXPORT print_basic_help();
    }

    /**
     * An NameGenerator allows for the random generation of names. A name is
     * determined by a given race and optionally a gender and produces a name
     * with both a first and last name by calling make_name(). You can get an
     * independant first and last name by calling make_first() and make_last()
     * respectively.
     **/
    class NAMES_EXPORT NameGenerator {
    private:
        /* the toplevel location to use when building our namelist */
        std::string location;

    public:
        /* the race to use when selecting our namelist */
        std::string race;

        /* the gender to use when selecting our namelist */
        std::string gender;

        /**
         * @desc Constructor for NameGenerator that is passed two optional 
         * arguments. It sets race equal to _race and sets gender to _gender.
         * 
         * @param string _race = "dwarf" - the race to use. defaults to dwarf 
         * @param string _gender = "" - the gender of our race. defaults to empty
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
         * @desc Generates a random full name by calling make_first and make_last,
         * checking their outputs, and concatenating a string together. If either
         * make_first or make_last return "\0", it is not added to the string.
         * If the string would be empty, this function returns "\0"
         * 
         * @return string - a concatenated string containing a full name. If no
         * string could be produced it will return "\0"
         **/
        std::string make_name();

        /**
         * @desc Generates a random first name by reading from a random namelist
         * in the given location with the given race. If the race is gendered, but
         * no gender is currently set, we will randomly set gender to either female
         * or male. If no name can be generated this function will return "\0"
         * 
         * @return string - a string containing a first name. If no name could be
         * produced it will return "\0" as a string.
         **/
        std::string make_first();

        /**
         * @desc Generates a random last name by reading from a random namelist
         * in the given location with the given race. If no name can be generated
         * this function will return "\0"
         * 
         * @return string - a string containing a last name. If no name could be
         * produced it will return "\0" as a string.
         **/
        std::string make_last();
    };
}

#endif /* SRC_GENERATOR_H_ */
