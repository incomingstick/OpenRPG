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
        protected:
            const int _MAX = 20;
        public:
            Die(int max = 20):_MAX(
                    /* If max is less than 2, set MAX to 2; else set MAX to max.
                    * Ensures we don't have nonsense like a 1- or 0-sided die
                    * (or a negative-sided die) */
                    (max < 2) ? 2
                            : max
                    ){};

            /**
             * @desc randomly generate an int between 1 and _MAX, where MAX is the value
             * that was passed to the Die when it was constructed. The result is generated
             * by using a random_device to seed a Mersenne Twister engine that generates 
             * uniformly distributed integers between 1 and _MAX.
             * between 1 and _MAX
             * @return int - a pesudo random integer between 1 and _MAX
             */
            int roll() {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution<int> dist(1, _MAX);

                auto ret = dist(mt);

                /* verbosely prints die rolls in the form "dX -> N" */
                if(Core::VB_FLAG) printf("d%i -> %i\n", _MAX, ret);

                return ret;
            }

            /**
             * @desc returns _MAX, the number of sides this dice has. This is the same as
             * the max value that could potentially be rolled.
             * @return int - the maximum value that could be returned by this die
             */
            const int MAX() { return _MAX; }
    };
}

#endif /* SRC_DIE_H_ */
