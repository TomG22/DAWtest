#include "Gui.h"
#include <iostream>

Gui::Gui(KeyboardController* keyboardController) : keyboardController(keyboardController) {
	
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool Gui::isKeyDown(int keyCode) {
	return glfwGetKey(window, keyCode) != 0;
}

void Gui::startGuiLoop() {
	// Init GLFW
	glfwInit();

	// Set GLFW version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// Set profile to CORE (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Instance window
	GLFWwindow* window = glfwCreateWindow(640, 480, "GFLW Window", NULL, NULL);

	glfwSetWindowUserPointer(window, (void*)keyboardController);

	// Set keyCallback
	glfwSetKeyCallback(window, keyCallback);

	// Window error condition
	/*if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}*/

	// GLFW window loop
	while (!glfwWindowShouldClose(window)) {
		printf("gui thread id: %d\n", std::this_thread::get_id());
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	KeyboardController* keyboardController = (KeyboardController*)glfwGetWindowUserPointer(window);
	keyboardController->processNoteInput(key, action);
}
