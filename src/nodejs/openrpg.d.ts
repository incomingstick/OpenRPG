/**
 * Type definitions for the openrpg-libs modules
 *
 * Project: OpenRPG <https://openrpg.io>
 * Definitions by: incomingstick <https://github.com/incomingstick>
 */
declare module 'openrpg-libs' {
    /**
     * @desc This function exports the version number of the built OpenRPG libraries that are being used
     * @return string - the version number of the built OpenRPG libraries that are being used
     **/
    export function ORPG_VERSION(): string;
    
    export class Die {
        public constructor(max: number);

        /**
         * @desc randomly generate a integers between 1 and _MAX, where MAX is the value
         * that was passed to the Die when it was constructed. The result is generated
         * by using a random_device to seed a Mersenne Twister engine that generates 
         * uniformly distributed integers between 1 and _MAX.
         * between 1 and _MAX
         * @return number - a pesudo random integers between 1 and _MAX
         */
        public roll(): number;

        /**
         * @desc returns the number of sides this dice has, this is the same as
         * the max value that could potentially be rolled.
         * @return number - the max value that could be returned by this die
         */
        public MAX(): number;
    }

    export class ExpressionTree {
        public constructor();

        public static is_expression_valid(exp: string): boolean;

        /**
         * @desc sets the input string to be scanned and parsed equal to the string exp
         * @param const string exp - the string to become the input string
         */
        public set_expression(exp: string): boolean;

        /**
         * @desc parses the parse_node tree and returns the end result of the expression
         * @return number - the end result of the expression
         */
        public parse_expression(): number;

        /**
         * @desc outputs an error with ERROR_CODE if there
         *     would be an addition overflow
         * @param number op1 - an integer to be added
         * @param number op2 - an integer to be added
         * @return number - op1 + op2
         */
        public checked_sum(op1: number, op2: number): number;

        /**
         * @desc outputs an error with ERROR_CODE if there
         *     would be a multiplication overflow
         * @param number op1 - an integer to be multiplied
         * @param number op2 - an integer to be multiply by
         * @return number - op1 * op2
         */
        public checked_multiplication(op1: number, op2: number): number;

        /**
         * @desc returns a string of the tree starting with
         *     the top node node and taking precidence over the left node
         * @return string - a string representation of the current tree
         */
        public to_string(): string;

        /**
         * @desc returns the input string that was give to the parser
         * @return string - the string that was give as input to the parser
         */
        public get_input_string(): string;
    }

    /**
     * @desc this function takes in a string value representing a race and checks
     * against a hard coded list of races without last names, to determine if it
     * would have a last name list in our data folder.
     *
     * NOTE(incomingstick): Is is worth putting this in a header and making it a
     * part of the public lib?
     *
     * @param string race - the race to check if it would have a last name list
     * @return boolean - a boolean value containing weather the given race would
     *                  have a last name list
     **/
    export function race_has_last(race: string): boolean;

    /**
     * @desc this function takes in a string value representing a race and checks
     * against a hard coded list of races with gendered lists, to determine if it
     * would have a gendered name list in our data folder.
     *
     * NOTE(incomingstick): Is is worth putting this in a header and making it a
     * part of the public lib?
     *
     * @param string race - the race to check if it would have a gendered name list
     * @return boolean - a boolean value containing weather the given race would
     *                  have a gendered name list
     **/
    export function race_is_gendered(race: string): boolean;

    export class NameGenerator {
        public race: string;
        public subrace: string;
        public gender: string;

        public constructor(_race: string);

        /**
         * @desc Constructor for NameGenerator that is passed two optional
         * arguments. It sets race equal to _race and sets gender to _gender.
         *
         * @param string _race = "dwarf" - the race to use. defaults to dwarf
         * @param string _gender = "" - the gender of our race. defaults to
         * empty
         **/
        public constructor(_race: string, _gender: string);

        /**
         * @desc Constructor for NameGenerator that is passed three arguments.
         * It sets race equal to _race, gender to _gender, and location to
         * _location
         *
         * @param string _race - the race to use
         * @param string _gender - the gender of our race
         * @param string _location - the toplevel location to check for lst files.
         * note that /names will be appended to this location
         **/
        public constructor(_race: string, _gender: string, _location: string);

        /**
         * @desc Getter function for the race string of the NameGenerator
         * class
         *
         * @return string - the current race string
         **/
        public get_race(): string;

        /**
         * @desc Getter function for the gender string of the NameGenerator
         * class
         *
         * @return string - the current gender string
         **/
        public get_gender(): string;

        /**
         * @desc Setter function for the race string of the NameGenerator
         * class
         *
         * @param string newRaceStr - a string to set as the new race
         **/
        public set_race(newRaceStr: string): void;

        /**
         * @desc Setter function for the gender string of the NameGenerator
         * class
         *
         * @param string newRaceStr - a string to set as the new race
         **/
        public set_gender(setGenderStr: string): void;

        /**
         * @desc Generates a random full name by calling make_first and make_last,
         * checking their outputs, and concatenating a string together. If either
         * make_first or make_last return an emprt string it added to the full
         * name. If the string would be empty, this function returns an empty
         * string
         *
         * @return string - a concatenated string containing a full name. If no
         * string could be produced it will return an empty string
         **/
        public make_name(): string;

        /**
         * @desc Generates a random first name by reading from a random namelist
         * in the given location with the given race. If the race is gendered, but
         * no gender is currently set, we will randomly set gender to either female
         * or male. If no name can be generated this function will return an empty
         * string
         *
         * @return string - a string containing a first name. If no name could be
         * produced it will return an empty string.
         **/
        public make_first(): string;

        /**
         * @desc Generates a random last name by reading from a random namelist
         * in the given location with the given race. If no name can be generated
         * this function will return an empty string
         *
         * @return string - a string containing a last name. If no name could be
         * produced it will return an empty string.
         **/
        public make_last(): string;
    }
}
