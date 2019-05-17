/*
character-generator - character.cpp
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>

#include "core/config.h"
#include "core/utils.h"
#include "roll.h"
#include "names.h"
#include "character.h"

using namespace std;
using namespace ORPG;

namespace ORPG {
    namespace Characters {
        void print_version_flag() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        void print_help_flag() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
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

        void print_basic_version() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
        }

        void print_basic_help() {
            fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
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
        }
    }

    /* an arrray that holds the EXP needed for each level */
    const int levels[] = {
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

    /*
    * mod is what is added to rolls
    * Prof is number of proficiencies, 0 if unproficient, 1 if proficient, 2 if doubly proficient
    * 
    * both are chars to reduce memory usage
    */
    Skill::Skill(void) {
        this->mod = 0;
        this->prof = 0;
    }
    Skill::Skill(char nb, unsigned char np) {
        this->mod = nb;
        this->prof = np;
    }
    void Skill::set(char nb, unsigned char np) {
        this->mod = nb;
        this->prof = np;
    }
    void Skill::setMod(char nb) {
        this->mod = nb;
    }
    void Skill::setProf(unsigned char np) {
        this->prof = np;
    }
    char Skill::getMod(void) {
        return this->mod;
    }
    unsigned char Skill::getProf(void) {
        return this->prof;
    }

    Skills::Skills(void) {
        
    }
    Skills::~Skills(void) {
        delete[] &skillsMap;
    }
    Skill* Skills::get(EnumSkill skill) {
        return skillsMap[skill];
    }

    Character::Character() {
        abils.STR = 10;    // Strength
        abils.DEX = 10;    // Dexterity
        abils.CON = 10;    // Constitution
        abils.INT = 10;    // Intelligence
        abils.WIS = 10;    // Wisdom
        abils.CHA = 10;    // Charisma
    }

    Character::Character(Ability ab):abils(ab) {
    }

    Character::~Character() {
        // TODO nothing yet
    }

    void Character::Initialize() {
        update_skills();
    }

    void Character::update_skills() {
        skills.get(ACR)->setMod(DEX_MOD());    // Acrobatics       (DEX)
        skills.get(ANM)->setMod(WIS_MOD());    // Animal Handling  (WIS)
        skills.get(ARC)->setMod(INT_MOD());    // Arcana           (INT)
        skills.get(ATH)->setMod(STR_MOD());    // Athletics        (STR)
        skills.get(DEC)->setMod(CHA_MOD());    // Deception        (CHA)
        skills.get(HIS)->setMod(INT_MOD());    // History          (INT)
        skills.get(INS)->setMod(WIS_MOD());    // Insight          (WIS)
        skills.get(ITM)->setMod(CHA_MOD());    // Intimidation     (CHA)
        skills.get(INV)->setMod(INT_MOD());    // Investigation    (INT)
        skills.get(MED)->setMod(WIS_MOD());    // Medicine         (WIS)
        skills.get(NAT)->setMod(INT_MOD());    // Nature           (INT)
        skills.get(PRC)->setMod(WIS_MOD());    // Perception       (WIS)
        skills.get(PRF)->setMod(CHA_MOD());    // Performance      (CHA)
        skills.get(PRS)->setMod(CHA_MOD());    // Persuasion       (CHA)
        skills.get(REL)->setMod(INT_MOD());    // Religion         (INT)
        skills.get(SLE)->setMod(DEX_MOD());    // Sleight of Hand  (DEX)
        skills.get(STL)->setMod(DEX_MOD());    // Stealth          (DEX)
        skills.get(SUR)->setMod(WIS_MOD());    // Survival         (WIS)
    }

    string Character::to_string() {
        string ret("");

        ret += "~~~ " + firstName.empty() ? "" : firstName;
        ret += " " + lastName.empty() ? "" : lastName;
        ret += " ~~~\n";

        ret += "STR: "+ std::to_string(STR()) + " (" + std::to_string(STR_MOD()) + ")\n";
        ret += "DEX: "+ std::to_string(DEX()) + " (" + std::to_string(DEX_MOD()) + ")\n";
        ret += "CON: "+ std::to_string(CON()) + " (" + std::to_string(CON_MOD()) + ")\n";
        ret += "INT: "+ std::to_string(INT()) + " (" + std::to_string(INT_MOD()) + ")\n";
        ret += "WIS: "+ std::to_string(WIS()) + " (" + std::to_string(WIS_MOD()) + ")\n";
        ret += "CHA: "+ std::to_string(CHA()) + " (" + std::to_string(CHA_MOD()) + ")\n";
        
        return ret;
    }

    string Character::format_mod(int mod, int spaces) {
        string ret("");
        if(mod > 0) {
            ret += "+";
        }
        
        ret += std::to_string(mod);
        ret = rightpad(ret, spaces, ' ');
        
        return ret;
    }

    string Character::to_sheet() {
        string ret("");

        const int SPACES_PER_MOD = 3;
        
        update_skills();
        
        //TODO A couple magic numbers in this function, possibly replace later

        //Second argument is 23 because there are 23 allotted spaces for the first name
        string charFName = leftpad(firstName, 23, ' ');
        //Second arg = 22 because thats how many spaces we alloted for last name
        string charLName = leftpad(lastName, 22, ' ');

        string sSTR = rightpad(std::to_string(STR()), SPACES_PER_MOD, ' ');
        string sSTRMod = format_mod(STR_MOD(), SPACES_PER_MOD);
        
        string sDEX = rightpad(std::to_string(DEX()), SPACES_PER_MOD, ' ');
        string sDEXMod = format_mod(DEX_MOD(), SPACES_PER_MOD);
        
        string sCON = rightpad(std::to_string(DEX()), SPACES_PER_MOD, ' ');
        string sCONMod = format_mod(CON_MOD(), SPACES_PER_MOD);
        
        string sINT = rightpad(std::to_string(INT()), SPACES_PER_MOD, ' ');
        string sINTMod = format_mod(INT_MOD(), SPACES_PER_MOD);
        
        string sWIS = rightpad(std::to_string(WIS()), SPACES_PER_MOD, ' ');
        string sWISMod = format_mod(WIS_MOD(), SPACES_PER_MOD);
        
        string sCHA = rightpad(std::to_string(CHA()), SPACES_PER_MOD, ' ');
        string sCHAMod = format_mod(CHA_MOD(), SPACES_PER_MOD);
        
        string sACR = format_mod(skills.getMod(ACR), SPACES_PER_MOD);
        string sANM = format_mod(skills.getMod(ANM), SPACES_PER_MOD);
        string sARC = format_mod(skills.getMod(ARC), SPACES_PER_MOD);
        string sATH = format_mod(skills.getMod(ATH), SPACES_PER_MOD);
        string sDEC = format_mod(skills.getMod(DEC), SPACES_PER_MOD);
        string sHIS = format_mod(skills.getMod(HIS), SPACES_PER_MOD);
        string sINS = format_mod(skills.getMod(INS), SPACES_PER_MOD);
        string sITM = format_mod(skills.getMod(ITM), SPACES_PER_MOD);
        string sINV = format_mod(skills.getMod(INV), SPACES_PER_MOD);
        string sMED = format_mod(skills.getMod(MED), SPACES_PER_MOD);
        string sNAT = format_mod(skills.getMod(NAT), SPACES_PER_MOD);
        string sPRC = format_mod(skills.getMod(PRC), SPACES_PER_MOD);
        string sPRF = format_mod(skills.getMod(PRF), SPACES_PER_MOD);
        string sPRS = format_mod(skills.getMod(PRS), SPACES_PER_MOD);
        string sREL = format_mod(skills.getMod(REL), SPACES_PER_MOD);
        string sSLE = format_mod(skills.getMod(SLE), SPACES_PER_MOD);
        string sSTL = format_mod(skills.getMod(STL), SPACES_PER_MOD);
        string sSUR = format_mod(skills.getMod(SUR), SPACES_PER_MOD);

        //TODO pull this into its own files
        //NOTE(var_username): To be fair, this is quite lazy on my part
        /* NOTE(incomingstick): this likely should be put in its own file with tags in the file as
        * placeholders for the different variables. That would pull this out from cluttering the
        * source code, as well as allowing for people to create their own styles with our predefined tags
        */
        
    ret += "                         ╭────────────────────────────────────────────────────╮\n";
    ret += " ────────────────────────┤                                                    │\n";
    ret += " \\" + charFName +      "│Class & Level     Background      Player Name       │\n";
    ret += "  \\"+ charLName +      "│                                                    │\n";
    ret += "_ ───────────────────────┤                                                    │\n";
    ret += "__\\  Character Name      │Race              Alignment       Experience Points │\n";
    ret += "                         ╰────────────────────────────────────────────────────╯\n";
    ret += "╭───╮╭─────────────────────────────────────────────────────────────────────────\n";
    ret += "│STR││╭───┬─────────────────╮╭───────────────────────╮╭───────────────────────╮\n";
    ret += "│"+sSTR+"│││   │   Inspiration   ││  ╭───╮  ╭────╮  ╭───╮ ││╭─────────────────────╮│\n";
    ret += "├───┤│╰───┴─────────────────╯│  │   │  │    │  │   │ │││                     ││\n";
    ret += "│"+sSTRMod+"││                       │  ├───┤  ├────┤  ├───┤ │││                     ││\n";
    ret += "╰───╯│╭───┬─────────────────╮│  │ AC│  │Init│  │SPD│ │││                     ││\n";
    ret += "     ││   │   Proficiency   ││  ╰───╯  ╰────╯  ╰───╯ │││                     ││\n";
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
    ret += "│   │     Passive Wisdom    ││CP│    │               ││                       │\n";
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
    /* }}}1 */

    int gen_stat() {
        /* TODO accept different types of stat generation */

        Die d6(6);

        return d6.roll() + d6.roll() + 6;
    }

    /* Generates a vector of ability scores base on the used type
        TODO allow multiple types of ability score generation */
    vector<int> ability_vector() {
        vector<int> ret;

        for(int i = 0; i < 6; i++) { ret.push_back(gen_stat()); }

        return ret;
    }

    /* Generates a struct of ability scores base on the used type
        TODO allow multiple types of ability score generation */
    Ability ability_struct() {
        Ability ret;

        ret.STR = gen_stat();     // Strength
        ret.DEX = gen_stat();     // Dexterity
        ret.CON = gen_stat();     // Constitution
        ret.INT = gen_stat();     // Intelligence
        ret.WIS = gen_stat();     // Wisdom
        ret.CHA = gen_stat();     // Charisma

        return ret;
    }

}