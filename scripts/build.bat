@echo off
REM ====================================================
REM   CMake Build Script for Windows
REM   Usage:
REM     build.bat              -> configure + build
REM     build.bat configure    -> only configure
REM     build.bat build        -> only build
REM     build.bat clean        -> remove build directory
REM ====================================================


REM -----------------------------
REM   Define relative paths
REM -----------------------------
set PROJ_NAME=DAWTest.exe
set ROOT_DIR=%~dp0..
set BUILD_DIR=%ROOT_DIR%\build
set TOOLCHAIN_FILE=%ROOT_DIR%\toolchain.cmake
set EXECUTABLE=%BUILD_DIR%\Debug\%PROJ_NAME%


REM -----------------------------
REM   Handle arguments
REM -----------------------------
if NOT "%2"=="" (
    echo ~ Build ERROR: Provide either no arguments for a default build or one of: configure ^| build ^| clean
    goto :eof
)

if "%1"=="" (
    call :configure
    call :build
    goto :eof
)

if /i "%1"=="configure" (
    call :configure
) else if /i "%1"=="build" (
    call :build
) else if /i "%1"=="clean" (
    call :clean
) else if /i "%1"=="run" (
    call :run
) else (
    echo ~ Build ERROR: Unrecognized argument: "%1"
    echo   Valid options: configure ^| build ^| clean
)

goto :eof


REM ====================================================
REM   CMake configuration step
REM   - Creates the build directory if it doesn't exist
REM   - Runs CMake to configure the project
REM ====================================================
:configure
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)
cmake -S "%ROOT_DIR%" -B "%BUILD_DIR%" -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%"
goto :eof


REM ====================================================
REM   CMake build step
REM   - Builds the project from the configured files
REM ====================================================
:build
cmake --build "%BUILD_DIR%"
if not exist "%EXECUTABLE%" (
    echo ~ Build ERROR: Executable not found at "%EXECUTABLE%"
    goto :eof
)
goto :eof


REM ====================================================
REM   Clean step
REM   - Deletes the entire build directory and contents
REM ====================================================
:clean
rmdir /s /q "%BUILD_DIR%"
goto :eof


REM ====================================================
REM   Run step
REM   - Runs the built executable if it exists
REM ====================================================
:run
if not exist "%EXECUTABLE%" (
    echo ~ Run ERROR: Executable not found at "%EXECUTABLE%"
    goto :eof
)

"%EXECUTABLE%"
goto :eof
