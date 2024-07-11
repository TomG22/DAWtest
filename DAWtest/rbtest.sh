TEST_FILE_NAME="RingBufferTest"
cd engines/AudioEngine/tests

# Delete the old file
rm -f build/$TEST_FILE_NAME.exe

# Build the executable
c++ -o build/$TEST_FILE_NAME.exe $TEST_FILE_NAME.cpp -I ../include ../src/RingBuffer.cpp

# Run the program if it exists
cd build
if [ -f $TEST_FILE_NAME.exe ]; then
	echo ' ~ Running "'$TEST_FILE_NAME'.exe"...'
	./$TEST_FILE_NAME.exe
else
	echo ' ~ FILE ERROR: Could not locate file: '$TEST_FILE_NAME
fi

# Exit terminal on key press
echo " ~ Press any key to exit"
while [ true ] ; do
	read -t 3 -n 1
if [ $? = 0 ] ; then
	exit ;
fi
done
