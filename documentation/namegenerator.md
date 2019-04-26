---
layout: docs
title: NameGenerator
description: Randomly generate names based on race
group: documentation
---

**Namespace:** ORPG, Names
**Assembly:** _none_  

## Definition
Defined in `#include "names.h"`
{% highlight c++ %}
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
{% endhighlight %}

## Member fields

Field         | Description |
 ------------ | ----------- |
std::string race | The race of the name to generate. This field is both readable and writeable. |
std::string subrace | The subrace of the name to generate. This field is both readable and writeable. |
std::string gender | The gender of the name to generate. This field is both readable and writeable. |

## Member functions

Function      | Description |
 ------------ | ----------- |
NameGenerator(std::string race, std::string gender, std::string subrace) | Creates an instance of the NameGenerator class with fields race, gender, and subrace. Race defaults to `"dwarf"` when left empty. Gender defaults to `"male"` when left empty. Subrace defaults to empty when left empty. |
std::string make_name() | Returns a string with a random full name based on the given `race`, `gender`, and `subrace`. Returns `"NULL"` for either first or last name if the namelist could not be found. |
std::string make_first() | Returns a string with a random first name based on the given `race`, `gender`, and `subrace`. Returns `"NULL"` if the namelist could not be found. |
std::string make_last() | Returns a string with a random last name based on the given `race`, `gender`, and `subrace`. Returns `"NULL"` if the namelist could not be found. |