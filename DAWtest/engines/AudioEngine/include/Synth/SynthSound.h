#pragma once

/**
 * Class description...
 */

#include "Sound.h"
#include "Oscillator.h"

class SynthSound : public Sound {
public:
    /**
     * Constructor for SynthSound class
     */
    SynthSound(Oscillator::OscillatorType type, double gtime);

    /**
     * 
     */
    Oscillator* getBaseOscillator();

private:
    Oscillator baseOscillator;
};