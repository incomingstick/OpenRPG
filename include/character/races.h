/*
characters - race.h
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_RACE_H_
#define SRC_RACE_H_

#include "ability-scores.h"

/*
 * This can be abstracted more, as we will need to account
 * for more than 5e as well as what if they want to do something
 * more custom?
 */
namespace ORPG {
    class Race {
    private:
    
    protected:
        /**
         * @desc Initialization for a generic Race that is passed no arguments. 
         * Currently there is no additonal intialization that is done.
         * 
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races should do.
         */
        void Initialize() {};

    public:
        /**
         * @desc Constructor for a generic Race that is passed no arguments.
         * Race::Initialize() is called at the end of the constructor.
         */
        Race() { Initialize(); };

        /**
         * @desc Deconstructor for a generic Race that is passed no arguments.
         * Currently does nothing, and the compiler handles deconstruction.
         */
        ~Race() {};
	
        /* The const int ID for a generic Race */
        static const int ID = 0x0000;

        /* The const string representation for a Race */
		static const std::string race;
    };

    /* TODO(incomingstick): Fully define Human comments */
    class Human : public Race {
    private:
        /* Allows Java like use of Super */
        typedef Race Super;

    protected:
        /* The bonuses to Ability Scores that being a Human provides */
        AbilityScores abilBonus;

        /**
         * @desc Initialization for a Human that is passed no arguments. 
         * Currently there is no additonal intialization that is done.
         * 
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races of type Human should do.
         */
        void Initialize();

    public:
        /**
         * @desc Constructor for a Human that is passed no arguments. A base Human
         * has +1 to all stats. Human::Initialize() is called at the end of the
         * constructor.
         */
        Human();

        /* The const int ID for a Human */
        static const int ID = 0x0001;

        /* The const string representation for a Human */
        static const std::string race;
    };

    /* TODO(incomingstick): Fully define Dwarf comments */
    class Dwarf : public Race {
    private:
        /* Allows Java like use of Super */
        typedef Race Super;
    
    protected:
        /* The bonuses to Ability Scores that being a Dwarf provides */
        AbilityScores abilBonus;

        /**
         * @desc Initialization for a Dwarf that is passed no arguments. 
         * Currently there is no additonal intialization that is done.
         * 
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races of type Dwarf should do.
         */
        void Initialize();

    public:
        /**
         * @desc Constructor for a Dwarf that is passed no arguments. A base Dwarf
         * has +2 to CON. Dwarf::Initialize() is called at the end of the
         * constructor.
         */
        Dwarf();

        /* The const int ID for a Dwarf */
        static const int ID = 0x0010;

        /* The const string representation for a Dwarf */
        static const std::string race;
    };

    /* TODO(incomingstick): Fully define HillDwarf comments */
    class HillDwarf : public Dwarf {
    private:
        /* Allows Java like use of Super */
        typedef Dwarf Super;

    public:
        /**
         * @desc Constructor for a HillDwarf that is passed no arguments. A base
         * HillDwarf has +2 to CON and +1 to WIS. HillDwarf::Initialize() is
         * called at the end of the constructor.
         */
        HillDwarf();

        /* The const int ID for a HillDwarf */
        static const int ID = 0x0011;

        /* The const string representation for a HillDwarf */
        static const std::string race;
    };

    /* TODO(incomingstick): Fully define Elf comments */
    class Elf : public Race {
    private:
        /* Allows Java like use of Super */
        typedef Race Super;

    protected:
        /* The bonuses to Ability Scores that being an Elf provides */
        AbilityScores abilBonus;

        /**
         * @desc Initialization for an Elf that is passed no arguments. 
         * Currently there is no additonal intialization that is done.
         * 
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races of type Elf should do.
         */
        void Initialize();

    public:
        /**
         * @desc Constructor for an Elf that is passed no arguments. A base Elf
         * has +2 to DEX. Elf::Initialize() is called at the end of the
         * constructor.
         */
        Elf();

        /* The const int ID for an Elf */
        static const int ID = 0x0020;
        
        /* The const string representation for an Elf */
        static const std::string race;
    };

    /* TODO(incomingstick): Fully define HighElf comments */
    class HighElf : public Elf {
    private:
        /* Allows Java like use of Super */
        typedef Elf Super;

    public:
        /**
         * @desc Constructor for a HighElf that is passed no arguments. A base
         * HighElf has +2 to DEX and +1 to INT. Elf::Initialize() is called at the
         * end of the constructor.
         */
        HighElf();

        /* The const int ID for a HighElf */
        static const int ID = 0x0021;

        /* The String representation for a HighElf */
        static const std::string race;
    };
}

#endif /* SRC_RACE_H_ */
