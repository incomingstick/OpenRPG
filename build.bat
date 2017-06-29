@echo off

WHERE cmake
IF %ERRORLEVEL% == 0 goto cmakeFound
IF %ERRORLEVEL% NEQ 0 goto cmakeMissing

:cmakeFound
IF exist build/ (
    pushd build

    cmake ..
    WHERE msbuild
    IF %ERRORLEVEL% == 0 goto msbuildFound
    IF %ERRORLEVEL% NEQ 0 goto msbuildMissing

    :msbuildFound
    msbuild OpenRPG.sln

    popd
    goto commonExit
)
mkdir build
goto cmakeFound

:cmakeMissing
echo cmake not found in PATH
goto commonExit

:msbuildMissing
echo msbuild not found in PATH
goto commonExit

:commonExit
echo exiting