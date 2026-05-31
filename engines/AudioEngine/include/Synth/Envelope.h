#pragma once

/**
 * Class description...
 */

#include "EasingMath.h"
#include <stdint.h>

class Envelope {
public:

    /**
     * Constructor for Envelope class
     */
    Envelope();

private:
    unsigned long   attackSamples = 0;
    uint8_t         attackLevel = 0;
    EasingMath::EasingStyle     attackEasingStyle = EasingMath::EasingStyle::linear;

    bool            hasAttack2 = false;
    unsigned long   attack2Samples = 0;
    EasingMath::EasingStyle     attack2EasingStyle = EasingMath::EasingStyle::linear;

    unsigned long   decaySamples = 0;
    EasingMath::EasingStyle     decayEasingStyle = EasingMath::EasingStyle::linear;

    uint8_t         sustainLevel = 0;

    unsigned long   releaseSamples = 0;
    uint8_t         releaseLevel = 0;
    EasingMath::EasingStyle     releaseEasingStyle = EasingMath::EasingStyle::linear;

    bool            hasRelease2 = false;
    unsigned long   release2Samples = 0;
    EasingMath::EasingStyle     release2EasingStyle = EasingMath::EasingStyle::linear;
};
