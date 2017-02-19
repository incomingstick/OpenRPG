---
layout: docs
title: Name Generator
description: Randomly generate names based on race
group: documentation
---

# Die
Defined in `#include "die.h"`
````C++
class NameGenerator {
    public:
        std::string race;
        std::string subrace;
        std::string gender;

        NameGenerator(std::string race = "dwarf", std::string gender = "male", std::string subrace = "");
        std::string make_name();
        std::string make_first();
        std::string make_last();
};
````

## TODO description of class

## TODO Member functions

Function      | Description |
 ------------ | ----------- |
