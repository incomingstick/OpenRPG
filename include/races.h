/*
character-generator - race.h
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef RACE_H_
#define RACE_H_

extern std::vector<std::string> races;

Character* CharacterFactory(std::string race);

class Human : public Character {
public:
    Human();
    Human(Ability ab);

    void Initialize();
};

class Dwarf : public Character {
public:
    Dwarf();
    Dwarf(Ability ab);

    void Initialize();
};

class HillDwarf : public Dwarf {
public:
    HillDwarf();
    HillDwarf(Ability ab);
};

#endif /* RACE_H_ */
