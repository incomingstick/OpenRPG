---
layout: docs
title: Source Setup
description: Here is how to build from source
group: documentation
---

# Building
Currently we require `cmake` (at least v2.8.4) and `make`

## Build script
**Linux:** run build.sh `$ ./build.sh`

## Manual build
Create a build directory `$ mkdir build && cd build`  
Run cmake `$ cmake ..` **OR** Optionally run `$ cmake -DCMAKE_INSTALL_PREFIX=/desired/install/location ..`  
Run make `$ make`  

# Check Integrity of build
Run make check `$ make check` 

# Installing
After building run make install `$ make install`