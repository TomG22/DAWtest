#include "PaStreamHandler.h"
#include <stdio.h>
#include <math.h>
#include <thread>

#define NUM_SECONDS   (1)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER (1048)

#define PI (3.14159265)

PaStreamHandler::PaStreamHandler() : paInitResult(Pa_Initialize()) {
    if (paInitResult != 0) {
        printf("ERROR: Stream iniitalization failed");
    } else if (!paOpenStream(Pa_GetDefaultOutputDevice())){
            printf("ERROR: Failed to open stream");
    } else {
        fillSampleSoundData();
    }
}

PaStreamHandler::~PaStreamHandler() {
    if (paInitResult == paNoError) {
        paCloseStream();
        Pa_Terminate();
    }
}

void PaStreamHandler::play() {
    PaError result = Pa_IsStreamActive(stream);
    // If a stream is not active, start a stream worker on a new thread
    if (result == 0) {
        paStreamHandlerThread = std::thread(&PaStreamHandler::startStreamWorker, this);
    } else if (result < 0) {
        printf("ERROR: Failed to check if stream is active");
    }
}

void PaStreamHandler::startStreamWorker() {
    paStartStream();
    phase = 0;
    cb = 0;
    while (Pa_IsStreamActive(stream)) {
        // Stream is running, do nothing
    }
    paStopStream();
    paStreamHandlerThread.detach();
    //printf("cb count: %d\n", cb);
    //printf("phase: %d\n", phase);
}

void PaStreamHandler::fillSampleSoundData() {
    for (int time = 0; time < tableSize; time++) {
        double frameValue = sin((double)time / tableSize * 2.0 * PI * frequency) * velocity / 100;
        double durationValue = tableSize * duration;
        double attackValue = attack * durationValue;
        double decayValue = decay * durationValue;
        double releaseValue = release * durationValue;
        double envelopeValue = 0;

        if (0 <= time && time <= attackValue) {
            envelopeValue = time / attackValue;
        } else if (attackValue <= time && time <= attackValue + decayValue) {
            envelopeValue = ((sustain - 1) / decayValue) * (time - (attackValue + decayValue)) + sustain;
        } else if (attackValue + decayValue <= time && time <= attackValue + decayValue + releaseValue) {
            envelopeValue = -(sustain / releaseValue) * (time - (attackValue + decayValue + releaseValue));
        }

        sampleSoundData[time] = frameValue * envelopeValue;
    }
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
    return ((PaStreamHandler*)userData)->PaStreamHandler::paCallbackMethod(
        inputBuffer,
        outputBuffer,
        framesPerBuffer,
        timeInfo,
        statusFlags,
        userData);
}

int PaStreamHandler::paCallbackMethod(
    const void *inputBuffer,
    void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    float* out = (float*)outputBuffer;

    // Prevent unused variable warnings
    (void) timeInfo;
    (void) statusFlags;
    (void) inputBuffer;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        // Write the values to the output buffer for both channels
        *out++ = sampleSoundData[phase];  // Left channel
        *out++ = sampleSoundData[phase];    // Right channel
        phase++;
        if (phase >= 44100) {
            return paComplete;
        }
    }
    cb++;
    printf("paStreamHandler thread id: %d\n", std::this_thread::get_id());
    return paContinue;
}

bool PaStreamHandler::paOpenStream(PaDeviceIndex index) {
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
        SAMPLE_RATE,
        paFramesPerBufferUnspecified,
        paClipOff,                      // we won't output out of range samples so don't bother clipping them
        &paCallback,
        this);                          // Using 'this' for userData so we can cast to PaStreamHandler* in paCallback method

    if (err != paNoError) {
        printf("ERROR: Failed to open stream to device");
        return false;
    }

    err = Pa_SetStreamFinishedCallback(stream, &paStreamFinished);

    if (err != paNoError) {
        printf("ERROR: Failed to set the stream finished callback");
        Pa_CloseStream( stream );
        stream = 0;
        return false;
    }

    return true;
}

bool PaStreamHandler::paCloseStream() {
    if (stream == 0)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = 0;

    return (err == paNoError);
}


PaError PaStreamHandler::paStartStream() {
    //printf("Starting new stream...\n");
    PaError err = Pa_StartStream(stream);

    return err;
}

bool PaStreamHandler::paStopStream() {
    if (stream == 0)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

void PaStreamHandler::paStreamFinished(void* userData) {
    printf("Stream finished running\n");
}

