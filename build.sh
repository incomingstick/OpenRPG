#!/bin/bash

cwd=$(pwd)

if [[ $OSTYPE == "linux"* ]]; then
    if [ ! -d "$cwd/build" ]; then
        mkdir "$cwd/build"
    fi

    cd $cwd/build/
    cmake ..
    make
else
    echo "UNSUPORTED PLATFORM $OSTYPE"
    exit
fi