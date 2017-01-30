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
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, MAX);

    int ret = dist(mt);

    /* prints die rolls in the form "dX -> N" */
    verbose("d"+ to_string(MAX) +" -> "+ to_string(ret));

    return ret;
}