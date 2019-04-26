---
layout: docs
title: Die
description: A simple header defined class to emulate a die roll
group: documentation
---

Represents a die with a max number passed at construction.

**Namespace:** ORPG

**Assembly:** _none_  

## Definition
Defined in `#include "die.h"`

{% highlight c++ %}
class Die {
    public:
        Die(int max);
        int roll();
};
{% endhighlight %}

## Member functions

Function      | Description |
 ------------ | ----------- |
Die(int max)  | creates a die that will roll between 1 and `max`|
int roll()    | gets a uniform random mt19937 number between 1 and max|
