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
    SynthSound sound = SynthSound(Oscillator::OscillatorType::sine, 1.00);
    audioEngine.playSound(&sound);
    printf("Tried to play sound (from main)\n");
    
    KeyboardController keyboardController = KeyboardController(&audioEngine);
    Gui gui = Gui(&keyboardController);

    std::thread guiThread = std::thread(&Gui::startGuiLoop, &gui);

    guiThread.join();
    while (true) {

    }
    return 0;
}
