#!/bin/bash

PROJ_NAME="DAWtest"
rm -rf build/*
cmd.exe /C "_build.bat"
buildResult=$?
echo $buildResult

# Run the program if it exists
if [ $buildResult -eq 0 ]; then
	echo " ~ Running $PROJ_NAME"
    cmd.exe /C ".\build\\$PROJ_NAME.exe"
fi
