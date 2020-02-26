---
layout: default
title: Contributing to OpenRPG
description: Learn how you can contribute to OpenRPG too
group: contributing
---
<h1>{{ page.title }}</h1>
<p class="lead">
    {{ page.description }}
</p>
<!-- Copied from CONTRIBUTING.md -->

## Contents

* Will be replaced with the ToC, including the "Contents" header
{:toc}

## Contributing Issues

### Before Submitting an Issue
First, please do a search in open issues to see if the issue or feature request has already been filed. If there is an issue add your comments to this issue.

## Reporting a Bug

Found something that is broken and needs fixing? Head on over to the [Issues](https://github.com/incomingstick/OpenRPG/issues) page and submit a new issue. When submitting a new issue, make sure you click 'Get Started' next to 'Bug Report' to make sure you are using the proper submission template. Please fill this out as thoroughly as possible so we can get to the bottom of your issue! 

## Request a Feature

Wish OpenRPG did something it doesn't already do? Head on over to the [Issues](https://github.com/incomingstick/OpenRPG/issues) page and submit a new issue. When submitting a new issue, make sure you click 'Get Started' next to 'Feature Request' to make sure you are using the proper submission template. Please fill this out as thoroughly as possible so we can get to the bottom of your issue! 

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

I have broken the goals and needs by the "Difficulty" of the task. Beginner tasks will be more specific, such as working on a certain function or method. Intermediate tasks will be a little broader, such as creating a specific class or utility. Advanced tasks will be major milestones that need to be completed. And should only be attempted by someone that understand the language.

## Pull Request

For something to be considered for merging into master it must be submitted as a Pull Request to a current developement branch first.
Pull requests must follow the format found in the [Pull Request Template](https://github.com/incomingstick/OpenRPG/blob/patch-v0.5.0-dev/.github/PULL_REQUEST_TEMPLATE.md)
file.

## Programming Standards

### File Naming

{% highlight cpp %}
cppFile.cpp
headerFile.h
{% endhighlight %}

### Code Blocks

{% highlight cpp %}
/**
  * @desc function description here
  * @param arg bar - what purpose this arg will serve
  * @return function - what does the function return and why
  */
function Class::foo(arg bar) {
    // do stuff
    // 4 space tabbed indent
}
{% endhighlight %}

### Function and Variable Naming

{% highlight cpp %}
/**
  * @desc function description here
  * @param arg variableName - what purpose this arg will serve
  * @return function - what does the function return and why
  */
function Class::my_function_name(arg variableName) {
    // do stuff
}
{% endhighlight %}

### Class Naming

{% highlight cpp %}
class ClassName {
private:
    // private variables and functions here

public:
    // public variables and functions here
};
{% endhighlight %}

### Switch Statements

{% highlight cpp %}
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
{% endhighlight %}