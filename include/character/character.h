/*
character-generator - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

/* NOTE: These are just the 5E character requirements */

/* an arrray that holds the EXP needed for each level */
const int levels[] = {
    300,          // Level 2
    900,          // Level 3
    2700,         // Level 4
    6500,         // Level 5
    14000,        // Level 6
    23000,        // Level 7
    34000,        // Level 8
    48000,        // Level 9
    64000,        // Level 10
    85000,        // Level 11
    100000,       // Level 12
    120000,       // Level 13
    140000,       // Level 14
    165000,       // Level 15
    195000,       // Level 16
    225000,       // Level 17
    265000,       // Level 18
    305000,       // Level 19
    355000        // Level 20
};

enum Alignment {
    LawfulGood,
    NeutralGood,
    ChaoticGood,
    
    LawfulNeutral,
    TrueNeutral,
    ChaoticNeutral,

    LawfulEvil,
    NeutralEvil,
    ChaoticEvil
};

enum Language {
    Common,    Dwarvish,   Elvish,
    Giant,     Gnomish,    Goblin,
    Halfling,  Orc,        Abyssal,
    Celestial, Draconic,   DeepSpeech,
    Infernal,  Primordial, Silvian,
    Undercommon
};

enum Gender {
    Male,
    Female,
    Agender
};

enum Size {
    Tiny,        // 2½ by 2½ ft.          [under 2 feet tall]
    Small,       // 5 by 5 ft.            [2 to 4 feet tall]
    Medium,      // 5 by 5 ft.            [4 to 8 feet tall]
    Large,       // 10 by 10 ft.          [8 to 12 feet tall]
    Huge,        // 15 by 15 ft.          [12 to 16 feet tall]
    Gatgantuan   // 20 by 20 ft or larger [taller than 16 feet]
};

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

enum VisionType {
    Normal,
    Blindsight,
    DarkVision,
    TrueSight
};

struct Vision {
    VisionType type;    // type of sight
    int radius;         // radius of vision in feet (-1 == infinite IF unobstructed)
};

/* Generates a stat > 1 && < 20 */
int gen_stat();

/* Generates an array of stats > 1 && < 20 */
std::vector<int> ability_vector();
Ability ability_struct();

/* 
returns an integer representation of the passed abilities modifier 

NOTE(incomingstick): This is intended to always round down. Data loss is acceptable.
*/
inline int modifier(int abil) { return (abil - 10) / 2; };

// TODO take an in depth look at what should and should not be public here
class Character {
protected:
    struct Vision vision;               // information about the characters vision
    size_t age;                         // the age of the character
    Alignment alignment;                // the character alignment
    Size size;                          // the size type
    std::string firstName;              // the characters first name
    std::string lastName;               // the characters first name
    Ability abils;                      // struct of ability scores
    Skills skills;                      // struct of skill checks
    int curr_hp;                        // current hit points
    int temp_hp;                        // temporary hit points
    int max_hp;                         // maximum hit points
    int prof;                           // proficiency bonus
    int level;                          // character level total
    int cur_exp;                        // current experience
    int max_exp;                        // experience needed for next level
    std::vector<Language> languages;    // the array of known languages
    Gender gender;                      // the characters gender
    
    virtual void Initialize() = 0;
    
public:
    Character();
    Character(Ability ab);
    ~Character();

    static const int ID = 0x0000;       // an integer that represents the Character class
    static const std::string race;      // our characters race (also denoted via the subclass)

    
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

#endif /* CHARACTER_H_ */
