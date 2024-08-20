#pragma once

/**
 * Class description...
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "KeyboardController.h"
#include <thread>

class Gui {
public:
	GLFWwindow* window;
	KeyboardController* keyboardController;

	Gui(KeyboardController* keyboardController);

	void startGuiLoop();

	bool isKeyDown(int keyCode);
};