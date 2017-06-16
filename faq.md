---
layout: default
title: FAQ
description: Got questions? Maybe we answered them!
group: faq
---
<h1>{{ page.title }}</h1>
<p class="lead">
    {{ page.description }}
</p>

# Contents

* Will be replaced with the ToC, excluding the "Contents" header
{:toc}

# What OS's (Operating System's) are supported?

Currently development and testing is mainly run on Linux systems, however our goal is to be able to build, install, and run on all major OS's including Windows, macOS, and Linux. We are currently seeking contributers for all platforms!

# How can I download OpenRPG?

Visit our downloads page [here](/download/)

# What do the OpenRPG version numbers mean?

The scheme is `x.y.z` (Major.Patch.Hotfix), where `x` is incremented only for massive changes, such as a reorganization of modules, support for new games or versions of games, or any other major changes, `y` is incremented whenever a new module is added or a patch is released, and `z` is incremented for maintenance releases such as hotfixes. `y` and `z` are reset to 0 if the value to the left changes.

# What is a module?

OpenRPG is built on the basic concept of modules, also know as libraries. At its core, a module is a collection of related features to accomplish an and goal, such as a doing math with dice, or creating a character.

# Is there any assurance OpenRPG or specific modules actually work as claimed?

No. The review process will hopefully eliminate the most seriously flawed modules, but a well constructed module with hidden defects is likely to slip through. Encouraging ordinary users to report their experience with a module is intended to address such concerns. Consult the test results for an indication of how well a modules works on specific platforms.

# How can the OpenRPG library be used successfully for important projects?

Many of the OpenRPG modules are actively maintained and improved, so backward compatibility with a prior version isn't always possible. Deal with this by freezing the version of the OpenRPG libraries used by your project. Only upgrade at points in your project's life cycle where a bit of change will not cause problems. Individual bug fixes can always be obtained from the OpenRPG repository, [here]({{ site.repo }}).

# How can I contribute to development?

Any one is able to contribute. Just visit our [contributing](/contributing/) page! If you have any questions join us in our discord channel [here]({{ site.chat }}).

# Must full source code be provided?

Yes, this is Free and Open Source Software!

# What is FOSS (Free and Open Source Software)?

FOSS programs are those that have licenses that allow users to freely run the program for any purpose, modify the program as they want, and also to freely distribute copies of either the original version or their own modified version.

# Are platform specific libraries acceptable?

No. OpenRPG aims to be completely cross platform. We attempt to do as much "in source" as we can to maintain this compatability. If there is a faster way to do something on a specific platform then we will do our best to utilize that functionality, but we must also provide a way to do this on other platforms as well.

# What license or licenses does OpenRPG use?

The software is licenses under the OpenRPG Licenses, which is essentially a reskin of the Boost License.
The Intellectual Property of derived content is covered under the Open Gaming License, which is owned by Wizards of the Coast.

Please see our [licensing](/about/license/) for specific details.

# Who owns OpenRPG?

No one! Because OpenRPG is Open Source anyone has the right to use or distribute this software. We do run in to some complication when it comes to content owned by Wizards of the Coast, Paizo, or other Culture Gaming Companies. To keep things simple, OpenRPG retains the right to the source code itself, whereas the Culture Gaming Companies own the right to their Intellectual Properties.

Please see our [licensing](/about/license/) for specific details.

# Is the web site a commercial business?

Absolutely not!  It is just some people getting together as a kind of cyberspace civic association. If it ever needs to incorporate, it would be as a non-profit organization.

# Does the site include material beyond module documentation?

Yes. Well.. sort of. OpenRPG is still in very active development, and has not even seen an initial release yet. We would like to see this website include information about how to use the modules, and even a web front end for the installable GUI!