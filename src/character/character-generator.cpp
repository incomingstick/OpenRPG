/*
character-generator - character-generator.cpp
Created on: Jan 24, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <vector>
#include <string>

#include "openrpg.h"
#include "character.h"

using namespace std;

static void print_version_flag() {
    fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

static void print_help_flag() {
    fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: character-generator [options] RACE GENDER\n"
                "\t-h --help                   Print this help screen\n"
                "\t-r --random                 Skips the character creator and generates a fully random character\n"
                "\t-v --verbose                Verbose program output\n"
                "\t-V --version                Print version info\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "See 'man character-generator' for more information [TODO add man pages].\n",
          stdout);
    exit(EXIT_SUCCESS);
}

/* Option parser - parse_args(argc, argv)
    This function parses all cla's passed to argv. */
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
            print_help_flag();
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
            print_version_flag();
        } break;
            
        /* parsing error */
        case ':':
        case '?': {
            print_help_flag();
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
    
        index = stoi(input);
    }

    return index;
}

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
            
            ret.STR = stoi(input);
        } break;

        case 1: {
            printf("Set Dexterity\t (DEX): ");

            cin >> input;
            
            ret.DEX = stoi(input);
        } break;

        case 2: {
            printf("Set Constitution (CON): ");

            cin >> input;
            
            ret.CON = stoi(input);
        } break;

        case 3: {
            printf("Set Intelligence (INT): ");

            cin >> input;
            
            ret.INT = stoi(input);
        } break;

        case 4: {
            printf("Set Wisdom\t (WIS): ");

            cin >> input;
            
            ret.WIS = stoi(input);
        } break;

        case 5: {
            printf("Set Charisma\t (CHA): ");

            cin >> input;
            
            ret.CHA = stoi(input);
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
    
    printf("Class\n");                         // TODO class menu
    printf("Background\n");                    // TODO background menu

    Ability abil = request_scores();
    
    printf("Skill select based on class\n");    // TODO Skill select based on class
    printf("Hit points\n");                     // TODO hit points max, avg, or roll + con mod
    printf("Equipment\n");                      // TODO select equipment based on class and background
    printf("Name:\n");                          // TODO read in name or generate random one?

    printf("\n");

    Character* character = factory.NewCharacter(abil);

    printf("%s", character->to_string().c_str());

    return status;
}
