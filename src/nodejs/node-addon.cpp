/*
roll - rollAddon.h
Created on: June 26, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <node.h>
#include "roll/roll-wrapper.h"
#include "names/names-wrapper.h"

using namespace ORPG;

namespace ORPGGUI {
    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports) {
        DieWrapper::Init(exports);
        ExpressionTreeWrapper::Init(exports);
        NameGeneratorWrapper::Init(exports);
    }

    NODE_MODULE(orpg, InitAll)
}