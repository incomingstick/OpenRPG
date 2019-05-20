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
#	ifndef character_EXPORTS
#   	define character_EXPORTS
#	endif
#	include "exports/character_exports.h"
#else
#	define CHARACTER_EXPORT
#endif

#include <map>

#include "core/types.h"

namespace ORPG {
    class CHARACTER_EXPORT Skill {
    public:
        Skill();
        Skill(int8 modifier, uint8 proficiencyBonus);
        ~Skill();
        void set(int8 newMod, uint8 newProficiencyBonus);
        void setMod(int8 newMod);
        void setProfBonus(uint8 newProficiencyBonus);
        int8 getMod();
        uint8 getProfBonus();

    private:
        /**
         * mod is what is added to rolls
         * profBonus is number of proficiencies, 
         *      0 if unproficient, 
         *      1 if proficient, 
         *      2 if double proficient
         * 
         * NOTE(incomingstick): What about half proficiency, like Bards?
         * 
         * both are chars to reduce memory usage
         **/
        int8 mod = 0;
        uint8 profBonus = 0;
    };

    enum CHARACTER_EXPORT EnumSkill {
        ACR, ANM, ARC, ATH, DEC,
        HIS, INS, ITM, INV, MED,
        NAT, PRC, PRF, PRS, REL,
        SLE, STL, SUR
    };

    class CHARACTER_EXPORT Skills {
        public:
        Skills();
        ~Skills();
        Skill* get(EnumSkill skill);

        int8 getMod(EnumSkill skill) {
            return skillsMap[skill]->getMod();
        }

        uint8 getProfBonus(EnumSkill skill);

        private:
        std::map <EnumSkill, Skill*> skillsMap;
    };
}

#endif /* SRC_SKILLS_H_ */