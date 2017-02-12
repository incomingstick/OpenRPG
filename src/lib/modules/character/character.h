/*
character-generator - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

struct Ability {
    int STR = 10;   // Strength
    int DEX = 10;   // Dexterity
    int CON = 10;   // Constitution
    int INT = 10;   // Intelligence
    int WIS = 10;   // Wisdom
    int CHA = 10;   // Charisma
};

// TODO better way??
// These are just the 5E Skills
struct Skills {
    int ACR = 0;    // Acrobatics       (DEX)
    int ANM = 0;    // Animal Handling  (WIS)
    int ARC = 0;    // Arcana           (INT)
    int ATH = 0;    // Athletics        (STR)
    int DEC = 0;    // Deception        (CHA)
    int HIS = 0;    // History          (INT)
    int INS = 0;    // Insight          (WIS)
    int ITM = 0;    // Intimidation     (CHA)
    int INV = 0;    // Investigation    (INT)
    int MED = 0;    // Medicine         (WIS)
    int NAT = 0;    // Nature           (INT)
    int PRC = 0;    // Perception       (WIS)
    int PRF = 0;    // Performance      (CHA)
    int PRS = 0;    // Persuasion       (CHA)
    int REL = 0;    // Religion         (INT)
    int SLE = 0;    // Sleight of Hand  (DEX)
    int STL = 0;    // Stealth          (DEX)
    int SUR = 0;    // Survival         (WIS)
};

// TODO take an in depth look at what should and should not be public here
class Character {
    private:
        Ability abils;
        Skills skills;
        int curr_hp;
        int temp_hp;
        int max_hp;
        int prof;
    public:
        Character(Ability ab, Skills sk);
        Character();
        ~Character();
        Ability copy_ability() { return abils; };
        Skills copy_skills() { return skills; };

        int gen_stat();

        /* accessor functions for ability score modifiers */
        int STR() { return abils.STR; };
        int DEX() { return abils.DEX; };
        int CON() { return abils.CON; };
        int INT() { return abils.INT; };
        int WIS() { return abils.WIS; };
        int CHA() { return abils.CHA; };

        /* accessor functions for ability score modifiers */
        int STR_MOD() { return (abils.STR - 10) / 2; };
        int DEX_MOD() { return (abils.DEX - 10) / 2; };
        int CON_MOD() { return (abils.CON - 10) / 2; };
        int INT_MOD() { return (abils.INT - 10) / 2; };
        int WIS_MOD() { return (abils.WIS - 10) / 2; };
        int CHA_MOD() { return (abils.CHA - 10) / 2; };

        int passive_stat(int stat) { return 8 + prof + stat; };
};

#endif /* SRC_CHARACTER_H_ */