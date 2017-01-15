#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "config.h"
#include "utils.h"
#include "generator.h"

using namespace std;

int nameGenerator(string gender, string race){
    cout << "Running name generation function for a " << gender << " " << race << "...\n";
    
    if(!(gender == "male" || gender == "female")){
        //cout << "Not a valid gender, sorry!\n";//idk about this; need a case to handle nonbinary genders
    }
    
    string raceFile = "../assets/names/" + race + "/";
    
    vector<string> firstNames = {};
    vector<string> lastNames = {};
    
    ifstream genderLoad;
    ifstream lastLoad;
    genderLoad.open(raceFile + gender);
    lastLoad.open(raceFile + "last");
    if(genderLoad.is_open() && lastLoad.is_open()){
        string line;
        while(getline(genderLoad,line)){
            firstNames.push_back(line.substr(0,line.size()-1));
        }
        line = {};
        genderLoad.close();
        while(getline(lastLoad,line)){
            lastNames.push_back(line.substr(0,line.size()-1));
        }
        lastLoad.close();
        
        cout << "Your character's name is " << firstNames[rand() % (firstNames.size() - 1)] << " " << lastNames[rand() % (lastNames.size() - 1)] << ".\n";

    }else{
        cout << "Error! Failed to load files.\n";
    }
    return 0;
}
