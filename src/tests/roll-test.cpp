/*
roll.cpp - Test program for roll module
Created on: Dec 1, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>
#include <string>
#include <map>
#include <random>

#include "die.h"

using namespace std;

/* taken from http://en.cppreference.com/w/cpp/numeric/random/random_device
    to test random_device output */
int main() {
    std::random_device rd;
    std::map<int, int> hist;

    Die d6(6);

    for (int n = 0; n < 20000; ++n) {
        ++hist[d6.roll()]; // note: demo only: the performance of many 
                          // implementations of random_device degrades sharply
                          // once the entropy pool is exhausted. For practical use
                          // random_device is generally only used to seed 
                          // a PRNG such as mt19937
    }
    
    for (auto p : hist) {
        std::cout << p.first << " : " << std::string(p.second/100, '*') << '\n';
    }
}