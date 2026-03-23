#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

#include "GUI/Event/EventSystem.h"

class Window {
public:
    Window(const std::string& windowName, int width, int height, EventSystem& e);
    ~Window();

    GLFWwindow* GetHandle() const;

	void DrawDecorations();

	int GetWidth() const;
	int GetHeight() const;

    bool ShouldClose() const;

    void BeginFrame() const;
    void EndFrame() const;
    void PollEvents() const;
	void SendKeyEvent(int key, int action);

private:
	static Window* createWindowUserPointer(GLFWwindow* window);
	static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    GLFWwindow* mWindowHandle = nullptr;
    int mWidth, mHeight;
	EventSystem& mEventSystem;
};
