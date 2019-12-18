/*
characters - classes.cpp
Created on: Aug 22, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#include "core/utils.h"
#include "character/classes.h"

namespace ORPG {
    namespace Characters {
        /**
         * @desc This function returns a random CharacterClassID as an unsigned integer,
         * from the available backgrounds.
         *
         * TODO(incomingstick): Is hardcoding this as a switch the best
         * option? This likely won't scale well.
         * 
         * @return uint - the randomly selected class ID
         **/
        const uint random_class_id() {
            switch(Utils::randomInt(0, 0)) {
            case 0 : {
                return Wizard::ID;
            }

            default: {
                return 0;
            }
            }
        }

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
        CharacterClass* select_character_class(const int identifier) {
            const auto id = (identifier < 0) ?
                random_class_id() : identifier;

            switch(id) {
            case Wizard::ID : {
                return new Wizard();
            }

            default: {
                return nullptr;
            }
            }
        }
    }

    Wizard::Wizard() {
        // TODO Construct Wizard
        Initialize();
    }

    void Wizard::Initialize() {
        // TODO Initialize Wizard
    }
}