/*
 * main.cpp
 *
 *  Created on: Nov 10, 2016
 */
#include <iostream>
#include "generator.h"

using namespace std;

int main(int argc, char* argv[]) {
    string race("dwarf");
    string gender("female");

    if(argc > 2) {
        // TODO we should have cla's for testing purposes
        // This will also parse commands like the race
        // and gender of the desired character
        race = argv[1];
        gender = argv[2];
    }

    NameGenerator gen(race, gender);

    cout << "Random first name: " << gen.make_first() << endl;
    cout << "Random last name: " << gen.make_last() << endl;
    cout << "Random full name: " << gen.make_name() << endl;

	return 0;
}