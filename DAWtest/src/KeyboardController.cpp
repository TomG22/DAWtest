#include "KeyboardController.h"
#include "AudioEngine.h"

#include <iostream>
#include <cmath>
#include <chrono>

using namespace std::chrono;

KeyboardController::KeyboardController(AudioEngine* audioEngine) : audioEngine(audioEngine) {
    configMap = largeConfigMap;
    configMapLength = sizeof(largeConfigMap) / sizeof(int);
    /*
    configMap = miniConfigMap;
    configMapLength = sizeof(miniConfigMap) / sizeof(int);
    */



    // using namespace std;
    //
    // //...cout << "playing sound\n";
    // 
    // PlaySound(TEXT("test"), NULL, SND_ASYNC);
    // double testTime = 1.0;
    // auto start = std::chrono::steady_clock::now();
    // auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
    // 
    // int i = 0;
    // while (deltaTime < testTime) {
    //  //...cout << testTime - deltaTime << '\n';
    //  deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
    // }
    // PlaySound(TEXT("test"), NULL, SND_ASYNC);
    // //...cout << "mid\n";
    // start = std::chrono::steady_clock::now();
    // deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
    // 
    // while (deltaTime < testTime) {
    //  //...cout << testTime - deltaTime << '\n';
    //  deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
    // }
}

void KeyboardController::playTone() {
    // Play a new sine sound that plays for 1 second
    //SynthSound sound = SynthSound(Oscillator::OscillatorType::sine, 1);
    //audioEngine->playSound(&sound);
}

void KeyboardController::updateInterface() {
    //system("cls");

            // Keyboard Output
    //...cout << "key pressed: " << keyNamesMap[configMap[keyIndex]] << endl;

        // Note Color
    //...cout << "note color: ";
    if (configMap[keyIndex] >= configMap[0] && configMap[keyIndex] <= configMap[configMapLength - 1]) {
        //...cout << "white\n";
    }
    else if (configMap[keyIndex] >= configMap[1] && configMap[keyIndex] <= configMap[configMapLength - 2]) {
        //...cout << "black\n";
    }
    else {
        //...cout << "undefined\n";
    }


    //Note Name
    char noteNames[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' }; 
    int whiteNoteIndex = configMap[keyIndex] - configMap[0];
    int blackNoteIndex = configMap[keyIndex] - configMap[1];
    if (configMap[keyIndex] >= configMap[0] && configMap[keyIndex] <= configMap[configMapLength - 1]) {
        //...cout << "note: " << noteNames[(whiteNoteIndex % 7)] << paStreamHandler->octave + ((whiteNoteIndex + 2) / 7) << endl;
    }
    else if (configMap[keyIndex] >= configMap[1] && configMap[keyIndex] <= configMap[configMapLength - 2]) {
        //...cout << "note: " << noteNames[(blackNoteIndex % 7)] << '#' << paStreamHandler->octave + ((blackNoteIndex + 2) / 7) << '/'
        //  << noteNames[(blackNoteIndex + 1) % 7] << 'b' << paStreamHandler->octave + ((blackNoteIndex + 3) / 7) << endl;
    }
        // Controls
    /*if (paStreamHandler->pedal == 1) {
        //...cout << "Sustain: On\n";
    }
    else {
        //...cout << "Sustain: Off\n";
    }
    ...cout << "Duration: " << paStreamHandler->duration << endl
        << "Frequency: " << paStreamHandler->frequency << " Hz\n"
        << "Octave: " << paStreamHandler->octave << endl
        << "Velocity: " << paStreamHandler->velocity << endl
        << "Attack: " << paStreamHandler->attack <<
        " | Decay: " << paStreamHandler->decay <<
        " | Sustain: " << paStreamHandler->sustain <<
        " | Release: " << paStreamHandler->release << endl;*/
}

void KeyboardController::processNoteInput(int keyCode, int state) {
    for (int keyIndex = 0; keyIndex < configMapLength; keyIndex++) {
        if (state == 1 && keyCode == glfwKeyCodes[configMap[keyIndex]]) {
            this->keyIndex = keyIndex;
            // Start at C frequency since it will be the first index
            double frequencyVal = round(130.81278265 * pow(2.0, double((keyIndex + 12 * (octave - 3)) / 12.0)));
            //paStreamHandler->frequency = frequencyVal;
            //playTone();

            //std::thread worker1(updateInterface, this);
            //worker1.join();
            
            //updateInterface();
            //...cout << "playing sound\n";
            //...cout << "played sound\n";
        }
    }
}

void KeyboardController::processControlsInput(int keyCode, int state) {
    for (int keyIndex = 0; keyIndex < sizeof(controlsMap) / sizeof(int); keyIndex++) {
        if (state == 1 && keyCode == glfwKeyCodes[controlsMap[keyIndex]]) {
            /*if (controlsNames[keyIndex] == "Sustain") {
                if (paStreamHandler->pedal) {
                    paStreamHandler->pedal = 0;
                } else {
                    paStreamHandler->pedal = 1;
                }
            }
            if (controlsNames[keyIndex] == "Octave Down") {
                paStreamHandler->octave -= 1;
            }
            else if (controlsNames[keyIndex] == "Octave Up") {
                paStreamHandler->octave += 1;
            }
            else if (paStreamHandler->velocity > 0 && controlsNames[keyIndex] == "Velocity Down") {
                paStreamHandler->velocity -= 10;
            }
            else if (controlsNames[keyIndex] == "Velocity Up") {
                paStreamHandler->velocity += 10;
            }
            updateInterface();
        }
        else if (state == 0 && keyCode == glfwKeyCodes[controlsMap[keyIndex]]) {
            /* Computer keyboard input is limited so hold mode takes up an extra input space.
               Eventually make ui for toggling between toggle and hold mode for sustain.
            if (controlsNames[keyIndex] == "Sustain") {
                paStreamHandler->pedal = 0;
            }   
            */
            // updateInterface();
        }
        else {
            // key is held down
        }
    }
}
