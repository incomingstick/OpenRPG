/*
character-generator - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_
#include <map>

using namespace std;

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

class Skill {
	public:
		Skill(void);
		Skill(char modifier, unsigned char proficiency);
		~Skill(void);
		void set(char newMod, unsigned char newProficiency);
		void setMod(char newMod);
		void setProf(unsigned char newProficiency);
		char getMod(void);
		unsigned char getProf(void);

	private:
		char mod = 0;
		unsigned char prof = 0;
};

enum EnumSkill{
    ACR, ANM, ARC, ATH, DEC, 
    HIS, INS, ITM, INV, MED, 
    NAT, PRC, PRF, PRS, REL, 
    SLE, STL, SUR
};

class Skills {
	public:
		Skills(void);
		~Skills(void);
		Skill* get(EnumSkill skill);
		char getMod(EnumSkill skill) {
			return skillsMap[skill]->getMod();
		}
		unsigned char getProf(EnumSkill skill);

	private:
		std::map <EnumSkill, Skill*> skillsMap = {
			{ ACR, new Skill(0, 0) },    // Acrobatics       (DEX)
			{ ANM, new Skill(0, 0) },    // Animal Handling  (WIS)
			{ ARC, new Skill(0, 0) },    // Arcana           (INT)
			{ ATH, new Skill(0, 0) },    // Athletics        (STR)
			{ DEC, new Skill(0, 0) },    // Deception        (CHA)
			{ HIS, new Skill(0, 0) },    // History          (INT)
			{ INS, new Skill(0, 0) },    // Insight          (WIS)
			{ ITM, new Skill(0, 0) },    // Intimidation     (CHA)
			{ INV, new Skill(0, 0) },    // Investigation    (INT)
			{ MED, new Skill(0, 0) },    // Medicine         (WIS)
			{ NAT, new Skill(0, 0) },    // Nature           (INT)
			{ PRC, new Skill(0, 0) },    // Perception       (WIS)
			{ PRF, new Skill(0, 0) },    // Performance      (CHA)
			{ PRS, new Skill(0, 0) },    // Persuasion       (CHA)
			{ REL, new Skill(0, 0) },    // Religion         (INT)
			{ SLE, new Skill(0, 0) },    // Sleight of Hand  (DEX)
			{ STL, new Skill(0, 0) },    // Stealth          (DEX)
			{ SUR, new Skill(0, 0) }    // Survival         (WIS)
		};
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
 * returns an integer representation of the passed abilities modifier 
 * 
 * NOTE(incomingstick): This is intended to always round down. Data loss is acceptable.
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
    
		void Initialize();

	public:
		Character();
		Character(Ability ab);
		~Character();
    
		std::string format_mod(int mod, int spaces);
    
		void update_skills();

		// an integer that represents the Character class
		static const int ID = 0x0000;
		// our characters race (also denoted via the subclass)		
		static const std::string race;      

		// Returns a copy of our Ability abils struct
		Ability get_ability_copy() { return abils; };

		// Returns a copy of our Skills skills struct
		// NOTE(var_username): Commented out because I broke it
		// Skills get_skills_copy() { return skills; };
    
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
		std::string to_sheet();
};

#endif /* CHARACTER_H_ */
