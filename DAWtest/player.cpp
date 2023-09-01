#include "player.h"
#include "synth.h"
#include <iostream>
#include <Windows.h>
#include "MMSystem.h"
#include <chrono>

#pragma comment(lib, "winmm.lib")


using namespace std::chrono;

void player::playFrequency(double frequency) {
	cout << "playing sound: " << frequency << " Hz\n";
	synth synthObj;
	synthObj.writeFrequency(frequency);
	PlaySound(TEXT("test"), NULL, SND_ASYNC);
	cout << "played sound: " << frequency << " Hz\n";

};

player::player() {
	using namespace std;
	


	// cout << "playing sound\n";
	// 
	// PlaySound(TEXT("test"), NULL, SND_ASYNC);
	// double testTime = 1.0;
	// auto start = std::chrono::steady_clock::now();
	// auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// 
	// int i = 0;
	// while (deltaTime < testTime) {
	// 	cout << testTime - deltaTime << '\n';
	// 	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// }
	// PlaySound(TEXT("test"), NULL, SND_ASYNC);
	// cout << "mid\n";
	// start = std::chrono::steady_clock::now();
	// deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// 
	// while (deltaTime < testTime) {
	// 	cout << testTime - deltaTime << '\n';
	// 	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
	// }
}