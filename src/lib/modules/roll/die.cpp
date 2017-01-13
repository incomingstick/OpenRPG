/*
 * die.cpp
 *
 *  Created on: Jan 8, 2017
 *      Author: Nick Gaulke
 */
#include <functional>
#include <random>
#include "utils.h"
#include "die.h"

using namespace std;

Die::Die()
    :MAX(6) {
    verbose("created 1d"+to_string(MAX));
}

Die::Die(int max)
    :MAX(max) {
    verbose("created 1d"+to_string(MAX));
}

Die::~Die() {

}

int Die::roll() {
    default_random_engine generator;

    generator.seed(time(NULL));

    uniform_int_distribution<int> dist(1, MAX);
    auto fn_rand = std::bind(dist, generator);

    for(int i = 0; i < fn_rand(); i++) fn_rand();

    return fn_rand();
}