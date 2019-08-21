/*
characters - skills.h
Created on: Apr 27, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_SKILLS_H_
#define SRC_SKILLS_H_

#ifdef _WIN32
#	include "exports/character_exports.h"
#else
#	define CHARACTER_EXPORT
#endif

#include <map>

#include "core/types.h"

#define UNPROFICIENT            0
#define PROFICIENT              1
#define DOUBLE_PROFICIENT       2
#define HALF_PROFICIENT         3

namespace ORPG {
    /**
     * An Skill represents the modifier bonus of some skill. A modifier (mod)
     * is an unsigned 8-bit integer. A Skill has the profBonus property, a
     * unsigned 8-bit integer value denoting how the modifier bonus should be
     * added to a check of the given Skill.
     *
     * This currently assumes 5e. What can we do to abstract outside of
     * that space?
     **/
    class CHARACTER_EXPORT Skill {
    private:
        /* mod is what the proficiency modifier added to rolls */
        int8 mod = 0;

        /**
         * profBonus is number of proficiencies:    
         *      UNPROFICIENT            0
         *      PROFICIENT              1
         *      DOUBLE_PROFICIENT       2
         *      HALF_PROFICIENT         3
         * 
         * NOTE(incomingstick): What about half proficiency, like Bards?
         **/
        uint8 profBonus = 0;

    public:
        /**
         * mod is what is added to rolls
         * Prof is number of proficiencies, 0 if unproficient, 1 if proficient, 2 if doubly proficient
         *
         * both are chars to reduce memory usage
         **/
        Skill();

        /**
         * @desc Constructor for a new Skill object that takes an int8 and to set
         * as the modifier, and a uint8 to set as the proficiencyBonus
         *
         * @param int8 modifier - an int8 to set as the mod (modifier)
         * @param uint8 proficiencyBonus - a uint8 to set as the proficiency level
         **/
        Skill(int8 modifier, uint8 proficiencyBonus);

        /**
         * @desc Setter function that combines the setting of the modifier and
         * proficiency bonus into a single function. To set the values it just
         * calls their own individual setters.
         *
         * @param int8 modifier - the int8 to set as the new mod
         * @param uint8 newPoficiencyBonus - the uint8 to set as the new profBonus
         **/
        void set(int8 newMod, uint8 newProficiencyBonus);

        /**
         * @desc Setter function for the mod (modifier) this Skill provides
         *
         * @param int8 modifier - the int8 to set as the new mod
         **/
        void setMod(int8 newMod);

        /**
         * @desc Setter function for the profBonus of this Skill
         *
         * @param uint8 newPoficiencyBonus - the uint8 to set as the new profBonus
         **/
        void setProfBonus(uint8 newProficiencyBonus);

        /**
         * @desc Get the modifier bonus of the given EnumSkill contained
         * within this Skill object
         *
         * @return int8 - the modifier bonus of the queried skill
         **/
        int8 getMod();

        /**
         * @desc Get the proficiency bonus level that is to be used when
         * calculating the amount proficiency to add to this skills
         * modifier bonus.
         *
         * Currently proficiency bonus levels are defined as follows:
         *      0 - if unproficient
         *      1 - if proficient
         *      2 - if double proficient
         *
         * @return uint8 - the proficiency bonus level that is used when calculating
         * the amount proficiency to add to this skills modifier bonus
         **/
        uint8 getProf();

        /**
         * @desc Converts this Skills data to std::string format. It is retruned in the
         * following format:
         * 
         * (+/-)[value]
         * Example: "+3"
         *
         * @return string - a string 
         **/
        std::string to_string();
    };

    /**
     * An enum containing 3-char representations of the D&D 5e skill
     * system: ACR, ANM, ARC, ATH, DEC, HIS, INS, ITM, INV, MED, NAT, PRC,
     * PRF, PRS, REL, SLE, STL, SUR
     **/
    enum CHARACTER_EXPORT EnumSkill {
        ACR,    // Acrobatics       (DEX)
        ANM,    // Animal Handling  (WIS)
        ARC,    // Arcana           (INT)
        ATH,    // Athletics        (STR)
        DEC,    // Deception        (CHA)
        HIS,    // History          (INT)
        INS,    // Insight          (WIS)
        ITM,    // Intimidation     (CHA)
        INV,    // Investigation    (INT)
        MED,    // Medicine         (WIS)
        NAT,    // Nature           (INT)
        PRC,    // Perception       (WIS)
        PRF,    // Performance      (CHA)
        PRS,    // Persuasion       (CHA)
        REL,    // Religion         (INT)
        SLE,    // Sleight of Hand  (DEX)
        STL,    // Stealth          (DEX)
        SUR     // Survival         (WIS)
    };

    /**
     * Skills is a class to assist in working with the Skill class. It creates
     * a map, pairing EnumSkill's to Skill's.
     * 
     * This currently assumes 5e. What can we do to abstract outside of
     * that space?
     **/
    class CHARACTER_EXPORT Skills {
    private:
        /* a std::map that maps EnumSkill's to Skill pointers */
        std::map <EnumSkill, Skill*> skillsMap;
        
        /* this is a pointer to our container (likely a character, however
            we cannot assume it is) that expects a function named
            get_proficiency_bonus that returns an integer */
        void* container;

        /* to_string method used internally for iterative purposes */
        static std::string internal_to_string(std::pair<EnumSkill, Skill*>);

    public:
        /**
         * @desc Constructor for the Skills class that maps Skill classes to
         * their respective EnumSkill, with a modifier of 0 and proficiency
         * bonus level of 0.
         **/
        Skills(void* owner);

        /**
         * @desc Desctructor function for the Skills class that ensures
         * the internal std::map skillsMap is deleted
         **/
        ~Skills();

        /**
         * @desc Getter function that returns a pointed to the Skill object
         * of the given EnumSkill skill.
         *
         * @param EnumSkill skill - the skill to query
         *
         * @return Skill* - a pointer to the Skill object of the given
         * EnumSkill
         **/
        Skill* get(EnumSkill skill) {
            return skillsMap[skill];
        };

        /**
         * @desc Get the modifier bonus of the given EnumSkill contained
         * within this Skills object
         *
         * @param EnumSkill skill - the skill to query
         *
         * @return int8 - the modifier bonus of the queried skill
         **/
        int8 getMod(EnumSkill skill);

        /**
         * @desc Get the proficiency bonus level that is to be used when
         * calculating the amount proficiency to add to the given skills
         * modifier bonus.
         *
         * Currently proficiency bonus levels are defined as follows:
         *      0 - if unproficient
         *      1 - if proficient
         *      2 - if double proficient
         *
         * @param EnumSkill skill - the skill to query
         *
         * @return uint8 - the proficiency bonus level that is used when calculating
         * the amount proficiency to add to the given skills modifier bonus
         **/
        uint8 getProfBonus(EnumSkill skill) {
            return skillsMap[skill]->getProf();
        };

        /**
         * @desc Converts this Skills data to std::string format. It is retruned in the
         * following format:
         * 
         * {Skill}: (+/-)[value]
         * Example: "ACR: +3"
         *
         * @return string - a string 
         **/
        std::string to_string();
    };
}

#endif /* SRC_SKILLS_H_ */