/*
characters - ability-scores.h
Created on: Apr 27, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_ABILITY_SCORES_H_
#define SRC_ABILITY_SCORES_H_

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
    /**
     * An AbilityScore represents the score of some ability. A score is an
     * unsigned 8-bit integer. An AbilityScore has the isProf property, a
     * boolean value denoting whether or not a proficiency bonus should be
     * added to the save modifier of the given AbilityScore. A modifier is
     * defined as:
     * 
     * Mod = floor((Score - 10) / 2);
     * 
     * This currently assumes 5e. What can we do to abstract outside of
     * that space?
     */
    class CHARACTER_EXPORT AbilityScore {
    public:
        /**
         * @desc Constructor for AbilityScore that is passed no arguments.
         * It sets score equal to a randomly generated number between 8 and 18,
         * and sets isProf to false.
         */
        AbilityScore();
        
        /**
         * @desc Constructor for AbilityScore that is passed two arguments.
         * It sets this->score equal to score and sets this->isProf to isProf.
         * 
         * @param uint8 score - the unsigned 8-bit integer score value to set. 
         * @param bool isProf - a boolean value denoting whether or not a
         * proficiency bonus should be added to the save of the given AbilityScore
         */
        AbilityScore(uint8 score, bool isProf);
        
        /**
         * @desc Deconstructor for AbilityScore that is passed no arguments.
         * Currently does nothing, and the compiler handles deconstruction.
         */
        ~AbilityScore();
        
        /**
         * @desc Setter method for score and isProf. isProf is a boolean
         * representation of whether or not a proficiency bonus should be added to
         * the save of the given AbilityScore.
         * 
         * @param uint8 score - the unsigned 8-bit integer score value to set. 
         * @param bool isProf - a boolean value denoting whether or not a
         * proficiency bonus should be added to the save of the given AbilityScore
         */
        void set(uint8 newScore, bool isProf);
        
        /**
         * @desc Setter method for an AbilityScore's score.
         * 
         * @param uint8 score - the unsigned 8-bit integer score value to set. 
         */
        void setScore(uint8 newScore);
        
        /**
         * @desc Setter method for the isProf property. isProf is a boolean
         * representation of whether or not a proficiency bonus should be
         * added for the save of the given AbilityScore.
         * 
         * @param bool isProf - a boolean value denoting whether or not a
         * proficiency bonus should be added to the save of the given AbilityScore
         */
        void setIsProf(bool isProf);
        
        /**
         * @desc Accessor method for an AbilityScore's score.
         * 
         * @return uint8 - an unsigned 8-bit integer of the AbilityScore's score
         */
        uint8 getScore();
        
        /**
         * @desc Accessor method for the AbilityScore's modifier.
         * A modifier is defined as:
         * 
         * Mod = floor((Score - 10) / 2);
         * 
         * @return int8 - an 8-bit integer of the AbilityScore's modifier
         */
        int8 getMod();

        /**
         * @desc Accessor method for the isProf property. The current Proficiency
         * bonus should be added to any AbilityScore's modifier that has isProf
         * set to true, otherwise it is just the AbilityScore's modifier. It is
         * up to the implementer to handle that addition.
         * 
         * @return bool - a boolean value denoting whether or not a proficiency
         * bonus should be added to the save of this AbilityScore
         */
        bool isProf();

    private:
        /* An unsigned 8-bit integer value representing the score of this ability */
        uint8 score = 0;

        /** 
         * A boolean value denoting whether or not a proficiency bonus should
         * be added to the score.
         */
        bool prof = false;
	};

    /**
     * An enum containing the 3-char representation of the standard
     * pen and paper ability system: STR, DEX, CON, INT, WIS, CHA
     */
	enum CHARACTER_EXPORT EnumAbilityScore {
		STR, DEX, CON,
		INT, WIS, CHA
	};

    /**
     * AbilityScores is a class to assist in working with the AbilityScore
     * class. It creates a map, pairing EnumAbilityScore's to AbilityScore's.
     * Currently this follows 5e rules.
     */
	class CHARACTER_EXPORT AbilityScores {
    public:
        /**
         * @desc Constructor for AbilityScores that is passed no arguments.
         * It sets all ability scores equal to 10 and isProf to false.
         */
        AbilityScores();

        /**
         * @desc Deconstructor for AbilityScores that is passed no arguments.
         * Currently does nothing, and the compiler handles deconstruction.
         */
        ~AbilityScores();

        /**
         * @desc Setter method for an AbilityScore's score and isProf, denoted
         * by EnumAbilityScore ability. isProf is a boolean representation of whether
         * or not a proficiency bonus should be added to the save of the given
         * AbilityScore.
         * 
         * @param EnumAbilityScore ability - the AbilityScore score to query
         * @param uint8 score - the unsigned 8-bit integer score value to set. 
         * @param bool isProf - a boolean value denoting whether or not a
         * proficiency bonus should be added to the save of the given AbilityScore
         */
        void set(EnumAbilityScore ability, uint8 newScore, bool isProf);

        /**
         * @desc Accessor method for an AbilityScore, denoted by
         * EnumAbilityScore ability. This returns the pointer of the queried
         * AbilityScore.
         * 
         * @param EnumAbilityScore ability - the AbilityScore score to query
         * 
         * @return AbilityScore* - an pointer to the AbilityScore's denoted by
         * EnumAbilityScore ability
         */
        AbilityScore* get(EnumAbilityScore ability);

        /**
         * @desc Setter method for an AbilityScore's score, denoted
         * by EnumAbilityScore ability. A modifier is defined as:
         * 
         * Mod = floor((Score - 10) / 2);
         * 
         * @param EnumAbilityScore ability - the AbilityScore score to query
         * @param uint8 score - the unsigned 8-bit integer score value to set. 
         */
        void setScore(EnumAbilityScore ability, uint8 score);

        /**
         * @desc Setter method for the isProf property of AbilityScore, denoted by
         * EnumAbilityScore ability. isProf is a boolean representation of whether
         * or not a proficiency bonus should be added to the save of the given
         * AbilityScore.
         * 
         * @param EnumAbilityScore ability - the AbilityScore score to query
         * @param bool isProf - a boolean value denoting whether or not a
         * proficiency bonus should be added to the save of the given AbilityScore
         */
        void setIsProf(EnumAbilityScore ability, bool isProf);

        /**
         * @desc Setter method for curProf, the current Proficiency Bonus
         * that is added to any AbilityScore that has isProf set to true.
         * 
         * @param uint8 newProf - a unsigned 8-bit integer containing the current
         * Proficiency bonus that is added to any AbilityScore that has isProf
         * set to true
         */
        void setCurrentProf(uint8 newProf);

        /**
         * @desc Accessor method for an AbilityScore's score, denoted
         * by EnumAbilityScore ability.
         * 
         * @param EnumAbilityScore ability - the AbilityScore score to query
         * 
         * @return uint8 - an unsigned 8-bit integer of the AbilityScore's score
         */
        uint8 getScore(EnumAbilityScore ability) {
            return scoresMap[ability]->getScore();
        };
        
        /**
         * @desc Accessor method for an AbilityScore's modifier, denoted
         * by EnumAbilityScore ability. A modifier is defined as:
         * 
         * Mod = floor((Score - 10) / 2);
         * 
         * @param EnumAbilityScore ability - the ability score modifier to query
         * 
         * @return int8 - an 8-bit integer of the AbilityScore's modifier
         */
        int8 getMod(EnumAbilityScore ability) {
            return scoresMap[ability]->getMod();
        };

        /**
         * @desc Accessor method for an AbilityScore's isProf property, denoted
         * by EnumAbilityScore ability. The current Proficiency bonus is added
         * to any AbilityScore's modifier that has isProf set to true,
         * otherwise it is just the AbilityScore's modifier.
         * 
         * @param EnumAbilityScore ability - the ability score modifier to query
         * 
         * @return bool - a boolean value denoting whether or not a proficiency
         * bonus should be added to the save of the given AbilityScore
         */
        bool isProf(EnumAbilityScore ability) {
            return scoresMap[ability]->isProf();
        }

        /**
         * @desc Accessor method for an AbilityScore's save modifier, denoted
         * by EnumAbilityScore ability. The current Proficiency bonus is added
         * to any AbilityScore's modifier that has isProf set to true,
         * otherwise it is just the AbilityScore's modifier.
         * 
         * @param EnumAbilityScore ability - the AbilityScore save to query
         * 
         * @return int8 - an 8-bit integer of the AbilityScore's save modifier
         */
        int8 getSave(EnumAbilityScore ability) {
            return scoresMap[ability]->isProf() ?
                    this->getMod(ability) + curProf :
                    this->getMod(ability);
        };

        /**
         * @desc Accessor method for curProf, the current Proficiency Bonus
         * that is added to any AbilityScore that has isProf set to true.
         * 
         * @return uint8 - a unsigned 8-bit integer containing the current
         * Proficiency bonus that is added to any AbilityScore that has isProf
         * set to true.
         */
        uint8 getCurrentProf() {
            return curProf;
        };

    private:
        /* The current unsigned 8-bit integer proficiency bonus to add */
        uint8 curProf = 0;

        /* The map relating EnumAbilityScore to their respective AbilityScore */
        std::map <EnumAbilityScore, AbilityScore*> scoresMap;
	};
}

#endif /* SRC_ABILITY_SCORES_H_ */