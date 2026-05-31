#!/bin/bash

PROJ_NAME="DAWtest"

cmd.exe /C "buildWinHelper.bat"
buildResult=$?

[ $buildResult -eq 0 ] && exit 0    # exit with no error
exit 1                              # exit with build error
