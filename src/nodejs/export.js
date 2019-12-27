const os = require('os');
const path = require('path');

/**
 * define the location to import the node addon wrappers from
 * Windows:         ../build/Releasse/
 * Linux and macOS: ../build/lib/openrpg/
 **/
let prefix = null;
const appDir = path.dirname(path.dirname(__dirname));

const locations = [
    path.join(appDir, '/build/lib/openrpg/'),
    path.join(appDir, '/build/Debug/'),
    path.join(appDir, '/build/Release/'),
    path.join(appDir, '/bin/'),
    path.join(appDir, '/dist/'),
    '/bin',
    '/usr/bin',
    '/usr/share/bin',
    'c:/Program Files/OpenRPG/',
    'c:/Program Files (x86)/OpenRPG/'
]

if (os.type() === 'Windows_NT' ||
    os.type() === 'Linux' ||
    os.type() === 'Darwin') {
    const fs = require("fs");

    for(let index in locations) {
        if (fs.existsSync(locations[index])) {
            prefix = locations[index];
            break;
        }
    }
    if(prefix === null)
        throw new Error("Error: Unable to locate OpenRPG!");

} else
   throw new Error("Unsupported OS found: " + os.type());

// define the export libraries here
module.exports = require(prefix + 'orpgNode');
