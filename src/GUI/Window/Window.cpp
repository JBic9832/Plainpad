#include "Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(mWindowHandle, true);
	ImGui_ImplOpenGL3_Init("#version 330");

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

int Window::GetWidth() const {
	return mWidth;
}

int Window::GetHeight() const {
	return mHeight;
}

void Window::DrawDecorations() {
	if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))    { /* ... */ }
            if (ImGui::MenuItem("Open"))   { /* ... */ }
            if (ImGui::MenuItem("Save"))   { /* ... */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Quit"))   glfwSetWindowShouldClose(mWindowHandle, true);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {} // disabled item
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About")) { /* show about window */ }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Window::BeginFrame() const {
    glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::EndFrame() const {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(mWindowHandle);
}

void Window::PollEvents() const {
    glfwPollEvents();
}
