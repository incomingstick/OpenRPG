/*
characters - background.cpp
Created on: Jul 7, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#include "core/utils.h"
#include "character/backgrounds.h"

namespace ORPG {
    namespace Characters {
        /**
         * @desc This function returns a random BackgroundID as an unsigned integer,
         * from the available backgrounds.
         *
         * TODO(incomingstick): Is hardcoding this as a switch the best
         * option? This likely won't scale well.
         * 
         * @return uint - the randomly selected background ID
         **/
        const uint random_bg_id() {
            switch(Utils::randomInt(0, 0)) {
            case 0 : {
                return Acolyte::ID;
            }

            default: {
                return 0;
            }
            }
        }
    }

    Acolyte::Acolyte() {
        // TODO Construct Acolyte
    }

    void Acolyte::Initialize() {
        // TODO Initialize Acolyte
    }
}