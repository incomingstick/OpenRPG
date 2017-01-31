/*
name-generator - names.h
Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_GENERATOR_H_
#define SRC_GENERATOR_H_

class NameGenerator {
    private:
        std::string location;
        std::string race;
        std::string gender;
    public:
        NameGenerator(std::string race = "dwarf", std::string gender = "male");
        ~NameGenerator();
        std::string make_name();
        std::string make_first();
        std::string make_last();
};

#endif /* SRC_GENERATOR_H_ */