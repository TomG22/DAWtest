#include "Device.h"
#include <cmath>

Device::Device() {

}

int Device::getSampleRate() {
    return sampleRate;
}

int Device::getBitDepth() {
    return log2(bitDepth);
}

int Device::getMaxAmplitude() {
    return bitDepth/2;
}