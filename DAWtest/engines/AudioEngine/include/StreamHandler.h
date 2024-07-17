#pragma once

/**
 * This class handles PortAudio stream methods and 
 * implements the callback method.
 * @author Tom G
 */

#include "Device.h"
#include "Sound.h"
#include "Synth.h"
#include "portaudio.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>

class StreamHandler {
public:
    /**
     * Constructor for the StreamHandler class
     * Initializes the PortAudio runtime
     */
    StreamHandler(Device& device);

    int FRAMES_PER_BUFFER = 256;

    std::mutex soundMapMutex;
    std::unordered_map<int, Sound*>& getSoundMap();

    /**
     * 
     */
    void addSound(Sound* sound);

    /**
     * Starts or resumes a stream worker
     */
    void streamSounds();

    /**
     * Thread worker for the PortAudio stream
     */
    void startThreadWorker();
    
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
    
    /**
     * Destructor for  the handler class
     * Cleans up the PortAudio runtime 
     */
    ~StreamHandler();

private:
    Device device;

    PaError paInitResult;
    
    PaStream* stream = nullptr;
    
    bool isPlaying = false;

    Synth synth = Synth();
    std::unordered_map<int, Sound*> soundMap;

    //std::mutex mutex;

    int phase = 0;
    int cb = 0;
};