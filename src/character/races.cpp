/*
character-generator - race.cpp
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>
#include <cstdlib>

#include "names.h"
#include "character.h"

using namespace std;

const string Human::race = "Human";

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
    abils.CHA = ab.CHA + 1;    // Charisma

    Initialize();
}

void Human::Initialize() {
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

const string Dwarf::race = "Dwarf";

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
    abils.CHA = ab.CHA;     // Charisma

    Initialize();
}

void Dwarf::Initialize() {
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
    abils.CHA = ab.CHA;     // Charisma

    Initialize();
}

CharacterFactory::CharacterFactory() {
    // TODO populate race tree here and remove the above race vector
    head = allocate_node(Character::ID, false, NULL);
    
    race_node* human = allocate_node(Human::ID, true, head);
    
    race_node* dwarf = allocate_node(Dwarf::ID, true, head);
   
    race_node* hillDwarf = allocate_node(HillDwarf::ID, true, dwarf);
    
    dwarf->children = {
        hillDwarf
    };
    
    head->children = {
        human,
        dwarf
    };

    current = head;
}

CharacterFactory::~CharacterFactory() {
    //TODO clean up here
}

CharacterFactory::race_node* CharacterFactory::allocate_node(int raceID,
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


Character* CharacterFactory::NewCharacter(Ability ab) {
    switch(current->raceID) {
    case Human::ID : {
        return new Human(ab);
    }
        
    case Dwarf::ID : {
        return new Dwarf(ab);
    }
        
    case HillDwarf::ID : {
        return new HillDwarf(ab);
    }
    default: {
        return NULL;
    }
    }
}

Character* CharacterFactory::NewCharacter(int identifier) {
    switch(identifier) {
    case Human::ID : {
        return new Human;
    }
        
    case Dwarf::ID : {
        return new Dwarf;
    }
        
    case HillDwarf::ID : {
        return new HillDwarf;
    }
    default: {
        return NULL;
    }
    }
}

Character* CharacterFactory::NewCharacter(int identifier, Ability ab) {
    switch(identifier) {
    case Human::ID : {
        return new Human(ab);
    }
        
    case Dwarf::ID : {
        return new Dwarf(ab);
    }
        
    case HillDwarf::ID : {
        return new HillDwarf(ab);
    }
    default: {
        return NULL;
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
        }
    }
    
    return ret;
}

bool CharacterFactory::has_options() {
    if(!current->children.empty())
        return true;
    else return false;
}

void CharacterFactory::select_option(int index) {
    if(current == NULL) return;

    if(index < 0 || (size_t)index > current->children.size())
        return;
    
    if(current->children[index] != NULL)
        current = current->children[index];
}

int CharacterFactory::current_id() {
    if(current != NULL) return current->raceID;
    return -1;
}
