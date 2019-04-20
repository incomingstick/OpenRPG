#!/bin/bash

cwd=$(pwd)

#TODO print a help output for this script.
# This should not have to adhear to our help output standards
# as the only people really ever running this script are devs
if [[ $1 == "help" || $1 == "h" ]]; then
    echo "This option is not yet supported: $1"
    exit 0
fi

if [[ $1 == "clean" || $1 == "rebuild" && -d "$cwd/build" ]]; then
    rm -rfv "$cwd/build"

    if [[ $1 == "clean" ]]; then
        exit 0
    fi
fi

#TODO add install command line option
# Should we rebuild and then install, or install
# using the last build on the system?
if [[ $1 == "install" || $2 == "install" ]]; then
    echo "This option is not yet supported: $2"
    exit 0
fi

if [[ $OSTYPE == "linux"* || $OSTYPE == "darwin"*  ||  $OSTYPE == "cygwin" ]]; then
    if hash cmake 2>/dev/null; then
        if hash make 2>/dev/null; then
            if [ ! -d "$cwd/build" ]; then
                mkdir "$cwd/build"
            fi

            pushd $cwd/build/

            #TODO we should check the arch we are building for?
            
            if [[ ! -a "Makefile" ]]; then
                cmake ..
            fi

            make
            popd

            exit 0
        else
            echo "MAKE NOT INSTALLED, ABORTING..."
            exit 1
        fi
    else
        echo "CMAKE NOT INSTALLED, ABORTING..."
        exit 1
    fi
else
    echo "UNSUPORTED PLATFORM $OSTYPE"
    exit 1
fi
