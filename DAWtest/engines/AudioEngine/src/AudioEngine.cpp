#include "AudioEngine.h"
#include "Device.h"     // Consider making class hierarchy as follows: AudioEngine->DeviceList[Device]->StreamHandler->SoundList[Sound]
#include "StreamHandler.h"

AudioEngine::AudioEngine() {

}

void AudioEngine::playSound(Sound* sound) {
    sound->registerDeviceInfo(&defaultDevice);
    sound->play();
    defaultStreamHandler.addSound(sound);
    defaultStreamHandler.streamSounds();
}