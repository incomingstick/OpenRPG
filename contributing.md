---
layout: default
title: Contributing
description: Learn how you can contribute to OpenRPG too
group: contributing
---
<h1>{{ page.title }}</h1>
<p class="lead">
    {{ page.description }}
</p>
<!-- Copied from CONTRIBUTING.md -->

## Contents

* Will be replaced with the ToC, including the "Contents" header
{:toc}

## Contributing Issues

### Before Submitting an Issue
First, please do a search in open issues to see if the issue or feature request has already been filed. If there is an issue add your comments to this issue.

## Writing Good Bug Reports and Feature Requests

File a single issue per problem and feature request, do not file combo issues.

The more information you can provide, the more likely someone will be successful reproducing the issue and finding a fix. Therefore:

* Provide reproducible steps, what the result of the steps was, and what you would have expected.
* Description of what you expect to happen
* Animated GIFs
* Code that demonstrates the issue
* Version of OpenRPG
* Errors printed to the command line

## Contributing Fixes
First and foremost check the TODO's to see what needs to be done.
Once you're ready to start programming see the Programming Standards section.

I have broken the goals and needs by the "Difficulty" of the task. Beginner tasks
will be more specific, such as working on a certain function or method. Intermediate tasks
will be a little broader, such as creating a specific class or utility. Advanced
tasks will be major milestones that need to be completed. And should only be attempted
by someone that understand the language.

## Pull Request

For something to be considered for merging into master it must be
submitted as a Pull Request to a current developement branch first.
Pull requests must follow the format found in the [Issue Template](https://github.com/incomingstick/OpenRPG/blob/patch-v0.3.0-dev/.github/ISSUE_TEMPLATE.md)
file.

## TODO's
If you have questions on where to start, come join us on Discord [here](https://discord.gg/xEwaYE5).

- spelling and grammar updates
- [ ] website documentation 
- [ ] man pages
- [ ] test suite
- [X] dice simulation program (began implementation in [v0.0.3-dev](https://github.com/incomingstick/OpenRPG/tree/v0.0.3-dev))
    - [ ] allows full math using dice (current development branch - roll-module)
- [X] name generator (began implementation in [v0.0.2-dev](https://github.com/incomingstick/OpenRPG/tree/v0.0.2-dev), current development branch - names-module)
    - [X] Aarakocra ([EE](http://dnd.wizards.com/articles/features/elementalevil_playerscompanion))
    - [ ] Aasimar: Protector, Scourge, Fallen (DMG (base only), VOLO)
    - [ ] Anthropomorphic Mice (DMG)
    - [ ] Changeling: ([UA: "Eberron"](https://media.wizards.com/2015/downloads/dnd/UA_Eberron_v1.pdf))
    - [ ] Deep Gnome/Svirfneblin ([EE](http://dnd.wizards.com/articles/features/elementalevil_playerscompanion), SCAG)
    - [ ] Dragonborn ([SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd), PHB)
    - [ ] Dwarf: Mountain or Hill ([PBR](http://dnd.wizards.com/articles/features/basicrules), [SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd) only Hill, PHB)
    - [ ] Dwarf: Duergar (SCAG)
    - [ ] Elf: High, Wood, or Drow ([PBR](http://dnd.wizards.com/articles/features/basicrules), [SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd) only High, PHB)
    - [ ] Elf: Eladrin (DMG)
    - [ ] Elf: Tajuru, Joraga, Mul daya ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [ ] Firbolg (VOLO)
    - [ ] Genasi (PotA, [EE](http://dnd.wizards.com/articles/features/elementalevil_playerscompanion))
    - [ ] Gnome ([SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd), PHB)
    - [ ] Goblin ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [ ] Goliath ([EE](http://dnd.wizards.com/articles/features/elementalevil_playerscompanion), VOLO)
    - [ ] Halfling: Lightfoot or Stout ([PBR](http://dnd.wizards.com/articles/features/basicrules), [SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd) only Lightfoot, PHB)
    - [ ] Halfling: Ghostwise (SCAG)
    - [ ] Half-Elf ([SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd), PHB)
    - [ ] Half-Elf: Variant (SCAG)
    - [ ] Half-Orc ([SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd), PHB)
    - [ ] Human: standard or variant ([PBR](http://dnd.wizards.com/articles/features/basicrules), [SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd) only standard, PHB, ZEN)
    - [ ] Kenku (VOLO)
    - [X] Kor ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [ ] Lizardfolk (VOLO)
    - [ ] Merfolk ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [X] Minotaur ([UA: "Waterborne Adventures"](https://media.wizards.com/2015/downloads/dnd/UA_Waterborne_v3.pdf))
    - [ ] Revenant ([UA: "Gothic Heroes"](https://dnd.wizards.com/sites/default/files/media/upload/articles/UA%20Gothic%20Characters.pdf))
    - [ ] Shifter: ([UA: "Eberron"](https://media.wizards.com/2015/downloads/dnd/UA_Eberron_v1.pdf))
    - [ ] Tabaxi (VOLO)
    - [X] Tiefling ([SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd), PHB)
    - [X] Tiefling: Variant (other than Winged) (SCAG)
    - [X] Tiefling: Winged Variant (SCAG)
    - [X] Tiefling: Infernal and Abyssal variants ([UA: "That Old Black Magic"](https://media.wizards.com/2015/downloads/dnd/07_UA_That_Old_Black_Magic.pdf))
    - [ ] Triton (VOLO)
    - [ ] Vampire ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [X] Warforged: ([UA: "Eberron"](https://media.wizards.com/2015/downloads/dnd/UA_Eberron_v1.pdf))
- [X] character generator (began implementation in [v0.1.0-dev](https://github.com/incomingstick/OpenRPG/tree/v0.1.0-dev), current development branch - character-module)
    - [ ] populates a PDF character sheet with the generated information
    - [ ] automatically determines if the character is legal in Adventurers League
    - [ ] can pass any number of stats and autofill the rest (blank for completely generated)

### v1.0.0 required
- [ ] fully portable GUI front-end for the CLI tools (current development branch - electron-gui)
- [ ] city/town generator - fully generate a city/town with business names, NPC's, and a population
    - [ ] passed basic info about town (name, size [exact diameter in meters OR small, medium, large, etc.], type [rural, metropolitan, mining, trade, etc.]) and generates the rest (blank for completely generated)
- [ ] encounter/combat generator
    - [ ] passed basic info about encounter/combat (combat rating, average group level, etc.) and generates the rest (blank for completely generated)
- [ ] world generator - fully generate a world with city/towns, roads, and geography
- [ ] world/town map generator - generates a image formatted file of a world and indiviual maps for its towns

## Programming Standards

### File Naming
````c++
cppFile.cpp
headerFile.h
````

### Code Blocks
````c++
/**
  * @desc function description here
  * @param arg bar - what purpose this arg will serve
  * @return function - what does the function return and why
  */
function Class::foo(arg bar) {
    // do stuff
    // 4 space tabbed indent
}
````

### Function and Variable Naming
````c++
/**
  * @desc function description here
  * @param arg variableName - what purpose this arg will serve
  * @return function - what does the function return and why
  */
function Class::my_function_name(arg variableName) {
    // do stuff
}
````

### Class Naming
````c++
class ClassName {
private:
    // private variables and functions here

public:
    // public variables and functions here
};
````

### Switch Statements
````c++
/* this should be the standard method for
    writing a switch statement unless switch
    scoping is required */
switch(c) {
case 'a': {
    // case a code here
} break;

case 'b': {
    // case b code here
} break;

case 'c': {
    // case c code here
} break;

default: {
    // catch all code here
}
}
````