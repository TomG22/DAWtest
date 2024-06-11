#pragma once
#include "PaStreamHandler.h"
#include <iostream>
#include <thread>

class Player {
private:
public:
    PaStreamHandler* paStreamHandler;
    std::mutex mutex;

    struct note {
        std::string soundName;
        bool isplaying = false;
        bool stopping = false;
        bool stopped = false;
    };

    int* configMap;
    int configMapLength;
    int keyIndex;
    int octave = 4;

    Player(PaStreamHandler* paStreamHandler);
    void updateInterface();
    void processControlsInput(int key, int action);
    void processNoteInput(int key, int action);
    void playTone();
};