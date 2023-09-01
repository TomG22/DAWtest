#include "Windows.h"

#pragma once

class input {

private:
	void printKeyboardOutput();
	void printNoteColor(int* config, int configLength, int keyIndex);
	void keyboardConfig(int* conifg, int configLength);
public:
	input();
};