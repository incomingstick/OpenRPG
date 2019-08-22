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
    }

    Wizard::Wizard() {
        // TODO Construct Wizard
    }

    void Wizard::Initialize() {
        // TODO Initialize Wizard
    }
}