## NOTE
This repository is for the back end libraries for OpenRPG. If you are looking for the App, please visit our sister repository, [here](https://github.com/incomingstick/OpenRPG-App).

# OpenRPG
[![Build Status](https://travis-ci.org/incomingstick/OpenRPG.svg?branch=master)](https://travis-ci.org/incomingstick/OpenRPG)
![Version Number](https://img.shields.io/badge/version-v0.5.2-blue.svg)
[![Discord Chat](https://img.shields.io/badge/chat-on%20discord-7289da.svg)](https://discord.gg/xEwaYE5)

[![NPM](https://nodei.co/npm/openrpg-libs.png)](https://nodei.co/npm/openrpg-libs/)

OpenRPG is still in its infancy and I want it to do a lot by v1.0.0!  
What OpenRPG aims to accomplish two fold.  

First, it will be a tool for someone to use to quickly create content
for a tabletop RPG world. v1.0.0 will focus specifically on the
5e rules, however I hope to have that expand out to include
Pathfinder and as far back as AD&D.

Secondly, OpenRPG should be structured in such a way that game developers
that want to emulate the d20 system in a video game could easily implement
our libraries in their games to help speed production of back end tools.

Some of the features this tool will include by v1.0.0 are:
- A GUI front-end for the CLI tools
- A die simulation tool
- A name generator tool
- A character generator tool (with the option to autofill a character sheet)
- A town generator tool
- An encounter/combat generator tool
- A world generator tool
- A world/town map generator

... And more (hopefully)!

v0.1.0 is a basis for the CLI/developer version, but v1.0.0 will contain a
portable GUI that works on Windows, Linux, and macOS.

## Installing
### Arch Linux Install
We are now on the Arch User Repository! You can use your favorite AUR wrapper, or simply makepkg.

**AUR Wrapper Example:** `$ yay -S openrpg-git`

**Makepkg Example:** `$ git clone https://aur.archlinux.org/openrpg-git.git && cd openrpg-git && makepkg -si`

Thats it! You should now be able to run the following commands from the command line: `openrpg`, `roll`, `name-generator`, `character-generator` as well as linking against our shared libraries!

### NodeJS (npm) Install
We are also available via the NodeJS Package Manager (npm). You may use us in your own node projects by running the command under NPM Dependancy Install example, or install us globally via the NPM Global Install example.

- **NPM Dependancy Install Example:** `$ npm install openrpg-libs`
- **NPM Global Install Example:** `$ npm install -g openrpg-libs`

When installing via `npm` we currently **do not** ensure our CLI binaries are in your path, though they ARE downloaded and installed. The libraries themselves are natively accessable however, and can be used in your JavaScript or TypeScript projects. We provide typings for TypeScript as well!

To include/import the entirety of OpenRPG in a project simply use one of the following examples, depending on what JavaScript standard you are using:

- CommonJS: `const ORPG = require('openrpg-libs')`
- ECMAScript: `import * as ORPG from 'openrpg-libs'`

If you would only like to use specific parts of our library, try the following (this example shows how to use our ExpressionTree class):

- CommonJS: `const ExpressionTree = require('openrpg-libs').ExpressionTree`
- ECMAScript: `import { ExpressionTree } from 'openrpg-libs'`

Once included in this way you can then create an ExpressionTree as so:

```js
// Evaluate a die roll
export function die_eval(exp: string) {
    const parser = new ExpressionTree();

    if (parser.set_expression(exp)) {
        return parser.parse_expression();
    }

    return -1;
}
```

When working on our project we also provide the following `npm` scripts:
- `npm install`
- `npm start`
- `npm test`
- `npm run build`
- `npm run build:core`
- `npm run rebuild` 
- `npm run rebuild:core`
- `npm run compile`
- `npm run compile:core`
- `npm run dist`
- `npm run dist:core`
- `npm run dist:electron`
- `npm run clean`

**NOTE**: Some `npm` scripts have multiple targets. Any `npm` script with the `:core` target uses the build.js script to run instead of directly through `cmake-js`. This means they will not target the `orpgNode` binary, only targeting the core libraries and binaries. If the npm script has the `:electron` target, it builds against the Electron NodeJS version used by [OpenRPG-App](https://github.com/incomingstick/OpenRPG-App) instead of defaulting to the locally installed NodeJS version.

### Manually Installing from Source
After following any of the [Building](#Building) instructions below, in the `build/` folder, run make install `$ make install`

## Building
Currently we require `cmake` (at least v3.0) and `make`, and your choice of C/C++
compiler that supports the C++17 standard. You may also use `npm` to assist with the building and testing process.

**Note**: This project strives to keep its source as clean of any dependancies to be as cross platform as possible. If you have suggestions or improvements to help move toward that goal, please feel free to open issues, or even a Pull Request!

### Linux Build Script
The build script now provides some extra assistance with building, installing, uninstalling and more.

- **Debug build:** `$ ./build.sh`
- **Install debug build:** `$ ./build.sh install`
- **Release build:** `$ ./build.sh release`
- **Install release build:** `$ ./build.sh release install`
- **Clean build files:** `$ ./build.sh clean`
- **Clean build files and rebuild:** `$ ./build.sh rebuild`

**NOTE**: `build.sh` has the potential to work on MacOS, but is currently untested. If you happen to use a Mac, please help us test this!

### Windows Build Script
This script is VERY minimal compared to its bash counterpart. It could use a ton of improvements, so if that is something you are interested in, open a PR! Please make sure you have Visual Studio Build Tools (i.e msbuild) in your `%PATH%`.

- **Debug build:** `> .\build.bat`
- **Release build:** `> .\build.bat release`
- **Clean build files:** `> .\build.bat clean`
- **Clean build files and rebuild:** `> .\build.bat rebuild`

### Node Build Script
The Node build script (`build.js`) is used to assist with `npm` scripts. In general, the `build.js` script just checks the OS and calls the equivalant build script above. However, this script does have the additional target `download` that the Batch and Bash scripts do not contain. Calling this target will download precompiled binaries for your OS and put them in the local `dist/` folder. This is called when `npm install` is run on our package.

To download the precompiled binaries run `$ node build.js download`

**NOTE**: When calling this target, it will clear the current `dist/` folder before moving the downloaded files to this folder.

### Manual Build
1. Create a build directory `$ mkdir build`  
2. Move to the build directory `$ cd build`
3. Run cmake `$ cmake ..`
    - **Optionally**: `$ cmake -DCMAKE_INSTALL_PREFIX=/desired/install/location ..`  
4. Run make `$ make`  

### Check Integrity of Build
In the `build/` folder, run make check `$ make check` 

# License
OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
