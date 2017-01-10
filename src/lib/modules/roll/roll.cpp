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
    int max = 6, out = 0;

    if(argc > 1) {
        // TODO we should have cla's for testing purposes
        // This will also parse commands like the race
        // and gender of the desired character
        for(int i = 1; i < argc; i++) {
            // TODO parse input here
            // e.g: $ roll 1d10
            Die die(max);
            out = die.roll(max);
        }
    }

    Die die(max);
    out = die.roll();
    cout << out << endl;

	return 0;
}