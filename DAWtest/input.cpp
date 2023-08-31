#include "input.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// 18 key config: white: A -> ', black: W -> P | white: 29 -> 39, black: 16 -> 24
// 24 Key config: white: tab -> \, black: 1 -> backspace | white: 14 -> 27, black: 1 -> 13

// master key array and have maps (using index math) as configs | also: windows keyboard layout; 36 norm, 17 special chars
string keyNames[] = {
	"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "Backspace",
	"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "\\",
	"Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Right Shift",
	"Left Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Right Shift" };

int keyCodes[] = {
	VK_OEM_3, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, VK_OEM_MINUS, VK_OEM_PLUS, VK_BACK,
	VK_TAB, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59, 0x55, 0x49, 0x4F, 0x50, VK_OEM_4, VK_OEM_6, VK_OEM_5,
	VK_CAPITAL, 0x41, 0x53, 0x44, 0x46, 0x47, 0x48, 0x4A, 0x4B, 0x4C, VK_OEM_1, VK_OEM_2, VK_RSHIFT,
	VK_LSHIFT, 0x5A, 0x58, 0x43, 0x56, 0x42, 0x4E, 0x4D, VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_2, VK_RSHIFT };


int miniConfig[] = {29, 39, 16, 24};
int largeConfig[] = {14, 27, 1, 13};

input::input() {
	while (true) {
		playTones(largeConfig);
	}
}

int lastPressed = 0;
void input::playTones(int* config) {
	for (int i = config[2]; i <= config[1]; i++) {
		if (GetAsyncKeyState(keyCodes[i])) {
			if (lastPressed != i) { // optional bool to prevent flickering
				lastPressed = i;
				system("cls");
				if (i >= config[0] && i <= config[1]) {
					cout << "white key";
				}
				else if (i >= config[2] && i <= config[3]) {
					cout << "black key";
				}
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