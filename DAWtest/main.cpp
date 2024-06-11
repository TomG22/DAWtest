#include "Gui.h"
#include "Player.h"
#include "PaStreamHandler.h"

#include <thread>
#include <iostream>
#include <stdio.h>
int main() {
    PaStreamHandler paStreamHandler = PaStreamHandler();
    Player player = Player(&paStreamHandler);
    Gui gui = Gui(&player);

    std::thread guiThread = std::thread(&Gui::startGuiLoop, &gui);

    guiThread.join();

    return 0;
}
