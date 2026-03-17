#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

class Window {
public:
    Window(const std::string& windowName, int width, int height);
    ~Window();

    GLFWwindow* GetHandle() const;

	int GetWidth() const;
	int GetHeight() const;

    bool ShouldClose() const;

    void BeginFrame() const;
    void EndFrame() const;
    void PollEvents() const;

private:
    GLFWwindow* mWindowHandle = nullptr;
    int mWidth, mHeight;
};
