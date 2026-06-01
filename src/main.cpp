// Widgetless example (window only)
// Key registration connected to synth for a basic keyboard test

#include <math.h>
#include <stdio.h>

#include <AudioEngine.h>
#include <GuiTypes.h>
#include <Synth.h>
#include <WindowManager.h>
#include "WindowListener.h"

int main() {
    WindowManager winManager = WindowManager();

    float width = 1440.0, height = 700.0f;

    Window* window = winManager.createWindow(static_cast<int>(width),
                                             static_cast<int>(height));
    window->maximize();

    WindowListener listener = WindowListener();

    // The audio engine starts its stream upon initialization
    AudioEngine ae = AudioEngine();

    // Dummy synth used to test the audioengine
    Synth synth = Synth(ae);

    // Dummy controller loop used to trigger inputs to the synth
    printf("Press 1-9 + ENTER to trigger/release note\n");
    printf("Press 'q' + ENTER to quit\n\n");

    listener.onKeyDown = [&synth](KeyName key, std::vector<ModKeyName> mods) mutable {
        if (key == KeyName::Q_KEY) exit(0);

        if (key >= KeyName::ONE_KEY && key <= KeyName::NINE_KEY) {
            NoteName note = static_cast<NoteName>(static_cast<int>(NoteName::C4) + (key - KeyName::ONE_KEY));

            synth.holdNote(note);
            printf("Holding note: %i\n", note);
        } else {
            printf("Unmapped key: %i\n", key);
        }
    };

    // On every key up event for this window, update the input state
    listener.onKeyUp = [&synth](KeyName key, std::vector<ModKeyName> mods) mutable {
        if (key >= KeyName::ONE_KEY && key <= KeyName::NINE_KEY) {
            NoteName note = static_cast<NoteName>(static_cast<int>(NoteName::C4) + (key - KeyName::ONE_KEY));

            synth.releaseNote(note);
            printf("Releasing note: %i\n", note);
        } else {
            printf("Unmapped key: %i\n", key);
        }
    };

    listener.onMouseMove = [](float x, float y) {
        printf("Mouse moved to (%f, %f) position\n", x, y);
    };

    listener.onMouseHover = [](float x, float y) {
        printf("Mouse hovered on (%f, %f) position\n", x, y);
    };

    listener.onMouseEnter = []() {
        printf("Mouse entered\n");
    };

    listener.onMouseLeave = []() {
        printf("Mouse left\n");
    };

    listener.onMouseDown = [](float x, float y, MouseButtonType type) {
        printf("Mouse button %d down at (%f, %f)\n", type, x, y);
    };

    listener.onMouseUp = [](float x, float y, MouseButtonType type) {
        printf("Mouse button %d up at (%f, %f)\n", type, x, y);
    };

    window->registerListener(&listener);

    winManager.startEventLoop();
}
