# Contributing to the project

So you want to know how you can help?? You've come to the right place!
Below you will find many ways you can help.

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

### TODO's

### General TODO's
- [ ] documentation and man pages
- [ ] spelling and grammar updates
- [ ] roll module test suite

### Release Requirement TODO's

#### v0.1.0-dev
- [X] dice simulation program (began implementation in [v0.0.3-dev](https://github.com/incomingstick/OpenRPG/tree/v0.0.3-dev))
    - [ ] allows full math using dice (current development branch - roll-module)
- [X] name generator (began implementation in [v0.0.2-dev](https://github.com/incomingstick/OpenRPG/tree/v0.0.2-dev), current development branch - names-module)
    - [ ] Aarakocra ([EE](http://dnd.wizards.com/articles/features/elementalevil_playerscompanion))
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
    - [ ] Kor ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [ ] Lizardfolk (VOLO)
    - [ ] Merfolk ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [ ] Minotaur ([UA: "Waterborne Adventures"](https://media.wizards.com/2015/downloads/dnd/UA_Waterborne_v3.pdf))
    - [ ] Revenant ([UA: "Gothic Heroes"](https://dnd.wizards.com/sites/default/files/media/upload/articles/UA%20Gothic%20Characters.pdf))
    - [ ] Shifter: ([UA: "Eberron"](https://media.wizards.com/2015/downloads/dnd/UA_Eberron_v1.pdf))
    - [ ] Tabaxi (VOLO)
    - [ ] Tiefling ([SRD](https://dnd.wizards.com/articles/features/systems-reference-document-srd), PHB)
    - [ ] Tiefling: Variant (other than Winged) (SCAG)
    - [ ] Tiefling: Winged Variant (SCAG)
    - [ ] Tiefling: Infernal and Abyssal variants ([UA: "That Old Black Magic"](https://media.wizards.com/2015/downloads/dnd/07_UA_That_Old_Black_Magic.pdf))
    - [ ] Triton (VOLO)
    - [ ] Vampire ([ZEN](http://media.wizards.com/2016/downloads/magic/Plane%20Shift%20Zendikar.pdf))
    - [ ] Warforged: ([UA: "Eberron"](https://media.wizards.com/2015/downloads/dnd/UA_Eberron_v1.pdf))
- [ ] character generator
    - [ ] populates a PDF character sheet with the generated information
    - [ ] automatically determines if the character is legal in Adventurers League
    - [ ] can pass any number of stats and autofill the rest (blank for completely generated)

#### v1.0.0
- [ ] fully portable GUI front-end for the CLI tools
- [ ] city/town generator - fully generate a city/town with business names, NPC's, and a population
    - [ ] passed basic info about town (name, size [exact diameter in meters OR small | medium |large | etc.], type [rural, metropolitan, mining, trade, etc.]) and generates the rest (blank for completely generated)
- [ ] encounter/combat generator
    - [ ] passed basic info about encounter/combat (combat rating, average group level, etc.) and generates the rest (blank for completely generated)
- [ ] world generator - fully generate a world with city/towns, roads, and geography
- [ ] world/town map generator - generates a image formatted file of a world and indiviual maps for its towns

Message me with questions or visit me on Tumblr at [import-os](mkesec.io).

### Pull Request

For something to be considered for merging into master it must be
submitted as a Pull Request to a current developement branch first.
Pull requests must follow the format found in the [Issue Template](ISSUE_TEMPLATE.md)
file.

### Programming Standards

#### Code Blocks
````c++
function Class::foo(arg bar) {
    // do stuff
    // 4 space tabbed indent
}
````

#### Function and Variable Naming
````c++
function Class::my_function_name(arg variableName) {
    // do stuff
}
````

#### Class Naming
````c++
class ClassName {
private:
    // private variables and functions here

public:
    // public variables and functions here
};
````

#### File Naming
````c++
cppFile.cpp
headerFile.h
````
