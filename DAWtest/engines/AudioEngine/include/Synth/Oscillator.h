#pragma once

/**
 * Class description...
 */

#include <vector>
#include <stdint.h>

class Oscillator {
public:
    enum OscillatorType {
        sine,
        triangle,
        square,
        sawtooth
    };

    /**
     * Constructor for Math class
     */
    Oscillator(OscillatorType type);
    
    /**
     * 
     */
    double getFrequency();

    /**
     * 
     */
    void setFrequency(double newFrequency);

    /**
     * 
     */
    void genSound(float* destination, int sampleIdx, int sampleCount);

    /**
     * 
     */
    void genSine(float* destination, int sampleIdx, int sampleCount);

    /**
     * 
     */
    void genTriangle();

    /**
     * 
     */
    void genSquare();

    /**
     * 
     */
    void genSawtooth();

private:
    OscillatorType type;

    uint8_t pan = 0;        // -100% left - 0 - +100% right
    uint8_t volume = 100;   // 0% - 100%
    double frequency = 440.0;
    double phaseShift = 0;

    int sampleRate = 44100;
    int maxAmplitude = 32768;
};