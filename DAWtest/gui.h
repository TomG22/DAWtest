#pragma once
#include <GLFW/glfw3.h>
#include "Player.h"
#include <thread>

class Gui {
public:
	std::mutex mutex;
	GLFWwindow* window;
	Player* playerPtr;

	Gui(Player* playerPtr);

	void startGuiLoop();

	bool isKeyDown(int keyCode);
};