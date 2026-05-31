#include "Sound.h"
#include <cmath>
#include <iostream>

int Sound::nextId = 0;

Sound::Sound(SoundType type, double time) : soundType(type), time(time) {
	id = nextId++;
	printf("new id: %d\n", id);
}

int Sound::getId() {
    return id;
}

unsigned long Sound::getFramesGenerated() {
	return framesGenerated;
}

unsigned long Sound::getFrameCount() {
	return frameCount;
}

bool Sound::getType() {
	return soundType;
}

void Sound::genFrames(int frames) {
	framesGenerated += frames;
}

bool Sound::isGenerated() {
	return framesGenerated >= frameCount;
}

bool Sound::isPlaying() {
	return playing == true;
}

void Sound::play() {
	framesGenerated = 0;
	playing = true;
}

void Sound::play(int startFrame) {
	framesGenerated = startFrame;
	playing = true;
}

void Sound::stop() {
	playing = false;
}

void Sound::registerDeviceInfo(Device* device) {
    printf("time: %f\n", time);
	int newSampleRate = device->getSampleRate();
	printf("sr: %d\n", newSampleRate);
    framesGenerated = static_cast<unsigned long>(
					      std::ceil(static_cast<double>(frameCount) / framesGenerated)
					  ) * newSampleRate;
    printf("fg: %d\n", framesGenerated);
	frameCount = static_cast<unsigned long>(std::ceil(newSampleRate * time));
    printf("fc: %d\n", frameCount);
}