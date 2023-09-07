#include "input.h"
#include "synth.h"
#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

// make synthobj an input class variable

// 18 key configMap: white: A -> ', black: W -> P | white: 29 -> 39, black: 16 -> 24
// 24 Key configMap: white: tab -> \, black: 1 -> backspace | white: 14 -> 27, black: 1 -> 13

// master key array with maps (using indices) as configMaps;...
// consider merging master key to be alternating upper/lower rows for index abstraction
int keyCodes[] = {
	VK_OEM_3, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, VK_OEM_MINUS, VK_OEM_PLUS, VK_BACK,
	VK_TAB, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59, 0x55, 0x49, 0x4F, 0x50, VK_OEM_4, VK_OEM_6, VK_OEM_5,
	VK_CAPITAL, 0x41, 0x53, 0x44, 0x46, 0x47, 0x48, 0x4A, 0x4B, 0x4C, VK_OEM_1, VK_OEM_7, VK_RSHIFT,
	VK_LSHIFT, 0x5A, 0x58, 0x43, 0x56, 0x42, 0x4E, 0x4D, VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_2, VK_RSHIFT };

string keyNames[] = {
	"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "Backspace",
	"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "\\",
	"Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Right Shift",
	"Left Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Right Shift" };

string controlsNames[] = { "Sustain", "Octave Down", "Octave Up", "Amplitude Down", "Amplitude Up" };

// string controlsNames[] = { "Sustain", "Octave Down", "Octave Up", "Amplitude Down", "Amplitude Up", "" };
int controlsMap[] = { 41, 42, 43, 44, 45 };

int miniConfigMap[] = { 29, 16, 30, 17, 31, 32, 19, 33, 20, 34, 21, 35, 36, 23, 37, 24, 38, 39 };
int largeConfigMap[] = { 14, 1, 15, 2, 16, 17, 4, 18, 5, 19, 6, 20, 21, 8, 22, 9, 23, 24, 11, 25, 12, 26, 13, 27 };


synth synthObj = synth();
 
input::input() {
	/*
	input::configMap = miniConfigMap;
	input::configMapLength = sizeof(miniConfigMap) / sizeof(int);
	*/

	configMap = largeConfigMap;
	configMapLength = sizeof(largeConfigMap) / sizeof(int);
	
	player playerObj;
	while (true) {
		processControlsInput();
		processNoteInput();
	}
}

void input::updateInterface() {
	system("cls");
	printKeyboardOutput();
	printNoteColor();
	printNoteName();
	printControls();
}

void input::printNoteColor() {
	cout << "note color: ";
	if (configMap[keyIndex] >= configMap[0] && configMap[keyIndex] <= configMap[configMapLength - 1]) {
		cout << "white\n";
	} else if (configMap[keyIndex] >= configMap[1] && configMap[keyIndex] <= configMap[configMapLength - 2]) {
		cout << "black\n";
	} else {
		cout << "undefined\n";
	}
}

void input::printNoteName() {
	char noteNames[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B'};
	int whiteNoteIndex = configMap[keyIndex] - configMap[0];
	int blackNoteIndex = configMap[keyIndex] - configMap[1];
	if (configMap[keyIndex] >= configMap[0] && configMap[keyIndex] <= configMap[configMapLength - 1]) {
		cout << "note: " << noteNames[(whiteNoteIndex % 7)] << synthObj.octave + ((whiteNoteIndex + 2) / 7) << endl;
	} else if (configMap[keyIndex] >= configMap[1] && configMap[keyIndex] <= configMap[configMapLength - 2]) {
		cout << "note: " << noteNames[(blackNoteIndex % 7)] << '#' << synthObj.octave + ((blackNoteIndex + 2) / 7) << '/'
			<< noteNames[(blackNoteIndex + 1) % 7] << 'b' << synthObj.octave + ((blackNoteIndex + 3) / 7) << endl;
	}
}

player playerObj;
int lastPressed = 0;
void input::processNoteInput() {
	for (int keyIndex = 0; keyIndex < configMapLength; keyIndex++) {
		if (GetAsyncKeyState(keyCodes[configMap[keyIndex]])) {
			if (lastPressed != keyIndex) { // optional bool to prevent console flickering
				lastPressed = keyIndex;
				input::keyIndex = keyIndex;
				synthObj.frequency = 130.81278265 * pow(double(2), double(keyIndex / 12.0));
				//	synthObj.attack = 0;
				//	synthObj.decay = 2;
				//	synthObj.sustain = 1;
				//	synthObj.release = 0;
				updateInterface();
				cout << "playing sound: " << synthObj.frequency << " Hz\n";
				playerObj.playTone(synthObj);
				cout << "played sound\n";
			}
		}
	}
}

void input::printKeyboardOutput() {
	cout << "key pressed: " << keyNames[configMap[keyIndex]] << endl;
}


void input::processControlsInput() {
	synthObj.octave = 3;
	for (int i = 0; i < sizeof(controlsMap) / sizeof(int); i++) {
		if (GetAsyncKeyState(keyCodes[controlsMap[i]])) {
			if (controlsNames[i] == "Sustain") {
				synthObj.pedal = 1;
			}
			if (controlsNames[i] == "Octave Down") {
				synthObj.octave -= 1;
			} else if (controlsNames[i] == "Octave Up") {
				synthObj.octave += 1;
			} else if (controlsNames[i] == "Velocity Down") {
				synthObj.velocity -= 5;
			} else if (controlsNames[i] == "Velocity Up") {
				synthObj.velocity += 5;
			}

		} else {
			if (synthObj.pedal == true) {
				// updateInterface();
			}
			synthObj.pedal = 0;
		}
	}
}

void input::printControls() {
	if (synthObj.pedal == true) {
		cout << "Sustain: On\n";
	} else {
		cout << "Sustain: Off\n";
	}
	cout << "Duration: " << synthObj.duration << endl
		<< "Octave: " << synthObj.octave << endl 
		<< "Velocity: " << synthObj.velocity << endl 
		<< "Attack: " << synthObj.attack << 
		" | Decay: " << synthObj.decay << 
		" | Sustain: " << synthObj.sustain << 
		" | Release: " << synthObj.release << endl;
}