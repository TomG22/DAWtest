#pragma once

/**
 * This class is used to store and operate on a particular sound frame
 * which is intended to be divided into chunks for streaming purposes
 * @author Tom G
 */

#include "Device.h"

class Sound {
public:
    enum SoundType {
        sample,
        synth
    };

    /**
     * Constructor for Sound class
     */
    Sound(SoundType type, double time);

    /**
     * 
     */
    int getId();

    /**
     *
     */
    unsigned long getFramesGenerated();

    /**
     *
     */
    unsigned long getFrameCount();

    /**
     *
     */
    bool getType();

    /**
     *
     */
    void genFrames(int frames);

    /**
     *
     */
    bool isGenerated();

    /**
     *
     */
    bool isPlaying();

    /**
     * 
     */
    void play();
    void play(int startFrame);

    /**
     * 
     */
    void stop();

    /**
     * 
     */
    void registerDeviceInfo(Device* device);

protected:
    SoundType soundType;

    bool playing = false;

    double time = 0.00;

    unsigned long frameCount = 0;
    unsigned long framesGenerated = 0;

    int id;
    static int nextId;

    // Support wanted for:
    // Oscillators
    // Modulators
    // Filters
    // FXs
    // Envelopes
};