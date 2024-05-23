#pragma once
#include "synth.h"
#include <iostream>
#include <thread>

class Player {
private:
public:
	//std::thread playerThread;
	Synth* synthPtr;

	struct note {
		std::string soundName;
		bool isplaying = false;
		bool stopping = false;
		bool stopped = false;
	};

	Player();
	void updateInterface();
	void processControlsInput(int key, int action);
	void processNoteInput(int key, int action);
	int* configMap;
	int configMapLength;
	int keyIndex;
	void playTone();
};