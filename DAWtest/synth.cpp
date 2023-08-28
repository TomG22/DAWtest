#include "synth.h"
#include <iostream>
#include <cmath>

void synth::writeAsBytes(ofstream& file, int value, int byteSize) { // using this to convert to correct byte format
	file.write(reinterpret_cast<const char*>(&value), byteSize); // calls file sending to function-ofstream has write function which can write in binary-reinterpret_cast takes value reference and turns it into const char by casting it
}

synth::synth() {
	ofstream wav;
	wav.open("test.wav", ios::binary);

	if (wav.is_open()) {
		wav << chunkId;
		wav << chunkSize;
		wav << format;

		wav << subChunk1Id;
		writeAsBytes(wav, subChunk1Size, 4);
		writeAsBytes(wav, audioFormat, 2);
		writeAsBytes(wav, numChannels, 2);
		writeAsBytes(wav, sampleRate, 4);
		writeAsBytes(wav, byteRate, 4);
		writeAsBytes(wav, blockAlign, 2);
		writeAsBytes(wav, bitsPerSample, 2);

		wav << subChunk2Id;
		wav << subChunk2Size;

		//Marker for writing audio 
		int startAudio = wav.tellp();

		for (int i = 0; i < sampleRate * duration; i++) {
			// Respect max amplitude and operate as a wave
			double amplitude = 5000;
			double value = sin((2 * 3.14 * i * frequency) / sampleRate);

			double channel1 = amplitude * value;
			double channel2 = amplitude * value;

			// inserting channel data (l, r, l, r, l, r,...)
			writeAsBytes(wav, channel1, 2);
			writeAsBytes(wav, channel2, 2);
		}

		int endAudio = wav.tellp();
		wav.seekp(startAudio - 4); // minus 4 bytes in sound data
		writeAsBytes(wav, endAudio - startAudio, 4); // subchunk2 size

		wav.seekp(4, ios::beg); // 4th bit after beginning
		writeAsBytes(wav, endAudio - 8, 4); //Minus 8 "is fine" 
	}

	wav.close();
}