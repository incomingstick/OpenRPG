/*
roll - die.h
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_DIE_H_
#define SRC_DIE_H_

#include <random>
#include <functional>

#include "core/utils.h"

#ifdef _WIN32
#   include "roll/exports/parser_exports.h"
#else
#   define ROLL_PARSER_EXPORT
#endif

namespace ORPG {
    class ROLL_PARSER_EXPORT Die {
        private:
            //TODO(incomingstck): MAX does not need to be private, as it is const
        public:
            Die(int max = 20):MAX(
                    /* If max is less than 2, set MAX to 2; else set MAX to max.
                    * Ensures we don't have nonsense like a 1- or 0-sided die
                    * (or a negative-sided die) */
                    (max < 2) ? 2
                            : max
                    ){};

            /**
             * @desc roll creates a std::random_device and a std::mt199377 via that
             * random device. We will then use uniform int distribution to generate
             * psuedo-random numbers with mt19937. If VB_FLAG is true, it will print
             * to stdout.
             * 
             * @return int - a psuedo-random number between 1 and MAX (inclusive)
             **/
            int roll() {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution<int> dist(1, MAX);

                auto ret = dist(mt);

                /* verbosely prints die rolls in the form "dX -> N" */
                if(Core::VB_FLAG) printf("d%i -> %i\n", MAX, ret);

                return ret;
            }

            /* The highest the die could possibly roll */
            const int MAX = 20;
    };
}

#endif /* SRC_DIE_H_ */
