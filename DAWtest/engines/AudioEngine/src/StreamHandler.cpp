#include "StreamHandler.h"
#include <stdio.h>
#include <cstring>
#include <math.h>

StreamHandler::StreamHandler(Device& device) : device(device) {
    paInitResult = Pa_Initialize();

    if (paInitResult != 0) {
        printf("PaStream ERROR: Stream initialization failed\n");
    } else if (!paOpenStream(Pa_GetDefaultOutputDevice())){
        printf("PaStream ERROR: Failed to open stream\n");
    } else {
        std::thread streamHandlerThread = std::thread(&StreamHandler::startThreadWorker, this);
        streamHandlerThread.detach();
    }
}

StreamHandler::~StreamHandler() {
    if (paInitResult == paNoError) {
        paCloseStream();
        Pa_Terminate();
    }
}

std::unordered_map<int, Sound*>& StreamHandler::getSoundMap() {
    return soundMap;
}

void StreamHandler::addSound(Sound* sound) {
    if (sound) {
        soundMapMutex.lock();
        soundMap.insert({sound->getId(), sound});
        soundMapMutex.unlock();
        printf("Added a new sound to the map\n");
        printf("Map isn't empty state: %d\n", !soundMap.empty());
    } else {
        printf("WARNING: Tried to stream a null sound reference\n");
    }
}

/*void StreamHandler::streamSounds() {
    PaError result = Pa_IsStreamActive(stream);
    // If a stream is not active, start a stream worker on a new thread
    if (result == 0) {
        std::thread streamHandlerThread = std::thread(&StreamHandler::startPaStreamWorker, this);
        streamHandlerThread.detach();
    } else if (result < 0) {

        printf("PaStream ERROR: Failed to check if stream is active\n");
    }
}*/

void StreamHandler::startThreadWorker() {
    //phase = 0;
    //cb = 0;
    //paStartStream();
    //printf("before loop - Map isn't empty state: %d\n", !soundMap.empty());
    //printf("stream is active: %d\n", isPlaying);
    //isPlaying = true;
    while (true) {
        //printf("~ Stream handler thread is running ~\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //printf("s is active: %d\n",isPlaying);
        //printf("mid loop - Map isn't empty state: %d\n", !soundMap.empty());
    }
    //printf("The worker loop stopped\n");
    //paStopStream();
    //printf("cb count: %d\n", cb);
    //printf("phase: %d\n", phase);
}

// This routine will be called by the PortAudio engine when audio is needed.
// It may called at interrupt level on some machines so don't do anything
// that could mess up the system like calling malloc() or free().
static int paCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    // Here we cast userData to a reference to our class so we can call the instance method paCallback,
    // we can do that since we called Pa_OpenStream with 'this' for userData
    return ((StreamHandler*)userData)->StreamHandler::paCallbackMethod(
        inputBuffer,
        outputBuffer,
        framesPerBuffer,
        timeInfo,
        statusFlags,
        userData);
}

