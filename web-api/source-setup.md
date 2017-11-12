---
layout: docs
title: Source Setup
description: Here is how to build from source
group: web-api
---

# Pre-build steps

Move into api directory `$ cd api/`

Open Rocket.toml with your favorite editor.

Edit the line `address` and put your ip in quotes. (This is the IP or address which you will be able to access the api from)
    **Example**: `address = "xxx.xx.xx.xxx"`

Edit the line `workers` to the number of workers/threads you want the API to use. A single worker can NOT process 2 requests at the same time, so if you have 2 workers you could have 2 different requests being processed.

    **Example**: `workers = 4`

    **NOTE**: unless you plan to have many people accessing the api at once 1 or 2 workers would be fine.

Return to root directory `$ cd ..`

# Building

Currently we **require** `rust-nightly`

## Build script

### Linux && macOS

Run build.sh `$ ./build.sh api`

To clean the build run `$ ./build.sh clean-api`

### Windows

Windows builds are not yet supported

## Manual build

First follow build instructions for CPP sources [here]({{ site.baseurl }}/documentation/source-setup/)

Make the build directory in api/ `$ mkdir api/build/`

Move files to build directory for the api `cp build/{character-generator,name-generator,roll,openrpg} api/build/`

Move into api directory `$ cd api/`

Run cargo build `$ cargo build`

# Running

After building run cargo run `$ cargo run`
