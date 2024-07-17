#include "Oscillator.h"
#include <cmath>
#include <stdio.h>

Oscillator::Oscillator(OscillatorType type) : type(type) {

}

double Oscillator::getFrequency() {
    return frequency;
}

void Oscillator::setFrequency(double newFrequency) {
    frequency = newFrequency;
}

void Oscillator::genSound(float* destination, int frameIdx, int frameCount) {
	if (type == OscillatorType::sine) {
		printf("gening sine...\n");
		genSine(destination, frameIdx, frameCount);
	} else {
		// TODO
 	}
}

void Oscillator::genSine(float* destination, int frameIdx, int frameCount) {
	printf("fi: %d\n", frameIdx);
	printf("fc: %d\n", frameCount);
	while (frameIdx < frameCount) {
		double frameValue = volume * maxAmplitude * sin((frameIdx / frameCount - phaseShift) * 2 * M_PI * frequency);
		*destination++ = frameValue;
		*destination++ = frameValue;
	}
}

void Oscillator::genSquare() {
	// TODO
}

void Oscillator::genTriangle() {
	// TODO
}

void Oscillator::genSawtooth() {
	// TODO
}