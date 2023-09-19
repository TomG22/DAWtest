#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class gui {
public:
	GLFWwindow* window;
	int isKeyDown(int keyCode);
	gui();
};