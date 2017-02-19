/*
character-generator - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>

#include "utils.h"
#include "die.h"
#include "names.h"
#include "character.h"

using namespace std;

Character::Character() {
    NameGenerator ng;

    name = ng.make_name();

    abils.STR = gen_stat();    // Strength
    abils.DEX = gen_stat();    // Dexterity
    abils.CON = gen_stat();    // Constitution
    abils.INT = gen_stat();    // Intelligence
    abils.WIS = gen_stat();    // Wisdom
    abils.CHA = gen_stat();    // Charisma

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = DEX();    // Acrobatics       (DEX)
    skills.ANM = WIS();    // Animal Handling  (WIS)
    skills.ARC = INT();    // Arcana           (INT)
    skills.ATH = STR();    // Athletics        (STR)
    skills.DEC = CHA();    // Deception        (CHA)
    skills.HIS = INT();    // History          (INT)
    skills.INS = WIS();    // Insight          (WIS)
    skills.ITM = CHA();    // Intimidation     (CHA)
    skills.INV = INT();    // Investigation    (INT)
    skills.MED = WIS();    // Medicine         (WIS)
    skills.NAT = INT();    // Nature           (INT)
    skills.PRC = WIS();    // Perception       (WIS)
    skills.PRF = CHA();    // Performance      (CHA)
    skills.PRS = CHA();    // Persuasion       (CHA)
    skills.REL = INT();    // Religion         (INT)
    skills.SLE = DEX();    // Sleight of Hand  (DEX)
    skills.STL = DEX();    // Stealth          (DEX)
    skills.SUR = WIS();    // Survival         (WIS)
}

Character::Character(Ability ab)
    :abils(ab) {
    NameGenerator ng;

    name = ng.make_name();

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = DEX();    // Acrobatics       (DEX)
    skills.ANM = WIS();    // Animal Handling  (WIS)
    skills.ARC = INT();    // Arcana           (INT)
    skills.ATH = STR();    // Athletics        (STR)
    skills.DEC = CHA();    // Deception        (CHA)
    skills.HIS = INT();    // History          (INT)
    skills.INS = WIS();    // Insight          (WIS)
    skills.ITM = CHA();    // Intimidation     (CHA)
    skills.INV = INT();    // Investigation    (INT)
    skills.MED = WIS();    // Medicine         (WIS)
    skills.NAT = INT();    // Nature           (INT)
    skills.PRC = WIS();    // Perception       (WIS)
    skills.PRF = CHA();    // Performance      (CHA)
    skills.PRS = CHA();    // Persuasion       (CHA)
    skills.REL = INT();    // Religion         (INT)
    skills.SLE = DEX();    // Sleight of Hand  (DEX)
    skills.STL = DEX();    // Stealth          (DEX)
    skills.SUR = WIS();    // Survival         (WIS)
}

Character::Character(Ability ab, Skills sk)
    :abils(ab),
     skills(sk) {
    NameGenerator ng;

    name = ng.make_name();
}

Character::~Character() {
    // TODO nothing yet
}

/* TODO format a ASCII text version of a character sheet */
string Character::to_string() {
    string ret("");

    ret += "~~~ " + name + " ~~~\n";

    ret += "STR: "+ std::to_string(STR()) + " (" + std::to_string(STR_MOD()) + ")\n";
    ret += "DEX: "+ std::to_string(DEX()) + " (" + std::to_string(DEX_MOD()) + ")\n";
    ret += "CON: "+ std::to_string(CON()) + " (" + std::to_string(CON_MOD()) + ")\n";
    ret += "INT: "+ std::to_string(INT()) + " (" + std::to_string(INT_MOD()) + ")\n";
    ret += "WIS: "+ std::to_string(WIS()) + " (" + std::to_string(WIS_MOD()) + ")\n";
    ret += "CHA: "+ std::to_string(CHA()) + " (" + std::to_string(CHA_MOD()) + ")\n";

    return ret;
}

/* TODO accept different types of stat generation */
int gen_stat() {
    Die d6(6);

    return d6.roll() + d6.roll() + 6;
}

/* Generates a vector of ability scores base on the used type
    TODO allow multiple types of ability score generation */
vector<int> abil_arr() {
    vector<int> ret;

    for(int i = 0; i < 6; i++) { ret.push_back(gen_stat()); }

    return ret;
}