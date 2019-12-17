/*
roll - rollWrapper.h
Created on: June 26, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_DIE_WRAPPER_H_
#define SRC_DIE_WRAPPER_H_

#include <node.h>
#include <node_object_wrap.h>

#include "roll.h"

namespace ORPGGUI {
    class DieWrapper : public ORPG::Die, public node::ObjectWrap {
        private:
            explicit DieWrapper(int max);
            ~DieWrapper();

            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Persistent<v8::Function> constructor;

            static void roll(const v8::FunctionCallbackInfo<v8::Value>& args);

            static void MAX(const v8::FunctionCallbackInfo<v8::Value>& args);
        public:
            static void Init(v8::Local<v8::Object> exports);
    };

    class ExpressionTreeWrapper : public ORPG::ExpressionTree, public node::ObjectWrap {
    private:
        static ORPG::ExpressionTree wrappedTree;

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Persistent<v8::Function> constructor;

        /**
         * @desc sets the input string to be scanned and parsed equal to the string exp
         * @param const std::string exp - the string to become the input string
         */
        static void set_expression(const v8::FunctionCallbackInfo<v8::Value>& args);
        
        /**
         * @desc parses the parse_node tree and returns the end result of the expression
         * @return int - the end result of the expression
         */
        static void parse_expression(const v8::FunctionCallbackInfo<v8::Value>& args);
        
        static void checked_sum(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void checked_multiplication(const v8::FunctionCallbackInfo<v8::Value>& args);
        
        /**
         * @desc returns a string of the tree starting with
         *     the top node node and taking precidence over the left node
         * @return string - a string representation of the current tree
         */
        static void to_string(const v8::FunctionCallbackInfo<v8::Value>& args);

        /**
         * @desc returns the input string that was give to the parser
         * @return string - the string that was give as input to the parser
         */
        static void get_input_string(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void is_exppression_valid(const v8::FunctionCallbackInfo<v8::Value>& args);
    public:
        static void Init(v8::Local<v8::Object> exports);
    };
}

#endif /* SRC_DIE_WRAPPER_H_*/
