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
#	ifndef character_EXPORTS
#   	define character_EXPORTS
#	endif
#	include "exports/character_exports.h"
#else
#	define CHARACTER_EXPORT
#endif

#include "ability-scores.h"

namespace ORPG {
    namespace Characters {
        /**
         * @desc This function returns a random RaceID as an integer, from
         * the available races.
         *
         * @return int - the randomly selected race ID
         **/
        const int CHARACTER_EXPORT random_race_id();
    }

    class CHARACTER_EXPORT Race {
    protected:
        /* The bonuses to Ability Scores that being a Human provides */
        AbilityScores abilBonus;

        /* The const string representation for a Race */
        const std::string race_str;

        /**
         * @desc Initialization for a generic Race that is passed no arguments.
         * Currently there is no additonal intialization that is done.
         *
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races should do.
         **/
        virtual void Initialize() = 0;

    public:
        /**
         * @desc A function that returns the Race::ID static property
         *
         * @return const int - the ID value of the calling class
         **/
        virtual const int id() = 0;

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

        /* The const int ID for a generic Race */
        static const int ID = 0x0000;
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
         * @return const int - the ID value of the calling class
         **/
        const int id() { return Human::ID; };

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

        /* The const int ID for a Human */
        static const int ID = 0x0001;
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
         * @return const int - the ID value of the calling class
         **/
        const int id() { return Dwarf::ID; };

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

        /* The const int ID for a Dwarf */
        static const int ID = 0x0010;
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
         * @return const int - the ID value of the calling class
         **/
        const int id() { return HillDwarf::ID; };

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

        /* The const int ID for a HillDwarf */
        static const int ID = 0x0011;
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
         * @return const int - the ID value of the calling class
         **/
        const int id() { return Elf::ID; };

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

        /* The const int ID for an Elf */
        static const int ID = 0x0020;
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
         * @return const int - the ID value of the calling class
         **/
        const int id() { return HighElf::ID; };

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

        /* The const int ID for a HighElf */
        static const int ID = 0x0021;
    };
}

#endif /* SRC_RACE_H_ */
