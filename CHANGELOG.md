# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html). However, note that all pre-v0.5.0 releases will have the suffix "-dev"

## [Unreleased]
### Added
- `man openrpg` thanks to [@var-username](https://github.com/var-username)

### Changed
- Moved the ASSET_LOC from a preprocessor definition to a Core function that searches multiple locations until it finds our data directory, throwing an error if no data can be found
- Core now takes advantage of the STL C++17 Filesystem library to locate our data folder using an array of paths

### Fixed

### Removed

## [0.5.0]
There is likely a TON that has changed that is not noted below. This release is a HUGE one, so we likely missed something. If you notice something is missing, please open a PR to fix it (with commit citations please)!

### Added
- We are now on the Arch User Repository and supporting Arch as our first Linux distro, as it is what I ([@incomingstick](http://github.comincomingstick)) use!
    - You can use the PKGBUILD branch of this Repo to build from `makepkg` that way
    - Clone us out of the AUR yourself by running `git clone https://aur.archlinux.org/openrpg-git.git && cd openrpg-git && makepkg -si`
    - You can use your favorite AUR helper, such as `yay`
        - Run `$ yay -S openrpg`
- We have improved our CMake logic to include the use of CPack for packaging, for all supported OS's! Check out our [downloads](https://openrpg.io/download/) page for your systems installer!
- Build scripts now include a package target for packaging with CPack
- NodeJS and `npm` integrated into the project workflow. You can now use `npm` and subsequently `cmake-js` to compile an additional `orpgAddon.node` binary that is a compiled Node module. 
    - This NodeJS addon aims to be a complete wrap of the C++ libraries. As such, most functions and classes should operate as you would expect the C++ counterpart.
    - Expose the `VERSION` preprocessor definition via the `ORPG_VERSION()` function
- An ASCII character sheet in `data/` thanks to [@var-username](https://github.com/var-username)
    - data/character_sheets/ascii_char_sheet
    - "data/character_sheets/Blank ASCII Character Sheet.txt"
- Added build info for Windows and improved the Unix documentation
- Added an uninstall target to CMake and Make, allowing for the use of `make uninstall` to... uninstall
    - cmake_uninstall.cmake.in
- build.sh has a ton of new commands, including an uninstall command `$ ./build.sh uninstall`
- This Changelog! You are likely looking at CHANGELOG.md
- The OGL is now in our main LICENSE, in addition to the OSL, to hopefully cover our bases with that stuff... hopefully we don't accidentally use copyright WotC stuff, or anyones stuff for that matter
- We now generate export headers via CMake for the Windows DLLs to ensure proper linking
- Some suggested vim settings, if thats your editor of choice
- TravisCI Windows builds! We are now testing Windows via TravisCI, as well as AppVeyor
- OSC XCode8 tests on TravisCI!
- Lots of namespacing to help prevent name collision when our project is used, the structure is as follows:
    - `ORPG`
    - `ORPG::Core`
    - `ORPG::Utils`
    - `ORPG::Roll`
    - `ORPG::Names`
    - `ORPG::Character`
- `NameGenerator` class now has a constructor that takes a file location as a `std::string`, here are some important notes:
    - By creating this constructor we are allowing an end user to specify the location the namelist we will read from. It is extremely important we explore any possible security implications of this further. I [@incomingstick](http://github.comincomingstick)) do think it could prove a beneficial feature to allow end users to specify namelists.
    - I, [@incomingstick](http://github.comincomingstick), created this function specifically to help the test suite. When testing on a fresh system, we are built before we test, but the release builds defines ASSET_LOC as: "/usr/local/data/openrpg" Because of this, it attempts to check a folder that has not been installed yet, and we need a way to point NameGenerator to our source data folder.
- Character module  now takes full advantage of our Names library to allow for the use of first and last names
- Added the Elf race to the Characters library
    - `class Elf : public Character`
    - `class HighElf : public Elf`
- `CharacterFactory` class has a new constructor that takes a name as a `std::string`
- Character library has a new class, `Skill` that helps represent the 5e Skill in a better way, and makes use of the new `EnumSkill` enum to pair score to human readable tags thanks to [@var-username](https://github.com/var-username)
- `ExpressionParser` now handles the modulo operation!

### Changed
- Building Libraries as Dynamic instead of Static, because why wouldn't a game want Dynamic/Shared libraries!
- Split .github/ISSUE_TEMPLATE.md into two files:
    - .github/FEATURE_REQUEST.md
    - .github/BUG_REPORT.md
- Renamed `int random(...)` to `int randomInt(...)` in the Utils namespace thanks to [@var-username](https://github.com/var-username)
- Fixed some install locations to better form to different platforms
- build.bat now has actual commands such as `> .\build.bat clean`, or `> .\build.bat rebuild` as well as better error reporting
- Make sure we don't accidentally add some packaged/compressed files to the repo, cuz that would be obnoxious
- Lots of "auto-fication" across the project, as well as other C++11 improvements
- Lots of restructuring within the files themeselves to help keep things better organized
- Lots of additional documention comments throughout the project for you other devs out there
- `levels[]` is now an externally definded global variable renamed to `EXP[]` in the `include/character/character.h` header, so you must link to the Character library to use is
- The `Skills` struct is now a class that acts as a wrapper of sorts for the `Skill` class and the `EnumSkill` enum thanks to [@var-username](https://github.com/var-username)
- `Character` class now uses the `Skills` class internally and has a new function to interface with it via `void update_skills()` thanks to [@var-username](https://github.com/var-username)
- Some header guards improved to better show their purpose in the project file system

### Fixed
- Typo in the Warforged namelist that gave "Zealot" a period (was "Zealot.")
- Consistant URL usage for [openrpg.io](https://openrpg.io)
- Better CMake output to help you developers understand whats going where / when.
- When installed on some systems, the creation of a data folder could potentially cause VSCode to fail to open
- Linking issues when running `make check` could cause some tests to fail, on some systems
- Issue when running `make check` on a release build, that caused the tests to be unable to locate the data assets
- A bug that would cause some divide by zero operations, as well as preventing the rolling of a 1 sided die thanks to [@tehguy](https://github.com/tehguy)
- A typo in the roll parser test that was incorrectly validating d6's thanks to [@pashcovich](https://github.com/pashcovich)
- Missing note in Core::print_basic_help() about how to exit OpenRPG.
- Fixed a bug in the ExpressionTree where the `globalReadOffset` was not being reset when a new expression was set
- Fixed a bug when stringing multiple rolls together that would causing the tree to parse an expression such as 2d6+4d8 as (2d6+4)d8
    - Honestly there are a TON of bug fixes with the roll parser now that we are using the Mocha test suite
- Fixed a bug in NameGenerator that wasn't resetting the raceFile when a new race was set
- Fixed version sheild in CHANGELOG.md (it still had the '-dev'affix)

### Removed
- Obliterated the old Name Generator test src/tests/name-generator-test.cpp


## [0.4.4-dev] - 2017-11-05
### Added
- Windows build script: build.bat
- A `help` or `h` command in the orpg console `orpg >`
- A Code of Conduct! See .github/CODE_OF_CONDUCT.md

### Changed
- Put back the Linux Clang 5.0 build that was hidden in the last patch
- TravisCI builds on OSX will do a brew update, as sometimes they were not up to date for the build we were trying to do...

### Removed
- All Unix/POSIX headers to allow for compilation on Windows
- Some redundant headers
- The `get_console_width()` and `get_console_height()` functions
- The TODO's list from the Contributing file, .github/CONTRIBUTING.md


## [0.4.3-dev] - 2017-10-14
### Removed
- TravisCI was failing internally when trying to use Clang 5.0 through the LLVM toolchain on Linux via the truster repository. Specifically it would fail during an apt call, something outside of our control, so we simple will hide this test for now.


## [0.4.2-dev] - 2017-06-02
### Added
- A whole suite of new TravisCI builds for testing GCC, LLVM, and Clang compilers on multiple platforms

### Changed
- The build compiler is set to c++14 and the individual modules have `CXX_STANDARD` set to 11 in CMake


## [0.4.1-dev] - 2017-05-31
### Fixed
- A fatal bug from running `make check` in the Roll Parser test that was calling a function that no longer existed...


## [0.4.0-dev] - 2017-05-31
### Added
- `INCLUDE` rule for our `include/` folder in CMakeLists.txt to install the headers with our library when running `make install`
- `build.sh` support for "darwin" (OSX) and "cygwin" builds
- Install rules for TravisCI in .travis.yml
- .gitignore rules updated to block extra api and Rust stuff thanks to [@hurnhu](https://github.com/hurnhu) as well as some web files/folders
- A new constructor in `NameGenerator` that accepts two `std::string`'s, race and gender
- The Character library now contains a constant array, `levels[]`, with 20 integers that contain the experince values used when determining if you should level up
- The traditional alignment grid is expressed via the `Alignment` enum in the Character library
- All of the 5e languages are expressed via the `Language` enum in the Character library
- The Charcter library contains a small `enum Gender`
- An enum exists within the Charcter library that contains the 5e sizes
- Ability scores that are traditionally used in D&D are allocated via a struct called `Ability`
- The 5e Skill list is expressed via the `Skills` struct
- The concept of 5e vision via `enun VisionType` and `struct Vision` in the Character library
- A function `int gen_stat()` that generates an array of stats > 1 && < 20 in the Character library
- A function `int modifier(...)` that returns an integer representation of the passed ability modifier defined as `(abil - 10) / 2` exactly
    - Note, this is intended to always round down. Data loss is acceptable, as it is a floor function
- A `Character` class that is the general outline for a 5e character sheet, with a few additions that a programmer may find handy
- "Race" classes that are children of the `Character` class that make use of the `Ability` struct to apply racial bonuses:
    - `class Human : public Character {...}`
    - `class Dwarf : public Character {...}`
    - `class HillDwarf : public Dwarf {...}`
- A helper class `CharacterFactory` that helps generate a `Character` object that contains the following functions:
    - `Character* NewCharacter(Ability ab = ability_struct())`
    - `Character* NewCharacter(int identifier)`
    - `Character* NewCharacter(int identifier, Ability ab)`
    - `void reset()`
    - `std::vector<std::string> current_options()`
    - `bool has_options()`
    - `void select_option(int index)`
    - `int current_id()`
- Tons of new namelists added to `data/names/` for `NameGenerator` to use thanks primarily to [Hen](hwangcodes@gmail.com) unless otherwise noted:
    - dragonborn/child.lst thanks to [@capsicaw](https://github.com/capsicaw)
    - elf/child.lst thanks to [@capsicaw](https://github.com/capsicaw)
    - goliath/female.lst
    - goliath/last.lst
    - goliath/male.lst
    - halfling/female.lst
    - halfling/last.lst
    - halfling/male.lst
    - kor/female.lst
    - kor/male.lst
    - minotaur/female.lst
    - minotaur/last.lst
    - minotaur/male.lst
    - tiefling/female.lst
    - tiefling/last.lst
    - tiefling/male.lst
    - aarakocra.lst
    - changeling.lst
    - warforged.lst
- An API can be built using Rust that interfaces with our compiled binaries thanks to [@hurnhu](https://github.com/hurnhu):
    - api/Cargo.toml
    - api/main.rs
    - api/Rocket.toml
- Discord info in the `CONTRIBUTING.md` file instead of my old tumblr blog

### Changed
- Renamed some header guards for better consistancy across the library
- Renamed Utils library to Core
- Moved C++ standard back to C++14
- Improved `openrpg -n` call to `NameGenerator` to account for gender and warn when too few arguments are given
- Better error reporting when invalid syntax is provided to `roll`
- Better error reporting when invalid syntax is provided to `name-generator` as well as when it is unable to locate a data file
- Structure of `include/` to better mirror that of other well known libraries, leaning heavily on Boost specifically  
    - character.h == redefined
    - die.h -> roll/die.h
    - names.h == redefined
    - openrpg.h ++ added
    - opt-parser.h -> core/opt-parser.h
    - roll-parser.h -> roll/roll-parser.h
    - roll.h ++ added
    - utils.h -> include/core/utils.h

### Fixed
- Segfault caused when anything other than exact syntax is provided, i.e: `$ roll hahahaha -v 2d10+6`
- Errors when a only a race is provided to `name-generator`

### Removed
- Cleaned up some CMakeLists.txt logic of irrelevant header logic
- Unnecessary and platform dependant headers project wide


## [0.3.0-dev] - 2017-04-24
### Added
- We have our own custom option parser (command line argument parser) fully defined in its own opt-parser header, designed to replace the platform dependant `<getopt.h>`
    - include/opt-parser.h
- Version number badge located at the top of the README.md
- Our CMake build now has a build type `CMAKE_BUILD_TYPE`
- A new config.h.in preprocessor defition for the build type, pulled fromt the variable `CMAKE_BUILD_TYPE`
- Windows `WIN32` preprocessor checks, because now we can build on Windows, kinda!
- Utils library now has a `gcd(...)` function that computes the greatest common divisor of int args a and b
- Open Gaming License (OGL) located in a new data directory
    - data/LICENSE

### Changed
- Discord badge color in README.md from blue to 7289da (discords official purple, I [@incomingstick](http://github.comincomingstick)) think...)
- ASSET_LOC in config.h.in pulls the CMake `DATA_DIR` variable
- Major project filesystem restructuring as noted below:
    - Moved the `src/tests/` folder out of `src/
        - src/tests/CMakeLists.txt -> tests/CMakeLists.txt
        - src/tests/generator-test.cpp -> src/tests/name-generator-test.cpp
        - src/tests/roll-parser-test.cpp -> tests/roll-parser-test.cpp
    - Moved all header files into a new `include/` folder structure
        - src/lib/utils.h -> include/utils.h
        - src/lib/modules/character.h -> include/character.h
        - src/lib/modules/names.h -> include/names.h
        - src/lib/modules/die.h -> include/die.h
        - src/lib/modules/roll-parser.h -> include/roll-parser.h
    - Restructured the `src/` folder to remove unnecessary folder layers
        - src/lib/utils.cpp -> src/utils.cpp
        - src/lib/modules/character/CMakeLists.txt -> src/character/CMakeLists.txt 
        - src/lib/modules/character/character-generator.cpp -> src/character/character-generator.cpp
        - src/lib/modules/character/character.cpp -> src/character/character.cpp
        - src/lib/modules/names/CMakeLists.txt -> src/names/CMakeLists.txt 
        - src/lib/modules/names/names-generator.cpp -> src/names/name-generator.cpp
        - src/lib/modules/names/names.cpp -> src/names/names.cpp
        - src/lib/modules/roll/CMakeLists.txt -> src/roll/CMakeLists.txt 
        - src/lib/modules/roll/names-generator.cpp -> src/roll/name-generator.cpp
        - src/lib/modules/roll/names.cpp -> src/roll/names.cpp
    - Moved all assests into a new `data/` folder structure
        - src/assets/banners/welcome_mat1 ->  data/banners/welcome_mat1
        - src/assets/chatacter_sheets/ -> data/chatacter_sheets/
        - src/assets/dwarf/female -> data/dwarf/female
        - src/assets/dwarf/last -> data/dwarf/last
        - src/assets/dwarf/male -> data/dwarf/male
        - Merged human namelists in a new data directory they were all merged, see Removed section below)
            - data/names/human/female
            - data/names/human/last
            - data/names/human/male
- `NameGenerator` no longer checks for a relative assets folder, instead it checks for a predefind data folder when building
- `roll` CLA's verbose and version V's swapped
    - "verbose" = 'v'
    - "version" = 'V'
- `character-generator` CLA's verbose and version V's swapped
    - "verbose" = 'v'
    - "version" = 'V'

### Fixed
- Syntax throught the codebase that could be updated to use things provided in C++11

### Removed
- Due to folder restructuring, there was no need for some CMakeList.txt files!
    - src/lib/CMakeLists.txt
    - src/lib/modules/CMakeLists.txt
- `NameGenerator` class constructor no longer calls for a gender string
- Individual Human subrace namelists (they were all merged, see Changed section above)
    - src/assets/names/human/calishite/{female, last, male}
    - src/assets/names/human/chondathan/{female, last, male}
    - src/assets/names/human/damaran/{female, last, male}
    - src/assets/names/human/illuskan/{female, last, male}
    - src/assets/names/human/mulan/{female, last, male}
    - src/assets/names/human/rashemu/{female, last, male}
    - src/assets/names/human/shou/{female, last, male}
    - src/assets/names/human/truami/{female, last, male}


## [0.2.1-dev] - 2017-02-25
### Fixed
- Fatal bug that caused endless loop when running `roll`, always... oops


## [0.2.0-dev] - 2017-02-18
### Added
- Linux build scripts via `build.sh`
- Header guards and autogeneration notes in config.h.in and the resulting config.h
- The Names module now has a concept of subraces to allow for the reading of the human namelists
- Added namelist Asset files for Humans thanks to [@bloodredyeti](https://github.com/bloodredyeti)
    - src/assets/names/human/calishite/{female, last, male}
    - src/assets/names/human/chondathan/{female, last, male}
    - src/assets/names/human/damaran/{female, last, male}
    - src/assets/names/human/illuskan/{female, last, male}
    - src/assets/names/human/mulan/{female, last, male}
    - src/assets/names/human/rashemu/{female, last, male}
    - src/assets/names/human/shou/{female, last, male}
    - src/assets/names/human/truami/{female, last, male}
- First attempts at OSX building via .travis.yml and TravisCI
- ExpressionTree class in the Roll module that will handle all of the heavy lifting for die math parsing (this is the muscle)
- Two new `Character` class constructors that accept Ability and Skill structs
- `Character` class accessor functions for each Ability score's respective modifier
- A function called `passive_stat(...)` that accepts an int and computes what its "passive" value is, and we assume this int is the value of a 5e Skill
- Allowing an extremely rudimentary character sheet to be printed of a `Character` class type via the `to_string()` function
- Layout of what the general character generation process should look like via `character-generator`
- Comments better defined in .github/CONTRIBUTING.md, and added stylizion guide for switch statements

### Changed
- Renamed the Die library to the Roll Parser library
- Pulled what was the `Die` class definitions out of die.cpp and put it into the die.h header file as its just so small, this allowed for the renaming of die.cpp to roll-parser.cpp
    - src/modules/roll/die.cpp -> src/modules/roll/roll-parser.cpp
- Renamed roll.h to roll-parser.h
    - src/modules/roll/roll.h -> src/modules/roll/roll-parser.h
- Renamed the Roll module test to the Roll Parser test
    - src/tests/roll-test.cpp -> src/tests/roll-parser-test.cpp
- `openrpg` binary now links to the Names and Roll Parser libraries and no longer uses system calls to run those binaries
- Improved `openrpg` command line argument warnings when taking invalid input and arguments, as well as when using the `orpg >` prompt
- Improved `name-generator` command line argument warnings when taking invalid input and arguments
- Minor warning improvements when `roll` is aborting
- Character module now links to `roll-parser` and `names` libraries when linking during build time
- Expanded the `Character` classes internals to include stats such as current health, max health, level, experience, etc.

### Fixed
- `make install` should now properly grab include files

### Removed
- Git ignore definition for config.h was added in v0.1.1 but was never removed from source, and now it has
    - src/lib/config.h
- `int output(string log, int status)` from the Utils library
- Warnings from the `NameGenerator` class when unable to read from a file


## [0.1.1-dev] - 2017-02-12
### Changed
- License changed from GNU/GPLv3+ to the OpenRPG Software License (OSL) - Version 1.0

### Fixed
- Now preventing project generated such as Makefiles and config.h from being accidentally committed to the codebase

### Removed
- Gutted use of Bison or Flex for a lexer, we will do the heavy lifting ourselves, however this release does not contain that muscle
    - src/lib/modules/roll/roll-parser.y
    - src/lib/modules/roll/roll-scanner.l


## [0.1.0-dev] - 2017-01-31
### Added
- Brand new website and small project branding at https://openrpg.io
- Defined OpenRPGs goals as a library, and software, as well as laid out an initial v1.0 release goal in both README.md and .github/CONTRIBUTING.md
- License information at the bottom of README.md
- Discord badge located at the top of the README.md
- TravisCI build badge located at the top of the README.md
- .travis.yml file for webhooking TravisCI builds whenever we push to GitHub
- Standardized exit codes across the project with flags defined in the Utils library within utils.h
- Initial test files for the Roll module, called when running `make check`
    - src/lib/tests/roll-test.cpp
- Utils library now offers a `random(...)` function to give us a standard way to get a random integer between two bounds
- Siginificant overhaul of the Roll module, and first pass at using a lexer for better parsing
    - New src/lib/modules/roll-parser.y
    - New src/lib/modules/roll-parser.l
    - New src/lib/modules/roll.h
    - New command line arguments "positive" or 'p', and "sum-series" or 's'
    - A total of 16 additional preprocessor definitions for represending types of operations for die math
    - POS_FLAG and SUM_FLAG global boolean flag variables
    - `read_string(...)` function for flex and bison to parse in a string to yyi
    - `parse_node` struct for helping parse die math and a series of functions for building a parse tree
- `character-generator` command and Character module classes and functions, including your standard tabletop Stat block as a struct, the 5e D&D skills list as a struct, and the `Character` class
    - src/lib/modules/character/CMakeLists.txt
    - src/lib/modules/character/character-generator.cpp
    - src/lib/modules/character/character.cpp
    - src/lib/modules/character/character.h
- D&D 5e Character sheets as licensed in the OGL by WotC see src/assets/chatacter_sheets/

### Changed
- Clarified in README.md that the install location instructions are optional for building OpenRPG
- Utils now builds as its own separate library, instead of building directly into the `openrpg` binary
- Generator module renamed to Names module and links to the Utils library
    - src/lib/modules/generator/CMakeLists.txt -> src/lib/modules/names/CMakeLists.txt
    - src/lib/modules/generator/name-generator.cpp -> src/lib/modules/names/name-generator.cpp
    - src/lib/modules/generator/generator.cpp -> src/lib/modules/names/names.cpp
    - src/lib/modules/generator/generator.h -> src/lib/modules/names/names.h
- Renamed a couple of functions in the Utils library to better align with what they do
    - load_file(...) -> file_to_string(...)
    - verbose(...) -> output(...)
- Die module converted to using the Utils libraries provided `random(...)` function, as noted above
- src/lib/modules/roll/CMakeLists.txt searches for Bison and Flex to output parser and scanner files for the Roll module
- `Die` is pulled out into its own library

### Fixed
- CMake Legacy Cygwin errors hidden when using Cygwin to compile with GNU compilers


## [0.0.3-dev] - 2017-01-19
### Added
- Install location `-DCMAKE_INSTALL_PREFIX=/desired/install/location` instructions for CMake in README.md
- `src/lib/modules/CMakeLists.txt` that sets output directories and addes the generator and roll directories to the build tree ([@ShinyHobo](https://github.com/ShinyHobo))
- `generator` command and Generator module classes and functions, including the `NameGenerator` class, and `make_name()`, `make_first()`, `make_last()` functions. Also its CMake build rules.
    - src/lib/modules/generator/CMakeLists.txt
    - src/lib/modules/generator/name-generator.cpp
    - src/lib/modules/generator/generator.cpp
    - src/lib/modules/generator/generator.h
- `roll` command and Roll module classes and functions, including a basic parser of "die math" (i.e 1d6+1), and the `Die` class with the `roll(...)` functions.
    - src/lib/modules/roll/CMakeLists.txt
    - src/lib/modules/roll/roll.cpp
    - src/lib/modules/roll/die.cpp
    - src/lib/modules/roll/die.h
- More preprocessor defines in config.h.in including `VERSION`, `AUTHOR`, `COPYRIGHT`, and `ASSET_LOC`
- Parsing of arguments via a `parse_args(...)` function called at the start of each programs main function
- `bool QUIET_FLAG` and `bool VB_FLAG` in the Utils library and defaulting both to `false`
- `print_version_flag()` and `print_help_flag()` functions that adhear to the GNU guidelines for help and version arguments
- `bool print_file(std::string file)` to the Utils library that prints the text contents of the given file
- `int verbose(string log, int status)` to the Utils library that outputs the log string to `stderr` if `VB_FLAG` is set
- `int parse_input(string in)` to the Utils library that parses text input into the console and determines the appropriate response/action such as calling `roll`, or `generator`, from another process
- `TESTING_FLAG` and `TESTING_ASSET_LOC` preprocessor definitions for help distinguishing when testing
- src/lib/config.h from CMake output of config.h.in saved with source ([@ShinyHobo](https://github.com/ShinyHobo))

### Changed
- Made .github/PULL_REQUEST_TEMPLATE.md more concise
- Renamed `src/main.cpp` -> `src/openrpg.cpp`
- Utils `parse(...)` to help the roll module to handle addition and subtraction of all standard D&D dice in additon to D2 and D30 ([@ShinyHobo](https://github.com/ShinyHobo))
- Moved the `assets/` folder into the `src/` folder ([@ShinyHobo](https://github.com/ShinyHobo))
    - assets/banners/welcome_mat1 -> src/assets/banners/welcome_mat1
    - assets/names/dwarf/female -> src/assets/names/dwarf/female
    - assets/names/dwarf/last -> src/assets/names/dwarf/last
    - assets/names/dwarf/male -> src/assets/names/dwarf/male
- Linking to Generator and Roll modules when building openrpg so we don't have to call system commands from ([@ShinyHobo](https://github.com/ShinyHobo))
- Building with C++11 as a standard across the project ([@ShinyHobo](https://github.com/ShinyHobo))

### Fixed
- consistant commenting for file headings
- Typos in CMakeLists.txt
- `make check` can now properly be run prior to `make install`


### Removed
- Git CMake package hook as there is no current need for our software to understand its own git versioning
- Post `openrpg` CMake build target that copied the assets folder after building


## [0.0.2-dev] - 2017-01-08
### Added
- LICENSE (GNU General Public License, version 3)
- README.md containing a short description and build, integrity check, and install instructions
- GitHub integration files to help make contributing, bug reporting, and pull requests just a little easier
    - .gitignore
    - .github/CONTRIBUTING.md
    - .github/ISSUE_TEMPLATE.md
    - .github/PULL_REQUEST_TEMPLATE.md
- Initial CMake build files, build targets for `openrpg` as well as rules for `make install`
    - CMakeLists.txt
    - config.h.in that generates src/lib/config.h
- Building with C++14 as a standard across the project
- Initial test files for the Generator module and rules for `make check`
    - src/tests/CMakeLists.txt
    - src/tests/generator-test.cpp
- The `openrpg` command's main C++ source file
    - src/main.cpp
- A utilities modules to help with building functions project wide, including file loading, getting console dimensions, and reading safer input from a user
    - src/lib/utils.cpp
    - src/lib/utils.h
- Added namelist Asset files for Dwarfs
    - src/assets/names/dwarf/female
    - src/assets/names/dwarf/last
    - src/assets/names/dwarf/male
- The `openrpg` command welcome banner
    - src/assets/banners/welcome_mat1

[Unreleased]: https://github.com/incomingstick/OpenRPG/compare/v0.5.0...master
[0.5.0]: https://github.com/incomingstick/OpenRPG/compare/v0.4.4-dev...v0.5.0
[0.4.4-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.4.3-dev...v0.4.4-dev
[0.4.3-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.4.2-dev...v0.4.3-dev
[0.4.2-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.4.1-dev...v0.4.2-dev
[0.4.1-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.4.0-dev...v0.4.4-dev
[0.4.0-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.3.0-dev...v0.4.0-dev
[0.3.0-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.2.1-dev...v0.3.0-dev
[0.2.1-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.2.0-dev...v0.2.1-dev
[0.2.0-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.1.1-dev...v0.2.0-dev
[0.1.1-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.1.0-dev...v0.1.1-dev
[0.1.0-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.0.3-dev...v0.1.0-dev
[0.0.3-dev]: https://github.com/incomingstick/OpenRPG/compare/v0.0.2-dev...v0.0.3-dev
[0.0.2-dev]: https://github.com/incomingstick/OpenRPG/tree/v0.0.2-dev