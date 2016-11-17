/*
 * generator.h
 *
 *  Created on: Nov 10, 2016
 *      Author: Tumblr
 */

#ifndef SRC_GENERATOR_H_
#define SRC_GENERATOR_H_

#include <string>

class NameGenerator {
    private:
        std::string race;
        std::string gender;
    public:
        NameGenerator(std::string race, std::string gender);
        ~NameGenerator();
        std::string get_name();
        std::string get_first();
        std::string get_last();
};

#endif /* SRC_GENERATOR_H_ */
