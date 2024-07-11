#pragma once

/**
 * Description...
 * @author Tom G
 */

#include "Sound.h"

class SampleSound : public Sound {
public:

    /**
     * Constructor for SampleSound class
     */
    SampleSound(float* sample, double time);
};