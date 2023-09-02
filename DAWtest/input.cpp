#include "input.h"
#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

// 18 key config: white: A -> ', black: W -> P | white: 29 -> 39, black: 16 -> 24
// 24 Key config: white: tab -> \, black: 1 -> backspace | white: 14 -> 27, black: 1 -> 13

// master key array with maps (using indices) as configs;...
// consider merging master key to be alternating upper/lower rows for index abstraction
string keyNames[] = {
	"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "Backspace",
	"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "\\",
	"Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Right Shift",
	"Left Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Right Shift" };

int keyCodes[] = {
	VK_OEM_3, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, VK_OEM_MINUS, VK_OEM_PLUS, VK_BACK,
	VK_TAB, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59, 0x55, 0x49, 0x4F, 0x50, VK_OEM_4, VK_OEM_6, VK_OEM_5,
	VK_CAPITAL, 0x41, 0x53, 0x44, 0x46, 0x47, 0x48, 0x4A, 0x4B, 0x4C, VK_OEM_1, VK_OEM_7, VK_RSHIFT,
	VK_LSHIFT, 0x5A, 0x58, 0x43, 0x56, 0x42, 0x4E, 0x4D, VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_2, VK_RSHIFT };

//	   16    17       19    20    21 -     23    24
//	29 16 30 17 31 32 19 33 20 34 21 35 36 23 37 24 38 39
int miniConfigNotes[] = { 29, 16, 30, 17, 31, 32, 19, 33, 20, 34, 21, 35, 36, 23, 37, 24, 38, 39 };
int largeConfigNotes[] = { 14, 1, 15, 2, 16, 17, 4, 18, 5, 19, 6, 20, 21, 8, 22, 9, 23, 24, 11, 25, 12, 26, 13, 27 };


 
input::input() {
	player hi;
	while (true) {
		keyboardConfig(largeConfigNotes, sizeof(largeConfigNotes) / sizeof(largeConfigNotes[0]));
		// keyboardConfig(miniConfigNotes, sizeof(miniConfigNotes) / sizeof(miniConfigNotes[0]));
	}
}

void input::printNoteColor(int* config, int configLength, int keyIndex) {
	cout << "note color: ";
	if (config[keyIndex] >= config[0] && config[keyIndex] <= config[configLength - 1]) {
		cout << "white\n";
	} else if (config[keyIndex] >= config[1] && config[keyIndex] <= config[configLength - 2]) {
		cout << "black\n";
	} else {
		cout << "undefined\n";
	}
}

void input::printNoteName(int* config, int configLength, int keyIndex, int octave) {
	char noteNames[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B'};
	int whiteNoteIndex = config[keyIndex] - config[0];
	int blackNoteIndex = config[keyIndex] - config[1];
	if (config[keyIndex] >= config[0] && config[keyIndex] <= config[configLength - 1]) {
		cout << "note: " << noteNames[(whiteNoteIndex % 7)] << octave << endl;
	} else if (config[keyIndex] >= config[1] && config[keyIndex] <= config[configLength - 2]) {
		cout << "note: " << noteNames[(blackNoteIndex % 7)] << '#' << octave << '/' << noteNames[(blackNoteIndex + 1) % 7] << 'b' << octave << endl;
	}
	// '#', 'b' 
}

int lastPressed = 0;
void input::keyboardConfig(int* config, int configLength) { 
	for (int i = 0; i < configLength; i++) {
		if (GetAsyncKeyState(keyCodes[config[i]])) {
			if (lastPressed != i) { // optional bool to prevent console flickering
				lastPressed = i;
				system("cls");
				printNoteName(config, configLength, i, 3);
				printNoteColor(config, configLength, i);
				
				player hi;

				double frequency = 130.81278265 * pow(double(2), double(i / 12.0));
				hi.playFrequency(frequency);
				
				
			}
		}
	}
}

void input::printKeyboardOutput() {
	for (int i = 0; i < sizeof(keyCodes) / sizeof(keyCodes[i]); i++) {
		if (GetAsyncKeyState(keyCodes[i]))
			cout << keyNames[i];
	}
}