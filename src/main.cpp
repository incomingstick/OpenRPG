/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
#include <limits.h>
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        try {
            string arg(argv[i]);

            if(arg == "-n") {
                string race(argv[i + 1]);
                string gender(argv[i + 2]);

                cout << "TODO Print " << gender << " " << race << " name here" << endl;
            }
        } catch(...) {
            cerr << "invalid arg/use print" << endl;
        }

        exit(0);
    }

    print_file("banners/welcome_mat1");
    
    string in = "";

    while(in != "exit") {
        cout << "\33[4morpg\33[0m > ";
        cin >> in;
    }

	return 0;
}