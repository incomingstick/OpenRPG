
/*
name-generator - names.h
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_GENERATOR_H_
#define SRC_GENERATOR_H_

class NameGenerator {
private:
    std::string location;

public:
    std::string race;
    std::string subrace;
    std::string gender;

    NameGenerator(std::string race = "dwarf");
    NameGenerator(std::string race, std::string gender);

    std::string make_name();
    std::string make_first();
    std::string make_last();
};

#endif /* SRC_GENERATOR_H_ */
