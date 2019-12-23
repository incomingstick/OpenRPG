const ORPG = require('../src/nodejs/export');
const path = require('path');
const assert = require('assert');

// Control variables go here
const LOOP_INT = 1e4;   // The number of times we want to run loops
const LOOP_COMP = 3e-1;  // For higher processing computations this is used to compress/decrease the loop count
const TESTING_ASSET_LOC = path.join(path.dirname(__dirname), 'data/');

// TODO shrink this via the use of lists and loops!
describe('OpenRPG', () => {
    describe('Roll Module', () => {
        describe('Die', () => {
            let val;
            let die;
            it('d4.roll() >= 1 && <= 4', () => {
                die = new ORPG.Die(4);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 4);
                }
            });

            it('d6.roll() >= 1 && <= 6', () => {
                die = new ORPG.Die(6);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 6);
                };
            });

            it('d8.roll() >= 1 && <= 8', () => {
                die = new ORPG.Die(8);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 8);
                };
            });

            it('d10.roll() >= 1 && <= 10', () => {
                die = new ORPG.Die(10);
                for(i = 0; i < LOOP_INT; i++) { 
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 10);
                 };
            });

            it('d12.roll() >= 1 && <= 12', () => {
                die = new ORPG.Die(12);
                for(i = 0; i < LOOP_INT; i++) { 
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 12);
                 };
            });

            it('d20.roll() >= 1 && <= 20', () => {
                die = new ORPG.Die();
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 20);
                };
            });

            it('d100.roll() >= 1 && <= 100', () => {
                die = new ORPG.Die(100);
                for(i = 0; i < LOOP_INT; i++) {
                    val = die.roll();
                    assert.ok(val >= 1);
                    assert.ok(val <= 100);
                };
            });
        });

        describe('ExpressionTree', () => {
            let val;
            let exp = new ORPG.ExpressionTree();
            it('expression \'1d4\' >= 1 && <= 4', () => {
                exp.set_expression('1d4');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 4);
                }
            });

            it('expression \'1d6\' >= 1 && <= 6', () => {
                exp.set_expression('1d6');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 6);
                }
            });

            it('expression \'1d8\' >= 1 && <= 8', () => {
                exp.set_expression('1d8');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 8);
                }
            });

            it('expression \'1d10\' >= 1 && <= 10', () => {
                exp.set_expression('1d10');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 10);
                }
            });

            it('expression \'1d12\' >= 1 && <= 12', () => {
                exp.set_expression('1d12');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 12);
                }
            });

            it('expression \'1d100\' >= 1 && <= 100', () => {
                exp.set_expression('1d100');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 100);
                }
            });


            it('expression \'4d6h3\' > 3 && <= 18', () => {
                exp.set_expression('4d6h3');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 3);
                    assert.ok(val <= 18);
                }
            });

            it('expression \'4d6l3 + 6\' >= 9 && <= 41', () => {
                exp.set_expression('4d6l3 + 6');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 9);
                    assert.ok(val <= 24);
                }
            });

            it('expression \'d6 + d8 + 2\' >= 4 && <= 16', () => {
                exp.set_expression('d6 + d8 + 2');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 4);
                    assert.ok(val <= 16);
                }
            });

            it('expression \'d6 + d8 % 2\' >= 0 && <= 1', () => {
                exp.set_expression('d6 + d8 % 2');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 0);
                    assert.ok(val <= 1);
                }
            });

            it('expression \'2d6 + 4d6 + 5\' >= 11 && <= 41', () => {
                exp.set_expression('2d6 + 4d6 + 5');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 11);
                    assert.ok(val <= 41);
                }
            });

            it('expression \'(2d6 + 4)d6 + 5\' >= 11 && <= 101', () => {
                exp.set_expression('(2d6 + 4)d6 + 5');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 11);
                    assert.ok(val <= 101);
                }
            });

            it('expression \'2d(1d6 + 2) / 2\' >= 1 && <= 8', () => {
                exp.set_expression('2d(1d6 + 2) / 2');
                for(i = 0; i < LOOP_INT; i++) {
                    val = exp.parse_expression();
                    assert.ok(val >= 1);
                    assert.ok(val <= 8);
                }
            });

            it('expression \'\' to_string() === \'expression not yet set\'', () => {
                exp.set_expression('');
                assert.ok(exp.to_string() === 'expression not yet set');
            });

            it('expression \'\' === 0', () => {
                exp.set_expression('');
                assert.ok(exp.parse_expression() === 0);
            });

            it('expression \'0\' to_string() === \'head->(0)\\n\'', () => {
                exp.set_expression('0');
                assert.ok(exp.to_string() === 'head->(0)\n');
            });

            it('expression \'0\' === 0', () => {
                exp.set_expression('0');
                assert.ok(exp.parse_expression() === 0);
            });

            it('expression \'42\' to_string() === \'head->(42)\\n\'', () => {
                exp.set_expression('42');
                assert.ok(exp.to_string() === 'head->(42)\n');
            });

            it('expression \'42\' === 42', () => {
                exp.set_expression('42');
                assert.ok(exp.parse_expression() === 42);
            });

            it('expression \'dhgdshd\' to_string() === \'invalid expression\'', () => {
                exp.set_expression('dhgdshd');
                assert.ok(exp.to_string() === 'invalid expression');
            });

            it('expression \'dhgdshd\' === 0', () => {
                exp.set_expression('dhgdshd');
                assert.ok(exp.parse_expression() === 0);
            });

            it('expression \'-1d0\' === 0', () => {
                exp.set_expression('-1d0');
                assert.ok(exp.parse_expression() === 0);
            });

            it('expression \'0d-1\' === -1', () => {
                exp.set_expression('0d-1');
                assert.ok(exp.parse_expression() === -1);
            });

            // TODO continue adding expression tests to esure we fully test our ExpressionParser
        });
    });

    describe('Names Module', () => {
        describe('NameGenerator', () => {
            let first;
            let last;
            let full;
            let ng = new ORPG.NameGenerator('dwarf', 'male', TESTING_ASSET_LOC);

            // Alphabetical list of races (and genders) to test
            const raceList = [
                {
                    race: '',
                    gender: ''
                },
                {
                    race: 'aarakocra',
                    gender: ''
                },
                {
                    race: 'changeling',
                    gender: ''
                },
                {
                    race: 'dragonborn',
                    gender: 'male'
                },
                {
                    race: 'dragonborn',
                    gender: 'female'
                },
                {
                    race: 'dwarf',
                    gender: 'male'
                },
                {
                    race: 'dwarf',
                    gender: 'female'
                },
                {
                    race: 'elf',
                    gender: 'male'
                },
                {
                    race: 'elf',
                    gender: 'female'
                },
                {
                    race: 'gnome',
                    gender: 'male'
                },
                {
                    race: 'gnome',
                    gender: 'female'
                },
                {
                    race: 'goliath',
                    gender: 'male'
                },
                {
                    race: 'goliath',
                    gender: 'female'
                },
                {
                    race: 'half-elf',
                    gender: 'male'
                },
                {
                    race: 'half-elf',
                    gender: 'female'
                },
                {
                    race: 'half-orc',
                    gender: 'male'
                },
                {
                    race: 'half-orc',
                    gender: 'female'
                },
                {
                    race: 'halfling',
                    gender: 'male'
                },
                {
                    race: 'halfling',
                    gender: 'female'
                },
                {
                    race: 'human',
                    gender: 'male'
                },
                {
                    race: 'human',
                    gender: 'female'
                },
                {
                    race: 'kalashtar',
                    gender: 'male'
                },
                {
                    race: 'kalashtar',
                    gender: 'female'
                },
                {
                    race: 'kor',
                    gender: 'male'
                },
                {
                    race: 'kor',
                    gender: 'female'
                },
                {
                    race: 'minotaur',
                    gender: 'male'
                },
                {
                    race: 'minotaur',
                    gender: 'female'
                },
                {
                    race: 'shifter',
                    gender: ''
                },
                {
                    race: 'tiefling',
                    gender: 'male'
                },
                {
                    race: 'tiefling',
                    gender: 'female'
                },
                {
                    race: 'warforged',
                    gender: ''
                }
            ];

            // TODO the NameGenerator could be optimized.
            for(item in raceList) {
                it('NameGenerator(\''+ raceList[item].race +'\', \''+ raceList[item].gender +'\') > 0', () => {
                    ng = new ORPG.NameGenerator(raceList[item].race, raceList[item].gender, TESTING_ASSET_LOC);
                    for(i = 0; i < LOOP_INT * LOOP_COMP; i++) {
                        first = ng.make_first();
                        last = ng.make_last();
                        full = ng.make_name();
                
                        // Check first name function
                        assert.ok(first.length > 0);
                
                        // Check last name function
                        if(ORPG.race_has_last(raceList[item].race)) {
                            assert.ok(last.length > 0);
                        } else {
                            assert.ok(last.length === 0);
                        }
                
                        // Check full name function
                        assert.ok(full.length > 0);
                    }
                });
            }
        });
    });
});