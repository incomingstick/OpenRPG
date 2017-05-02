/*
character-generator - race.cpp
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>

#include "names.h"
#include "character.h"

using namespace std;

Human::Human() {
    abils.STR = gen_stat() + 1;    // Strength
    abils.DEX = gen_stat() + 1;    // Dexterity
    abils.CON = gen_stat() + 1;    // Constitution
    abils.INT = gen_stat() + 1;    // Intelligence
    abils.WIS = gen_stat() + 1;    // Wisdom
    abils.CHA = gen_stat() + 1;    // Charisma

    Initialize();
}

Human::Human(Ability ab) {
    abils.STR = ab.STR + 1;    // Strength
    abils.DEX = ab.DEX + 1;    // Dexterity
    abils.CON = ab.CON + 1;    // Constitution
    abils.INT = ab.INT + 1;    // Intelligence
    abils.WIS = ab.WIS + 1;    // Wisdom
    abils.CHA = ab.STR + 1;    // Charisma

    Initialize();
}

void Human::Initialize() {
    race = races[0]; // see races TODO at the top
    NameGenerator ng(race);

    firstName = ng.make_first();
    lastName = ng.make_last();

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = DEX_MOD();    // Acrobatics       (DEX)
    skills.ANM = WIS_MOD();    // Animal Handling  (WIS)
    skills.ARC = INT_MOD();    // Arcana           (INT)
    skills.ATH = STR_MOD();    // Athletics        (STR)
    skills.DEC = CHA_MOD();    // Deception        (CHA)
    skills.HIS = INT_MOD();    // History          (INT)
    skills.INS = WIS_MOD();    // Insight          (WIS)
    skills.ITM = CHA_MOD();    // Intimidation     (CHA)
    skills.INV = INT_MOD();    // Investigation    (INT)
    skills.MED = WIS_MOD();    // Medicine         (WIS)
    skills.NAT = INT_MOD();    // Nature           (INT)
    skills.PRC = WIS_MOD();    // Perception       (WIS)
    skills.PRF = CHA_MOD();    // Performance      (CHA)
    skills.PRS = CHA_MOD();    // Persuasion       (CHA)
    skills.REL = INT_MOD();    // Religion         (INT)
    skills.SLE = DEX_MOD();    // Sleight of Hand  (DEX)
    skills.STL = DEX_MOD();    // Stealth          (DEX)
    skills.SUR = WIS_MOD();    // Survival         (WIS)

    curr_hp = 10;                   // current hit points
    temp_hp = 10;                   // temporary hit points
    max_hp = 10;                    // maximum hit points
    prof = 2;                       // proficiency bonus
    level = 1;                      // character level total
    cur_exp = 0;                    // current experience
    max_exp = levels[level - 1];    // experience needed for next level
}

Dwarf::Dwarf() {
    abils.STR = gen_stat();     // Strength
    abils.DEX = gen_stat();     // Dexterity
    abils.CON = gen_stat() + 2; // Constitution
    abils.INT = gen_stat();     // Intelligence
    abils.WIS = gen_stat();     // Wisdom
    abils.CHA = gen_stat();     // Charisma

    Initialize();
}

Dwarf::Dwarf(Ability ab) {
    abils.STR = ab.STR;     // Strength
    abils.DEX = ab.DEX;     // Dexterity
    abils.CON = ab.CON + 2; // Constitution
    abils.INT = ab.INT;     // Intelligence
    abils.WIS = ab.WIS;     // Wisdom
    abils.CHA = ab.STR;     // Charisma

    Initialize();
}

void Dwarf::Initialize() {
    race = races[1]; /* see races TODO at the top
                        NOTE(incomingstick): this is supposed to JUST
                        be dwarf as the subrace no longer matters*/

    NameGenerator ng(race);

    firstName = ng.make_first();
    lastName = ng.make_last();

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = DEX_MOD();    // Acrobatics       (DEX)
    skills.ANM = WIS_MOD();    // Animal Handling  (WIS)
    skills.ARC = INT_MOD();    // Arcana           (INT)
    skills.ATH = STR_MOD();    // Athletics        (STR)
    skills.DEC = CHA_MOD();    // Deception        (CHA)
    skills.HIS = INT_MOD();    // History          (INT)
    skills.INS = WIS_MOD();    // Insight          (WIS)
    skills.ITM = CHA_MOD();    // Intimidation     (CHA)
    skills.INV = INT_MOD();    // Investigation    (INT)
    skills.MED = WIS_MOD();    // Medicine         (WIS)
    skills.NAT = INT_MOD();    // Nature           (INT)
    skills.PRC = WIS_MOD();    // Perception       (WIS)
    skills.PRF = CHA_MOD();    // Performance      (CHA)
    skills.PRS = CHA_MOD();    // Persuasion       (CHA)
    skills.REL = INT_MOD();    // Religion         (INT)
    skills.SLE = DEX_MOD();    // Sleight of Hand  (DEX)
    skills.STL = DEX_MOD();    // Stealth          (DEX)
    skills.SUR = WIS_MOD();    // Survival         (WIS)

    curr_hp = 10;                   // current hit points
    temp_hp = 10;                   // temporary hit points
    max_hp = 10;                    // maximum hit points
    prof = 2;                       // proficiency bonus
    level = 1;                      // character level total
    cur_exp = 0;                    // current experience
    max_exp = levels[level - 1];    // experience needed for next level
}

