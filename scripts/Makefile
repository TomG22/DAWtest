PROJ_NAME := DAWTest
EXECUTABLE := ../build/Debug/$(PROJ_NAME).exe


### User-facing target ###
build:
	cmd.exe /C "build.bat build"


### Rebuild from scratch ###
rebuild:
	cmd.exe /C "build.bat clean"
	cmd.exe /C "build.bat configure"
	cmd.exe /C "build.bat build"


### Clean ###
clean:
	cmd.exe /C "build.bat clean"


### Run executable ###
run: $(EXECUTABLE)
	cmd.exe /C "build.bat run"


.PHONY: build rebuild clean run

