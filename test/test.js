const os = require('os');
const path = require('path');

/**
 * define the location to import the node addon wrappers from
 * Windows:         ../build/Releasse/
 * Linux and macOS: ../build/lib/openrpg/
 **/
let prefix;
const appDir = path.dirname(__dirname);

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

const orpg = require(prefix + 'orpgNode');
var assert = require('assert');

const LOOP_INT = 10000;

describe('OpenRPG', () => {
    describe('Roll Module', () => {
        describe('Die', () => {
            let die;
            let val;
            it('d4.roll()', () => {
                die = new orpg.Die(4);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 4);
                }
            });

            it('d6.roll()', () => {
                die = new orpg.Die(6);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 6);
                };
            });

            it('d8.roll()', () => {
                die = new orpg.Die(8);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 8);
                };
            });

            it('d10.roll()', () => {
                die = new orpg.Die(10);
                for(i = 0; i < LOOP_INT; i++) { 
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 10);
                 };
            });

            it('d12.roll()', () => {
                die = new orpg.Die(12);
                for(i = 0; i < LOOP_INT; i++) { 
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 12);
                 };
            });

            it('d20.roll()', () => {
                die = new orpg.Die();
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 20);
                };
            });

            it('d100.roll()', () => {
                die = new orpg.Die(100);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 100);
                };
            });
        });
    });
});