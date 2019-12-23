/*
core - core-wrapper.h
Created on: Dec 23, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CORE_WRAPPER_H_
#define SRC_CORE_WRAPPER_H_

#include <node.h>
#include <node_object_wrap.h>

#include "config.h"

namespace ORPGJS {
    void ORPG_VERSION(const v8::FunctionCallbackInfo<v8::Value>& args);
}

#endif /* SRC_CORE_WRAPPER_H_*/