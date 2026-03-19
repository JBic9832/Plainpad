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

    int count = 1;
    for (const auto& l : file.GetLines()) {
        std::cout << count<< " " << l << std::endl;
        ++count;
    }
}

int main() {
    Window win{"Plainpad", 800, 600};
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	TextFile file;
    std::jthread t{RunLogic, std::ref(file)};

    TextRenderer tr {RESOURCES_PATH "fonts/Arial.TTF", 24, projection};
    const int fHeight = tr.GetGlyphHeight();

    Shader cursorShader{RESOURCES_PATH "shaders/cursor.vs", RESOURCES_PATH "shaders/cursor.fs"};
	Cursor cursor;
	cursor.SetCursorHeight(fHeight);
    cursorShader.Bind();
    cursorShader.setUniformMatrix4f("projection", projection);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (running) {
        running = !win.ShouldClose();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        win.BeginFrame();
		win.DrawDecorations();

		int lineNumber = 1;
		for (const auto& line : file.GetLines()) {
			float relPos = ((fHeight + 3) * lineNumber);
			float pos = relPos - (static_cast<float>(win.GetHeight()) - relPos);
			tr.RenderText(line, 15.0f, static_cast<float>(win.GetHeight()) - relPos - fHeight, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			++lineNumber;
		}

        cursorShader.Bind();
        cursorShader.setUniformFloat("time", glfwGetTime());
		cursor.Draw({15.0f, win.GetHeight() - (fHeight + 3)});

        win.EndFrame();
        win.PollEvents();
    }

    return 0;
}
