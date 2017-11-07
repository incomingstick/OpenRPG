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

Character::Character(Ability ab)
    :abils(ab) {
}

Character::~Character() {
    // TODO nothing yet
}

void Character::Initialize() {
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
