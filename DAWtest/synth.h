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
	void writeAsBytes(ofstream& file, int value, int byteSize);
public:
	const int duration = 2;
	const int maxAmplitude = 32767;
	const double frequency = 440;
	synth();

};