#include "Windows.h"

#pragma once

class input {

private:
	void printKeyboardOutput();
	void printNoteColor(int* config, int configLength, int keyIndex);
	void printNoteName(int* config, int configLength, int keyIndex, int octave);
	void keyboardConfig(int* conifg, int configLength);
public:
	input();
};