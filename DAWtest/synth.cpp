#include "synth.h"
#include "input.h"
#include <iostream>
#include <cmath>

void synth::writeAsBytes(ofstream& file, int value, int byteSize) { // using this to convert to correct byte format
	file.write(reinterpret_cast<const char*>(&value), byteSize); // calls file sending to function-ofstream has write function which can write in binary-reinterpret_cast takes value reference and turns it into const char by casting it
}

void synth::writeFile() {
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

		for (int time = 0; time < sampleRate * duration;time++) {
			// Respect max amplitude and operate as a wave
			double frequencyValue = sin((2 * 3.14 * time * frequency * 2) / sampleRate);
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

			double channel1 = amplitude * frequencyValue * envelopeValue;
			double channel2 = amplitude * frequencyValue * envelopeValue;

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

synth::synth() {
}