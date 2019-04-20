
/*
character-generator - race.h
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef RACE_H_
#define RACE_H_

class Human : public Character {
private:
    typedef Character super;

protected:
    void Initialize();

public:
    Human();
    Human(Ability ab);
    Human(Ability ab, std::string name);

    static const int ID = 0x0001;
    static const std::string race;
};

class Dwarf : public Character {
private:
    typedef Character super;
    
protected:
    void Initialize();

public:
    Dwarf();
    Dwarf(Ability ab);
    Dwarf(Ability ab, std::string name);

    static const int ID = 0x0010;
    static const std::string race;
};

class HillDwarf : public Dwarf {
private:
    typedef Dwarf super;
public:
    HillDwarf();
    HillDwarf(Ability ab);
    HillDwarf(Ability ab, std::string name);

    static const int ID = 0x0011;
};

class Elf : public Dwarf {
protected:
    void Initialize();

public:
    Elf();
    Elf(Ability ab);
    Elf(Ability ab, std::string name);

    static const int ID = 0x0020;
    static const std::string race;
};

class HighElf : public Elf {
public:
    HighElf();
    HighElf(Ability ab);
    HighElf(Ability ab, std::string name);

    static const int ID = 0x0021;
};

class CharacterFactory {
private:
    struct race_node {
        int raceID;
        bool required;
        
        race_node* parent;
        std::vector<race_node* > children;
    };

    race_node* head;
    race_node* current;
    race_node* allocate_node(int raceID,
                             bool required,
                             race_node* parent);
public:
    CharacterFactory();
    ~CharacterFactory();

    Character* NewCharacter(Ability ab = ability_struct());
    Character* NewCharacter(int identifier);
    Character* NewCharacter(int identifier, Ability ab);
    Character* NewCharacter(Ability ab,std::string name);

    void reset() { current = head; };
    std::vector<std::string> current_options();
    bool has_options();
    void select_option(int index);
    int current_id();
};

#endif /* RACE_H_ */
