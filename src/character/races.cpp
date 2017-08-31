
/*
character-generator - race.cpp
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>
#include <cstdlib>

#include "names.h"
#include "character.h"

using namespace std;

//'SRD' refers to System Reference Document v5.1

const string Dwarf::race = "Dwarf";
/* Dwarf Traits:
    CON +2
    Speed: 25ft, not slowed by armor
    Darkvision 60ft
    Dwarven Resilience:
        Advantage on saving throws against poison,
        resistance against poison damage
    Dwarven Combat Training:
        Proficiency with battleaxes, handaxes, throwing hammers, and warhammers
    Tool Proficiency:
        Choose proficiency of one of the following:
            Smith's tools
            Brewer's tools
            Mason's tools
    Stonecunning:
        Whenever you make an Intelligence (History) check related to the origin
        of stonework, you are considered proficient in the History skill and
        add double your proficiency bonus to the check, instead of your normal
        proficiency bonus
    Languages:
        Common: Speak, read, write
        Dwarvish: Spead, read, write
    Subraces:
        Hill Dwarf:
            WIS +1
            Dwarven Toughness:
                HP +1, increase HP by 1 each time you level up
        Mountain Dwarf:
            STR +2
            Dwarven Armor Training:
                Proficiency with light and medium armor
*/
Dwarf::Dwarf() {
    abils.STR = gen_stat();     // Strength
    abils.DEX = gen_stat();     // Dexterity
    abils.CON = gen_stat() + 2; // Constitution
    abils.INT = gen_stat();     // Intelligence
    abils.WIS = gen_stat();     // Wisdom
    abils.CHA = gen_stat();     // Charisma

    Initialize();
}

Dwarf::Dwarf(Ability ab) {
    abils.STR = ab.STR;     // Strength
    abils.DEX = ab.DEX;     // Dexterity
    abils.CON = ab.CON + 2; // Constitution
    abils.INT = ab.INT;     // Intelligence
    abils.WIS = ab.WIS;     // Wisdom
    abils.CHA = ab.CHA;     // Charisma

    Initialize();
}

void Dwarf::Initialize() {
    NameGenerator ng(race);

    firstName = ng.make_first();
    lastName = ng.make_last();

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = DEX_MOD();    // Acrobatics       (DEX)
    skills.ANM = WIS_MOD();    // Animal Handling  (WIS)
    skills.ARC = INT_MOD();    // Arcana           (INT)
    skills.ATH = STR_MOD();    // Athletics        (STR)
    skills.DEC = CHA_MOD();    // Deception        (CHA)
    skills.HIS = INT_MOD();    // History          (INT)
    skills.INS = WIS_MOD();    // Insight          (WIS)
    skills.ITM = CHA_MOD();    // Intimidation     (CHA)
    skills.INV = INT_MOD();    // Investigation    (INT)
    skills.MED = WIS_MOD();    // Medicine         (WIS)
    skills.NAT = INT_MOD();    // Nature           (INT)
    skills.PRC = WIS_MOD();    // Perception       (WIS)
    skills.PRF = CHA_MOD();    // Performance      (CHA)
    skills.PRS = CHA_MOD();    // Persuasion       (CHA)
    skills.REL = INT_MOD();    // Religion         (INT)
    skills.SLE = DEX_MOD();    // Sleight of Hand  (DEX)
    skills.STL = DEX_MOD();    // Stealth          (DEX)
    skills.SUR = WIS_MOD();    // Survival         (WIS)

    curr_hp = 10;                   // current hit points
    temp_hp = 10;                   // temporary hit points
    max_hp = 10;                    // maximum hit points
    prof = 2;                       // proficiency bonus
    level = 1;                      // character level total
    cur_exp = 0;                    // current experience
    max_exp = levels[level - 1];    // experience needed for next level
}