HillDwarf::HillDwarf() {
    abils.STR = gen_stat();     // Strength
    abils.DEX = gen_stat();     // Dexterity
    abils.CON = gen_stat() + 2; // Constitution
    abils.INT = gen_stat();     // Intelligence
    abils.WIS = gen_stat() + 1; // Wisdom
    abils.CHA = gen_stat();     // Charisma

    Initialize();
}

HillDwarf::HillDwarf(Ability ab) {
    abils.STR = ab.STR;     // Strength
    abils.DEX = ab.DEX;     // Dexterity
    abils.CON = ab.CON + 2; // Constitution
    abils.INT = ab.INT;     // Intelligence
    abils.WIS = ab.WIS + 1; // Wisdom
    abils.CHA = ab.STR;     // Charisma

    Initialize();
}

/* TODO find a better way than hard coding this and its values 
   Perhaps with preprocessor identifiers??? We need to be able to
   tree out the races/subraces/varients. As an example, humans do
   not have subraces per se, but they have an OPTIONAL variant
   (+2 of players choice and a feat) whereas Dwarfs have Hill Dwarfs
   or Mountain Dwarfs, and you MUST pick ONE subrace.*/
vector<string> races = {
    "Human",
    "Dwarf",
    "Hill Dwarf"
};

CharacterFactory::CharacterFactory() {
    // TODO populate race tree here and remove the above race vector
    /* head->parent = head;
    head->race = NULL;
    head->required = false;
    
    Node* human;

    human->race = new Human;
    human->required = true;
    human->parent = head;
    
    Node* dwarf;

    dwarf->race = new Dwarf;
    dwarf->required = true;
    dwarf->parent = head;
   
    Node* hillDwarf;

    hillDwarf->race = new HillDwarf;
    hillDwarf->required = true;
    hillDwarf->parent = head;

    dwarf->children[] = {
        hillDwarf
    };
    
    head->children[] = {
        human,
        dwarf
    }; */
};

CharacterFactory::~CharacterFactory() {
    //TODO clean up here
};

CharacterFactory::Node* CharacterFactory::allocate_node(Node* parent,
                                             Node* children[],
                                             Character* race,
                                             bool required) {
    Node* node = new Node;
    return node;
}

Character* CharacterFactory::NewCharacter(string race) {
    if(race == races[1]) return new Dwarf;
    if(race == races[2]) return new HillDwarf;
    else return new Human;
}
