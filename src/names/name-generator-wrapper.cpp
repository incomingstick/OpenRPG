/*
roll - DieWrapper.cpp
Created on: June 26, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <vector>
#include "names/names-wrapper.h"

namespace ORPGGUI {
    using v8::Context;
    using v8::Function;
    using v8::FunctionCallbackInfo;
    using v8::FunctionTemplate;
    using v8::Isolate;
    using v8::Local;
    using v8::NewStringType;
    using v8::Number;
    using v8::Boolean;
    using v8::Object;
    using v8::Persistent;
    using v8::String;
    using v8::Value;

    using namespace ORPG;

    Persistent<Function> NameGeneratorWrapper::constructor;
    NameGenerator NameGeneratorWrapper::wrappedGenerator;

    NameGeneratorWrapper::NameGeneratorWrapper(std::string _race) : NameGenerator(_race) {
        // does nothing
    }

    NameGeneratorWrapper::NameGeneratorWrapper(std::string _race, std::string _gender) : NameGenerator(_race, _gender) {
        // does nothing
    }

    NameGeneratorWrapper::NameGeneratorWrapper(std::string _race, std::string _gender, std::string _location) : NameGenerator(_race, _gender, _location) {
        // does nothing
    }

    NameGeneratorWrapper::~NameGeneratorWrapper() {
        // does nothing
    }

    void NameGeneratorWrapper::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "NameGenerator", NewStringType::kNormal).ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "get_race", get_race);
        NODE_SET_PROTOTYPE_METHOD(tpl, "get_gender", get_gender);
        NODE_SET_PROTOTYPE_METHOD(tpl, "set_race", set_race);
        NODE_SET_PROTOTYPE_METHOD(tpl, "set_gender", set_gender);
        NODE_SET_PROTOTYPE_METHOD(tpl, "make_name", make_name);
        NODE_SET_PROTOTYPE_METHOD(tpl, "make_first", make_first);
        NODE_SET_PROTOTYPE_METHOD(tpl, "make_last", make_last);

        Local<Context> context = isolate->GetCurrentContext();
        constructor.Reset(isolate, tpl->GetFunction(context).ToLocalChecked());
        exports->Set(context, String::NewFromUtf8(isolate, "NameGenerator", NewStringType::kNormal).ToLocalChecked(),
                     tpl->GetFunction(context).ToLocalChecked());
    }

    void NameGeneratorWrapper::New(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new NameGenerator(...)`
            NameGeneratorWrapper* obj;
            Local<String> def;

            std::vector<std::string> argv;

            for(int i = 0; i < args.Length(); i++) {
                v8::String::Utf8Value v8Str(isolate, args[i]);
                std::string str(*v8Str);
                argv.push_back(str);
            }

            switch (argv.size()) {
            case 1: {
                wrappedGenerator = NameGenerator(argv[0]);
                obj = new NameGeneratorWrapper(argv[0]);
                break;
            }

            case 2: {
                obj = new NameGeneratorWrapper(argv[0], argv[1]);
                wrappedGenerator = NameGenerator(argv[0], argv[1]);
                break;
            }

            case 3: {
                obj = new NameGeneratorWrapper(argv[0], argv[1], argv[2]);
                wrappedGenerator = NameGenerator(argv[0], argv[1], argv[2]);
                break;
            }

            default: {
                wrappedGenerator = NameGenerator();
                obj = new NameGeneratorWrapper();
            }
            }

            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            // Invoked as plain function `NameGenerator(...)`, turn into construct call.
            const int argc = 1;
            Local<Value> argv[argc] = { args[0] };
            Local<Function> cons = Local<Function>::New(isolate, constructor);
            Local<Object> result =
                cons->NewInstance(context, argc, argv).ToLocalChecked();
            args.GetReturnValue().Set(result);
        }
    }

    void NameGeneratorWrapper::get_race(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        auto raceString = wrappedGenerator.get_race();
        const char*  str = raceString.c_str();

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }

    void NameGeneratorWrapper::get_gender(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        auto genderString = wrappedGenerator.get_gender();
        const char*  str = genderString.c_str();

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }

    void NameGeneratorWrapper::set_race(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        String::Utf8Value v8Str(isolate, args[0]);

        std::string str = *v8Str ? *v8Str : "dwarf";

        wrappedGenerator.set_race(str);

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str(), NewStringType::kNormal).ToLocalChecked());
    }

    void NameGeneratorWrapper::set_gender(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        String::Utf8Value v8Str(isolate, args[0]);

        std::string str = *v8Str ? *v8Str : "";

        wrappedGenerator.set_gender(str);

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str(), NewStringType::kNormal).ToLocalChecked());
    }

    void NameGeneratorWrapper::make_name(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        auto nameString = wrappedGenerator.make_name();
        const char*  str = nameString.c_str();

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }

    void NameGeneratorWrapper::make_first(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        auto nameString = wrappedGenerator.make_first();
        const char*  str = nameString.c_str();

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }

    void NameGeneratorWrapper::make_last(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        auto nameString = wrappedGenerator.make_last();
        const char*  str = nameString.c_str();

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }
}