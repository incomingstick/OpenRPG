#!/bin/bash
cwd=$(pwd)

buildVars=''
makeFlags='-s'

# TODO print a help output for this script.
# This should not have to adhear to our (the GNU, really) help output standards
# as the only people really ever running this script are devs
if [[ $1 == "help" || $1 == "-h" ]]; then
    echo "This option is not yet supported: $1"
    exit 1

#    echo    "openrpg " VERSION " - " COPYRIGHT "\n"
#            "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
#            "This is free software: you are free to change and redistribute it.\n"
#            "There is NO WARRANTY, to the extent permitted by law.\n\n"
#            "Usage: sh build.sh\n"
#                "\t-h help                   Print this help screen.\n"
#                "\t   nuke | clean           Delete the dist/ and node_modules/ folders, if they exist"
#                "\t   release | install      Adds a release flag to the CMake build variables"
#                "\t   uninstall              "
#            "\n"
#            "Long options may not be passed with a single dash.\n"
#            "OpenRPG home page: <https://openrpg.io>\n"
#            "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
#            "See 'man openrpg' for more information [TODO add man pages].\n",
fi

# TODO finish this logics
if [[ ($1 == "nuke" || $1 == "clean" || $1 == "rebuild" || $1 == "install" || $2 == "install") && -d "$cwd/build" ]]; then
    rm -rfv $cwd/build
    rm -rfv $cwd/include/**/exports/
    rm -fv  $cwd/include/core/config.h

    if [[ $1 == "nuke" && -d "$cwd/dist" ]]; then
        echo "Warning, if you continue this will nuke the dist/ and node_modules/ folders, which do not need to be cleaned often!"
        read -e -p "Continue (y/N)? " confirm
        if [[ $confirm == "y" || $confirm == "yes" ]]; then
            rm -rfv $cwd/dist
            rm -rfv $cwd/node_modules
        fi
    fi
fi

if [[ $1 == "clean" || $1 == "nuke" ]]; then
    echo "exiting..."
    exit 0
fi

if [[ $1 == "release" || $2 == "release" || $1 == "install" || $2 == "install" ]]; then
    buildVars="$buildVars -DCMAKE_BUILD_TYPE=RELEASE"
fi

if [[ $OSTYPE == "linux"* || $OSTYPE == "darwin"*  ||  $OSTYPE == "cygwin" ]]; then
    if hash cmake 2>/dev/null; then
        if hash make 2>/dev/null; then
            if [ ! -d "$cwd/build" ]; then
                mkdir "$cwd/build"
            fi

            pushd $cwd/build/

            # Should we rebuild and then install, or install
            # using the last build on the system?
            if [[ $1 == "uninstall" || $2 == "uninstall" ]]; then
                sudo make uninstall
                popd
                
                exit 0
            fi

            # TODO we should check the arch we are building for?
            
            if [[ ! -a "Makefile" ]]; then
                cmake  $buildVars  ..
            fi

            # Should we rebuild and then install, or install
            # using the last build on the system?
            if [[ $1 == "check" || $2 == "check" || $1 == "install" || $2 == "install" ]]; then
                make $makeFlags check
                
                if [[ $1 == "install" || $2 == "install" ]]; then
                    sudo make $makeFlags install
                fi
                
                popd

                exit 0
            fi

            if [[ $1 == "package" || $2 == "package" ]]; then
                make $makeFlags package
            else
                make $makeFlags
            fi

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
