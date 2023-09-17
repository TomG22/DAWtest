#pragma once

#include "synth.h"

class player {
private:
public:
	void updateInterface();
	void printControls();
	void printKeyboardOutput();
	void printNoteColor();
	void printNoteName();
	void processControlsInput(int key, int action);
	void processNoteInput(int key, int action);
	int* configMap;
	int configMapLength;
	int keyIndex;
	void playTone(synth synthObj);
	player();
};