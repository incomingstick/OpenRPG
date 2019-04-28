/*
characters - race.cpp
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>
#include <cstdlib>

#include "names.h"
#include "character.h"

using namespace std;
using namespace ORPG;

/*
 * TODO(incomingstick): based on how much copy pasting I did, it is clear that
 * setting the name could get ugly quick if we don't turn as much of it into
 * functions.
 */

namespace ORPG {
    const string Human::race = "Human";

    Human::Human() {
        abilBonus.setScore(STR, 1);    // Strength
        abilBonus.setScore(DEX, 1);    // Dexterity
        abilBonus.setScore(CON, 1);    // Constitution
        abilBonus.setScore(INT, 1);    // Intelligence
        abilBonus.setScore(WIS, 1);    // Wisdom
        abilBonus.setScore(CHA, 1);    // Charisma

        Initialize();
    }

    void Human::Initialize() {
        // TODO

        Race::Initialize();
    }

    const string Dwarf::race = "Dwarf";

    Dwarf::Dwarf() {
        abilBonus.setScore(STR, 0);     // Strength
        abilBonus.setScore(DEX, 0);     // Dexterity
        abilBonus.setScore(CON, 2);     // Constitution
        abilBonus.setScore(INT, 0);     // Intelligence
        abilBonus.setScore(WIS, 0);     // Wisdom
        abilBonus.setScore(CHA, 0);     // Charisma

        Initialize();
    }

    void Dwarf::Initialize() {
        // TODO

        Race::Initialize();
    }

    HillDwarf::HillDwarf() {
        abilBonus.setScore(STR, 0);     // Strength
        abilBonus.setScore(DEX, 0);     // Dexterity
        abilBonus.setScore(CON, 2);     // Constitution
        abilBonus.setScore(INT, 0);     // Intelligence
        abilBonus.setScore(WIS, 1);     // Wisdom
        abilBonus.setScore(CHA, 0);     // Charisma

        Initialize();
    }

    const string Elf::race = "Elf";

    Elf::Elf() {
        abilBonus.setScore(STR, 0);      // Strength
        abilBonus.setScore(DEX, 2);      // Dexterity
        abilBonus.setScore(CON, 0);      // Constitution
        abilBonus.setScore(INT, 0);      // Intelligence
        abilBonus.setScore(WIS, 0);      // Wisdom
        abilBonus.setScore(CHA, 0);      // Charisma

        Initialize();
    }


    void Elf::Initialize() {

        Super::Initialize();
    }

    HighElf::HighElf() {
        abilBonus.setScore(STR,0);      // Strength
        abilBonus.setScore(DEX,2);      // Dexterity
        abilBonus.setScore(CON,0);      // Constitution
        abilBonus.setScore(INT,1);      // Intelligence
        abilBonus.setScore(WIS,0);      // Wisdom
        abilBonus.setScore(CHA,0);      // Charisma

        Initialize();
    }
}
