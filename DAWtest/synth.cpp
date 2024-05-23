#include "Synth.h"
#include <stdio.h>
#include <math.h>
#include <thread>

#define NUM_SECONDS   (1)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (1024)
#define PI (3.14159265)

void Synth::buffer() {
	for( int time = 0; time < sampleRate; time++ ) {
		double amplitudeValue = (float) sin( (double) time/tableSize * PI * 2.0 * frequency);
		double durationValue = sampleRate * duration;
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

		waveTable[time] = velocity / 100 * amplitudeValue * envelopeValue;
	}
}

bool Synth::setTableValue(int key, float value) {
	if (key >= 0 && key < tableSize) {
		waveTable[key] = value;
		return true;
	}
	return false;
}

float Synth::getTableValue(int key) {
	return waveTable[key];
}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int paCallback(
	const void *inputBuffer,
	void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData ) {

   /* Here we cast userData to a reference to our class so we can call the instance method paCallbackMethod,
   	  we can do that since we called Pa_OpenStream with 'this' for userData */
	return ((Synth*)userData)->Synth::paCallbackMethod(
		inputBuffer,
		outputBuffer,
		framesPerBuffer,
		timeInfo,
		statusFlags);
}

bool Synth::open(PaDeviceIndex index) {
	PaStreamParameters outputParameters;

	outputParameters.device = index;
	if (outputParameters.device == paNoDevice) {
		return false;
	}

	const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
	if (pInfo != 0) {
		//printf("Output device name: '%s'\r", pInfo->name);
	}

    outputParameters.channelCount = 2;       	// stereo output
    outputParameters.sampleFormat = paFloat32; 	// 32 bit floating point output
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	PaError err = Pa_OpenStream(
		&stream,
      	NULL, 							// no input
		&outputParameters,
		SAMPLE_RATE,
		paFramesPerBufferUnspecified,
      	paClipOff,						// we won't output out of range samples so don't bother clipping them
		&paCallback,
     	this);            				// Using 'this' for userData so we can cast to Sine* in paCallback method

	if (err != paNoError) {
		//printf("Error: Failed to open stream to device");
		return false;
	}

	err = Pa_SetStreamFinishedCallback( stream, paStreamFinished );

	if (err != paNoError) {
		//printf("Error: Stream finished callback failed");
		Pa_CloseStream( stream );
		stream = 0;
		return false;
	}

	return true;
}

bool Synth::close() {
	if (stream == 0)
		return false;

	PaError err = Pa_CloseStream( stream );
	stream = 0;

	return (err == paNoError);
}


PaError Synth::start() {
	/*if (stream == 0)
		return false;
	*/
	PaError err = Pa_StartStream( stream );

	return err;
}

bool Synth::stop() {
	if (stream == 0)
		return false;

	PaError err = Pa_StopStream( stream );

	return (err == paNoError);
}

    /* The instance callback, where we have access to every method/variable in object of class Sine */
int Synth::paCallbackMethod(
	const void *inputBuffer,
	void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags) {
	float *out = (float*)outputBuffer;
	unsigned long i;
//~
	//printf("timeInfo: %d\n", timeInfo);
//~
	// Prevent unused variable warnings
   	//(void) timeInfo;
	(void) statusFlags;
	(void) inputBuffer;

	for( i=0; i<framesPerBuffer; i++ ) {
         *out++ = waveTable[left_phase];
         *out++ = waveTable[right_phase];

		left_phase++;
		if( left_phase >= tableSize )
			left_phase -= tableSize;

		right_phase++;
		if( right_phase >= tableSize )
			right_phase -= tableSize;
	}

	return paContinue;
}


void Synth::paStreamFinishedMethod() {
        printf( "Stream Completed: %s\n", message );
}

/*
 * This routine is called by portaudio when playback is done.
 */
void Synth::paStreamFinished(void* userData) {
	return ((Synth*)userData)->paStreamFinishedMethod();
}


class ScopedPaHandler {
public:
	ScopedPaHandler() : _result(Pa_Initialize()) {
	}
	~ScopedPaHandler() {
		if (_result == paNoError) {
			Pa_Terminate();
		}
	}

	PaError result() const { return _result; }

private:
	PaError _result;
};

void Synth::play() {
	//buffer bufferObj;
	//currentBuffer = bufferObj;


	ScopedPaHandler paInit;

	if (open(Pa_GetDefaultOutputDevice())) {
		buffer();
		start();
		// have to loop callbacks somehow in order for the stream to continue being played...may need to make external event system so gui can update as well
		// for now, the stream could be processed on queue, but the gui won't be able to be processed during this time, hence ^
		// or, multithreading can be used if possible
		// int i = 0;
		printf("Hi\n");
		

		Pa_Sleep(1000);
	}
}

/*double Synth::getCurrentBuffer() {
	return currentBuffer;
}*/

Synth::Synth() {
	
}
