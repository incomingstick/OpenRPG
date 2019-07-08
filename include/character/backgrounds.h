/*
characters - backgrounds.h
Created on: Jul 7, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_BACKGROUNDS_H_
#define SRC_BACKGROUNDS_H_

#ifdef _WIN32
#	include "exports/character_exports.h"
#else
#	define CHARACTER_EXPORT
#endif

#include <vector>

#include "skills.h"

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
        const uint CHARACTER_EXPORT random_bg_id();
    }

    /* An enum containing the list of D&D 5E languages */
    enum CHARACTER_EXPORT Language {
        Common,    Dwarvish,   Elvish,
        Giant,     Gnomish,    Goblin,
        Halfling,  Orc,        Abyssal,
        Celestial, Draconic,   DeepSpeech,
        Infernal,  Primordial, Silvian,
        Undercommon, PlayerChoice
    };

    class CHARACTER_EXPORT Background {
    protected:
        // TODO(incomingstick): expand on each of these concepts
        std::string personalityTrait;
        std::string ideal;
        std::string bond;
        std::string flaw;
        std::string equipment;  // TODO(incomingstick): dont use a string here
        std::vector<ORPG::EnumSkill> skillProfs;
        std::vector<ORPG::Language> langs;

        /* The const string representation for a Background */
        const std::string bg_str;

        /**
         * @desc Initialization for a generic Background that is passed no
         * arguments. Currently there is no additonal intialization that is
         * done.
         *
         * NOTE(incomingstick): Here we should finish setting up our race,
         * by doing everything that ALL Races should do.
         **/
        virtual void Initialize() = 0;

    public:
        /**
         * @desc A function that returns the Background::ID static property
         *
         * NOTE: Background class IDs start with 0x1b81
         * 
         * @return const uint - the ID value of the calling class
         **/
        virtual const uint id() = 0;

        /**
         * @desc A function that returns the Background as its string
         * representation
         *
         * @return const std::string - the string representation of a Background
         **/
        virtual const std::string to_string() = 0;

        /* The const uint ID for a generic Background */
        static const uint ID = 0x1b810000;
    };

    class CHARACTER_EXPORT Acolyte : virtual public Background {
    protected:
        /* The const string representation for a Human */
        const std::string bg_str = "Acolyte";

        /**
         * @desc Initialization for an Acolyte that is passed no arguments.
         *
         * NOTE(incomingstick): Here we should finish setting up our background,
         * by doing everything that ALL backgrounds of type Acolyte should do.
         **/
        void Initialize();

    public:
        /**
         * @desc Constructor for a Acolyte that is passed no arguments. An Acolyte
         * is proficient in Insight, and Religion, gains Two of languages their choice.
         * Human::Initialize() is called at the end of the constructor.
         **/
        Acolyte();

        /**
         * @desc A function that returns the Background::ID static property
         *
         * NOTE: Background class IDs start with 0x1b81
         * 
         * @return const int - the ID value of the calling class
         **/
        const uint id() { return Acolyte::ID; };

        /**
         * @desc A function that returns the Background as its string
         * representation
         *
         * @return const std::string - the string representation of a Background
         **/
        const std::string to_string() { return bg_str; };

        /* The const uint ID for a generic Background */
        static const uint ID = 0x1b810001;
    };
}

#endif /* SRC_BACKGROUNDS_H_ */