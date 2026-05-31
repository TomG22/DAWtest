#pragma once

/**
 * Description...
 * @author Tom G
 */

class Device {
public:
    /**
     * Constructor for Device class
     */
    Device();

    /**
     * 
     */
    int getSampleRate();

    /**
     * 
     */
    int getBitDepth();

    /**
     * 
     */
    int getMaxAmplitude();

    /**
     * 
     */
    //PaDeviceIndex getPaIndex();

    /**
     * 
     */
    //std::string getName();


private:
    //PaDeviceIndex paIndex;
    //std::string name;
    int sampleRate = 44100;
    int bitDepth = 65535;
};