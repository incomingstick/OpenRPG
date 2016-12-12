/*
 * generator.h
 *
 *  Created on: Nov 10, 2016
 *      Author: Nick Gaulke
 */

#ifndef SRC_GENERATOR_H_
#define SRC_GENERATOR_H_

class NameGenerator {
    private:
        std::string race;
        std::string gender;
        int random(int min, int max);
    public:
        NameGenerator(std::string race, std::string gender);
        ~NameGenerator();
        std::string make_name();
        std::string make_first();
        std::string make_last();
};

#endif /* SRC_GENERATOR_H_ */
