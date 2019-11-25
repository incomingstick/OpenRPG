import * as os from 'os';
import * as path from 'path';

/**
 * define the location to import the node addon wrappers from
 * Windows:         ../build/Releasse/
 * Linux and macOS: ../build/lib/openrpg/
 **/
let prefix: string;
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
export default require(prefix + 'openrpgAddon');
export const ExpressionTree = require(prefix + 'openrpgAddon').ExpressionTree;
export const Die = require(prefix + 'openrpgAddon').Die;
