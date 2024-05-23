#pragma once
#include <GLFW/glfw3.h>
#include "Player.h"
#include <thread>

class Gui {
public:	
	GLFWwindow* window;
	Player* playerPtr;
	Gui();
	int isKeyDown(int keyCode);
};