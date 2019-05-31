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
#   ifndef roll_parser_EXPORTS
#       define roll_parser_EXPORTS
#   endif
#   include "roll/exports/parser_exports.h"
#else
#   define ROLL_PARSER_EXPORT
#endif

namespace ORPG {
    class ROLL_PARSER_EXPORT Die {
        private:
            const int MAX = 20;
        public:
            Die(int max):MAX(
                    /* If max is less than 2, set MAX to 2; else set MAX to max.
                    * Ensures we don't have nonsense like a 1- or 0-sided die
                    * (or a negative-sided die) */
                    (max < 2) ? 2
                            : max
                    ){};

            int roll() {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution<int> dist(1, MAX);

                auto ret = dist(mt);

                /* verbosely prints die rolls in the form "dX -> N" */
                if(Core::VB_FLAG) printf("d%i -> %i\n", MAX, ret);

                return ret;
            }
    };
}

#endif /* SRC_DIE_H_ */
