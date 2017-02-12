/*
character-generator - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include "utils.h"
#include "die.h"
#include "character.h"

using namespace std;

Character::Character(Ability ab, Skills sk)
    :abils(ab),
     skills(sk) {
    output("character created", VB_CODE);
}

Character::Character() {
    output("character created", VB_CODE);

    abils.STR = gen_stat();
    abils.DEX = gen_stat();
    abils.CON = gen_stat();
    abils.INT = gen_stat();
    abils.WIS = gen_stat();
    abils.CHA = gen_stat();
}

Character::~Character() {
    // TODO nothing yet
}

int Character::gen_stat() {
    Die d6(6);

    return d6.roll() + d6.roll() + 6;
}