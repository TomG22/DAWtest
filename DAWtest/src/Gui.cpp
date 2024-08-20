#include "Gui.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <iostream>

#include <filesystem>
#include <windows.h>

Gui::Gui(KeyboardController* keyboardController) : keyboardController(keyboardController) {
	
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

bool Gui::isKeyDown(int keyCode) {
	return glfwGetKey(window, keyCode) != 0;
}

void Gui::startGuiLoop() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Window", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window/n");
        glfwTerminate();
    } else {
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, keyCallback);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetWindowUserPointer(window, (void*)keyboardController);
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD/n");
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f, 
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

    Shader shader("Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    //shader.SetUniformMat4f("u_MVP", proj);

    Texture texture("res/imgs/popcat.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        renderer.Clear();
        renderer.clearColor(0.8f, 0.5f, 0.2f, 1.0f);

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.8f, 1.0f);

        renderer.Draw(va, ib, shader);

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    glfwTerminate();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	KeyboardController* keyboardController = (KeyboardController*)glfwGetWindowUserPointer(window);
	keyboardController->processNoteInput(key, action);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
