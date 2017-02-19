---
layout: docs
title: Dice
description: Emulate a die roll, and preform advance die math
group: documentation
---

# Die
Defined in `#include "die.h"`
````C++
class Die {
    public:
        Die(int max):MAX(max){};
        int roll()
};
````

## TODO description of class

## Member functions

Function      | Description |
 ------------ | ----------- |
Die(int max)  | creates a die that will roll between 1 and `max`|
int roll()    | gets a uniform random mt19937 number between 1 and max|
