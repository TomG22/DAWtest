#include "player.h"
#include <iostream>
#include <Windows.h>
#include "MMSystem.h"
#pragma comment(lib, "winmm.lib")

using namespace std;

player::player() {
	std::cout << "playing sound\n";
	PlaySound(TEXT("test"), NULL, SND_ASYNC);
	double testTime = 2.0;

	time_t start, end;

	time(&start);
	while (double(end - start)) {
		
	};
	cout << "played sound\n";

}