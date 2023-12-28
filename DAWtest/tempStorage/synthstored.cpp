#include "synth.h"
#include <stdio.h>
#include <math.h>

#define FRAMES_PER_BUFFER  (1024)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif


PaStream *stream;

 static int paCallback( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData )
    {
        /* Here we cast userData to Sine* type so we can call the instance method paCallbackMethod, we can do that since
           we called Pa_OpenStream with 'this' for userData */
        return ((this*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
            framesPerBuffer,
            timeInfo,
            statusFlags);
    }


int paCallback( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData );


bool synth::open(PaDeviceIndex index)
{
    PaStreamParameters outputParameters;


    outputParameters.device = index;
    if (outputParameters.device == paNoDevice) {
        return false;
    }

    const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
    if (pInfo != 0)
    {
        printf("Output device name: '%s'\r", pInfo->name);
    }

        outputParameters.channelCount = 2;       /* stereo output */
        outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err = Pa_OpenStream(
        &stream,
            NULL, /* no input */
        &outputParameters,
        synth::sampleRate,
        paFramesPerBufferUnspecified,
            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
        paCallback,
            this            /* Using 'this' for userData so we can cast to Sine* in paCallback method */
        );

    if (err != paNoError)
    {
            /* Failed to open stream to device !!! */
        return false;
    }

    err = Pa_SetStreamFinishedCallback( stream, &paStreamFinished );



    if (err != paNoError)
    {
        Pa_CloseStream( stream );
        stream = 0;

        return false;
    }

    return true;
}

bool synth::close()
{
    if (stream == 0)
        return false;

    PaError err = Pa_CloseStream( stream );
    stream = 0;

    return (err == paNoError);
}


bool synth::start()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StartStream( stream );

    return (err == paNoError);
}

bool synth::stop()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StopStream( stream );

    return (err == paNoError);
}

void synth::play() {

    if (open(Pa_GetDefaultOutputDevice()))
    {
        if (start())
        {
            Pa_Sleep( duration * 1000 );

            stop();
        }

        close();
    }
}



    /* The instance callback, where we have access to every method/variable in object of class Sine */


/*
    // This routine will be called by the PortAudio engine when audio is needed.
    // It may called at interrupt level on some machines so don't do anything
    // that could mess up the system like calling malloc() or free().
    //
    static int paCallback( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData )
    {
        // Here we cast userData to Sine* type so we can call the instance method paCallbackMethod, we can do that since
        //   we called Pa_OpenStream with 'this' for userData
        return ((Sine*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
            framesPerBuffer,
            timeInfo,
            statusFlags);
    }

*/



int synth::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags)
    {
        float *out = (float*)outputBuffer;
        unsigned long i;

        (void) timeInfo; /* Prevent unused variable warnings. */
        (void) statusFlags;
        (void) inputBuffer;

        for( i=0; i<framesPerBuffer; i++ )
        {
            *out++ = sine[left_phase];  /* left */
            *out++ = sine[right_phase];  /* right */
            left_phase += 1;
            if( left_phase >= TABLE_SIZE ) left_phase -= TABLE_SIZE;
            right_phase += 1; /* higher pitch so we can distinguish left and right. */
            if( right_phase >= TABLE_SIZE ) right_phase -= TABLE_SIZE;
        }

        return paContinue;

    }



synth::synth() {
    /* initialise sinusoidal wavetable */
    for( int time=0; time<synth::sampleRate; time++ )
    {

        double amplitudeValue = sin((2 * M_PI * time * frequency * 2) / sampleRate);
        double durationValue = synth::sampleRate * duration;
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

        sin[i] = amplitude * velocity / 100 * amplitudeValue * envelopeValue;
    }
}