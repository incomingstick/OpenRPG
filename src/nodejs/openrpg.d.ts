/**
 * Type definitions for the openrpg-libs modules
 *
 * Project: OpenRPG <https://openrpg.io>
 * Definitions by: incomingstick <https://github.com/incomingstick>
 */
declare module 'openrpg-libs' {
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
         * @param const std::string exp - the string to become the input string
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

    export class NameGenerator {
        public race: string;
        public subrace: string;
        public gender: string;

        public constructor(_race: string);
        public constructor(_race: string, _gender: string);
        public constructor(_race: string, _gender: string, _location: string);

        public make_name(): string;
        public make_first(): string;
        public make_last(): string;
    }
}
