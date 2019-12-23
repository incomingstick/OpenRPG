/*
nodejs - node-addon.cpp
Created on: June 26, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <node.h>
#include "wrappers.h"

using namespace ORPG;

namespace ORPGJS {
    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports) {
        DieWrapper::Init(exports);
        ExpressionTreeWrapper::Init(exports);
        NameGeneratorWrapper::Init(exports);

        NODE_SET_METHOD(exports, "ORPG_VERSION", ORPG_VERSION);

        NODE_SET_METHOD(exports, "race_has_last", race_has_last);
        NODE_SET_METHOD(exports, "race_is_gendered", race_is_gendered);
    }

    NODE_MODULE(orpg, InitAll)
}