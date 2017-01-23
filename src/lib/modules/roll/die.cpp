/*
roll - die.cpp

Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <functional>
#include <random>

#ifdef HAVE_GETPID

#include <sys/types.h>
#include <unistd.h>

#endif

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

/* sets generator.seed() usig the current
    time bitwise anded with the PID*/
#ifdef HAVE_GETPID

    generator.seed(time(NULL) & getpid());

#else

    generator.seed(time(NULL));

#endif

    uniform_int_distribution<int> dist(1, MAX);
    auto fn_rand = std::bind(dist, generator);

    for(int i = 0; i < fn_rand() * MAX; i++) fn_rand();

    int ret = fn_rand();

    /* prints die rolls in the form "dX -> N" */
    verbose("d"+ to_string(MAX) +" -> "+ to_string(ret));

    return ret;
}