/* Elf race
DEX +2
Speed: 30ft
Darkvision 60ft
Keen Senses:
    Proficiency in Perception
Fey Ancestry:
    Advantage on saving throws against being charmed, and magic can't put you to sleep
Trance:
    Elves don’t need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day.
    (The Common word for such meditation is “trance.”) While meditating, you can dream after a fashion;
    such dreams are actually mental exercises that have become reflexive through years of practice. After
    resting in this way, you gain the same benefit that a human does from 8 hours of sleep.
Languages:
    Common: Speak, read, write
    Elvish: Speak, read, write
Subraces:
    High Elf:
        INT +1
        Elf Weapon Training:
            Proficiency with longswords, shortswords, shortbows, and longbow
        Cantrip:
            Learn choice cantrip from wizard spell list. Your spellcasting ability for it is INT
    Wood Elf:
        WIS +1
        Elf Weapon Training:
            Proficiency with longswords, shortswords, shortbows, and longbow
        Fleet of Foot:
            Base walking speed increases to 35ft
        Mask of the Wind:
            You can attempt to hide even when you are only lightly obscured by foliage, heavy rain,
            falling snow, mist, and other natural phenomena.
    Dark Elf:
        CHA +1
        Superior Darkvision: 120ft
        Sunlight Sensitivity:
            You have disadvantage on attack rolls and on WIS (Perception) checks that rely on
            sight when you, the target of your attack, or whatever you are trying to perceive is
            in direct sunlight.
        Drow Magic:
            You know the dancing lights cantrip. When you reach 3rd level, you can cast the faerie fire
            spell once per day. When you reach 5th level, you can also cast the darkness spell once per day.
            CHA is your spellcasting ability for these spells.
        Drow Weapon Training:
            Proficiency with rapiers, shortswords, and hand crossbows
*/

/* Gnome race
INT +2
Speed: 25ft
Darkvision: 60ft
Gnome Cunning:
    Advantage on all INT, WIS, and CHA saving throws against magic
Languages:
    Common: Speak, read, write
    Gnomish: Speak, read, write
Subraces:
    Forest Gnome:
        DEX +1
        Natural Illusionist:
            You know the minor illusion cantrip. Intelligence is your spellcasting ability for it
        Speak with Small Beasts:
            Through sounds and gestures, you can communicate simple ideas with Small or smaller beasts.
            Forest gnomes love animals and often keep squirrels, badgers, rabbits, moles, woodpeckers,
            and other creatures as beloved pets.
    Rock Gnome:
        CON +1
        Artificer's Lore:
        Tinker:
            You have proficiency with artisan’s tools (tinker’s tools). Using thse tools, you can
            spend 1 hour and 10 gp worth of materials to construct a Tiny clockwork device (AC 5, 1 hp).
            The device ceases to function after 24 hours (unless you spend 1 hour repairing it to keep
            the device functioning), or when you use your action to dismantle it; at that time, you can
            reclaim the materials used to create it. You can have up to three such devices active at
            a time. When you create a device, choose one of the following options:
                Clockwork Toy:
                    This toy is a clock work animal, monster, or person, such as a frog, mouse, bird,
                    dragon, or soldier. When placed on the ground, the toy moves 5 feet a cross the
                    ground on each of your turns in a random direction. It makes noises as appropriate
                    to the creature it represents.
                Fire Starter:
                    The device produces a miniature flame, which you can use to light a candle, torch,
                    or campfire. Using the device requires your action.
                Music Box:
                    When opened, this music box plays a single song at a moderate volume. The box stops
                    playing when it reaches the song’s end or when it is closed.
*/

/* Halfling race
DEX +2
Speed: 25ft
Lucky:
    When you roll a 1 on an attack roll, ability check, or saving throw, you can reroll the die and
    must use the new roll.
Brave:
     You have advantage on saving throws against being frightened.
Halfling Nimbleness:
    You can move through the space of any creature that is of a size larger than yours.
Languages:
    Common: Speak, read, write
    Halfling: Speak, read, write
Subraces:
    Lightfoot:
        CHA +1
        Naturally Stealthy:
            You can attempt to hide even when you are obscured only by a creature that is at least one size
            larger than you
    Stout:
        CON +1
        Stout Resilience:
            Advantage on saving throughs against poison, resistance against poison damage
*/

