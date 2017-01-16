/*
 * main.cpp
 *
 *  Created on: Nov 10, 2016
 */
#include <iostream>
#include <string>
#include "config.h"
#include "roll.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand (time(NULL));//need a much better random number generator
    int total = roll(argv[1]);
    for (int i = 2; i < argc; i += 2) {
        /*if (argv[++i]) {
            int faces = atoi(argv[i]);
            roll(faces);
        } else {
            cout << "missing sides\n";
        }*/
        if ((string) argv[i] == "+" && argv[i+1]) {
            total += roll(argv[i+1]);
        } else if ((string) argv[i] == "-" && argv[i+1]) {
            total -= roll(argv[i+1]);
        }
    }
    cout << total << endl;
	return total;
}