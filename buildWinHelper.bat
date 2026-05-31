@echo off

:: Configure for cross compilation from Linux -> Windows
cmake -S . -B build -G "MinGW Makefiles"

:: Build with the preset configuration
cmake --build build
