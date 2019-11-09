/*
roll - DieWrapper.cpp
Created on: June 26, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include "rollWrapper.h"

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

    Persistent<Function> DieWrapper::constructor;

    DieWrapper::DieWrapper(int max) : Die(max) {
        // does nothing
    }

    DieWrapper::~DieWrapper() {
        // does nothing
    }

    void DieWrapper::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "Die", NewStringType::kNormal).ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "roll", roll);

        Local<Context> context = isolate->GetCurrentContext();
        constructor.Reset(isolate, tpl->GetFunction(context).ToLocalChecked());
        exports->Set(context, String::NewFromUtf8(isolate, "Die", NewStringType::kNormal).ToLocalChecked(),
                     tpl->GetFunction(context).ToLocalChecked());
    }

    void DieWrapper::New(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new Die(...)`
            auto value = args[0]->IsUndefined() ? 0 :
                         args[0]->NumberValue(context).FromMaybe(0);
            DieWrapper* obj = new DieWrapper(value);
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            // Invoked as plain function `Die(...)`, turn into construct call.
            const int argc = 1;
            Local<Value> argv[argc] = { args[0] };
            Local<Function> cons = Local<Function>::New(isolate, constructor);
            Local<Object> result =
                cons->NewInstance(context, argc, argv).ToLocalChecked();
            args.GetReturnValue().Set(result);
        }
    }

    void DieWrapper::roll(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        DieWrapper* obj = ObjectWrap::Unwrap<DieWrapper>(args.Holder());
        Die die(obj->MAX);

        args.GetReturnValue().Set(Number::New(isolate, die.roll()));
    }

    Persistent<Function> ExpressionTreeWrapper::constructor;
    ExpressionTree ExpressionTreeWrapper::wrappedTree;

    void ExpressionTreeWrapper::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "ExpressionTree", NewStringType::kNormal).ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "set_expression", set_expression);
        NODE_SET_PROTOTYPE_METHOD(tpl, "parse_expression", parse_expression);
        NODE_SET_PROTOTYPE_METHOD(tpl, "checked_sum", checked_sum);
        NODE_SET_PROTOTYPE_METHOD(tpl, "checked_multiplication", checked_multiplication);
        NODE_SET_PROTOTYPE_METHOD(tpl, "to_string", to_string);
        NODE_SET_PROTOTYPE_METHOD(tpl, "is_exppression_valid", is_exppression_valid);

        Local<Context> context = isolate->GetCurrentContext();
        constructor.Reset(isolate, tpl->GetFunction(context).ToLocalChecked());
        exports->Set(context, String::NewFromUtf8(isolate, "ExpressionTree", NewStringType::kNormal).ToLocalChecked(),
                     tpl->GetFunction(context).ToLocalChecked());
    }

    void ExpressionTreeWrapper::New(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new ExpressionTreeWrapper(...)`
            ExpressionTreeWrapper* obj = new ExpressionTreeWrapper();
            wrappedTree = ExpressionTree();
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            // Invoked as plain function `ExpressionTreeWrapper(...)`, turn into construct call.
            const int argc = 1;
            Local<Value> argv[argc] = { args[0] };
            Local<Context> context = isolate->GetCurrentContext();
            Local<Function> cons = Local<Function>::New(isolate, constructor);
            Local<Object> result =
                cons->NewInstance(context, argc, argv).ToLocalChecked();
            args.GetReturnValue().Set(result);
        }
    }

    void ExpressionTreeWrapper::set_expression(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        String::Utf8Value v8Str(isolate, args[0]);

        std::string exp = *v8Str ? *v8Str : "1d20";

        args.GetReturnValue().Set(Boolean::New(isolate, wrappedTree.set_expression(exp)));
    }

    void ExpressionTreeWrapper::parse_expression(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        args.GetReturnValue().Set(Number::New(isolate, wrappedTree.parse_expression()));
    }

    void ExpressionTreeWrapper::checked_sum(const v8::FunctionCallbackInfo<v8::Value>& args) {
        // TODO add wrapper
    }

    void ExpressionTreeWrapper::checked_multiplication(const v8::FunctionCallbackInfo<v8::Value>& args) {
        // TODO add wrapper
    }

    void ExpressionTreeWrapper::to_string(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        auto treeString = wrappedTree.to_string();

        const char*  str = treeString.c_str();

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }

    void ExpressionTreeWrapper::is_exppression_valid(const v8::FunctionCallbackInfo<v8::Value>& args) {
        Isolate* isolate = args.GetIsolate();

        String::Utf8Value v8Str(isolate, args[0]);

        const std::string exp = *v8Str ? *v8Str : "1d20";

        args.GetReturnValue().Set(Boolean::New(isolate, ExpressionTree::is_expression_valid(exp)));
    }
}