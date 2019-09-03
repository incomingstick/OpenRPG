/*
characters - character.cpp
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>
#include <algorithm>

#include "core/config.h"
#include "core/xml.h"
#include "roll.h"
#include "names.h"
#include "character.h"

using namespace std;
using namespace ORPG;

namespace ORPG {
    namespace Characters {
        /**
         * @desc prints the version info when -V or --version is an argument to the command.
         * This adhears to the GNU standard for version printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void print_version_flag() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        /**
         * @desc prints the help info when -h or --help is an argument to the command.
         * This adhears to the GNU standard for help printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void print_help_flag() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: character-generator [options] RACE GENDER\n"
                        "\t-h --help                   Print this help screen.\n"
                        "\t-r --random                 Skips the character creator and generates a fully random character.\n"
                        "\t-s --sheet                  Prints a fancy character sheet when done building the character.\n"
                        "\t-v --verbose                Verbose program output.\n"
                        "\t-V --version                Print version info.\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
                "See 'man character-generator' for more information [TODO add man pages].\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        /**
         * @desc prints the version info when version, ver, v, or V are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void print_basic_version() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
        }

        /**
         * @desc prints the help info when help, h, or H are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void print_basic_help() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: character-generator [options] RACE GENDER\n"
                        "\t-h --help                   Print this help screen\n"
                        "\t-r --random                 Skips the character creator and generates a fully random character\n"
                        "\t-s --sheet                  Prints a fancy character sheet when done building the character.\n"
                        "\t-v --verbose                Verbose program output\n"
                        "\t-V --version                Print version info\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
                "See 'man character-generator' for more information [TODO add man pages].\n",
                stdout);
        }

        // TODO Find cleaner way to do this factory, things get entered in too many places!!!
        RaceSelector::RaceSelector() {
            head = allocate_node(Race::ID, false, NULL);

            auto human = allocate_node(Human::ID, true, head);

            auto dwarf = allocate_node(Dwarf::ID, true, head);
            auto hillDwarf = allocate_node(HillDwarf::ID, true, dwarf);

            auto elf = allocate_node(Elf::ID, true, head);
            auto highElf = allocate_node(HighElf::ID, true, elf);

            dwarf->children = {
                hillDwarf
            };

            elf->children = {
                highElf
            };

            head->children = {
                human,
                dwarf,
                elf
            };

            current = head;
        }

        RaceSelector::~RaceSelector() {
            //TODO clean up here
        }

        RaceSelector::race_node* RaceSelector::allocate_node(uint raceID,
                                                            bool required,
                                                            race_node* parent) {
            auto node = new race_node;

            if(node == NULL) {
                printf("out of memory");
                exit(EXIT_FAILURE);
            }

            node->raceID = raceID;
            node->required = required;
            node->parent = parent;

            return node;
        }

        vector<string> RaceSelector::current_options() {
            vector<string> ret;

            for(auto node : current->children) {
                switch(node->raceID) {
                case Human::ID : {
                    ret.push_back("Human");
                    break;
                }

                case Dwarf::ID : {
                    ret.push_back("Dwarf");
                    break;
                }

                case HillDwarf::ID : {
                    ret.push_back("Hill Dwarf");
                    break;
                }

                case Elf::ID : {
                    ret.push_back("Elf");
                    break;
                }

                case HighElf::ID : {
                    ret.push_back("High Elf");
                    break;
                }
                }
            }

            return ret;
        }

        bool RaceSelector::has_options() {
            if(!current) return false;
            else if(!current->children.empty())
                return true;
            else return false;
        }

        void RaceSelector::select_option(int8 index) {
            if(current == NULL) return;

            if(index < 0 || (size_t)index > current->children.size())
                return;

            if(current->children[index] != NULL)
                current = current->children[index];
        }

        uint RaceSelector::current_id() {
            if(current != NULL) return current->raceID;
            return -1;
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
         * @desc Takes a point to an array of unit8's, randomly selects an index
         * from within that array, gets the value of that index to return, and
         * removes it from the vector. Do note that the vectors size is reduced
         * by one.
         * 
         * TODO(incomingstick): Make this generic and put it somewhere in the Utils
         * namespace
         *
         * @param vector<uint8> *arr - the pointer of the vectory array to operate on
         * @return auto - the extracted value from the randomly selected element
         **/
        uint8 extract_random_element(vector<uint8>* arr) {
            auto randIndex = Utils::randomInt(0, arr->size()-1);
            auto ret = arr->at(randIndex);

            arr->erase(arr->begin()+randIndex);

            return ret;
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
        int request_selection(RaceSelector factory) {
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
         * @desc This function is build to work specifically in tandem with the Character
         * module. It prompts to stdout a request for user input, from stdin, to help determine
         * whether or not we should just randomly create the character
         *
         * TODO character creator switch ('-r' argv should ALSO handle this)
         * 
         * @return bool - true if user wants to be random, false otherwise
         **/
        bool request_is_random() {
            printf("Use character creator (Y/n): ");

            string in;

            Utils::safeGetline(cin, in);
            transform(in.begin(), in.end(), in.begin(), ::tolower);

            cin.clear();

            if(in == "y" || in == "ye" || in == "yes" || in.empty()) {
                return false;
            } else if(in == "n" || in == "no") {
                return true;
            } else {
                printf("Invalid input!\n");
                return request_is_random();
            }
        }

        /**
         * @desc This function is build to work specifically in tandem with the Character
         * module. This function prompts the user for their race by using the RaceSelector
         * to first prompt to stdout the base race, then requesting a corresponding number
         * via stdin. It repeats this process for the subrace, and will continue prompting
         * until no other race types could possibly be chosen.
         * 
         * @return Race* - a pointer to a new Race determined by the RaceSelector
         **/
        Race* request_race() {
            RaceSelector selector;

            printf("Choose Race:\n");

            selector.select_option(request_selection(selector));

            if(selector.has_options()) {
                printf("Choose Subrace:\n");
                selector.select_option(request_selection(selector));
            }

            return select_race(selector.current_id());
        }

        /**
         * @desc This function prompts the user, via stdout, for 6 numbers to
         * use as their characters abilities. It specifically request their
         * ability scores in the following order: Strength, Dexterity,
         * Constitution, Intelligence, Wisdom, Charisma.
         *
         * NOTE(incomingsting): currently, we are only using numbered input
         * (i.e '12') so the above purity check function strictly ensures the input
         * will only contain digits. If it does not, it will continue to prompt the
         * user.
         *
         * This function could likely also be cleaner. Its just a giant switch
         * currently, which looks kinda ungly, and takes up space. Like this comment.
         *
         * @return AbilityScores* - an AbilityScores object containing the users input
         * scores
         **/
        AbilityScores* request_scores() {
            printf("\n");

            AbilityScores* ret = new AbilityScores;
            string input;
            auto stats = ability_score_vector();

            printf("We rolled the following ability scores (2d6+6): \n");

            for(auto num : stats) printf("%i (%i)\n", num, modifier(num));

            printf("\n");

            printf("(leave blank to randomly assign from the list above)\n");

            for(int8 i = 0; i < 6; i++) {
                switch(i) {
                case 0: {
                    printf("Set Strength\t (STR): ");

                    Utils::safeGetline(cin, input);

                    if(safety_check_stoi(input)) {
                        ret->set_score(EnumAbilityScore::STR, stoi(input));
                    } else if(input.empty()) {
                        ret->set_score(EnumAbilityScore::STR,
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
                        ret->set_score(EnumAbilityScore::DEX, stoi(input));
                    } else if(input.empty()) {
                        ret->set_score(EnumAbilityScore::DEX,
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
                        ret->set_score(EnumAbilityScore::CON, stoi(input));
                    } else if(input.empty()) {
                        ret->set_score(EnumAbilityScore::CON,
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
                        ret->set_score(EnumAbilityScore::INT, stoi(input));
                    } else if(input.empty()) {
                        ret->set_score(EnumAbilityScore::INT,
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
                        ret->set_score(EnumAbilityScore::WIS, stoi(input));
                    } else if(input.empty()) {
                        ret->set_score(EnumAbilityScore::WIS,
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
                        ret->set_score(EnumAbilityScore::CHA, stoi(input));
                    } else if(input.empty()) {
                        ret->set_score(EnumAbilityScore::CHA,
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
         * @desc This function prompts the user via stdout for a name, and reading
         * from stdin the input. We use the safeGetline funtion via the ORPG::Utils
         * namespace to ensure integrity across platforms.
         * 
         * @return string - the user input string to be used as a name
         **/
        string request_name() {
            printf("(leave blank for random name)\n");
            printf("Name: ");

            string ret;

            Utils::safeGetline(cin, ret);

            printf("\n");

            return ret;
        }

        /**
         * @desc prints "Background\n" to stdout
         *
         * TODO(incomingstick): Add backgrounds
         *
         * @return bool - always will return true
         **/
        uint request_background() {
            printf("Acolyte Background Automatically Chosen\n");
            return Acolyte::ID;
        }

        /**
         * @desc prints "Wizard Class Automatically Chosen\n" to stdout
         * and returns a pointer to a new Wizard.
         *
         * TODO(incomingstick): Add more character classes
         *
         * @return CharacterClass* - always will return a pointer to a Wizard
         **/
        CharacterClass* request_class() {
            printf("Wizard Class Automatically Chosen\n");
            return new Wizard;
        }

        /**
         * @desc prints "Skill select based on class\n" to stdout
         *
         * TODO(incomingstick): Improve skills once classes are added
         *
         * @return bool - always will return true
         **/
        Skills* request_skills() {
            printf("Skill select based on class\n");
            return new Skills;
        }

        /**
         * @desc prints "Hit points\n" to stdout
         *
         * TODO(incomingstick): Set hitpoints based on classes hit die
         *
         * @return bool - always will return true
         **/
        bool request_hitpoints(CharacterClass* classPtr) {
            printf("Hit points\n");
            return true;
        }

        /**
         * @desc prints "Equipment\n" to stdout
         *
         * TODO(incomingstick): Choose equipment based on class
         * and background
         *
         * @return bool - always will return true
         **/
        bool request_equipment() {
            printf("Equipment\n\n");
            return true;
        }

        /**
         * @desc import_character takes in the location of a file as a string
         * and attempts to load it as a character class. If a new Character is
         * able to be created from the file, it will return a pointer to that
         * character.
         * 
         * @return Character* - a pointer to a character created via the file
         **/
        Character* import_character(string file) {
            if(file.empty()) return new Character;

            // TODO(incomingstick): check whether the file is XML or not

            // create the container for the XML file to be opened
            Core::XMLDocument document;

            if (document.load_file(file)) {
                //TODO: create a character based on the imported XML file
            } else {
                /* TODO: Raise an exception here, if an asset file
                 cannot be opened then something serious has gone wrong. */
            }

            return new Character();
        }
    }

    /* an arrray that holds the EXP needed for each level */
    const int EXP[] = {
        300,          // Level 2
        900,          // Level 3
        2700,         // Level 4
        6500,         // Level 5
        14000,        // Level 6
        23000,        // Level 7
        34000,        // Level 8
        48000,        // Level 9
        64000,        // Level 10
        85000,        // Level 11
        100000,       // Level 12
        120000,       // Level 13
        140000,       // Level 14
        165000,       // Level 15
        195000,       // Level 16
        225000,       // Level 17
        265000,       // Level 18
        305000,       // Level 19
        355000        // Level 20
    };

    /**
     * mod is what is added to rolls
     * Prof is number of proficiencies, 0 if unproficient, 1 if proficient, 2 if doubly proficient
     *
     * both are chars to reduce memory usage
     **/
    Skill::Skill() {
        this->mod = 0;
        this->profBonus = 0;
    }

    /**
     * @desc Constructor for a new Skill object that takes an int8 and to set
     * as the modifier, and a uint8 to set as the proficiencyBonus
     *
     * @param int8 modifier - an int8 to set as the mod (modifier)
     * @param uint8 proficiencyBonus - a uint8 to set as the proficiency level
     **/
    Skill::Skill(int8 modifier, uint8 proficiencyBonus):
        mod(modifier),
        profBonus(proficiencyBonus) {
        /* Does nothing else currently */
    }

    /**
     * @desc Setter function that combines the setting of the modifier and
     * proficiency bonus into a single function. To set the values it just
     * calls their own individual setters.
     *
     * @param int8 modifier - the int8 to set as the new mod
     * @param uint8 newPoficiencyBonus - the uint8 to set as the new profBonus
     **/
    void Skill::set(int8 modifier, uint8 proficiencyBonus) {
        set_mod(modifier);
        set_prof_bonus(proficiencyBonus);
    }

    /**
     * @desc Setter function for the mod (modifier) this Skill provides
     *
     * @param int8 modifier - the int8 to set as the new mod
     **/
    void Skill::set_mod(int8 modifier) {
        this->mod = modifier;
    }

    /**
     * @desc Setter function for the profBonus of this Skill
     *
     * @param uint8 newPoficiencyBonus - the uint8 to set as the new profBonus
     **/
    void Skill::set_prof_bonus(uint8 newProficiencyBonus) {
        this->profBonus = newProficiencyBonus;
    }

    /**
     * @desc Get the modifier bonus of the given EnumSkill contained
     * within this Skill object
     *
     * @return int8 - the modifier bonus of the queried skill
     **/
    int8 Skill::get_mod() {
        return this->mod;
    }

    /**
     * @desc Get the proficiency bonus level that is to be used when
     * calculating the amount proficiency to add to this skills
     * modifier bonus.
     *
     * Currently proficiency bonus levels are defined as follows:
     *      0 - if unproficient
     *      1 - if proficient
     *      2 - if double proficient
     *
     * @return uint8 - the proficiency bonus level that is used when calculating
     * the amount proficiency to add to this skills modifier bonus
     **/
    unsigned char Skill::get_prof() {
        return this->profBonus;
    }

    /**
     * @desc Converts this Skills data to std::string format. It is retruned in the
     * following format:
     * 
     * (+/-)[value]
     * Example: "+3"
     *
     * @return string - a string 
     **/
    std::string Skill::to_string() {
        string ret = "";

        if(mod > 0) ret = "+";

        return ret + std::to_string(mod);
    };

    /**
     * @desc Constructor for the Skills class that maps Skill classes to
     * their respective EnumSkill, with a modifier of 0 and proficiency
     * bonus level of 0.
     **/
    Skills::Skills() {
        this->skillsMap = {
            { ACR, new Skill(0, 0) },    // Acrobatics       (DEX)
            { ANM, new Skill(0, 0) },    // Animal Handling  (WIS)
            { ARC, new Skill(0, 0) },    // Arcana           (INT)
            { ATH, new Skill(0, 0) },    // Athletics        (STR)
            { DEC, new Skill(0, 0) },    // Deception        (CHA)
            { HIS, new Skill(0, 0) },    // History          (INT)
            { INS, new Skill(0, 0) },    // Insight          (WIS)
            { ITM, new Skill(0, 0) },    // Intimidation     (CHA)
            { INV, new Skill(0, 0) },    // Investigation    (INT)
            { MED, new Skill(0, 0) },    // Medicine         (WIS)
            { NAT, new Skill(0, 0) },    // Nature           (INT)
            { PRC, new Skill(0, 0) },    // Perception       (WIS)
            { PRF, new Skill(0, 0) },    // Performance      (CHA)
            { PRS, new Skill(0, 0) },    // Persuasion       (CHA)
            { REL, new Skill(0, 0) },    // Religion         (INT)
            { SLE, new Skill(0, 0) },    // Sleight of Hand  (DEX)
            { STL, new Skill(0, 0) },    // Stealth          (DEX)
            { SUR, new Skill(0, 0) }     // Survival         (WIS)
        };
    };

    /**
     * @desc Constructor for the Skills class that maps Skill classes to
     * their respective EnumSkill, with a modifier of 0 and proficiency
     * bonus level of 0.
     **/
    Skills::Skills(void* owner):container(owner) {
        this->skillsMap = {
            { ACR, new Skill(0, 0) },    // Acrobatics       (DEX)
            { ANM, new Skill(0, 0) },    // Animal Handling  (WIS)
            { ARC, new Skill(0, 0) },    // Arcana           (INT)
            { ATH, new Skill(0, 0) },    // Athletics        (STR)
            { DEC, new Skill(0, 0) },    // Deception        (CHA)
            { HIS, new Skill(0, 0) },    // History          (INT)
            { INS, new Skill(0, 0) },    // Insight          (WIS)
            { ITM, new Skill(0, 0) },    // Intimidation     (CHA)
            { INV, new Skill(0, 0) },    // Investigation    (INT)
            { MED, new Skill(0, 0) },    // Medicine         (WIS)
            { NAT, new Skill(0, 0) },    // Nature           (INT)
            { PRC, new Skill(0, 0) },    // Perception       (WIS)
            { PRF, new Skill(0, 0) },    // Performance      (CHA)
            { PRS, new Skill(0, 0) },    // Persuasion       (CHA)
            { REL, new Skill(0, 0) },    // Religion         (INT)
            { SLE, new Skill(0, 0) },    // Sleight of Hand  (DEX)
            { STL, new Skill(0, 0) },    // Stealth          (DEX)
            { SUR, new Skill(0, 0) }     // Survival         (WIS)
        };
    }

    /**
     * @desc Desctructor function for the Skills class that ensures
     * the internal std::map skillsMap is deleted
     **/
    Skills::~Skills() {
        delete[] &skillsMap;
    }

    /**
     * @desc Get the modifier bonus of the given EnumSkill contained
     * within this Skills object
     *
     * @param EnumSkill skill - the skill to query
     *
     * @return int8 - the modifier bonus of the queried skill
     **/
    int8 Skills::get_mod(EnumSkill skill) {
        int finalProf = 0;
        auto currProf = ((Character*)container)->get_proficiency_bonus();
        auto profRank = skillsMap[skill]->get_prof();

        if(profRank == PROFICIENT) finalProf = currProf;
        else if(profRank == HALF_PROFICIENT) finalProf = currProf / 2;
        else if(profRank == DOUBLE_PROFICIENT) finalProf = currProf * 2;

        return skillsMap[skill]->get_mod() + finalProf;
    };

    /* to_string method used internally for iterative purposes */
    std::string Skills::internal_to_string(std::pair<EnumSkill, Skill*> skill) {
        string ret = "";
        auto eskill = skill.first;

        switch(eskill) {
        case ACR: { ret = "ACR: "; } break;   // Acrobatics       (DEX)
        case ANM: { ret = "ANM: "; } break;   // Animal Handling  (WIS)
        case ARC: { ret = "ARC: "; } break;   // Arcana           (INT)
        case ATH: { ret = "ATH: "; } break;   // Athletics        (STR)
        case DEC: { ret = "DEC: "; } break;   // Deception        (CHA)
        case HIS: { ret = "HIS: "; } break;   // History          (INT)
        case INS: { ret = "INS: "; } break;   // Insight          (WIS)
        case ITM: { ret = "ITM: "; } break;   // Intimidation     (CHA)
        case INV: { ret = "INV: "; } break;   // Investigation    (INT)
        case MED: { ret = "MED: "; } break;   // Medicine         (WIS)
        case NAT: { ret = "NAT: "; } break;   // Nature           (INT)
        case PRC: { ret = "PRC: "; } break;   // Perception       (WIS)
        case PRF: { ret = "PRF: "; } break;   // Performance      (CHA)
        case PRS: { ret = "PRS: "; } break;   // Persuasion       (CHA)
        case REL: { ret = "REL: "; } break;   // Religion         (INT)
        case SLE: { ret = "SLE: "; } break;   // Sleight of Hand  (DEX)
        case STL: { ret = "STL: "; } break;   // Stealth          (DEX)
        case SUR: { ret = "SUR: "; } break;   // Survival         (WIS)
        default: {
            cout << "Error! Unknown EnumSkill in Skills::internal_to_string(): " << eskill << endl;
        }
        }

        ret += skill.second->to_string() +"\n";

        return ret;
    };

    /**
     * @desc Converts this Skills data to std::string format. It is retruned in the
     * following format:
     * 
     * {Skill}: (+/-)[value]
     * Example: "ACR: +3"
     *
     * @return string - a string 
     **/
    string Skills::to_string() {
        string ret = "";

        for (std::map<EnumSkill, Skill*>::iterator it = skillsMap.begin(); it != skillsMap.end(); ++it) {
            ret += internal_to_string(*it);
        }

        return ret;
    }

    /**
     * @desc Constructor for AbilityScore that is passed no arguments.
     * It sets score equal to a randomly generated number between 8 and 18,
     * and sets is_prof to false.
     */
    AbilityScore::AbilityScore() {
        this->score = gen_stat();
        this->prof = false;
    }

    /**
     * @desc Constructor for AbilityScore that is passed two arguments.
     * It sets this->score equal to score and sets this->is_prof to is_prof.
     *
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     * @param bool is_prof - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    AbilityScore::AbilityScore(uint8 score, bool is_prof) {
        this->score = score;
        this->prof = is_prof;
    }

    /**
     * @desc Deconstructor for AbilityScore that is passed no arguments.
     * Currently does nothing, and the compiler handles deconstruction.
     */
    AbilityScore::~AbilityScore() {
        // TODO
    }

    /**
     * @desc Setter method for score and is_prof. is_prof is a boolean
     * representation of whether or not a proficiency bonus should be added to
     * the save of the given AbilityScore.
     *
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     * @param bool is_prof - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScore::set(uint8 newScore, bool is_prof) {
        this->score = newScore;
        this->prof = is_prof;
    }

    /**
     * @desc Setter method for an AbilityScore's score.
     *
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     */
    void AbilityScore::set_score(uint8 score) {
        this->score = score;
    }

    /**
     * @desc Setter method for the is_prof property. is_prof is a boolean
     * representation of whether or not a proficiency bonus should be
     * added for the save of the given AbilityScore.
     *
     * @param bool is_prof - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScore::set_is_prof(bool is_prof) {
        this->prof = is_prof;
    }

    /**
     * @desc Accessor method for an AbilityScore's score.
     *
     * @return uint8 - an unsigned 8-bit integer of the AbilityScore's score
     */
    uint8 AbilityScore::get_score() {
        return this->score;
    }

    /**
     * @desc Accessor method for the AbilityScore's modifier.
     * A modifier is defined as:
     *
     * Mod = floor((Score - 10) / 2);
     *
     * @return int8 - an 8-bit integer of the AbilityScore's modifier
     */
    int8 AbilityScore::get_mod() {
        return modifier(this->score);
    }

    /**
     * @desc Accessor method for the is_prof property. The current Proficiency
     * bonus should be added to any AbilityScore's modifier that has is_prof
     * set to true, otherwise it is just the AbilityScore's modifier. It is
     * up to the implementer to handle that addition.
     *
     * @return bool - a boolean value denoting whether or not a proficiency
     * bonus should be added to the save of this AbilityScore
     */
    bool AbilityScore::is_prof() {
        return this->prof;
    }

    /**
     * @desc Constructor for AbilityScores that is passed a uint8 to use as
     * the default Ability score value. If no argument is passed this function
     * sets all ability scores equal to 0. is_prof will always be set to false.
     * 
     * @param uint8 def - the default value to use for all Ability scores
     */
    AbilityScores::AbilityScores(uint8 def) {
        this->scoresMap = {
            { STR, new AbilityScore(def, false) },
            { DEX, new AbilityScore(def, false) },
            { CON, new AbilityScore(def, false) },
            { INT, new AbilityScore(def, false) },
            { WIS, new AbilityScore(def, false) },
            { CHA, new AbilityScore(def, false) }
        };
    }

    /**
     * @desc Operator overload for adding two AbilityScores objects together.
     *
     * @param const AbilityScores obj - the LHS AbilityScores object during the
     * addition operator.
     *
     * @return AbilityScores& - an AbilityScores object containing the addition of
     * the calling object and the passed AbilityScores object
     **/
    AbilityScores AbilityScores::operator+(AbilityScores obj) {
        AbilityScores ret;

        ret.set(EnumAbilityScore::STR,
                scoresMap[EnumAbilityScore::STR]->get_score()
                + obj.get_score(EnumAbilityScore::STR),
                scoresMap[EnumAbilityScore::STR]->is_prof() || obj.is_prof(EnumAbilityScore::STR));

        ret.set(EnumAbilityScore::DEX,
                scoresMap[EnumAbilityScore::DEX]->get_score()
                + obj.get_score(EnumAbilityScore::DEX),
                scoresMap[EnumAbilityScore::DEX]->is_prof() || obj.is_prof(EnumAbilityScore::DEX));

        ret.set(EnumAbilityScore::CON,
                scoresMap[EnumAbilityScore::CON]->get_score()
                + obj.get_score(EnumAbilityScore::CON),
                scoresMap[EnumAbilityScore::CON]->is_prof() || obj.is_prof(EnumAbilityScore::CON));

        ret.set(EnumAbilityScore::INT,
                scoresMap[EnumAbilityScore::INT]->get_score()
                + obj.get_score(EnumAbilityScore::INT),
                scoresMap[EnumAbilityScore::INT]->is_prof() || obj.is_prof(EnumAbilityScore::INT));

        ret.set(EnumAbilityScore::WIS,
                scoresMap[EnumAbilityScore::WIS]->get_score()
                + obj.get_score(EnumAbilityScore::WIS),
                scoresMap[EnumAbilityScore::WIS]->is_prof() || obj.is_prof(EnumAbilityScore::WIS));

        ret.set(EnumAbilityScore::CHA,
                scoresMap[EnumAbilityScore::CHA]->get_score()
                + obj.get_score(EnumAbilityScore::CHA),
                scoresMap[EnumAbilityScore::CHA]->is_prof() || obj.is_prof(EnumAbilityScore::CHA));

        return ret;
    }

    /**
     * @desc Deconstructor for AbilityScores that is passed no arguments.
     * Currently does nothing, and the compiler handles deconstruction.
     */
    AbilityScores::~AbilityScores() {
        // TODO
    }

    /**
     * @desc Setter method for an AbilityScore's score and is_prof, denoted
     * by EnumAbilityScore ability. is_prof is a boolean representation of
     * whether or not a proficiency bonus should be added to the save of the
     * given AbilityScore.
     *
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     * @param bool is_prof - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScores::set(EnumAbilityScore ability, uint8 newScore, bool is_prof) {
        scoresMap[ability]->set(newScore, is_prof);
    }

    /**
     * @desc Accessor method for an AbilityScore, denoted by
     * EnumAbilityScore ability. This returns the pointer of the queried
     * AbilityScore.
     *
     * @param EnumAbilityScore ability - the AbilityScore score to query
     *
     * @return AbilityScore* - an pointer to the AbilityScore's denoted by
     * EnumAbilityScore ability
     */
    AbilityScore* AbilityScores::get(EnumAbilityScore ability) {
        return scoresMap[ability];
    }

    /**
     * @desc Setter method for an AbilityScore's score, denoted
     * by EnumAbilityScore ability. A modifier is defined as:
     *
     * Mod = floor((Score - 10) / 2);
     *
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     */
    void AbilityScores::set_score(EnumAbilityScore ability, uint8 score) {
        scoresMap[ability]->set_score(score);
    }

    /**
     * @desc Setter method for the is_prof property AbilityScore, denoted by
     * EnumAbilityScore ability. is_prof is a boolean representation of whether
     * or not a proficiency bonus should be added to the save of the given
     * AbilityScore.
     *
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param bool is_prof - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScores::set_is_prof(EnumAbilityScore ability, bool is_prof) {
        scoresMap[ability]->set_is_prof(is_prof);
    }

    /**
     * @desc Setter method for curProf, the current Proficiency Bonus
     * that is added to any AbilityScore that has is_prof set to true.
     *
     * @param uint8 - a unsigned 8-bit integer containing the current
     * Proficiency bonus that is added to any AbilityScore that has is_prof
     * set to true.
     */
    void AbilityScores::set_current_prof(uint8 newProf) {
        curProf = newProf;
    }

    /**
     * NOTE(incomingstick): Should this be accessable to the library at large?
     **/
    Background* background_selector(const int identifier = -1) {
        const auto id = (identifier <= -1) ?
            Characters::random_bg_id() : identifier;

        switch(id) {
        case Acolyte::ID : {
            return new Acolyte();
        }

        default: {
            return nullptr;
        }
        }
    }

    /**
     * NOTE(incomingstick): Should this be accessable to the library at large?
     **/
    CharacterClass* class_selector(const int identifier = -1) {
        const auto id = (identifier <= -1) ?
            Characters::random_class_id() : identifier;

        switch(id) {
        case Wizard::ID : {
            return new Wizard();
        }

        default: {
            return nullptr;
        }
        }
    }

    Character::Character(Race* racePtr, AbilityScores* ab, CharacterClass* classPtr,
                        const int bgID, Skills* sk, std::string name):
                        race(racePtr), abils(ab), cClass(classPtr), skills(sk) {
        bg = background_selector(bgID);

        if(name.empty()) {
            NameGenerator ng(race->to_string());

            firstName = ng.make_first();
            lastName = ng.make_last();
        } else {
            /* TODO make this work by parsing the name into a first and last */
            firstName = name;
            lastName = name;
        }

        Initialize();
    }

    Character::~Character() {
        // TODO nothing yet
    }

    void Character::Initialize() {
        race->applyRacialBonus(abils);

        /* Make some of our interals aware of who we are */
        cClass->set_owner(this);
        skills->set_owner(this);

        max_hp = cClass->HIT_DIE_MAX() + CON_MOD(); // maximum hit points
        curr_hp = max_hp;                           // TODO current hit points
        temp_hp = 0;                                // TODO temporary hit points
        prof = 2;                                   // proficiency bonus
        level = 1;                                  // character level total
        curr_exp = 0;                               // current experience
        max_exp = EXP[level-1];                     // experience needed for next level

        // TODO Apply racial bonuses here? Or during the request process?
        update_skills();
    }

    // TODO(incomingstick): Make this more efficient
    void Character::update_skills() {
        skills->get(ACR)->set_mod(DEX_MOD());    // Acrobatics       (DEX)
        skills->get(ANM)->set_mod(WIS_MOD());    // Animal Handling  (WIS)
        skills->get(ARC)->set_mod(INT_MOD());    // Arcana           (INT)
        skills->get(ATH)->set_mod(STR_MOD());    // Athletics        (STR)
        skills->get(DEC)->set_mod(CHA_MOD());    // Deception        (CHA)
        skills->get(HIS)->set_mod(INT_MOD());    // History          (INT)
        skills->get(INS)->set_mod(WIS_MOD());    // Insight          (WIS)
        skills->get(ITM)->set_mod(CHA_MOD());    // Intimidation     (CHA)
        skills->get(INV)->set_mod(INT_MOD());    // Investigation    (INT)
        skills->get(MED)->set_mod(WIS_MOD());    // Medicine         (WIS)
        skills->get(NAT)->set_mod(INT_MOD());    // Nature           (INT)
        skills->get(PRC)->set_mod(WIS_MOD());    // Perception       (WIS)
        skills->get(PRF)->set_mod(CHA_MOD());    // Performance      (CHA)
        skills->get(PRS)->set_mod(CHA_MOD());    // Persuasion       (CHA)
        skills->get(REL)->set_mod(INT_MOD());    // Religion         (INT)
        skills->get(SLE)->set_mod(DEX_MOD());    // Sleight of Hand  (DEX)
        skills->get(STL)->set_mod(DEX_MOD());    // Stealth          (DEX)
        skills->get(SUR)->set_mod(WIS_MOD());    // Survival         (WIS)
    }

    string Character::to_string() {
        string ret("");

        ret += "First: "+ (firstName.empty() || firstName == "NULL" ? "" : firstName) +"\n";
        ret += "Last: " + (lastName.empty() || lastName == "NULL" ? "" : lastName) +"\n";

        ret += "Race: "+ race->to_string() +"\n";
        ret += "Background: "+ bg->to_string() +"\n";
        ret += "Class: "+ cClass->to_string() +"\n"; // TODO Multiclassing

        ret += "Level: "+ std::to_string(level) + "\n";
        ret += "EXP: " + std::to_string(curr_exp) +"/"+ std::to_string(max_exp) + "\n";

        ret += "TempHP: "+ std::to_string(temp_hp) +"\n";        
        ret += "HP:"+ std::to_string(curr_hp) +"/"+ std::to_string(max_hp) +"\n";
        
        ret += "Proficiency: "+ format_mod(prof, 0) +"\n";

        ret += "STR: "+ std::to_string(STR()) + " (" + format_mod(STR_MOD(), 0) + ")\n";
        ret += "DEX: "+ std::to_string(DEX()) + " (" + format_mod(DEX_MOD(), 0) + ")\n";
        ret += "CON: "+ std::to_string(CON()) + " (" + format_mod(CON_MOD(), 0) + ")\n";
        ret += "INT: "+ std::to_string(INT()) + " (" + format_mod(INT_MOD(), 0) + ")\n";
        ret += "WIS: "+ std::to_string(WIS()) + " (" + format_mod(WIS_MOD(), 0) + ")\n";
        ret += "CHA: "+ std::to_string(CHA()) + " (" + format_mod(CHA_MOD(), 0) + ")\n";

        ret += skills->to_string();

        return ret;
    }

    string Character::format_mod(int mod, int spaces) {
        string ret("");
        if(mod > 0) {
            ret += "+";
        }

        ret += std::to_string(mod);
        ret = Utils::rightpad(ret, spaces, ' ');
        
        return ret;
    }

    string Character::to_ascii_sheet() {
        string ret("");

        const int SPACES_PER_MOD = 3;

        update_skills();

        //TODO A couple magic numbers in this function, possibly replace later

        //Second argument is 23 because there are 23 allotted spaces for the first name
        string charFName = Utils::leftpad(firstName, 23, ' ');

        //Second arg is 22 because thats how many spaces we alloted for last name
        string charLName = Utils::leftpad(lastName, 22, ' ');

        //Second arg is 12 because thats how many spaces we alloted for backgrounds
        string charBg = Utils::rightpad(bg->to_string(), 12, ' ');

        //Second arg is 12 because thats how many spaces we alloted for the race
        string charRace = Utils::rightpad(race->to_string(), 14, ' ');

        string charEXP = std::to_string(curr_exp) + '/' + std::to_string(max_exp);
        charEXP = Utils::rightpad(charEXP, 10, ' ');

        string sProf = format_mod(prof, SPACES_PER_MOD);

        string sSTR = Utils::rightpad(std::to_string(STR()), SPACES_PER_MOD, ' ');
        string sSTRMod = format_mod(STR_MOD(), SPACES_PER_MOD);
        
        string sDEX = Utils::rightpad(std::to_string(DEX()), SPACES_PER_MOD, ' ');
        string sDEXMod = format_mod(DEX_MOD(), SPACES_PER_MOD);
        
        string sCON = Utils::rightpad(std::to_string(DEX()), SPACES_PER_MOD, ' ');
        string sCONMod = format_mod(CON_MOD(), SPACES_PER_MOD);
        
        string sINT = Utils::rightpad(std::to_string(INT()), SPACES_PER_MOD, ' ');
        string sINTMod = format_mod(INT_MOD(), SPACES_PER_MOD);
        
        string sWIS = Utils::rightpad(std::to_string(WIS()), SPACES_PER_MOD, ' ');
        string sWISMod = format_mod(WIS_MOD(), SPACES_PER_MOD);
        
        string sCHA = Utils::rightpad(std::to_string(CHA()), SPACES_PER_MOD, ' ');
        string sCHAMod = format_mod(CHA_MOD(), SPACES_PER_MOD);

        string sACR = format_mod(skills->get_mod(ACR), SPACES_PER_MOD);
        string sANM = format_mod(skills->get_mod(ANM), SPACES_PER_MOD);
        string sARC = format_mod(skills->get_mod(ARC), SPACES_PER_MOD);
        string sATH = format_mod(skills->get_mod(ATH), SPACES_PER_MOD);
        string sDEC = format_mod(skills->get_mod(DEC), SPACES_PER_MOD);
        string sHIS = format_mod(skills->get_mod(HIS), SPACES_PER_MOD);
        string sINS = format_mod(skills->get_mod(INS), SPACES_PER_MOD);
        string sITM = format_mod(skills->get_mod(ITM), SPACES_PER_MOD);
        string sINV = format_mod(skills->get_mod(INV), SPACES_PER_MOD);
        string sMED = format_mod(skills->get_mod(MED), SPACES_PER_MOD);
        string sNAT = format_mod(skills->get_mod(NAT), SPACES_PER_MOD);
        string sPRC = format_mod(skills->get_mod(PRC), SPACES_PER_MOD);
        string sPRF = format_mod(skills->get_mod(PRF), SPACES_PER_MOD);
        string sPRS = format_mod(skills->get_mod(PRS), SPACES_PER_MOD);
        string sREL = format_mod(skills->get_mod(REL), SPACES_PER_MOD);
        string sSLE = format_mod(skills->get_mod(SLE), SPACES_PER_MOD);
        string sSTL = format_mod(skills->get_mod(STL), SPACES_PER_MOD);
        string sSUR = format_mod(skills->get_mod(SUR), SPACES_PER_MOD);

        string passPRC = format_mod(passive_stat(skills->get_mod(SUR)), SPACES_PER_MOD);

        //TODO pull this into its own files
        //NOTE(var_username): To be fair, this is quite lazy on my part
        /* NOTE(incomingstick): this likely should be put in its own file with tags in the file as
        * placeholders for the different variables. That would pull this out from cluttering the
        * source code, as well as allowing for people to create their own styles with our predefined tags
        */

        ret += "                         ╭────────────────────────────────────────────────────╮\n";
        ret += " ────────────────────────┤                  "+ charBg +"                      │\n";
        ret += " \\" + charFName +      "│Class & Level     Background      Player Name       │\n";
        ret += "  \\"+ charLName +      "│                                                    │\n";
        ret += "_ ───────────────────────┤"+ charRace +"                    "+charEXP+"        │\n";
        ret += "__\\  Character Name      │Race              Alignment       Experience Points │\n";
        ret += "                         ╰────────────────────────────────────────────────────╯\n";
        ret += "╭───╮╭─────────────────────────────────────────────────────────────────────────\n";
        ret += "│STR││╭───┬─────────────────╮╭───────────────────────╮╭───────────────────────╮\n";
        ret += "│"+sSTR+"│││   │   Inspiration   ││  ╭───╮  ╭────╮  ╭───╮ ││╭─────────────────────╮│\n";
        ret += "├───┤│╰───┴─────────────────╯│  │   │  │    │  │   │ │││                     ││\n";
        ret += "│"+sSTRMod+"││                       │  ├───┤  ├────┤  ├───┤ │││                     ││\n";
        ret += "╰───╯│╭───┬─────────────────╮│  │ AC│  │Init│  │SPD│ │││                     ││\n";
        ret += "     ││"+sProf+"│   Proficiency   ││  ╰───╯  ╰────╯  ╰───╯ │││                     ││\n";
        ret += "╭───╮│╰───┴─────────────────╯│                       │││                     ││\n";
        ret += "│DEX││                       │  ╭──────────────────╮ │││  Personality Traits ││\n";
        ret += "│"+sDEX+"││╭─┬───┬───────────────╮│  │                  │ ││├─────────────────────┤│\n";
        ret += "├───┤││ │   │      STR      ││  │                  │ │││                     ││\n";
        ret += "│"+sDEXMod+"│││ │   │      DEX      ││  │     Curr. HP     │ │││                     ││\n";
        ret += "╰───╯││ │   │      CON      ││  ├──────────────────┤ │││        Ideals       ││\n";
        ret += "     ││ │   │      INT      ││  │                  │ ││├─────────────────────┤│\n";
        ret += "╭───╮││ │   │      WIS      ││  │     Temp. HP     │ │││                     ││\n";
        ret += "│CON│││ │   │      CHA      ││  ╰──────────────────╯ │││                     ││\n";
        ret += "│"+sCON+"││├─┴───┴───────────────┤│                       │││        Bonds        ││\n";
        ret += "├───┤││    Saving throws    ││ ╭────────╮ ╭────────╮ ││├─────────────────────┤│\n";
        ret += "│"+sCONMod+"││╰─────────────────────╯│ │        │ │S O-O-O │ │││                     ││\n";
        ret += "╰───╯│                       │ ├────────┤ │F O-O-O │ │││                     ││\n";
        ret += "     │╭─┬───┬───────────────╮│ │Hit Dice│ │ Saves  │ │││        Flaws        ││\n";
        ret += "╭───╮││ │"+sACR+"│Acrobatics     ││ ╰────────╯ ╰────────╯ ││╰─────────────────────╯│\n";
        ret += "│INT│││ │"+sANM+"│Animal Handling│╰───────────────────────╯╰───────────────────────╯\n";
        ret += "│"+sINT+"│││ │"+sARC+"│Arcana         │╭────────┬─────┬────────╮╭───────────────────────╮\n";
        ret += "├───┤││ │"+sATH+"│Athletics      ││Name    │ ATK │DMG Type││                       │\n";
        ret += "│"+sINTMod+"│││ │"+sDEC+"│Deception      ││        │     │        ││                       │\n";
        ret += "╰───╯││ │"+sHIS+"│History        ││        │     │        ││                       │\n";
        ret += "     ││ │"+sINS+"│Insight        ││        │     │        ││                       │\n";
        ret += "╭───╮││ │"+sITM+"│Intimidation   │├────────┴─────┴────────┤│                       │\n";
        ret += "│WIS│││ │"+sINV+"│Investigation  ││                       ││                       │\n";
        ret += "│"+sWIS+"│││ │"+sWISMod+"│Medicine       ││                       ││                       │\n";
        ret += "├───┤││ │"+sNAT+"│Nature         ││                       ││                       │\n";
        ret += "│"+sWISMod+"│││ │"+sPRC+"│Perception     ││                       ││                       │\n";
        ret += "╰───╯││ │"+sPRF+"│Performance    ││                       ││                       │\n";
        ret += "     ││ │"+sPRS+"│Persuassion    ││                       ││                       │\n";
        ret += "╭───╮││ │"+sREL+"│Religion       ││                       ││                       │\n";
        ret += "│CHA│││ │"+sSLE+"│Sleight of Hand││                       ││                       │\n";
        ret += "│"+sCHA+"│││ │"+sSTL+"│Stealth        ││                       ││                       │\n";
        ret += "├───┤││ │"+sSUR+"│Survival       ││                       ││                       │\n";
        ret += "│"+sCHAMod+"││├─┴───┴───────────────┤├───────────────────────┤│                       │\n";
        ret += "╰───╯││       Skills        ││  Attacks and Spells   ││                       │\n";
        ret += "─────╯╰─────────────────────╯╰───────────────────────╯│                       │\n";
        ret += "╭───┬───────────────────────╮╭──┬────┬───────────────╮│                       │\n";
        ret += "│"+passPRC+"│    Passive Perception |│CP│    │               ││                       │\n";
        ret += "╰───┴───────────────────────╯│SP│    │               ││                       │\n";
        ret += "╭───────────────────────────╮│EP│    │               ││                       │\n";
        ret += "│                           ││GP│    │               ││                       │\n";
        ret += "│                           ││PP│    │               ││                       │\n";
        ret += "│                           │├──┴────╯               ││                       │\n";
        ret += "│                           ││                       ││                       │\n";
        ret += "│                           ││                       ││                       │\n";
        ret += "│                           ││                       ││                       │\n";
        ret += "│                           ││                       ││                       │\n";
        ret += "├───────────────────────────┤├───────────────────────┤├───────────────────────┤\n";
        ret += "│    Other Proficiencies    ││       Equipment       ││  Features and Traits  │\n";
        ret += "╰───────────────────────────╯╰───────────────────────╯╰───────────────────────╯\n";

        return ret;
    }

    uint8 gen_stat() {
        /*
         * TODO accept different types of stat generation
         * i.e 4d4+4 or 4d6h3+2
         */

        Die d6(6);

        return d6.roll() + d6.roll() + 6;
    }

    /* Generates a vector of ability scores base on the used type
        TODO allow multiple types of ability score generation */
    vector<uint8> ability_score_vector() {
        vector<uint8> ret;

        for(uint8 i = 0; i < 6; i++) { ret.push_back(gen_stat()); }

        return ret;
    }
}