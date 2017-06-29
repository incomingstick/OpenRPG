# Contributing to the project

So you want to know how you can help?? You've come to the right place!
Below you will find many ways you can help.

## Contributing Issues

### Before Submitting an Issue
First, please do a search in open issues to see if the issue or feature request has already been filed. If there is an issue add your comments to this issue.

## Writing Good Bug Reports and Feature Requests

File a single issue per problem and feature request, do not file combo issues.

The more information you can provide, the more likely someone will be successful reproducing the issue and finding a fix. Therefore:

* Provide reproducible steps, what the result of the steps was, and what you would have expected.
* Description of what you expect to happen
* Animated GIFs
* Code that demonstrates the issue
* Version of OpenRPG
* Errors printed to the command line

## Contributing Fixes
First and foremost check the [Issues](https://github.com/incomingstick/OpenRPG/issues) page to see what needs to be done.
Once you're ready to start programming see the Programming Standards section.

I have broken the goals and needs by the "Difficulty" of the task. Beginner tasks
will be more specific, such as working on a certain function or method. Intermediate tasks
will be a little broader, such as creating a specific class or utility. Advanced
tasks will be major milestones that need to be completed. And should only be attempted
by someone that understand the language.

## Pull Request

For something to be considered for merging into master it must be
submitted as a Pull Request to a current developement branch first.
Pull requests must follow the format found in the [Issue Template](https://github.com/incomingstick/OpenRPG/blob/patch-v0.3.0-dev/.github/ISSUE_TEMPLATE.md)
file.

## Programming Standards

### File Naming
````c++
cppFile.cpp
headerFile.h
````

### Code Blocks
````c++
/**
  * @desc function description here
  * @param arg bar - what purpose this arg will serve
  * @return function - what does the function return and why
  */
function Class::foo(arg bar) {
    // do stuff
    // 4 space tabbed indent
}
````

### Function and Variable Naming
````c++
/**
  * @desc function description here
  * @param arg variableName - what purpose this arg will serve
  * @return function - what does the function return and why
  */
function Class::my_function_name(arg variableName) {
    // do stuff
}
````

### Class Naming
````c++
class ClassName {
private:
    // private variables and functions here

public:
    // public variables and functions here
};
````

### Switch Statements
````c++
/* this should be the standard method for
    writing a switch statement unless switch
    scoping is required */
switch(c) {
case 'a': {
    // case a code here
} break;

case 'b': {
    // case b code here
} break;

case 'c': {
    // case c code here
} break;

default: {
    // catch all code here
}
}
````