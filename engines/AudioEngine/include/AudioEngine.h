#pragma once

/**
 * Description...
 * @author Tom G
 */

#include "StreamHandler.h"

class AudioEngine {
public:
    /**
     * Constructor for AudioEngine class
     */
    AudioEngine();

    /**
     *
     */
    void playSound(Sound* sound);

private:
    Device defaultDevice;

    StreamHandler defaultStreamHandler = StreamHandler(defaultDevice);

    //std::vector<Device& device> deviceList; // (could make this an unordered_map)
};