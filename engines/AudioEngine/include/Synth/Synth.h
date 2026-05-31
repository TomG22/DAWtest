#pragma once

/**
 * Description...
 * @author Tom G
 */

#include "SynthSound.h"
#include "SampleSound.h"
#include <stdint.h>

class Synth {
public:
    /**
     * Constructor for Synth class
     */
    Synth();

    /**
     * 
     */
    void soundStreamWorker();

    /**
     * 
     */
	void genFrames(SynthSound* sound, float* destination, int frames);

    /**
     * 
     */
    void genFrames(SampleSound* sound, float* destination, int frames);

private:
    uint8_t volume = 100;     // Percent of max amplitude
    static const int maxAmplitude = 32767;  // Expecting the Sound class to provide this info for post-implementation of the device system
};