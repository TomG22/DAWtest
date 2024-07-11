#include "Synth.h"

Synth::Synth() {
    //std::mutex mutex;
    //componentChain = 
}

/* code snippet of envelope being applied w/ using envelope object
    RingBuffer* dataBuffer = RingBuffer();
    unsigned long framesAvailable = (soundBuffer.getCapacity() - soundBuffer.getSize()) * 1024;
    float* generatedData = new float[sawmplesAvailable];
    for (int frameIdx = framesGenerated; frameIdx < frameCount && frameIdx < framesGenerated + framesAvailable) {
        double frameValue = sin((double)frameIdx/frameCount * 2.0 * PI * frequency) * velocity / 100;
        runningTotal += envelope.delayFrames;
        if (frameIdx <= runningTotal + envelope.attackFrames) {
            frameSoundData[frameIdx] = frameValue * (frameIdx - runningTotal) * (envelope.attackVelocity/100)/envelope.attackFrames;
            runningTotal += envelope.attackFrames;
            frameSoundData[frameIdx] = frameValue * 
        } else if (i <= runningTotal + envelope.holdFrames) {
            frameSoundData[frameIdx] = volume * (envelope.attackVelocity/100);
            runningTotal += envelope.holdFrames;
        } else if (i <= frameCount * (envelope.attackFrames + envelope.decayFrames + envelope.releaseFrames)/100) {
            frameSoundData[frameIdx] = volume * 
            envelopeValue = -(envelope.sustain / envelope.releaseValue) * (time - (attackValue + decayValue + releaseValue));
        }

    frameSoundData[time] = frameValue * envelopeValue;
*/


void Synth::genFrames(SynthSound* sound, float* destination, int frames) {
    sound->getBaseOscillator()->genSound(destination, sound->getFramesGenerated(), frames);
}

void Synth::genFrames(SampleSound* sound, float* destination, int frames) {
    //fstream
    //sound.getFrame();
}