#include "SynthSound.h"
#include <cmath>
#include <iostream>

SynthSound::SynthSound(Oscillator::OscillatorType type, double time) : Sound(Sound::SoundType::synth, time), baseOscillator(type) {

}

Oscillator* SynthSound::getBaseOscillator() {
	return &baseOscillator;
}