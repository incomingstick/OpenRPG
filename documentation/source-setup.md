---
layout: docs
title: Source Setup
description: Here is how to build from source
group: documentation
---

# Building
Currently we require `flex`, `bison`, `cmake` (at least v2.8.4) and `make`

Create a build directory `$ mkdir build && cd build`  
Run cmake `$ cmake ..` **OR** Optionally run `$ cmake -DCMAKE_INSTALL_PREFIX=/desired/install/location ..`  
Run make `$ make`  
Run make check `$ make check` 

# Installing
After building run make install `$ make install`