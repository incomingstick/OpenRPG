#include <iostream>
#include <math.h>
#include "config.h"
#include "utils.h"

using namespace std;

int roll(string type){
    string dieTypes[] = {"2", "4", "6", "8", "10", "12", "20", "30", "00"};
    
    for(string i : dieTypes) {
        if (type == "d" + i) {
            if (i == "00") {
                return round((rand() % 100) / 10) * 10 + 1;
            } else {
                return rand() % stoi(i) + 1;
            }
        }
    }
    
    cout << "You cannot use that die type\n";
    return -1;
}