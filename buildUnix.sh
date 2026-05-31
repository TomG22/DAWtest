#!/bin/bash

PROJ_NAME="DAWtest"
cmake -S . -B build -G "Unix Makefiles"
cmake --build build


# Run the program if it exists
if [ "build/$PROJ_NAME" ]; then
	echo " ~ Built $PROJ_NAME"
    exit 0
else
    echo " ~ Build ERROR: Could not locate executable: $PROJ_NAME"
    exit 1
fi
