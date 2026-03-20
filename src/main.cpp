#include <atomic>
#include <iostream>
#include <thread>

#include <glm/glm.hpp>

#include "Buffers/TextFile.h"
#include "GUI/Window/Window.h"
#include "GUI/Rendering/TextRenderer.h"
#include "GUI/Rendering/Cursor.h"

std::atomic<bool> running = true;

void RunLogic(TextFile& file) {
    bool insert;


    while (running) {
        std::string input;
        if(!std::getline(std::cin, input)) {
			break;
		}

        if (input.empty()) {
            continue; 
        }

        if (input[0] == 'q') { 
            running = false; 
            continue; 
        }

        if (input[0] == 'i') {
            insert = true;
        } else {
            insert = false;
        }

        int line = static_cast<int>(input[1] - '0');
        std::string text = input.substr(2);

        if (insert) 
            file.InsertLine(line, text);
        else
            file.EditLine(line, text);
    }

    //int count = 1;
    //for (const auto& l : file.GetLines()) {
    //    std::cout << count<< " " << l << std::endl;
    //    ++count;
    //}
}

int main() {
    Window win{"Plainpad", 800, 600};
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	TextFile file;
    std::jthread t{RunLogic, std::ref(file)};

	FontMap::GenerateFontMapping(RESOURCES_PATH "fonts/Arial.TTF", 24);

    TextRenderer tr {projection};
    const int fHeight = FontMap::GetGlyphHeight();

    Shader cursorShader{RESOURCES_PATH "shaders/cursor.vs", RESOURCES_PATH "shaders/cursor.fs"};
	Cursor cursor;
	cursor.SetCursorHeight(fHeight + 4);
    cursorShader.Bind();
    cursorShader.setUniformMatrix4f("projection", projection);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    file.InsertLine(0, "This is a test for cursor...");
    int col = 0;
    bool pressed = false;
    while (running) {
        running = !win.ShouldClose();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        win.BeginFrame();
		win.DrawDecorations();

        tr.RenderFile(file, {0.0f, 0.0f, 0.0f}, win);

        cursorShader.Bind();
        cursorShader.setUniformFloat("time", glfwGetTime());
		cursor.Draw({col, 0}, file.GetLineIterator(0), win.GetHeight());

        if (glfwGetKey(win.GetHandle(), GLFW_KEY_RIGHT) == GLFW_PRESS && !pressed) {
            auto it = file.GetLineIterator(0);
            for (auto c : it->GetCharacters()) {
                std::cout << c.Char;
            }
            std::cout << std::endl;
            std::cout << col << std::endl;
            ++col;
            pressed = true;
        }

        if (glfwGetKey(win.GetHandle(), GLFW_KEY_RIGHT) == GLFW_RELEASE) {
            pressed = false;
        }

        win.EndFrame();
        win.PollEvents();
    }

    return 0;
}
