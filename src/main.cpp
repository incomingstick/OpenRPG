/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
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
#include "lib/config.h"
#include "lib/utils.h"

using namespace std;

int nameGenerator(string gender, string race){
    cout << "Running name generation function for a " << gender << " " << race << "...\n";
    
    if(!(gender == "male" || gender == "female")){
        //cout << "Not a valid gender, sorry!\n";//idk about this; need a case to handle nonbinary genders
    }
    
    string raceFile = "assets/names/" + race + "/";
    
    vector<string> firstNames = {};
    vector<string> lastNames = {};
    
    ifstream genderLoad;
    ifstream lastLoad;
    genderLoad.open(raceFile + gender);
    lastLoad.open(raceFile + "last");
    if(genderLoad.is_open() && lastLoad.is_open()){
        string line;
        while(getline(genderLoad,line)){
            firstNames.push_back(line);
        }
        line = {};
        genderLoad.close();
        while(getline(lastLoad,line)){
            lastNames.push_back(line);
        }
        lastLoad.close();
        
        int one = rand() % (firstNames.size() - 1);
        int two = rand() % (lastNames.size() - 1);
        
        cout << firstNames[one] << "\n" << lastNames[two] << endl;//bug-> cannot print both names on same line. First name gets overwritten.

    }else{
        cout << "Error! Failed to load files.\n";
    }
    
   
}
 
//Parses text input into the console and determines the appropriate response/action
int parse(string in) {
    cout << "parsing..." << endl;//message to user that program is working to fulfill request
    
    if (in.size() > 0){
        vector<string> words; //parsed individual words
        string word; //temporary container for word being built
    
        for(int i = 0; i < in.size();i++){//standardizes inputs to ignore case
            in[i] = tolower(in[i]);
            
            if(in[i] < 123 && in[i] > 96){//letters only, implement numbers later
                word += in[i];//pushes character to word
            }else if(word.size() > 0){
                words.push_back(word);//end of word
                word = {};//resets word
            }
        }
        
        if(word.size() > 0){//end of command
            words.push_back(word);//end of word
            word = {};//resets word
        }
        
        if (words.size() > 0){
            cout << "Words (" << words.size() << "):\n";
            for(int i = 0; i < words.size();i++){
                cout << words[i];
                if(i != words.size() - 1){
                    cout << ", ";
                }
            }
            
            cout << endl;
            
            //simple commands, must be expanded on based on command content
            if(words[0] == "exit" || words[0] == "quit" || words[0] == "q"){//quit program
                cout << "Quitting program...\n";
                return 0;
            }else if(words[0] == "gen" || words[0] == "generate"){
                if(words.size() > 1){
                    nameGenerator(words[1],"dwarf");
                }else{
                    cout << "Missing arguments!\n";
                }
                
            }else if(in == "CMD1"){//placeholder command
                cout << "Running placeholder function 1!\n";
            }else if(in == "CMD2"){//placeholder command
                cout << "Running placeholder function 2!\n";
            }else{//default case
                cout << "Command not recognized!\n";
            }
            
            words = {};
            
            //string cmd("name-generator dwarf male"); // PLACEHOLDER VARIABLE
            //return system(cmd.c_str());;
        }else{
            cout << "No command!\n";
        }
    }
        
}

bool print_file(string file){
    ifstream fileToPrint;
    fileToPrint.open(file);
    if(fileToPrint.is_open()){
        string line;
        while(getline(fileToPrint,line)){
            cout << line << "\n";
        }
        fileToPrint.close();
    }else{
        cout << "Error! Failed to load file.\n";
    }
}

int main(int argc, char* argv[]) {
    int status = 0;

    srand (time(NULL));

    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            string arg(argv[i]);

            if(arg == "-n" || arg == "--name") {
                // TODO DANGEROUS - check integrity of array first
                string race(argv[++i]);
                string gender(argv[++i]);

                string cmd("name-generator "+race+" "+gender);
                
                // NOT HOW THIS SHOULD BE DONE
                status = system(cmd.c_str());
            } else if(arg == "-v" || arg == "--verbose") {
                fprintf(stdout,"%s v%d.%d.%d-%s\n",
                    argv[0],
                    OpenRPG_VERSION_MAJOR,
                    OpenRPG_VERSION_MINOR,
                    OpenRPG_VERSION_TWEAK,
                    OpenRPG_VERSION_SUFFIX);

                status = 0;
            }

            if(status != 0) exit(status);
        }
    } else {
        // TODO - cli-gui for program
        print_file("assets/banners/welcome_mat1");
    
        string in;
        
        cout << "Current commands:\n1.) CMD1\n2.) CMD2\n3.) GENERATE NAME\n4.) Quit\n\n";

        // get user input
        while(true) {
            cout << "\33[4morpg\33[0m > ";
            getline(cin, in);
            if(parse(in) == 0){
                break;
            }
            /*if(in == "exit" || in == "quit" || in == "q") break;
            else if((status == parse(in)) != 0) {
                return status;
            }*/
        }
    }

	return status;
}