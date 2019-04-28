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
        void Initialize() {};

    public:
        Race() {};
        ~Race() {};
	
        static const int ID = 0x0000;
		static const std::string race;
    };

    class Human : public Race {
    private:
        typedef Race Super;
        AbilityScores abilBonus;

    protected:
        void Initialize();

    public:
        Human();

        static const int ID = 0x0001;
        static const std::string race;
    };

    class Dwarf : public Race {
    private:
        typedef Race Super;

    protected:
        AbilityScores abilBonus;

        void Initialize();

    public:
        Dwarf();

        static const int ID = 0x0010;
        static const std::string race;
    };

    class HillDwarf : public Dwarf {
    private:
        typedef Dwarf Super;

    public:
        HillDwarf();

        static const int ID = 0x0011;
    };

    class Elf : public Race {
    private:
        typedef Race Super;

    protected:
        void Initialize();

        AbilityScores abilBonus;

    public:
        Elf();

        static const int ID = 0x0020;
        static const std::string race;
    };

    class HighElf : public Elf {
    private:
        typedef Elf Super;

    public:
        HighElf();

        static const int ID = 0x0021;
    };
}

#endif /* SRC_RACE_H_ */
