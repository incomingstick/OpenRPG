const os = require('os');
const path = require('path');

/**
 * define the location to import the node addon wrappers from
 * Windows:         ../build/Releasse/
 * Linux and macOS: ../build/lib/openrpg/
 **/
let prefix;
const appDir = path.dirname(path.dirname(__dirname));

if (os.type() === 'Linux' || os.type() === 'Darwin') {
    prefix = path.join(appDir, '/build/lib/openrpg/');
} else if (os.type() === 'Windows_NT') {
    const fs = require("fs");

    if (fs.existsSync(path.join(appDir, '/build/Debug/'))) {
        prefix = path.join(appDir, '/build/Debug/');
    } else
        prefix = path.join(appDir, '/build/Release/');

} else
   throw new Error("Unsupported OS found: " + os.type());

// define the export libraries here
const ORPG = require(prefix + 'orpgNode');

let ng = new ORPG.NameGenerator();
ng.set_race('dwarf');

console.log(ng.make_first());
console.log(ng.make_last());
console.log(ng.make_name());

ng.set_race('aarakocra');

console.log(ng.make_first());
console.log(ng.make_last());
console.log(ng.make_name());

module.exports = ORPG;
