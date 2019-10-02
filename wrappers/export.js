var os = require('os');

/**
 * define the location to import the node addon wrappers from
 * Windows:         ../build/Releasse/
 * Linux and macOS: ../build/lib/openrpg/
 **/
let prefix;

if (os.type() === 'Linux' || os.type() === 'Darwin') {
    prefix = '../build/lib/openrpg/';
}
else if (os.type() === 'Windows_NT') {
    prefix = '../build/Release/';
}
else
   throw new Error("Unsupported OS found: " + os.type());


// define the export libraries here
const libroll = require(prefix + 'rollAddon');

module.exports = libroll;