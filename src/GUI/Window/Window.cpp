#include "Window.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>

Window::Window(const std::string& windowName, int width, int height) : mWidth { width }, mHeight { height } {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW..." << std::endl;
        return;
    }

    mWindowHandle = glfwCreateWindow(mWidth, mHeight, windowName.c_str(), nullptr, nullptr);

    if(!mWindowHandle) {
        std::cout << "Failed to create window..." << std::endl;
        return;
    }

    glfwMakeContextCurrent(mWindowHandle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init glad..." << std::endl;
        glfwTerminate();
        return;
    }
}

Window::~Window() {
    glfwTerminate();
}

GLFWwindow* Window::GetHandle() const {
    return mWindowHandle;
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(mWindowHandle);
}

void Window::BeginFrame() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndFrame() const {
    glfwSwapBuffers(mWindowHandle);
}

void Window::PollEvents() const {
    glfwPollEvents();
}