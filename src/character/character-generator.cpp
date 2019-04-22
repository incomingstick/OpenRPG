/*
character-generator - character-generator.cpp
Created on: Jan 24, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <cctype>
#include <vector>
#include <string>

#include "openrpg.h"
#include "character.h"

using namespace std;
using namespace ORPG;

/**
  * @desc This function parses all cla's passed to argv from the command line.
  * This function may terminate the program.
  * 
  * @param int argc - the number of arguments passed / the length of argv[]
  * @param char* argv[] - the arguments passed from the command line
  * @return int - an integer code following the C/C++ standard for program success
  */
int parse_args(int argc, char* argv[]) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"random",  no_argument,        0,  'r'},
        {"verbose", no_argument,        0,  'v'},
        {"version", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "rhvV",
                               long_opts, &opt_ind)) != EOF &&
                               status != EXIT_FAILURE) {
        string cmd("");

        switch (opt) {
        /* -h --help */
        case 'h': {
            Characters::print_help_flag();
        } break;

        /* -r --random */
        case 'r': {
            // TODO skip character creator and generate fully random character
        } break;

        /* -V --verbose */
        case 'v': {
            VB_FLAG = true;
            QUIET_FLAG = false;
        } break;

        /* -v --version */
        case 'V': {
            Characters::print_version_flag();
        } break;
            
        /* parsing error */
        case ':':
        case '?': {
            Characters::print_help_flag();
        } break;

        /* if we get here something very bad happened */
        default: {
            printf("Aborting...\n");
            status = EXIT_FAILURE;
        }
        }
    }

    return status;
}

/* 
 * Currently this function only checks to ensure the string contains
 * only digits, and returns true. It will return false otherwise.
 * 
 * NOTE(incomingsting): This could, and probably should, be improved
 * to also ensure we are at least coming in as an int, but possibly
 * even within the bounds on the "question" being asked.
 * 
 * @param: string check - this string to be checked
 * @return bool - returns true if check contains only numbers
 */
bool purity_check_string(string check) {
    for(char c : check) {
        if(!isdigit((unsigned char)c)) return false;
    }

    return true;
}

/* 
 * This function is built to work in tandem specifically with the character
 * module. It takes in a CharacterFactory and checks what stage it is
 * currently in, prompting the user for any required input from cin.
 * 
 * NOTE(incomingsting): currently, we are only using numbered input
 * (i.e '1') so the above purity check function strictly ensures the input 
 * will only contain digits. If it does not, it will continue to prompt the
 * user.
 * 
 * @param: CharacterFactory factory - the factory to check and prompt from
 * @return int - the selected input
 */
int request_selection(CharacterFactory factory) {
    int index = -1;
    string input;

    vector<string> list;
    
    if(factory.has_options())
        list = factory.current_options();
    
    while(index < 0 || index > (signed)list.size()) {
        
        int tick = 0;

        for(string str : list) {
            cout << "\t" << (tick++) << ") " << str;
            
            if(tick % 3 == 0) cout << endl;
        }
        
        tick = 0;
        
        cout << "\n#? ";
        cin >> input;

        if(purity_check_string(input)) {
            index = stoi(input);
        } else {
            cout << "invalid input!" << endl;
        }
    }

    return index;
}

/* 
 * This function prompts the user for 6 numbers to use as their characters
 * abilities. It specifically request their ability scores in the following
 * order: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma.
 * 
 * NOTE(incomingsting): currently, we are only using numbered input
 * (i.e '12') so the above purity check function strictly ensures the input 
 * will only contain digits. If it does not, it will continue to prompt the
 * user.
 * 
 * This function could likely also be cleaner. Its just a giant switch
 * currently, which looks kinda ungly, and takes up space. Like this comment.
 * 
 * @return Ability - an Ability containing the users input scores
 */
Ability request_scores() {    
    printf("\n");

    Ability ret;
    string input;
    vector<int> stats = ability_vector();

    printf("You generated the following ability scores: \n");

    for(int num : stats) printf("%i (%i)\n", num, modifier(num));

    printf("\n");

    for(size_t i = 0; i < stats.size(); i++) {
        switch(i) {
        case 0: {
            printf("Set Strength\t (STR): ");

            cin >> input;

            if(purity_check_string(input)) {
                ret.STR = stoi(input);
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 1: {
            printf("Set Dexterity\t (DEX): ");

            cin >> input;

            if(purity_check_string(input)) {
                ret.DEX = stoi(input);
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 2: {
            printf("Set Constitution (CON): ");

            cin >> input;

            if(purity_check_string(input)) {
                ret.CON = stoi(input); 
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 3: {
            printf("Set Intelligence (INT): ");

            cin >> input;

            if(purity_check_string(input)) {
                ret.INT = stoi(input);
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 4: {
            printf("Set Wisdom\t (WIS): ");

            cin >> input;

            if(purity_check_string(input)) {
                ret.WIS = stoi(input);
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 5: {
            printf("Set Charisma\t (CHA): ");

            cin >> input;

            if(purity_check_string(input)) {
                ret.CHA = stoi(input);
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        default: {
            printf("should not have gotten here");
            exit(EXIT_FAILURE);
        }
        }
    }

    printf("\n");
    
    return ret;
}

/**
  * @desc entry point for the character-generator program. This contains the 
  * main logic for creating a character via the character-generator. All 
  * command line arguments are parsed before character creation begins, and
  * the program may terminate before allowing user input.
  * 
  * @param string in - the users input to be parsed
  * @return int - an integer code following the C/C++ standard for program success
  */
int main(int argc, char* argv[]) {
    int status = parse_args(argc, argv); // may exit
    
    /* begin creating the character here */
    printf("Use character creator (Y/n)\n");   // TODO character creator switch ('-r' argv should ALSO handle this)

    CharacterFactory factory;
    
    printf("Choose Race:\n");
    
    factory.select_option(request_selection(factory));

    if(factory.has_options()) {
        printf("Choose Subrace:\n");
        factory.select_option(request_selection(factory)); 
    }
    
    printf("Class\n");                         // TODO class menu.
    printf("Background\n");                    // TODO background menu

    Ability abil = request_scores();
    
    printf("Skill select based on class\n");   // TODO Skill select based on class
    printf("Hit points\n");                    // TODO hit points max, avg, or roll + con mod
    printf("Equipment\n\n");                   // TODO select equipment based on class and background

    printf("(leave blank for random name)\n");
    printf("Name: ");

    string name;

    cin.ignore();
    getline(cin, name);

    printf("\n");

    Character* character = name.empty() ? factory.NewCharacter(abil) : factory.NewCharacter(abil, name);
    
    printf("%s", character->to_string().c_str());

    return status;
}