/* Half-Elf race
    Effects:
        Speed +30
        CHA +2
        Two other choice abilities +1
        Darkvision 60ft
        Advantage on saving throws against being charmed
        Resistance to Magical-sleep
        Common and Elvish languages
*/

/* Half-Orc race
STR +2
CON +1
Speed: 30ft
Darkvision 60ft
Menacing:
    Proficiency in Intimidation
Relentless Endurance:
    When you are reduced to 0 hit points but not killed outright, you can drop to 1 hit point instead.
    You can’t use this feature again until you finish a long rest.
Savage Attacks:
    When you score a critical hit with a melee weapon attack, you can roll one of the weapon’s damage dice
    one additional time and add it to the extra damage of the critical hit.
Languages:
    Common: Speak, read, write
    Orc: Speak, read, write
*/

/* High Elf subrace:
CHA +2
Two choice stats +1
Speed: 30ft
Darkvision 60ft
Fey Ancestry:
    Advantage on saving throws against being charmed
Languages:
    Common: Speak, read, write
    Elvish: Speak, read, write
    One choice language: Speak, read, write
*/

HillDwarf::HillDwarf() {
    abils.STR = gen_stat();     // Strength
    abils.DEX = gen_stat();     // Dexterity
    abils.CON = gen_stat() + 2; // Constitution
    abils.INT = gen_stat();     // Intelligence
    abils.WIS = gen_stat() + 1; // Wisdom
    abils.CHA = gen_stat();     // Charisma

    Initialize();
}
/*  Effects of Hill Dwarf subrace:
        All effects of Dwarven main race
        WIS +1
        Dwarven Toughness: HP +1, increase HP by 1 each time you level up
*/
HillDwarf::HillDwarf(Ability ab) {
    abils.STR = ab.STR;     // Strength
    abils.DEX = ab.DEX;     // Dexterity
    abils.CON = ab.CON + 2; // Constitution
    abils.INT = ab.INT;     // Intelligence
    abils.WIS = ab.WIS + 1; // Wisdom
    abils.CHA = ab.CHA;     // Charisma

    Initialize();
}

const string Human::race = "Human";
/*  Effects of Human race:
        Speed +30
        All abilities +1
*/
Human::Human() {
    abils.STR = gen_stat() + 1;    // Strength
    abils.DEX = gen_stat() + 1;    // Dexterity
    abils.CON = gen_stat() + 1;    // Constitution
    abils.INT = gen_stat() + 1;    // Intelligence
    abils.WIS = gen_stat() + 1;    // Wisdom
    abils.CHA = gen_stat() + 1;    // Charisma

    Initialize();
}

Human::Human(Ability ab) {
    abils.STR = ab.STR + 1;    // Strength
    abils.DEX = ab.DEX + 1;    // Dexterity
    abils.CON = ab.CON + 1;    // Constitution
    abils.INT = ab.INT + 1;    // Intelligence
    abils.WIS = ab.WIS + 1;    // Wisdom
    abils.CHA = ab.CHA + 1;    // Charisma

    Initialize();
}

void Human::Initialize() {
    NameGenerator ng(race);

    firstName = ng.make_first();
    lastName = ng.make_last();

    // TODO will need to be modified when prof is taken in to account
    skills.ACR = DEX_MOD();    // Acrobatics       (DEX)
    skills.ANM = WIS_MOD();    // Animal Handling  (WIS)
    skills.ARC = INT_MOD();    // Arcana           (INT)
    skills.ATH = STR_MOD();    // Athletics        (STR)
    skills.DEC = CHA_MOD();    // Deception        (CHA)
    skills.HIS = INT_MOD();    // History          (INT)
    skills.INS = WIS_MOD();    // Insight          (WIS)
    skills.ITM = CHA_MOD();    // Intimidation     (CHA)
    skills.INV = INT_MOD();    // Investigation    (INT)
    skills.MED = WIS_MOD();    // Medicine         (WIS)
    skills.NAT = INT_MOD();    // Nature           (INT)
    skills.PRC = WIS_MOD();    // Perception       (WIS)
    skills.PRF = CHA_MOD();    // Performance      (CHA)
    skills.PRS = CHA_MOD();    // Persuasion       (CHA)
    skills.REL = INT_MOD();    // Religion         (INT)
    skills.SLE = DEX_MOD();    // Sleight of Hand  (DEX)
    skills.STL = DEX_MOD();    // Stealth          (DEX)
    skills.SUR = WIS_MOD();    // Survival         (WIS)

    curr_hp = 10;                   // current hit points
    temp_hp = 10;                   // temporary hit points
    max_hp = 10;                    // maximum hit points
    prof = 2;                       // proficiency bonus
    level = 1;                      // character level total
    cur_exp = 0;                    // current experience
    max_exp = levels[level - 1];    // experience needed for next level
}

