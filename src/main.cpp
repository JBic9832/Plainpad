#include "Buffers/TextFile.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include "GUI/Window/Window.h"
#include "Rendering/Shader.h"


std::atomic<bool> running = true;

void RunLogic(TextFile& file) {
    bool insert;

    while (running) {
        std::string input;
        std::getline(std::cin, input);

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


struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

std::map<char, Character> Characters;

void RenderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color)
{
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    // activate corresponding render state	
    s.Bind();
	s.setUniformVec3f("textColor", {color.x, color.y, color.z});
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int main() {
    Window win{"Plainpad", 800, 600};

	TextFile file;
    std::thread t{RunLogic, std::ref(file)};

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "Could not initialize FreeType library..." << std::endl;
		return -1;
	}

	FT_Face face;
	if (FT_New_Face(ft, RESOURCES_PATH "fonts/Arial.TTF", 0, &face)) {
		std::cout << "Could not initialize font face..." << std::endl;
		return -1;
	}

	const int fHeight = 16;
	FT_Set_Pixel_Sizes(face, 0, fHeight);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; ++c) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "Error loading char: " << c << std::endl;
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 
				face->glyph->bitmap.width, face->glyph->bitmap.rows,
				0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2 {face->glyph->bitmap.width, face->glyph->bitmap.rows},
			glm::ivec2 {face->glyph->bitmap_left, face->glyph->bitmap_top},
			static_cast<unsigned int>(face->glyph->advance.x)
		};

		Characters.insert(std::pair<char, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	Shader fontShader {RESOURCES_PATH "shaders/text.vs", RESOURCES_PATH "shaders/text.fs"};
	fontShader.Bind();

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	fontShader.setUniformMatrix4f("projection", projection);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (running) {
        running = !win.ShouldClose();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        win.BeginFrame();

		int lineNumber = 0;
		for (const auto& line : file.GetLines()) {
			float relPos = ((fHeight + 3) * lineNumber);
			float pos = relPos - (static_cast<float>(win.GetHeight()) - relPos);
			RenderText(fontShader, line, 15.0f, static_cast<float>(win.GetHeight()) - relPos - fHeight, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			++lineNumber;
		}

        win.EndFrame();
        win.PollEvents();
    }

    t.join();


    return 0;
}
