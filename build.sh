#!/bin/bash

cwd=$(pwd)

if [[ $OSTYPE == "linux"* ||  $OSTYPE == "cygwin" ]]; then
    if [ ! -d "$cwd/build" ]; then
        mkdir "$cwd/build"
    fi

    pushd $cwd/build/
    cmake ..
    make
    popd
else
    echo "UNSUPORTED PLATFORM $OSTYPE"
    exit
fi