/* Lightfoot subrace
    Effects:
        All effects of Halfling main race
        CHA +1
        Naturally Stealthy (See SRD)
*/

/* Rock gnome subrace
    Effects:
        CON +1
        Artificer's Lore (See SRD)
        Tinker (See SRD)
*/

/* Tiefling race
    Effects:
        Speed +30
        Darkvision 60ft
        INT +1
        CHA +2
        Fire damage Resistance
        Thaumaturgy cantrip
        Infernal Legacy (See SRD)
        Common and Infernal languages
*/

CharacterFactory::CharacterFactory() {
    // TODO populate race tree here and remove the above race vector
    head = allocate_node(Character::ID, false, NULL);

    race_node* human = allocate_node(Human::ID, true, head);

    race_node* dwarf = allocate_node(Dwarf::ID, true, head);

    race_node* hillDwarf = allocate_node(HillDwarf::ID, true, dwarf);

    dwarf->children = {
        hillDwarf
    };

    head->children = {
        human,
        dwarf
    };

    current = head;
}

CharacterFactory::~CharacterFactory() {
    //TODO clean up here
}

CharacterFactory::race_node* CharacterFactory::allocate_node(int raceID,
                                                             bool required,
                                                             race_node* parent) {
    race_node* node = new race_node;

    if(node == NULL) {
        printf("out of memory");
        exit(EXIT_FAILURE);
    }

    node->raceID = raceID;
    node->required = required;
    node->parent = parent;

    return node;
}

Character* CharacterFactory::NewCharacter(Ability ab) {
    switch(current->raceID) {
    case Human::ID : {
        return new Human(ab);
    }

    case Dwarf::ID : {
        return new Dwarf(ab);
    }

    case HillDwarf::ID : {
        return new HillDwarf(ab);
    }
    default: {
        return NULL;
    }
    }
}

Character* CharacterFactory::NewCharacter(int identifier) {
    switch(identifier) {
    case Human::ID : {
        return new Human;
    }

    case Dwarf::ID : {
        return new Dwarf;
    }

    case HillDwarf::ID : {
        return new HillDwarf;
    }
    default: {
        return NULL;
    }
    }
}

Character* CharacterFactory::NewCharacter(int identifier, Ability ab) {
    switch(identifier) {
    case Human::ID : {
        return new Human(ab);
    }

    case Dwarf::ID : {
        return new Dwarf(ab);
    }

    case HillDwarf::ID : {
        return new HillDwarf(ab);
    }
    default: {
        return NULL;
    }
    }
}

vector<string> CharacterFactory::current_options() {
    vector<string> ret;

    for(race_node* node : current->children) {
        switch(node->raceID) {
        case Human::ID : {
            ret.push_back("Human");
            break;
        }

        case Dwarf::ID : {
            ret.push_back("Dwarf");
            break;
        }

        case HillDwarf::ID : {
            ret.push_back("Hill Dwarf");
            break;
        }
        }
    }

    return ret;
}

bool CharacterFactory::has_options() {
    if(!current->children.empty())
        return true;
    else return false;
}

void CharacterFactory::select_option(int index) {
    if(current == NULL) return;

    if(index < 0 || (size_t)index > current->children.size())
        return;

    if(current->children[index] != NULL)
        current = current->children[index];
}

int CharacterFactory::current_id() {
    if(current != NULL) return current->raceID;
    return -1;
}
