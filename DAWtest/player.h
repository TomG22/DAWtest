#pragma once
#include "synth.h"
#include <iostream>

class player {
private:
public:
	struct note {
		std::string soundName;
		bool isplaying = false;
		bool stopping = false;
		bool stopped = false;
	};

	void updateInterface();
	void processControlsInput(int key, int action);
	void processNoteInput(int key, int action);
	int* configMap;
	int configMapLength;
	int keyIndex;
	void playTone();
	player();
};