/*
names - namesWrapper.h
Created on: December 8, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_NAMES_WRAPPER_H_
#define SRC_NAMES_WRAPPER_H_

#include <node.h>
#include <node_object_wrap.h>

#include "names.h"

namespace ORPGGUI {
    void race_is_gendered(const v8::FunctionCallbackInfo<v8::Value>& args);
    void race_has_last(const v8::FunctionCallbackInfo<v8::Value>& args);

    class NameGeneratorWrapper : public ORPG::NameGenerator, public node::ObjectWrap {
        private:
            static ORPG::NameGenerator wrappedGenerator;

            explicit NameGeneratorWrapper(std::string _race = "dwarf", std::string _gender = "");
            explicit NameGeneratorWrapper(std::string _race, std::string _gender, std::string _location);
            ~NameGeneratorWrapper();

            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Persistent<v8::Function> constructor;

            static void get_race(const v8::FunctionCallbackInfo<v8::Value>& args);
            static void get_gender(const v8::FunctionCallbackInfo<v8::Value>& args);

            static void set_race(const v8::FunctionCallbackInfo<v8::Value>& args);
            static void set_gender(const v8::FunctionCallbackInfo<v8::Value>& args);

            static void make_name(const v8::FunctionCallbackInfo<v8::Value>& args);
            static void make_first(const v8::FunctionCallbackInfo<v8::Value>& args);
            static void make_last(const v8::FunctionCallbackInfo<v8::Value>& args);
        public:
            static void Init(v8::Local<v8::Object> exports);
    };
}

#endif /* SRC_NAMES_WRAPPER_H_*/
