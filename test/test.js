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

const ORPG = require(prefix + 'orpgNode');
var assert = require('assert');

const LOOP_INT = 1e4;


// TODO shrink this via the use of lists and loops!
describe('OpenRPG', () => {
    describe('Roll Module', () => {
        describe('Die', () => {
            let val;
            let die;
            it('d4.roll() > 0 && <= 4', () => {
                die = new ORPG.Die(4);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 4);
                }
            });

            it('d6.roll() > 0 && <= 6', () => {
                die = new ORPG.Die(6);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 6);
                };
            });

            it('d8.roll() > 0 && <= 8', () => {
                die = new ORPG.Die(8);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 8);
                };
            });

            it('d10.roll() > 0 && <= 10', () => {
                die = new ORPG.Die(10);
                for(i = 0; i < LOOP_INT; i++) { 
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 10);
                 };
            });

            it('d12.roll() > 0 && <= 12', () => {
                die = new ORPG.Die(12);
                for(i = 0; i < LOOP_INT; i++) { 
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 12);
                 };
            });

            it('d20.roll() > 0 && <= 20', () => {
                die = new ORPG.Die();
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 20);
                };
            });

            it('d100.roll() > 0 && <= 100', () => {
                die = new ORPG.Die(100);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val > 0)
                    assert.ok(val <= 100);
                };
            });
        });

        describe('ExpressionTree', () => {
            let val;
            let exp = new ORPG.ExpressionTree();
            it('expression \'1d4\' > 0 && <= 4', () => {
                exp.set_expression('1d4');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val > 0)
                    assert.ok(val <= 4);
                }
            });

            it('expression \'1d6\' > 0 && <= 6', () => {
                exp.set_expression('1d6');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val > 0)
                    assert.ok(val <= 6);
                }
            });

            it('expression \'1d8\' > 0 && <= 8', () => {
                exp.set_expression('1d8');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val > 0)
                    assert.ok(val <= 8);
                }
            });

            it('expression \'1d10\' > 0 && <= 10', () => {
                exp.set_expression('1d10');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val > 0)
                    assert.ok(val <= 10);
                }
            });

            it('expression \'1d12\' > 0 && <= 12', () => {
                exp.set_expression('1d12');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val > 0)
                    assert.ok(val <= 12);
                }
            });

            it('expression \'1d100\' > 0 && <= 100', () => {
                exp.set_expression('1d100');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val > 0)
                    assert.ok(val <= 100);
                }
            });
        });
    });
});