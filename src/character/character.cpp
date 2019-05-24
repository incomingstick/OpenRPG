/*
characters - character.cpp
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>

#include "core/config.h"
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
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
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
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
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
        this->profBonus = 0;
    }

    Skill::Skill(int8 modifier, uint8 proficiencyBonus) {
        this->mod = modifier;
        this->profBonus = proficiencyBonus;
    }

    void Skill::set(int8 modifier, uint8 proficiencyBonus) {
        this->mod = modifier;
        this->profBonus = proficiencyBonus;
    }

    void Skill::setMod(int8 modifier) {
        this->mod = modifier;
    }

    void Skill::setProfBonus(uint8 modifier) {
        this->profBonus = modifier;
    }

    int8 Skill::getMod() {
        return this->mod;
    }

    unsigned char Skill::getProfBonus() {
        return this->profBonus;
    }

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
    }

    Skills::~Skills() {
        delete[] &skillsMap;
    }

    Skill* Skills::get(EnumSkill skill) {
        return skillsMap[skill];
    }

    /**
     * @desc Constructor for AbilityScore that is passed no arguments.
     * It sets score equal to a randomly generated number between 8 and 18,
     * and sets isProf to false.
     */
    AbilityScore::AbilityScore() {
        this->score = gen_stat();
        this->prof = false;
    }

    /**
     * @desc Constructor for AbilityScore that is passed two arguments.
     * It sets this->score equal to score and sets this->isProf to isProf.
     *
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    AbilityScore::AbilityScore(uint8 score, bool isProf) {
        this->score = score;
        this->prof = isProf;
    }

    /**
     * @desc Deconstructor for AbilityScore that is passed no arguments.
     * Currently does nothing, and the compiler handles deconstruction.
     */
    AbilityScore::~AbilityScore() {
        // TODO
    }

    /**
     * @desc Setter method for score and isProf. isProf is a boolean
     * representation of whether or not a proficiency bonus should be added to
     * the save of the given AbilityScore.
     *
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScore::set(uint8 newScore, bool isProf) {
        this->score = newScore;
        this->prof = isProf;
    }

    /**
     * @desc Setter method for an AbilityScore's score.
     *
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     */
    void AbilityScore::setScore(uint8 score) {
        this->score = score;
    }

    /**
     * @desc Setter method for the isProf property. isProf is a boolean
     * representation of whether or not a proficiency bonus should be
     * added for the save of the given AbilityScore.
     *
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScore::setIsProf(bool isProf) {
        this->prof = isProf;
    }

    /**
     * @desc Accessor method for an AbilityScore's score.
     *
     * @return uint8 - an unsigned 8-bit integer of the AbilityScore's score
     */
    uint8 AbilityScore::getScore() {
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
    int8 AbilityScore::getMod() {
        return modifier(this->score);
    }

    /**
     * @desc Accessor method for the isProf property. The current Proficiency
     * bonus should be added to any AbilityScore's modifier that has isProf
     * set to true, otherwise it is just the AbilityScore's modifier. It is
     * up to the implementer to handle that addition.
     *
     * @return bool - a boolean value denoting whether or not a proficiency
     * bonus should be added to the save of this AbilityScore
     */
    bool AbilityScore::isProf() {
        return this->prof;
    }

    /**
     * @desc Constructor for AbilityScores that is passed no arguments.
     * It sets all ability scores equal to 10 and isProf to false.
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
                scoresMap[EnumAbilityScore::STR]->getScore()
                + obj.getScore(EnumAbilityScore::STR),
                scoresMap[EnumAbilityScore::STR]->isProf() || obj.isProf(EnumAbilityScore::STR));
        
        ret.set(EnumAbilityScore::DEX,
                scoresMap[EnumAbilityScore::DEX]->getScore()
                + obj.getScore(EnumAbilityScore::DEX),
                scoresMap[EnumAbilityScore::DEX]->isProf() || obj.isProf(EnumAbilityScore::DEX));
        
        ret.set(EnumAbilityScore::CON,
                scoresMap[EnumAbilityScore::CON]->getScore()
                + obj.getScore(EnumAbilityScore::CON),
                scoresMap[EnumAbilityScore::CON]->isProf() || obj.isProf(EnumAbilityScore::CON));

        ret.set(EnumAbilityScore::INT,
                scoresMap[EnumAbilityScore::INT]->getScore()
                + obj.getScore(EnumAbilityScore::INT),
                scoresMap[EnumAbilityScore::INT]->isProf() || obj.isProf(EnumAbilityScore::INT));

        ret.set(EnumAbilityScore::WIS,
                scoresMap[EnumAbilityScore::WIS]->getScore()
                + obj.getScore(EnumAbilityScore::WIS),
                scoresMap[EnumAbilityScore::WIS]->isProf() || obj.isProf(EnumAbilityScore::WIS));

        ret.set(EnumAbilityScore::CHA,
                scoresMap[EnumAbilityScore::CHA]->getScore()
                + obj.getScore(EnumAbilityScore::CHA),
                scoresMap[EnumAbilityScore::CHA]->isProf() || obj.isProf(EnumAbilityScore::CHA));

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
     * @desc Setter method for an AbilityScore's score and isProf, denoted
     * by EnumAbilityScore ability. isProf is a boolean representation of
     * whether or not a proficiency bonus should be added to the save of the
     * given AbilityScore.
     *
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param uint8 score - the unsigned 8-bit integer score value to set.
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScores::set(EnumAbilityScore ability, uint8 newScore, bool isProf) {
        scoresMap[ability]->set(newScore, isProf);
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
    void AbilityScores::setScore(EnumAbilityScore ability, uint8 score) {
        scoresMap[ability]->setScore(score);
    }

    /**
     * @desc Setter method for the isProf property AbilityScore, denoted by
     * EnumAbilityScore ability. isProf is a boolean representation of whether
     * or not a proficiency bonus should be added to the save of the given
     * AbilityScore.
     *
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScores::setIsProf(EnumAbilityScore ability, bool isProf) {
        scoresMap[ability]->setIsProf(isProf);
    }

    /**
     * @desc Setter method for curProf, the current Proficiency Bonus
     * that is added to any AbilityScore that has isProf set to true.
     *
     * @param uint8 - a unsigned 8-bit integer containing the current
     * Proficiency bonus that is added to any AbilityScore that has isProf
     * set to true.
     */
    void AbilityScores::setCurrentProf(uint8 newProf) {
        curProf = newProf;
    }

    /**
     * NOTE(incomingstick): Should this be accessable to the library at large?
     **/
    Race* raceSelector(const int identifier = -1) {
        switch(identifier) {
        case Human::ID : {
            return new Human();
        }

        case Dwarf::ID : {
            return new Dwarf();
        }

        case HillDwarf::ID : {
            return new HillDwarf();
        }

        case Elf::ID : {
            return new Elf();
        }

        case HighElf::ID : {
            return new HighElf();
        }

        default: {
            return nullptr;
        }
        }
    }

    Character::Character() {
        race = raceSelector();
        
        // NOTE(incomginstick): there are better ways to do this
        abils.setScore(EnumAbilityScore::STR, gen_stat());    // Strength
        abils.setScore(EnumAbilityScore::DEX, gen_stat());    // Dexterity
        abils.setScore(EnumAbilityScore::CON, gen_stat());    // Constitution
        abils.setScore(EnumAbilityScore::INT, gen_stat());    // Intelligence
        abils.setScore(EnumAbilityScore::WIS, gen_stat());    // Wisdom
        abils.setScore(EnumAbilityScore::CHA, gen_stat());    // Charisma

        // TODO Gender??? What about asexual races? What if they want to enter a name?
        NameGenerator ng;

        firstName = ng.make_first();
        lastName = ng.make_last();


        Initialize();
    }

    Character::Character(const int raceID) {
        race = raceSelector(raceID);

        // NOTE(incomginstick): there are better ways to do this
        abils.setScore(EnumAbilityScore::STR, gen_stat());    // Strength
        abils.setScore(EnumAbilityScore::DEX, gen_stat());    // Dexterity
        abils.setScore(EnumAbilityScore::CON, gen_stat());    // Constitution
        abils.setScore(EnumAbilityScore::INT, gen_stat());    // Intelligence
        abils.setScore(EnumAbilityScore::WIS, gen_stat());    // Wisdom
        abils.setScore(EnumAbilityScore::CHA, gen_stat());    // Charisma

        NameGenerator ng(race->to_string());

        firstName = ng.make_first();
        lastName = ng.make_last();

        Initialize();
    }

    Character::Character(AbilityScores ab):abils(ab) {
        race = raceSelector();

        NameGenerator ng(race->to_string());

        firstName = ng.make_first();
        lastName = ng.make_last();

        Initialize();
    }

    Character::Character(AbilityScores ab, const int raceID):abils(ab) {
        race = raceSelector(raceID);

        NameGenerator ng(race->to_string());

        firstName = ng.make_first();
        lastName = ng.make_last();

        Initialize();
    }

    Character::Character(AbilityScores ab, std::string name):abils(ab) {
        race = raceSelector();

        /* TODO make this work by parsing the name into a first and last */
        firstName = name;
        lastName = name;

        Initialize();
    }

    Character::Character(std::string name) {
        race = raceSelector();

        // NOTE(incomginstick): there are better ways to do this
        abils.setScore(EnumAbilityScore::STR, gen_stat());    // Strength
        abils.setScore(EnumAbilityScore::DEX, gen_stat());    // Dexterity
        abils.setScore(EnumAbilityScore::CON, gen_stat());    // Constitution
        abils.setScore(EnumAbilityScore::INT, gen_stat());    // Intelligence
        abils.setScore(EnumAbilityScore::WIS, gen_stat());    // Wisdom
        abils.setScore(EnumAbilityScore::CHA, gen_stat());    // Charisma

        /* TODO make this work by parsing the name into a first and last */
        firstName = name;
        lastName = name;

        Initialize();
    }

    Character::Character(std::string name, const int raceID) {
        race = raceSelector(raceID);

        // NOTE(incomginstick): there are better ways to do this
        abils.setScore(EnumAbilityScore::STR, gen_stat());    // Strength
        abils.setScore(EnumAbilityScore::DEX, gen_stat());    // Dexterity
        abils.setScore(EnumAbilityScore::CON, gen_stat());    // Constitution
        abils.setScore(EnumAbilityScore::INT, gen_stat());    // Intelligence
        abils.setScore(EnumAbilityScore::WIS, gen_stat());    // Wisdom
        abils.setScore(EnumAbilityScore::CHA, gen_stat());    // Charisma

        /* TODO make this work by parsing the name into a first and last */
        firstName = name;
        lastName = name;

        Initialize();
    }

    Character::Character(AbilityScores ab, std::string name, const int raceID):abils(ab) {
        race = raceSelector(raceID);

        /* TODO make this work by parsing the name into a first and last */
        firstName = name;
        lastName = name;
    }

    Character::~Character() {
        // TODO nothing yet
    }

    void Character::Initialize() {
        race->applyRacialBonus(&abils);

        curr_hp = 10;                   // TODO current hit points
        temp_hp = 0;                    // TODO temporary hit points
        max_hp = curr_hp;               // TODO maximum hit points
        prof = 2;                       // proficiency bonus
        level = 1;                      // character level total
        cur_exp = 0;                    // current experience
        max_exp = levels[level - 1];    // experience needed for next level

        // TODO Apply racial bonuses here

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

        ret += "~~~ " + (firstName.empty() || firstName == "NULL" ? "" : firstName);
        ret += " " + (lastName.empty() || lastName == "NULL" ? "" : lastName);
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

    string Character::to_ascii_sheet() {
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

    int8 gen_stat() {
        /*
         * TODO accept different types of stat generation
         * i.e 4d4+4 or 4d6h3+2
         */

        Die d6(6);

        return d6.roll() + d6.roll() + 6;
    }

    /* Generates a vector of ability scores base on the used type
        TODO allow multiple types of ability score generation */
    vector<int8> ability_score_vector() {
        vector<int8> ret;

        for(int8 i = 0; i < 6; i++) { ret.push_back(gen_stat()); }

        return ret;
    }

    // TODO Find cleaner way to do this factory, things get entered in too many places!!!
    CharacterFactory::CharacterFactory() {
        head = allocate_node(Character::ID, false, NULL);

        race_node* human = allocate_node(Human::ID, true, head);

        race_node* dwarf = allocate_node(Dwarf::ID, true, head);
        race_node* hillDwarf = allocate_node(HillDwarf::ID, true, dwarf);

        race_node* elf = allocate_node(Elf::ID, true, head);
        race_node* highElf = allocate_node(HighElf::ID, true, elf);

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

    CharacterFactory::~CharacterFactory() {
        //TODO clean up here
    }

    CharacterFactory::race_node* CharacterFactory::allocate_node(int8 raceID,
                                                                bool required,
                                                                race_node* parent) {
        race_node* node = new race_node;

        if(node == NULL) {
            printf("out of memory");
            exit(EXIT_FAILURE);
        }

        node->raceID = raceID;
        node->required = required;
        node->parent = parent;

        return node;
    }

    Character* CharacterFactory::NewCharacter(AbilityScores ab) {
        switch(current->raceID) {
        case Human::ID : {
            return new Character(ab, Human::ID);
        }

        case Dwarf::ID : {
            return new Character(ab, Dwarf::ID);
        }

        case HillDwarf::ID : {
            return new Character(ab, HillDwarf::ID);
        }

        case Elf::ID : {
            return new Character(ab, Elf::ID);
        }

        case HighElf::ID : {
            return new Character(ab, HighElf::ID);
        }

        default: {
            return new Character(ab, Race::ID);
        }
        }
    }

    Character* CharacterFactory::NewCharacter(int8 identifier, AbilityScores ab) {
        switch(identifier) {
        case Human::ID : {
            return new Character(ab, Human::ID);
        }

        case Dwarf::ID : {
            return new Character(ab, Dwarf::ID);
        }

        case HillDwarf::ID : {
            return new Character(ab, HillDwarf::ID);
        }

        case Elf::ID : {
            return new Character(ab, Elf::ID);
        }

        case HighElf::ID : {
            return new Character(ab, HighElf::ID);
        }

        default: {
            return new Character(ab, Race::ID);
        }
        }
    }

    Character* CharacterFactory::NewCharacter(string name, AbilityScores ab) {
        switch(current->raceID) {
        case Human::ID : {
            return new Character(ab, name, Human::ID);
        }

        case Dwarf::ID : {
            return new Character(ab, name, Dwarf::ID);
        }

        case HillDwarf::ID : {
            return new Character(ab, name, HillDwarf::ID);
        }

        case Elf::ID : {
            return new Character(ab, name, Elf::ID);
        }

        case HighElf::ID : {
            return new Character(ab, name, HighElf::ID);
        }

        default: {
            return new Character(ab, name, Race::ID);
        }
        }
    }

    vector<string> CharacterFactory::current_options() {
        vector<string> ret;

        for(race_node* node : current->children) {
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

    bool CharacterFactory::has_options() {
        if(!current->children.empty())
            return true;
        else return false;
    }

    void CharacterFactory::select_option(int8 index) {
        if(current == NULL) return;

        if(index < 0 || (size_t)index > current->children.size())
            return;

        if(current->children[index] != NULL)
            current = current->children[index];
    }

    int8 CharacterFactory::current_id() {
        if(current != NULL) return current->raceID;
        return -1;
    }
}