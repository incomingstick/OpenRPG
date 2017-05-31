/*
character-generator - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>

#include "core/utils.h"
#include "roll.h"
#include "names.h"

#include "character.h"

using namespace std;

Character::Character() {
    abils.STR = 10;    // Strength
    abils.DEX = 10;    // Dexterity
    abils.CON = 10;    // Constitution
    abils.INT = 10;    // Intelligence
    abils.WIS = 10;    // Wisdom
    abils.CHA = 10;    // Charisma
}

Character::Character(Ability ab)
    :abils(ab) {
}

Character::~Character() {
    // TODO nothing yet
}

/* TODO format a ASCII text version of a character sheet */
string Character::to_string() {
    string ret("");

    ret += "~~~ " + firstName + " " + lastName + " ~~~\n";

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
