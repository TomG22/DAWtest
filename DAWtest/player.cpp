#include "Player.h"
#include "gui.h"
#include "synth.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std::chrono;

// ARCH V2 opt 1: Input sends int key index and key up/down data. Player takes input, maps index to keymap and handles synth file properties
// opt 2: Input handles index to keymap and only sends index of synth property with change (and maybe bool for delta vs set)


// 18 key configMap: white: A -> ', black: W -> P | white: 29 -> 39, black: 16 -> 24
// 24 Key configMap: white: tab -> \, black: 1 -> backspace | white: 14 -> 27, black: 1 -> 13

// master key array with maps (using indices) as configMaps;...
// consider merging master key to be alternating upper/lower rows for index abstraction

int glfwKeyCodes[] = {
	96, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 45, 61, 259,
	258, 81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 91, 93, 92,
	280, 65, 83, 68, 70, 71, 72, 74, 75, 76, 59, 39, 257,
	340, 90, 88, 67, 86, 66, 78, 77, 44, 46, 47, 344 };


std::string keyNamesMap[] = {
	"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "Backspace",
	"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "\\",
	"Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Right Shift",
	"Left Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Right Shift" };

std::string controlsNames[] = { "Sustain", "Octave Down", "Octave Up", "Velocity Down", "Velocity Up" };

int controlsMap[] = { 42, 43, 44, 45, 46 };

int miniConfigMap[] = { 29, 16, 30, 17, 31, 32, 19, 33, 20, 34, 21, 35, 36, 23, 37, 24, 38, 39 };
int largeConfigMap[] = { 14, 1, 15, 2, 16, 17, 4, 18, 5, 19, 6, 20, 21, 8, 22, 9, 23, 24, 11, 25, 12, 26, 13, 27 };

Player::Player() {
	configMap = largeConfigMap;
	configMapLength = sizeof(largeConfigMap) / sizeof(int);
	this->synthPtr = new Synth();
	/*
	configMap = miniConfigMap;
	configMapLength = sizeof(miniConfigMap) / sizeof(int);
	*/



	// using namespace std;
	//
	// //...cout << "playing sound\n";
	// 
	// PlaySound(TEXT("test"), NULL, SND_ASYNC);
	// double testTime = 1.0;
	// auto start = std::chrono::steady_clock::now();
	// auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// 
	// int i = 0;
	// while (deltaTime < testTime) {
	// 	//...cout << testTime - deltaTime << '\n';
	// 	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// }
	// PlaySound(TEXT("test"), NULL, SND_ASYNC);
	// //...cout << "mid\n";
	// start = std::chrono::steady_clock::now();
	// deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// 
	// while (deltaTime < testTime) {
	// 	//...cout << testTime - deltaTime << '\n';
	// 	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// }
}

void Player::playTone() {
	std::thread synthThread;
	synthThread = std::thread(&Synth::play, synthPtr);
	//synthPtr->play();

/*std::thread worker2(timerObj.function2);
  worker1.join();
  worker2.join();*/

/*timer timerObj;
  std::thread worker1(timerObj.function1);
  std::thread worker2(timerObj.function2);
  worker1.join();
  worker2.join();
*/
}

void Player::updateInterface() {
	//system("cls");

			// Keyboard Output
	//...cout << "key pressed: " << keyNamesMap[configMap[keyIndex]] << endl;

		// Note Color
	//...cout << "note color: ";
	if (configMap[keyIndex] >= configMap[0] && configMap[keyIndex] <= configMap[configMapLength - 1]) {
		//...cout << "white\n";
	}
	else if (configMap[keyIndex] >= configMap[1] && configMap[keyIndex] <= configMap[configMapLength - 2]) {
		//...cout << "black\n";
	}
	else {
		//...cout << "undefined\n";
	}


	//Note Name
	char noteNames[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' }; 
	int whiteNoteIndex = configMap[keyIndex] - configMap[0];
	int blackNoteIndex = configMap[keyIndex] - configMap[1];
	if (configMap[keyIndex] >= configMap[0] && configMap[keyIndex] <= configMap[configMapLength - 1]) {
		//...cout << "note: " << noteNames[(whiteNoteIndex % 7)] << synthPtr->octave + ((whiteNoteIndex + 2) / 7) << endl;
	}
	else if (configMap[keyIndex] >= configMap[1] && configMap[keyIndex] <= configMap[configMapLength - 2]) {
		//...cout << "note: " << noteNames[(blackNoteIndex % 7)] << '#' << synthPtr->octave + ((blackNoteIndex + 2) / 7) << '/'
		//	<< noteNames[(blackNoteIndex + 1) % 7] << 'b' << synthPtr->octave + ((blackNoteIndex + 3) / 7) << endl;
	}
		// Controls
	/*if (synthPtr->pedal == 1) {
		//...cout << "Sustain: On\n";
	}
	else {
		//...cout << "Sustain: Off\n";
	}
	...cout << "Duration: " << synthPtr->duration << endl
		<< "Frequency: " << synthPtr->frequency << " Hz\n"
		<< "Octave: " << synthPtr->octave << endl
		<< "Velocity: " << synthPtr->velocity << endl
		<< "Attack: " << synthPtr->attack <<
		" | Decay: " << synthPtr->decay <<
		" | Sustain: " << synthPtr->sustain <<
		" | Release: " << synthPtr->release << endl;*/
}

void Player::processNoteInput(int keyCode, int state) {
	for (int keyIndex = 0; keyIndex < configMapLength; keyIndex++) {
		if (state == 1 && keyCode == glfwKeyCodes[configMap[keyIndex]]) {
			this->keyIndex = keyIndex;
			// Start at C frequency since it will be the first index
			synthPtr->frequency = round(130.81278265 * pow(2.0, double((keyIndex + 12 * (synthPtr->octave - 3)) / 12.0)));

			//std::thread worker1(updateInterface, this);
			//worker1.join();
			
			//updateInterface();
			//...cout << "playing sound\n";
			playTone();
			//...cout << "played sound\n";
		}
	}
}

void Player::processControlsInput(int keyCode, int state) {
	for (int keyIndex = 0; keyIndex < sizeof(controlsMap) / sizeof(int); keyIndex++) {
		if (state == 1 && keyCode == glfwKeyCodes[controlsMap[keyIndex]]) {
			/*if (controlsNames[keyIndex] == "Sustain") {
				if (synthPtr->pedal) {
					synthPtr->pedal = 0;
				} else {
					synthPtr->pedal = 1;
				}
			}
			if (controlsNames[keyIndex] == "Octave Down") {
				synthPtr->octave -= 1;
			}
			else if (controlsNames[keyIndex] == "Octave Up") {
				synthPtr->octave += 1;
			}
			else if (synthPtr->velocity > 0 && controlsNames[keyIndex] == "Velocity Down") {
				synthPtr->velocity -= 10;
			}
			else if (controlsNames[keyIndex] == "Velocity Up") {
				synthPtr->velocity += 10;
			}
			updateInterface();
		}
		else if (state == 0 && keyCode == glfwKeyCodes[controlsMap[keyIndex]]) {
			/* Computer keyboard input is limited so hold mode takes up an extra input space.
			 * Eventually make ui for toggling between toggle and hold mode for sustain.
			if (controlsNames[keyIndex] == "Sustain") {
				synthPtr->pedal = 0;
			}	
			*/
			// updateInterface();
		}
		else {
			// key is held down
		}
	}
}
