/*
roll - die.cpp
Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <functional>
#include <random>

#include "utils.h"
#include "die.h"

using namespace std;

Die::Die() {
    MAX = 6;
}

Die::Die(int max)
    :MAX(max) {

}

Die::~Die() {

}

int Die::roll() {
    return roll(MAX);
}

int Die::roll(int max) {
    default_random_engine generator;

    generator.seed(time(NULL));

    uniform_int_distribution<int> dist(1, max);
    auto fn_rand = std::bind(dist, generator);

    for(int i = 0; i < fn_rand(); i++) fn_rand();

    return fn_rand();
}