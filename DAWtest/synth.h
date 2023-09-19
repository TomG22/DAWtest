#pragma once

#include <fstream>

using namespace std;

class synth {
private:
	const string chunkId = "RIFF";
	const string chunkSize = "----"; // Represents 4 placeholder bytes
	const string format = "WAVE";

	// fmt sub-chunk
	const string subChunk1Id = "fmt "; // Looks for 4 bytes, must have 'space'
	const int subChunk1Size = 16;
	const int audioFormat = 1;
	const int numChannels = 2;
	const int sampleRate = 44100; // 44.1 kHz sampling frequency
	const int byteRate = sampleRate * numChannels * (subChunk1Size / 8); // Dividing num of bits in a byte
	const int blockAlign = numChannels * (subChunk1Size / 8);
	const int bitsPerSample = 16;
	const string subChunk2Id = "data";
	const string subChunk2Size = "----";
	const int maxAmplitude = 32767;
	void writeAsBytes(ofstream& file, int value, int byteSize);

public:
	synth();
	void writeFile(string fileName);
	double amplitude = 5000;	
	int velocity = 100; // Percent of max amplitude
	double frequency = 441;
	double duration = 2;
	double attack = 0.001;
	double decay = .3;
	double sustain = 0.001;
	double release = 0.001;
	int octave = 3;
	bool pedal = false;
};