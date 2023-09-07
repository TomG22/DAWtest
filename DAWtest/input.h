#pragma once

#include "Windows.h"
#include "synth.h"

class input {

private:
	void updateInterface();
	void processControlsInput();
	void printControls();
	void printKeyboardOutput();
	void printNoteColor();
	void printNoteName();
	void processNoteInput();
public:
	int* configMap;
	int configMapLength;
	int keyIndex;
	input();
};