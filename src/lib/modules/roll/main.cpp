/*
 * main.cpp
 *
 *  Created on: Nov 10, 2016
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "config.h"
#include "utils.h"
#include "roll.h"

using namespace std;

int main(int argc, char* argv[]) {
    for(int i = 0; i < argc; i++) {
        if(argv[++i]){
            srand (time(NULL));//need a much better random number generator
            int faces = atoi(argv[i]);
            roll(faces);
        }else{
            cout << "missing sides\n";
        }
    }
	return 0;
}