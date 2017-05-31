/*
roll - die.h
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_DIE_H_
#define SRC_DIE_H_

#include <random>
#include <functional>

#include "core/utils.h"

class Die {
    private:
        const int MAX = 20;
    public:
        Die(int max):MAX(max){};
        int roll() {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(1, MAX);

            int ret = dist(mt);

            /* verbosely prints die rolls in the form "dX -> N" */
            if(VB_FLAG) printf("d%i -> %i\n", MAX, ret);

            return ret;
        }
};

#endif /* SRC_DIE_H_ */
