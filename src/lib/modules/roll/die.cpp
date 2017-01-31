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
    output("created 1d"+to_string(MAX), 0);
}

Die::Die(int max)
    :MAX(max) {
    output("created 1d"+to_string(MAX), 0);
}

Die::~Die() {

}

int Die::roll() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, MAX);

    int ret = dist(mt);

    /* verbosely prints die rolls in the form "dX -> N" */
    output("d"+ to_string(MAX) +" -> "+ to_string(ret), VB_CODE);

    return ret;
}