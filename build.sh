#!/bin/bash

cwd=$(pwd)

if [[ $OSTYPE == "linux"* || $OSTYPE == "darwin"*  ||  $OSTYPE == "cygwin" ]]; then
    if hash cmake 2>/dev/null; then
        if hash make 2>/dev/null; then
            if [ ! -d "$cwd/build" ]; then
                mkdir "$cwd/build"
            fi

            pushd $cwd/build/

            #TODO should we check the arch we are building for?
            
            if [[ ! -a "Makefile" ]]; then
                cmake ..
            fi

            make
            popd  
        else
            echo "MAKE NOT INSTALLED, ABORTING..."
        fi
    else
        echo "CMAKE NOT INSTALLED, ABORTING..."
    fi
else
    echo "UNSUPORTED PLATFORM $OSTYPE"
fi
