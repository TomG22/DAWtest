#include "gui.h"
#include "player.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

gui::gui() {
	// Init GLFW
	glfwInit();

	// Set GLFW version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// Set profile to CORE (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Instance window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hi!", NULL, NULL);
	
	// Set keyCallback
	glfwSetKeyCallback(window, keyCallback);

	// Window error condition
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}

	// Instance player

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

player playerObj;


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	playerObj.processNoteInput(key, action);
	playerObj.processControlsInput(key, action);
}