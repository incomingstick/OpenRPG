/*
core - core-wrapper.cpp
Created on: Dec 23, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include "core/core-wrapper.h"

namespace ORPGJS {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::NewStringType;
    using v8::String;
    using v8::Value;

    /**
     * @desc exports the VERSION preprocessor definition as a 
     **/
    void ORPG_VERSION(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, VERSION, NewStringType::kNormal).ToLocalChecked());
    }
}