int StreamHandler::paCallbackMethod(
    const void *inputBuffer,
    void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    //printf("Callback method is running once\n");

    // Hazard check for myself when testing
    if (framesPerBuffer != FRAMES_PER_BUFFER) {
        printf("WARNING: Amount of frames per buffer (%d) is inconsistent in callback function\n", framesPerBuffer);
    }

    // Prevent unused variable warnings
    (void) timeInfo;
    (void) statusFlags;
    (void) inputBuffer;
    float* out = (float*)outputBuffer;

    memset(out, 0, framesPerBuffer * 2 * sizeof(float));

    isPlaying = false;

    soundMapMutex.lock();
    auto iter = soundMap.begin();

    while (iter != soundMap.end()) {
        //printf("Found sounds in the map, starting loop...\n");
        if (iter->second->isPlaying()) {
            if (!iter->second->isGenerated()) {
                isPlaying = true;

                int framesNeeded = framesPerBuffer;
                unsigned long framesLeft = iter->second->getFrameCount() - iter->second->getFramesGenerated();

                if (framesLeft < framesPerBuffer) {
                    framesNeeded = framesLeft;
                }

                /*
                if (iter->second->getType() == Sound::SoundType::synth) {
                    printf("synth sound detected\n");
                    synth.genFrames((SynthSound*) iter->second, out, framesNeeded);
                } else if (iter->second->getType() == Sound::SoundType::sample) {
                    printf("sample sound detected\n");
                    //synth.genFrames((FrameSound*) iter->second, out, inputFrames);
                }*/

                //printf("fc: %d\n", iter->second->getFrameCount());
                //unsigned long fi = iter->second->getFramesGenerated();

                out = (float*)outputBuffer;

                SynthSound* sound = (SynthSound*)iter->second;

                for (int i = 0; i < framesNeeded; i++) {
                    float amplitude = .2 * static_cast<float>(1 - ((static_cast<double>(sound->getFramesGenerated()) + i)/sound->getFrameCount()));
                    float frameValue = *out + amplitude * static_cast<float>(sin((i + static_cast<double>(sound->getFramesGenerated())) / device.getSampleRate() * 2 * 3.1459 * sound->getBaseOscillator()->getFrequency()));

                    // Normalize frameValue if it exceeds 1.0 or -1.0
                    if (frameValue > 1.0f) {
                        frameValue = 1.0f;
                    } else if (frameValue < -1.0f) {
                        frameValue = -1.0f;
                    }

                    // Write stereo samples to outputBuffer, ensuring they do not exceed -1.0 to 1.0 range
                    *out++ = frameValue;  // Left channel
                    *out++ = frameValue;  // Right channel
                    //printf("amp: %f\n", amplitude);
                    //printf("fv: %f\n", frameValue);
                }

                iter->second->genFrames(framesNeeded);
                ++iter; 
            } else {
                //printf("removed a sound from queue\n");
                // Remove the sound from the map if it's done generating
                iter->second->stop();
                iter = soundMap.erase(iter);
            }
        } else {
            // Remove the sound if it's not playing
            iter = soundMap.erase(iter);
        }
    }
    soundMapMutex.unlock();

    return paContinue;

}

bool StreamHandler::paOpenStream(PaDeviceIndex index) {
    PaStreamParameters outputParameters;

    outputParameters.device = index;
    if (outputParameters.device == paNoDevice) {
        return false;
    }

    const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
    if (pInfo != 0) {
        //printf("Output device name: '%s'\r", pInfo->name);
    }

    outputParameters.channelCount = 2;          // stereo output
    outputParameters.sampleFormat = paFloat32;  // 32 bit floating point output
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err = Pa_OpenStream(
        &stream,
        NULL,                           // no input
        &outputParameters,
        device.getSampleRate(),
        FRAMES_PER_BUFFER,
        paClipOff,                      // we won't output out of range samples so don't bother clipping them
        &paCallback,
        this);                          // Using 'this' for userData so we can cast to StreamHandler* in paCallback method

    if (err != paNoError) {
        printf("PaStream ERROR: Failed to open stream to device\n");
        return false;
    }

    err = Pa_SetStreamFinishedCallback(stream, &paStreamFinished);

    if (err != paNoError) {
        printf("PaStream ERROR: Failed to set the stream finished callback\n");
        Pa_CloseStream(stream);
        stream = 0;
        return false;
    }

    return true;
}
bool StreamHandler::paCloseStream() {
    if (stream == 0) {
        return false;
    }

    PaError err = Pa_CloseStream(stream);
    stream = 0;

    return (err == paNoError);
}


PaError StreamHandler::paStartStream() {
    PaError err = paNoError;

    if (!Pa_IsStreamActive(stream)) {
        isPlaying = true;
        err = Pa_StartStream(stream);
        printf("Started a new stream\n");
    }
    
    return err;
}

bool StreamHandler::paStopStream() {
    printf("Stopping the stream...\n");
    if (stream == 0)  {
        return false;
    }

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

void StreamHandler::paStreamFinished(void* userData) {
    printf("Stream finished running\n");
}