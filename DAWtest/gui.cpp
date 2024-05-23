#include "Gui.h"
#include "Player.h"
#include <iostream>
#include <thread>

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

using namespace std;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int Gui::isKeyDown(int keyCode) {
	return glfwGetKey(window, keyCode) != 0;
}

Gui::Gui() {
	// Make a new player object
	playerPtr = new Player();

	// Init GLFW
	glfwInit();

	// Set GLFW version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// Set profile to CORE (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Instance window
	GLFWwindow* window = glfwCreateWindow(640, 480, "GFLW Window", NULL, NULL);

	glfwSetWindowUserPointer(window, (void*)playerPtr);

	// Set keyCallback
	glfwSetKeyCallback(window, keyCallback);

	// Window error condition
	/*if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}*/

	// GLFW window loop
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}	

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	Player* playerPtr = (Player*)glfwGetWindowUserPointer(window);
	playerPtr->processNoteInput(key, action);
	//std::thread playerThread;
	//playerThread = std::thread(playerPtr->processNoteInput, playerPtr, key, action);
}