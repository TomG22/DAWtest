#!/bin/bash

# Configure CMake
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo -G "MinGW Makefiles"
PROJ_NAME="DAWtest"

# Delete the old fileS
rm -f build/$PROJ_NAME

# Build the executable
cd build ; mingw32-make

# Run the program if it exists
if [ -f $PROJ_NAME ]; then
	echo ' ~ Successfully built the '$PROJ_NAME' executable'
else
	echo ' ~ FILE ERROR: Could not locate file: '$PROJ_NAME''
fi

# Exit terminal on key press
echo " ~ Press any key to exit"
while [ true ] ; do
	read -t 3 -n 1
if [ $? = 0 ] ; then
	exit ;
fi
done