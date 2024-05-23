#pragma once
#include <fstream>
#include <iostream>
#include "portaudio.h"

class Synth {
public:
	PaStream *stream = 0;

	int tableSize = 44100;
	float waveTable[44100];
	int left_phase = 0;
	int right_phase = 0;
	char message[20];

	static const int sampleRate = 44100; // 44.1 kHz sampling frequency
	static const int maxAmplitude = 32767;
	double amplitude = 5000;
	int velocity = 100; // Percent of max amplitude
	double duration = 2;
	double attack = .001;
	double decay = .3;
	double sustain = 0.001;
	double release = 0.001;
	double frequency = 440;
	int octave = 4;
	bool pedal = false;

	Synth();

	bool setTableValue(int key, float value);

	float getTableValue(int key);

	int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags);
	
	bool open(PaDeviceIndex index);
	
	bool close();
	
	PaError start();
	
	bool stop();

	void paStreamFinishedMethod();

	static void paStreamFinished(void* userData);


	//double getCurrentBuffer();

	//double getFrequency();
	
	void play();

	void buffer();
};