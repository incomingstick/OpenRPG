/*
 * die.cpp
 *
 *  Created on: Jan 8, 2017
 *      Author: Nick Gaulke
 */
#include "die.h"

using namespace std;

Die::Die() {
    min = 1;
    max = 6;
}

Die::Die(int min, int max)
    :min(min),
     max(max) {

}

Die::~Die() {

}

int Die::roll() {
    int ret = 0;
    return ret;
}

int roll(int min, int max) {
    int ret = 0;
    return ret;
}