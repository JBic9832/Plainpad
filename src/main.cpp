#include "GUI/Rendering/TextRenderer.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include "Buffers/TextFile.h"
#include "GUI/Window/Window.h"
#include "GUI/Rendering/Shader.h"


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

	TextFile file;
    std::jthread t{RunLogic, std::ref(file)};

	Shader fontShader {RESOURCES_PATH "shaders/text.vs", RESOURCES_PATH "shaders/text.fs"};

    TextRenderer tr {RESOURCES_PATH "fonts/Arial.TTF", 24};
    const int fHeight = tr.GetGlyphHeight();


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

        win.EndFrame();
        win.PollEvents();
    }

    return 0;
}
