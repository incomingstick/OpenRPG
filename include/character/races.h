/*
characters - race.h
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_RACE_H_
#define SRC_RACE_H_

#ifdef _WIN32
#	include "exports/character_exports.h"
#else
#	define CHARACTER_EXPORT
#endif

#include "ability-scores.h"

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
    namespace Characters {
        /**
         * @desc This function returns a random RaceID as an integer, from
         * the available races.
         * 
         * NOTE: Race class IDs start with 0x1b80
         *
         * @return int - the randomly selected race ID
         **/
        const uint CHARACTER_EXPORT random_race_id();
    }

    class CHARACTER_EXPORT Race {
    protected:
        /* The bonuses to Ability Scores that being a Race provides */
        AbilityScores abilBonus;

        /* The const string representation for a Race */
        const std::string race_str;

        /**
         * @desc Initialization for a generic Race that is passed no arguments.
         * There is no additonal intialization that is done.
         **/
        virtual void Initialize() = 0;

    public:
        /**
         * @desc A function that returns the Race::ID static property
         *
         * NOTE: Race class IDs start with 0x1b80
         * 
         * @return const int - the ID value of the calling class
         **/
        virtual const uint id() = 0;

        /**
         * @desc apply the current Race's AbilityScores to the passed set
         * of AbilityScores located at the provided pointer location
         *
         * @param AbilityScores* - a pointer the base AbilityScores to
         * add to
         **/
        virtual void applyRacialBonus(AbilityScores* base) = 0;

        /**
         * @desc A function that returns the Race as its string representation
         *
         * @return const std::string - the string representation of a Race
         **/
        virtual const std::string to_string() = 0;

        /* The const uint ID for a generic Race */
        static const uint ID = 0x1b800000;
    };


    /* TODO(incomingstick): Fully define Human comments */
    class CHARACTER_EXPORT Human : virtual public Race {
    protected:
        /* The bonuses to Ability Scores that being a Human provides */
        AbilityScores abilBonus;

        /* The const string representation for a Human */
        const std::string race_str = "Human";

        /**
         * @desc Initialization for a Human that is passed no arguments.
         *
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races of type Human should do.
         **/
        void Initialize();

    public:
        /**
         * @desc Constructor for a Human that is passed no arguments. A base Human
         * has +1 to all stats. Human::Initialize() is called at the end of the
         * constructor.
         **/
        Human();

        /**
         * @desc A function that returns the Human::ID static property
         *
         * NOTE: Human class IDs start with 0x1b80000
         * 
         * @return const int - the ID value of the calling class
         **/
        const uint id() { return Human::ID; };

        /**
         * @desc apply the current Human's AbilityScores to the passed set
         * of AbilityScores located at the provided pointer location
         *
         * @param AbilityScores* - a pointer the base AbilityScores to
         * add to
         **/
        void applyRacialBonus(AbilityScores* base);

        /**
         * @desc A function that returns the Human as its string representation
         * Should always return "Human"
         *
         * @return const std::string - a string representation of a Human
         **/
        const std::string to_string() { return race_str; };

        /* The const uint ID for a Human */
        static const uint ID = 0x1b800001;
    };

    /* TODO(incomingstick): Fully define Dwarf comments */
    class CHARACTER_EXPORT Dwarf : virtual public Race {
    protected:
        /* The bonuses to Ability Scores that being a Dwarf provides */
        AbilityScores abilBonus;

        /* The const string representation for a Dwarf */
        const std::string race_str = "Dwarf";

        /**
         * @desc Initialization for a Dwarf that is passed no arguments.
         *
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races of type Dwarf should do.
         **/
        void Initialize();

    public:
        /**
         * @desc Constructor for a Dwarf that is passed no arguments. A base Dwarf
         * has +2 to CON. Dwarf::Initialize() is called at the end of the
         * constructor.
         **/
        Dwarf();

        /**
         * @desc A function that returns the Dwarf::ID static property
         *
         * NOTE: Dwarf class IDs start with 0x1b80001
         * 
         * @return const int - the ID value of the calling class
         **/
        const uint id() { return Dwarf::ID; };

        /**
         * @desc apply the current Dwarf's AbilityScores to the passed set
         * of AbilityScores located at the provided pointer location
         *
         * @param AbilityScores* - a pointer the base AbilityScores to
         * add to
         **/
        void applyRacialBonus(AbilityScores* base);

        /**
         * @desc A function that returns the Dwarf as its string representation
         * Should always return "Dwarf"
         *
         * @return const std::string - a string representation of a Dwarf
         **/
        const std::string to_string() { return race_str; };

        /* The const uint ID for a Dwarf */
        static const uint ID = 0x1b800010;
    };

    /* TODO(incomingstick): Fully define HillDwarf comments */
    class CHARACTER_EXPORT HillDwarf : public Dwarf {
    protected:
        /* The const string representation for a HillDwarf */
        const std::string race_str = "Hill Dwarf";

    public:
        /**
         * @desc Constructor for a HillDwarf that is passed no arguments. A base
         * HillDwarf has +2 to CON and +1 to WIS. HillDwarf::Initialize() is
         * called at the end of the constructor.
         **/
        HillDwarf();

        /**
         * @desc A function that returns the HillDwarf::ID static property
         *
         * NOTE: Dwarf class IDs start with 0x1b80001
         * 
         * @return const uint - the ID value of the calling class
         **/
        const uint id() { return HillDwarf::ID; };

        /**
         * @desc apply the current HillDwarf's AbilityScores to the passed set
         * of AbilityScores located at the provided pointer location
         *
         * @param AbilityScores* - a pointer the base AbilityScores to
         * add to
         **/
        void applyRacialBonus(AbilityScores* base);

        /**
         * @desc A function that returns the Hill Dwarf as its string representation
         * Should always return "Hill Dwarf"
         *
         * @return const std::string - a string representation of a Hill Dwarf
         **/
        const std::string to_string() { return race_str; };

        /* The const uint ID for a HillDwarf */
        static const uint ID = 0x1b800011;
    };

    /* TODO(incomingstick): Fully define Elf comments */
    class CHARACTER_EXPORT Elf : virtual public Race {
    protected:
        /* The bonuses to Ability Scores that being an Elf provides */
        AbilityScores abilBonus;

        /* The const string representation for an Elf */
        const std::string race_str = "Elf";

        /**
         * @desc Initialization for an Elf that is passed no arguments.
         *
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races of type Elf should do.
         **/
        void Initialize();

    public:
        /**
         * @desc Constructor for an Elf that is passed no arguments. A base Elf
         * has +2 to DEX. Elf::Initialize() is called at the end of the
         * constructor.
         **/
        Elf();

        /**
         * @desc A function that returns the Elf::ID static property
         *
         * NOTE: Elf class IDs start with 0x1b80002
         * 
         * @return const int - the ID value of the calling class
         **/
        const uint id() { return Elf::ID; };

        /**
         * @desc apply the current Elf's AbilityScores to the passed set
         * of AbilityScores located at the provided pointer location
         *
         * @param AbilityScores* - a pointer the base AbilityScores to
         * add to
         **/
        void applyRacialBonus(AbilityScores* base);

        /**
         * @desc A function that returns the Elf as its string representation
         * Should always return "Elf"
         *
         * @return const std::string - a string representation of an Elf
         **/
        const std::string to_string() { return race_str; };

        /* The const uint ID for an Elf */
        static const uint ID = 0x1b800020;
    };

    /* TODO(incomingstick): Fully define HighElf comments */
    class CHARACTER_EXPORT HighElf : public Elf {
    protected:
        /* The String representation for a HighElf */
        const std::string race_str = "High Elf";

    public:
        /**
         * @desc Constructor for a HighElf that is passed no arguments. A base
         * HighElf has +2 to DEX and +1 to INT. Elf::Initialize() is called at the
         * end of the constructor.
         **/
        HighElf();

        /**
         * @desc A function that returns the Elf::ID static property
         *
         * NOTE: Elf class IDs start with 0x1b80002
         * 
         * @return const uint - the ID value of the calling class
         **/
        const uint id() { return HighElf::ID; };

        /**
         * @desc apply the current HighElf's AbilityScores to the passed set
         * of AbilityScores located at the provided pointer location
         **/
        void applyRacialBonus(AbilityScores* base);

        /**
         * @desc A function that returns the High Elf as its string representation.
         * Should always return "High Elf"
         *
         * @return const std::string - a string representation of a High Elf
         **/
        const std::string to_string() { return race_str; };

        /* The const uint ID for a HighElf */
        static const uint ID = 0x1b800021;
    };
}

#endif /* SRC_RACE_H_ */
