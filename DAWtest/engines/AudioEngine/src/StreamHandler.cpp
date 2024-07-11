#include "StreamHandler.h"
#include <stdio.h>
#include <math.h>

StreamHandler::StreamHandler(Device& device) {
    this->device = device;
    paInitResult = Pa_Initialize();
    if (paInitResult != 0) {
        printf("PaStream ERROR: Stream initialization failed\n");
    } else if (!paOpenStream(Pa_GetDefaultOutputDevice())){
        printf("PaStream ERROR: Failed to open stream\n");
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
        soundMap.insert({sound->getId(), sound});
        printf("Added a new sound to the map\n");
        printf("Map isn't empty state: %d\n", !soundMap.empty());
    } else {
        printf("WARNING: Tried to stream a null sound reference\n");
    }
}

void StreamHandler::streamSounds() {
    PaError result = Pa_IsStreamActive(stream);
    // If a stream is not active, start a stream worker on a new thread
    if (result == 0) {
        paStartStream();

        //std::thread streamHandlerThread = std::thread(&StreamHandler::startPaStreamWorker, this);
        //streamHandlerThread.detach();
    } else if (result < 0) {

        printf("PaStream ERROR: Failed to check if stream is active\n");
    }
}

void StreamHandler::startPaStreamWorker() {
    //phase = 0;
    //cb = 0;
    paStartStream();
    printf("before loop - Map isn't empty state: %d\n", !soundMap.empty());
    printf("stream is active: %d\n", streamIsActive);
    while (!soundMap.empty()) {
        //printf("..\n");
        //printf("mid loop - Map isn't empty state: %d\n", !soundMap.empty());
    }
    printf("The worker loop stopped\n");
    paStopStream();
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

    // Hazard check for myself when testing
    if (framesPerBuffer != FRAMES_PER_BUFFER) {
        printf("WARNING: Amount of frames per buffer is not 1024 in callback function\n");
        printf("fpb: %d", framesPerBuffer);
    }

    float* out = (float*)outputBuffer;

    // Prevent unused variable warnings
    (void) timeInfo;
    (void) statusFlags;
    (void) inputBuffer;

    streamIsActive = false;
    auto iter = soundMap.begin();
    //printf("Callback method is running once\n");

    while (iter != soundMap.end()) {
        //printf("Found sounds in the map, starting loop...\n");
        if (iter->second->isPlaying()) {
            if (!iter->second->isGenerated()) {
                streamIsActive = true;

                int framesNeeded = FRAMES_PER_BUFFER;
                unsigned long framesLeft = iter->second->getFrameCount() - iter->second->getFramesGenerated();

                if (framesLeft < FRAMES_PER_BUFFER) {
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
                for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
                    if (i < framesNeeded) {
                        /*float frameValue = static_cast<float>(
                                               (iter->second->getFrameCount() - (iter->second->getFramesGenerated() + i)) *
                                               sin(((i + static_cast<double>(iter->second->getFramesGenerated())) / device.getSampleRate()) *
                                               2 * 3.1459 * 440));*/

                        float amplitude = static_cast<float>(1 - ((static_cast<double>(iter->second->getFramesGenerated()) + i)/iter->second->getFrameCount()));


                        float frameValue = amplitude * static_cast<float>(sin((i + static_cast<double>(iter->second->getFramesGenerated())) / device.getSampleRate() * 2 * 3.1459 * 440));
                        //printf("amp: %f\n", amplitude);
                        //printf("fv: %f\n", frameValue);
                        *out++ = frameValue;
                        *out++ = frameValue;

                    } else {
                        *out++ = 0;
                        *out++ = 0;
                    }
                }
                iter->second->genFrames(framesNeeded);

                //printf("fg: %d\n", fi);
                ++iter;
            } else {
                printf("removed a sound from queue\n");
            // Remove the sound from the map if it's done generating
                iter->second->stop();
                iter = soundMap.erase(iter);
            }
        }
    }


    if (streamIsActive) {
        return paContinue;
    } else {
        return paComplete;
    }

    //cb++;
    //printf("streamHandler thread id: %d\n", std::this_thread::get_id());
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
        Pa_CloseStream( stream );
        stream = 0;
        return false;
    }

    return true;
}
bool StreamHandler::paCloseStream() {
    if (stream == 0)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = 0;

    return (err == paNoError);
}


PaError StreamHandler::paStartStream() {
    //printf("Starting new stream...\n");
    streamIsActive = true;
    PaError err = Pa_StartStream(stream);

    return err;
}

bool StreamHandler::paStopStream() {
    if (stream == 0)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

void StreamHandler::paStreamFinished(void* userData) {
    printf("Stream finished running\n");
}