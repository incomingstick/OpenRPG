/*
 * main.cpp
 *
 *  Created on: Jan 8, 2017
 *  Author: Nick Gaulke
 */
#include <iostream>
#include "die.h"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc > 2) {
        // TODO we should have cla's for testing purposes
        // This will also parse commands like the race
        // and gender of the desired character
    }

    int min = 1, max = 6;

    Die die(min, max);

    cout << die.roll() << endl;

	return 0;
}