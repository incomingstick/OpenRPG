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
}

built_api(){
   if hash cargo 2>/dev/null; then
        if [[ ! -a "Cargo.toml" ]]; then

              pushd $cwd/api/

              cargo build

              popd
        else
              echo "CARGO.TOML NOT FOUND..."
        fi
   else
        echo "CARGO/RUST NOT INSTALLED..."
   fi
}

if [[ $OSTYPE == "linux"* || $OSTYPE == "darwin"*  ||  $OSTYPE == "cygwin" ]] && [[ $# -eq 0 ]]; then
    build_cpp
elif [[ "$1" == "api" ]]; then
    echo "BUILDING CPP SOURCE..."
    build_cpp
    echo "FINISHED.... MOVING FILES..."
    mkdir $cwd/api/build/
    cp $cwd/build/{character-generator,name-generator,roll,openrpg} $cwd/api/build/ 
    echo "FINISHED.... BUILDING API..."
    built_api
elif [[ "$1" == "clean-api" ]]; then
    if [ -d "$cwd/api/build/" ]; then
      echo "REMOVING API/BUILD"  
      rm -r "$cwd/api/build/"
    fi
    pushd $cwd/api/
    echo "CLEANING API DIR"
    cargo clean
    echo "API CLEAN... FINISHED"
    popd
else
    echo "UNSUPORTED PLATFORM $OSTYPE"
    exit 1
fi
