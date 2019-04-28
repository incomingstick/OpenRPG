/*
characters - ability-scores.h
Created on: Apr 27, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_ABILITY_SCORES_H_
#define SRC_ABILITY_SCORES_H_

#include <map>
#include "core/utils.h"

namespace ORPG {
    /*
     * This currently assumes 5e. What can we do to abstract outside of
     * that space?
     */
    class AbilityScore {
    public:
        AbilityScore();
        AbilityScore(int8 score, bool isProf);
        ~AbilityScore();
        void set(int8 newScore, bool isProf);
        void setScore(int8 newScore);
        void setIsProf(bool isProf);
        int8 getScore();
        int8 getMod();
        bool isProf();

    private:
        int8 score = 0;
        bool prof = false;
	};

	enum EnumAbilityScore {
		STR, DEX, CON,
		INT, WIS, CHA,
	};

	class AbilityScores {
    public:
        AbilityScores();
        ~AbilityScores();
        AbilityScore* get(EnumAbilityScore ability);

        void setScore(EnumAbilityScore ability, uint8 score);
        void setIsProf(EnumAbilityScore ability, bool isProf);
        void setCurrentProf(uint8 newProf);

        uint8 getScore(EnumAbilityScore ability) {
            return scoresMap[ability]->getScore();
        };
        
        int8 getMod(EnumAbilityScore ability) {
            return scoresMap[ability]->getMod();
        };

        int8 getSave(EnumAbilityScore ability) {
            return scoresMap[ability]->isProf() ?
                    scoresMap[ability]->getMod() + curProf :
                    scoresMap[ability]->getMod();
        };

        uint8 getCurrentProf() {
            return curProf;
        };

    private:
        /* The current proficiency bonus to add */
        uint8 curProf = 0;

        std::map <EnumAbilityScore, AbilityScore*> scoresMap;
	};
}

#endif /* SRC_ABILITY_SCORES_H_ */