#pragma once
#include <fstream>
#include <iostream>
#include "portaudio.h"


class synth {
public:


	static const int sampleRate = 44100; // 44.1 kHz sampling frequency
	static const int maxAmplitude = 32767;

	int paCallbackMethod();
	bool open(PaDeviceIndex index);
	void play();
	bool close();
	bool start();
	bool stop();
	synth();
	double amplitude = 5000;
	int velocity = 100; // Percent of max amplitude
	double frequency = 441;
	double duration = 2;
	double attack = .001;
	double decay = .3;
	double sustain = 0.001;
	double release = 0.001;
	int octave = 3;
	bool pedal = false;
};