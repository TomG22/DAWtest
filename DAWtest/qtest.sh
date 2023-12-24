# Configure CMake
cmake -S . -B build -G "MinGW Makefiles"
# Build
cd build ; mingw32-make
# Run Program
start ./PortAudioTest
# Keep Terminal Open
exec bash