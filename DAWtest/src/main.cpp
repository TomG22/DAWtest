#include "Gui.h"
#include "KeyboardController.h"
#include "AudioEngine.h"

#include <thread>
#include <iostream>
//#include <stdio.h>
//#include "Oscillator.h"
#include "SynthSound.h"

int main() {
    AudioEngine audioEngine;
    
    KeyboardController keyboardController = KeyboardController(&audioEngine);
    Gui gui = Gui(&keyboardController);

    std::thread guiThread = std::thread(&Gui::startGuiLoop, &gui);
    guiThread.detach();

    while (true) {
        //printf("~ Main thread is running ~\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}