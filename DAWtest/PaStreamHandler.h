/**
 * This class handles PortAudio stream methods and the 
 * implements the callback method.
 * @author Tom G
 */

#pragma once

#include <iostream>
#include "portaudio.h"
#include <mutex>
#include <thread>

class PaStreamHandler {
public:
    PaStream* stream = NULL;
    PaError paInitResult;
    std::thread paStreamHandlerThread;
    //std::mutex mutex;

    int phase = 0;
    int cb = 0;
    char message[20];

    static const int sampleRate = 44100; // 44.1 kHz sampling frequency
    static const int maxAmplitude = 32767;
    static const int tableSize = 44100;
    float sampleSoundData[tableSize];

    double amplitude = 5000;
    int velocity = 100; // Percent of amplitude
    double duration = 1.0;
    double attack = .001;
    double decay = .3;
    double sustain = 0.001;
    double release = 0.001;
    double frequency = 440.0;
    int octave = 4;
    bool pedal = false;

    /**
     * Constructor for the handler class
     * Initializes the PortAudio runtime
     */
    PaStreamHandler();

    /**
     * Destructor for  the handler class
     * Cleans up the PortAudio runtime 
     */
    ~PaStreamHandler();

    /**
     * Fills the sampleSoundData array with sound test data
     */
    void fillSampleSoundData();

    /**
     * Calls the PortAudio stream worker process in a new thread
     */
    void play();

    /**
     * Starts the PortAudio stream
     */
    void startStreamWorker();
    
    /**
     * The instance callback, where we have access to every method/variable in object of class Sine
     */
    int paCallbackMethod(const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);
    
    /**
     * Opens the PortAudio stream
     */
    bool paOpenStream(PaDeviceIndex index);
    
    /**
     * Closes or pauses the PortAudio stream
     */
    bool paCloseStream();
    
    /**
     * Starts the PortAudio stream
     */
    PaError paStartStream();

    /**
     * Stops the PortAudio stream
     */
    bool paStopStream();

    /**
     * This is called by portaudio when playback is done
     */
    static void paStreamFinished(void* userData);
    
};