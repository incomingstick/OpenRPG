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
    skills.ACR = abils.DEX;    // Acrobatics       (DEX)
    skills.ANM = abils.WIS;    // Animal Handling  (WIS)
    skills.ARC = abils.INT;    // Arcana           (INT)
    skills.ATH = abils.STR;    // Athletics        (STR)
    skills.DEC = abils.CHA;    // Deception        (CHA)
    skills.HIS = abils.INT;    // History          (INT)
    skills.INS = abils.WIS;    // Insight          (WIS)
    skills.ITM = abils.CHA;    // Intimidation     (CHA)
    skills.INV = abils.INT;    // Investigation    (INT)
    skills.MED = abils.WIS;    // Medicine         (WIS)
    skills.NAT = abils.INT;    // Nature           (INT)
    skills.PRC = abils.WIS;    // Perception       (WIS)
    skills.PRF = abils.CHA;    // Performance      (CHA)
    skills.PRS = abils.CHA;    // Persuasion       (CHA)
    skills.REL = abils.INT;    // Religion         (INT)
    skills.SLE = abils.DEX;    // Sleight of Hand  (DEX)
    skills.STL = abils.DEX;    // Stealth          (DEX)
    skills.SUR = abils.WIS;    // Survival         (WIS)

    output("character created", VB_CODE);
}

Character::Character(Ability ab)
    :abils(ab) {
    NameGenerator ng;

    name = ng.make_name();

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = abils.DEX;    // Acrobatics       (DEX)
    skills.ANM = abils.WIS;    // Animal Handling  (WIS)
    skills.ARC = abils.INT;    // Arcana           (INT)
    skills.ATH = abils.STR;    // Athletics        (STR)
    skills.DEC = abils.CHA;    // Deception        (CHA)
    skills.HIS = abils.INT;    // History          (INT)
    skills.INS = abils.WIS;    // Insight          (WIS)
    skills.ITM = abils.CHA;    // Intimidation     (CHA)
    skills.INV = abils.INT;    // Investigation    (INT)
    skills.MED = abils.WIS;    // Medicine         (WIS)
    skills.NAT = abils.INT;    // Nature           (INT)
    skills.PRC = abils.WIS;    // Perception       (WIS)
    skills.PRF = abils.CHA;    // Performance      (CHA)
    skills.PRS = abils.CHA;    // Persuasion       (CHA)
    skills.REL = abils.INT;    // Religion         (INT)
    skills.SLE = abils.DEX;    // Sleight of Hand  (DEX)
    skills.STL = abils.DEX;    // Stealth          (DEX)
    skills.SUR = abils.WIS;    // Survival         (WIS)

    output("character created", VB_CODE);
}

Character::Character(Ability ab, Skills sk)
    :abils(ab),
     skills(sk) {
    NameGenerator ng;

    name = ng.make_name();

    output("character created", VB_CODE);
}

Character::~Character() {
    // TODO nothing yet
}

/* TODO format a ASCII text version of a character sheet */
string Character::to_string() {
    string ret("");

    ret += "~~~ " + name + " ~~~\n";

    ret += "STR: "+ std::to_string(abils.STR) + "\n";
    ret += "DEX: "+ std::to_string(abils.DEX) + "\n";
    ret += "CON: "+ std::to_string(abils.CON) + "\n";
    ret += "INT: "+ std::to_string(abils.INT) + "\n";
    ret += "WIS: "+ std::to_string(abils.WIS) + "\n";
    ret += "CHA: "+ std::to_string(abils.CHA) + "\n";

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