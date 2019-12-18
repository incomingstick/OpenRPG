/*
characters - classes.h
Created on: Aug 22, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CLASSES_H_
#define SRC_CLASSES_H_

#ifdef _WIN32
#	include "exports/character_exports.h"
#else
#	define CHARACTER_EXPORT
#endif

#include <vector>

// TODO(incomingstick): this is likely too broad for includes, lets minimize
#include "roll/die.h"
#include "skills.h"

/**
 * NOTE(incomingstick): This note may get moved to a better place, but I want to
 * make sure all devs understand our ORPG ID system. Ideally we should be giving
 * any "unique" class an ID to help separate it from other classes with similar
 * parents. This is not unique for each created object, but for the class itself.
 * Please follow these rules for ID's:
 * 
 *  - All ID's are hex double words in length (32bit) 0xFFFFFFFF
 *  - ALL ID's start with 0x1b8 within the ORPG project and maybe be referred to
 *      as the "ORPG base ID index"
 *  - The last digit of ORPG base ID index is reserved for the class space we are
 *      within. (e.g Race class IDs start with 0x1b80)
 *  - The remaining 16bits are reserved for ID's within that Class space.
 *      (e.g the HighElf is 0x1b800021)
 * 
 * NOTE(incomingstick): a single bit for the class space is likely not going to be
 * enough, so then how many will?
 **/

namespace ORPG {
    /* Predefine the CharacterClass parent class so that anything defined in the Character namespace
        may use it in the event that they need access to it */
    class CharacterClass;

    namespace Characters {
        /**
         * @desc This function returns a random CharacterClass::ID as an unsigned integer,
         * from the available classes.
         *
         * TODO(incomingstick): Is hardcoding this as a switch the best
         * option? This likely won't scale well.
         * 
         * @return uint - the randomly selected CharacterClass ID
         **/
        const uint CHARACTER_EXPORT random_class_id();

        /**
         * @desc This function takes in an integer, ideally a CharacterClass::ID,
         * creates a new CharacterClass of that ID type and returns a pointer to it.
         * If an ID less than 0 is passed we instead will randomly select a 
         * CharacterClass type to return.
         * 
         * @param const int identifier - the CharacterClass of the class to be generated
         * 
         * @return CharacterClass* - a pointer to the newly created CharacterClass
         **/
        CHARACTER_EXPORT CharacterClass* select_character_class(const int identifier = -1);

        /**
         * @desc This function returns a pointer to a random new CharacterClass,
         * from the available classes.
         *
         * @return CharacterClass* - a pointer to a random new CharacterClass
         **/
        inline CHARACTER_EXPORT CharacterClass* new_random_character_class() { return select_character_class(); };
    }

    class CHARACTER_EXPORT CharacterClass {
    protected:
        // TODO(incomingstick): expand on each of these concepts, and add whats missing
        Die hitDie();
        std::string equipment;  // TODO(incomingstick): dont use a string here
        std::vector<ORPG::EnumSkill> skillProfs;

        /* this is a pointer to our container (likely a character, however
            we cannot assume it is) that expects a function named
            get_proficiency_bonus that returns an integer */
        void* container;

        /* The const string representation for a Background */
        const std::string class_str;

        /**
         * @desc Initialization for a generic CharacterClass that is passed no
         * arguments. Currently there is no additonal intialization that is
         * done.
         *
         * NOTE(incomingstick): Here we should finish setting up our CharacterClass,
         * by doing everything that ALL CharacterClasses should do.
         **/
        virtual void Initialize() = 0;

    public:
        /**
         * @desc Rolls the hitDie one time and returns a result between 1 and  
         **/
        virtual int roll_hit_die() = 0;

        /**
         * @desc This function simply returns the highest the die could possibly roll
         * 
         * @return const int - the MAX value of the hit die
         **/
        virtual const int HIT_DIE_MAX() = 0;

        /**
         * @desc set_owner takes a pointer to an object to set as the container,
         * as it expects access to its owners proficiency bonus via a function that
         * should be defined as 'int8 get_proficiency_bonus()'
         **/
        void set_owner(void* owner) { container = owner; };

        /**
         * @desc A function that returns the Class::ID static property
         *
         * NOTE: Class class IDs start with 0x1b82
         * 
         * @return const uint - the ID value of the calling class
         **/
        virtual const uint id() = 0;

        /**
         * @desc A function that returns the Class as its string
         * representation
         *
         * @return const std::string - the string representation of a Class
         **/
        virtual const std::string to_string() = 0;

        /* The const uint ID for a generic Class */
        static const uint ID = 0x1b820000;
    };

    class CHARACTER_EXPORT Wizard : virtual public CharacterClass {
    protected:
        /* The const string representation for a Human */
        const std::string class_str = "Wizard";

        /* The hit die determines player hp per level, as well as how much they
            can heal during short rests */
        Die hitDie = Die(6);

        /**
         * @desc Initialization for an Acolyte that is passed no arguments.
         *
         * NOTE(incomingstick): Here we should finish setting up our background,
         * by doing everything that ALL backgrounds of type Acolyte should do.
         **/
        void Initialize();

    public:
        /**
         * @desc Constructor for a Wizard that is passed no arguments.
         * Wizard::Initialize() is called at the end of the constructor.
         **/
        Wizard();

        /**
         * @desc Rolls the hitDie one time and returns a result between 1 and  
         **/
        int roll_hit_die() { return hitDie.roll(); };

        /**
         * @desc This function simply returns the highest the die could possibly roll
         * 
         * @return const int - the MAX value of the hit die
         **/
        const int HIT_DIE_MAX() { return hitDie.MAX(); };

        /**
         * @desc A function that returns the Wizard::ID static property
         *
         * NOTE: Class class IDs start with 0x1b82
         * 
         * @return const int - the ID value of the calling class
         **/
        const uint id() { return Wizard::ID; };

        /**
         * @desc A function that returns the Wizard as its string
         * representation
         *
         * @return const std::string - the string representation of a Wizard
         **/
        const std::string to_string() { return class_str; };

        /* The const uint ID for a generic Background */
        static const uint ID = 0x1b820001;
    };
}

#endif /* SRC_CLASSES_H_ */