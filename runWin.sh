#!/bin/bash

PROJ_NAME="DAWtest"

./buildWin
buildResult=$?

# Run the program if it exists
if [ $buildResult -eq 0 ]; then
	echo " ~ Successfully Built $PROJ_NAME"
else
    echo " ~ ERROR: Could not build $PROJ_NAME"

	echo " ~ Running $PROJ_NAME"
    cmd.exe /C ".\build\\$PROJ_NAME.exe"
fi
