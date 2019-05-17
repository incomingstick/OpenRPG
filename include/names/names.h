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

    class NAMES_EXPORT NameGenerator {
    private:
        std::string location;

    public:
        std::string race;
        std::string subrace;
        std::string gender;

        NameGenerator(std::string _race = "dwarf");
        NameGenerator(std::string _race, std::string _gender);
        NameGenerator(std::string _race, std::string _gender, std::string _location);
        ~NameGenerator(){};

        std::string make_name();
        std::string make_first();
        std::string make_last();
    };
}

#endif /* SRC_GENERATOR_H_ */
