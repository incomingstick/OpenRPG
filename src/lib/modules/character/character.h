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

/*
TODO better way?? We need to also keep track of what
skills have proficiency (or double prof)

Note: These are just the 5E Skills
*/
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

/* Generates a stat > 1 && < 20 */
int gen_stat();

/* Generates an array of stats > 1 && < 20 */
std::vector<int> abil_arr();

/* returns an integer representation of the passed abilities modifier */
inline int modifier(int abil) { return (abil - 10) / 2; };

// TODO take an in depth look at what should and should not be public here
class Character {
    private:
        std::string name;       // the characters name
        Ability abils;          // collection of ability scores
        Skills skills;          // collection of skill checks
        int curr_hp;            // current hit points
        int temp_hp;            // temporary hit points
        int max_hp;             // maximum hit points
        int prof;               // proficiency bonus
        int level;              // character level total
        int exp;                // current experience
        int max_exp;            // experience needed for next level
    public:
        Character();
        Character(Ability ab);
        Character(Ability ab, Skills sk);
        ~Character();

        // Returns a copy of our Ability abils struct   
        Ability get_ability_copy() { return abils; };

        // Returns a copy of our Skills skills struct
        Skills get_skills_copy() { return skills; };

        /* accessor functions for ability score modifiers */
        int STR() { return abils.STR; };
        int DEX() { return abils.DEX; };
        int CON() { return abils.CON; };
        int INT() { return abils.INT; };
        int WIS() { return abils.WIS; };
        int CHA() { return abils.CHA; };

        /* accessor functions for ability score modifiers */
        int STR_MOD() { return modifier(abils.STR); };
        int DEX_MOD() { return modifier(abils.DEX); };
        int CON_MOD() { return modifier(abils.CON); };
        int INT_MOD() { return modifier(abils.INT); };
        int WIS_MOD() { return modifier(abils.WIS); };
        int CHA_MOD() { return modifier(abils.CHA); };

        // allows quick conversion of a skill for its passive check
        int passive_stat(int stat) { return 8 + prof + stat; };

        std::string to_string();
};

#endif /* SRC_CHARACTER_H_ */