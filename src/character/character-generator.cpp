/*
character-generator - character-generator.cpp
Created on: Jan 24, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
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
 **/
int parse_args(int argc, char* argv[]) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    Core::opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct Core::option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"random",  no_argument,        0,  'r'},
        {"version", no_argument,        0,  'v'},
        {"verbose", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = Core::getopt_long(argc, argv, "rhvV",
                               long_opts, &opt_ind)) != EOF &&
                               status != EXIT_FAILURE) {

        switch (opt) {
        /* -h --help */
        case 'h': {
            Characters::print_help_flag();
        } break;

        /* -r --random */
        case 'r': {
            // TODO skip character creator and generate fully random character
        } break;

        /* -v --verbose */
        case 'v': {
            Core::VB_FLAG = true;
            Core::QUIET_FLAG = false;
        } break;

        /* -V --version */
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

/**
 * @desc Currently this function just checks to ensure the string contains
 * only digits, and returns true. It will return false otherwise.
 * If the provided string is empty, this function returns false.
 *
 * NOTE(incomingsting): This could, and probably should, be improved
 * to also ensure we are within the bounds on the "question" being asked.
 *
 * TODO(incomingstick): ensure we are at least coming in as an int32.
 *
 * @param: string check - this string to be checked
 * @return bool - returns true if check contains only numbers
 **/
bool safety_check_stoi(string check) {
    for(auto c : check) {
        if(!isdigit((unsigned)c)) return false;
    }

    return check.empty() ? false : true;
}

/**
 * @desc This function is built to work in tandem specifically with the character
 * module. It takes in a CharacterFactory and checks what stage it is
 * currently in, prompting the user for any required input from cin.
 *
 * NOTE(incomingsting): currently, we are only using numbered input
 * (i.e '1') so the above purity check function strictly ensures the input
 * will only contain digits. If it does not, it will continue to prompt the
 * user.
 *
 * @param: CharacterFactory factory - the factory to check and prompt from
 * @return auto - the selected input
 **/
auto request_selection(CharacterFactory factory) {
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
        Utils::safeGetline(cin, input);

        if(safety_check_stoi(input)) {
            index = stoi(input);
        } else {
            cout << "invalid input!" << endl;
        }

        cin.clear();
    }


    return index;
}

/**
 * @desc Takes a point to an array of unit8's, randomly selects an index
 * from within that array, gets the value of that index to return, and
 * removes it from the vector. Do note that the vectors size is reduced
 * by one.
 *
 * @param vector<uint8> *arr - the pointer of the vectory array to operate on
 * @return auto - the extracted value from the randomly selected element
 **/
auto extract_random_element(vector<uint8>* arr) {
    auto randIndex = Utils::randomInt(0, arr->size()-1);
    auto ret = arr->at(randIndex);

    arr->erase(arr->begin()+randIndex);

    return ret;
}

/**
 * @desc This function prompts the user for 6 numbers to use as their characters
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
 **/
AbilityScores request_scores() {
    printf("\n");

    AbilityScores ret;
    string input;
    auto stats = ability_score_vector();

    printf("You generated the following ability scores: \n");

    for(auto num : stats) printf("%i (%i)\n", num, modifier(num));

    printf("\n");

    printf("(leave blank to randomly assign from the list above)\n");

    for(int8 i = 0; i < 6; i++) {
        switch(i) {
        case 0: {
            printf("Set Strength\t (STR): ");

            Utils::safeGetline(cin, input);

            if(safety_check_stoi(input)) {
                ret.setScore(EnumAbilityScore::STR, stoi(input));
            } else if(input.empty()) {
                ret.setScore(EnumAbilityScore::STR,
                             extract_random_element(&stats));
            } else {
                i--;
                cout << "invalid input!" << endl;
                cin.clear();
            }
        } break;

        case 1: {
            printf("Set Dexterity\t (DEX): ");

            Utils::safeGetline(cin, input);

            if(safety_check_stoi(input)) {
                ret.setScore(EnumAbilityScore::DEX, stoi(input));
            } else if(input.empty()) {
                ret.setScore(EnumAbilityScore::DEX,
                             extract_random_element(&stats));
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 2: {
            printf("Set Constitution (CON): ");

            Utils::safeGetline(cin, input);

            if(safety_check_stoi(input)) {
                ret.setScore(EnumAbilityScore::CON, stoi(input));
            } else if(input.empty()) {
                ret.setScore(EnumAbilityScore::CON,
                             extract_random_element(&stats));
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 3: {
            printf("Set Intelligence (INT): ");

            Utils::safeGetline(cin, input);

            if(safety_check_stoi(input)) {
                ret.setScore(EnumAbilityScore::INT, stoi(input));
            } else if(input.empty()) {
                ret.setScore(EnumAbilityScore::INT,
                             extract_random_element(&stats));
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 4: {
            printf("Set Wisdom\t (WIS): ");

            Utils::safeGetline(cin, input);

            if(safety_check_stoi(input)) {
                ret.setScore(EnumAbilityScore::WIS, stoi(input));
            } else if(input.empty()) {
                ret.setScore(EnumAbilityScore::WIS,
                             extract_random_element(&stats));
            } else {
                i--;
                cout << "invalid input!" << endl;
            }
        } break;

        case 5: {
            printf("Set Charisma\t (CHA): ");

            Utils::safeGetline(cin, input);

            if(safety_check_stoi(input)) {
                ret.setScore(EnumAbilityScore::CHA, stoi(input));
            } else if(input.empty()) {
                ret.setScore(EnumAbilityScore::CHA,
                             extract_random_element(&stats));
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

        cin.clear();
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
 **/
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

    AbilityScores abil = request_scores();

    printf("Background\n");                    // TODO background menu

    printf("Class\n");                         // TODO class menu.
    printf("Skill select based on class\n");   // TODO Skill select based on class
    printf("Hit points\n");                    // TODO hit points max, avg, or roll + con mod

    printf("Equipment\n\n");                   // TODO select equipment based on class and background

    printf("(leave blank for random name)\n");
    printf("Name: ");

    string name;

    Utils::safeGetline(cin, name);

    printf("\n");

    auto character = name.empty() ?
        factory.NewCharacter(abil) :
        factory.NewCharacter(name, abil);

    printf("%s", character->to_string().c_str());

    return status;
}
