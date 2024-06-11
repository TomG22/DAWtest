# Configure CMake
cmake -S . -B build -G "MinGW Makefiles"
PROJ_NAME="DAWtest"

# Delete the old file
rm -f build/$PROJ_NAME.exe

# Build
cd build ; mingw32-make

# Run the program if it exists
if [ -f $PROJ_NAME.exe ]; then
	echo ' ~ Running "'$PROJ_NAME'.exe"...'
	start $PROJ_NAME.exe
else
	echo ' ~ FILE ERROR: Could not locate file: '$PROJ_NAME
fi

# Exit terminal on key press
echo " ~ Press any key to exit"
while [ true ] ; do
read -t 3 -n 1
if [ $? = 0 ] ; then
exit ;
fi
done
