#include <iostream>
#include "config.h"

using namespace std;

int roll(int faces){
    
    int sides;
    if(faces){
        sides = faces;
    }else{
        cout << "How many sides?\n";
        cout << "\33[4morpg\33[0m > ";
        cin >> sides;
    }
    
    int roll = rand() % sides + 1;
    if(roll == 20){
        cout << "You have rolled a nat20!" << endl;
    }else{
        cout << "You have rolled a(n) " << roll << "." << endl;
    }
    return 0;
}