#include "TextRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Buffers/FontMap.h"

TextRenderer::TextRenderer(glm::mat4 projection) {
	mFontShader = Shader{RESOURCES_PATH "shaders/text.vs", RESOURCES_PATH "shaders/text.fs"};
	mFontShader.Bind();
	mFontShader.setUniformMatrix4f("projection", projection);
}

void TextRenderer::RenderLine(std::shared_ptr<Line> line, float x, float y, float scale, glm::vec3 color) {
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
	mFontShader.Bind();
	mFontShader.setUniformVec3f("textColor", {color.x, color.y, color.z});
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

	auto characters = line->GetCharacters();
    // iterate through all characters
    for (auto ch = characters.begin(); ch != characters.end(); ch++)
    {
        float xpos = x + (*ch).Bearing.x * scale;
        float ypos = y - ((*ch).Size.y - (*ch).Bearing.y) * scale;

        float w = (*ch).Size.x * scale;
        float h = (*ch).Size.y * scale;
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
        glBindTexture(GL_TEXTURE_2D, (*ch).TextureId);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += ((*ch).Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::RenderFile(TextFile& file, glm::vec3 color, const Window& win) {
    int lineNumber = 1;
    for (auto& line : file.GetLines()) {
        float relPos = ((FontMap::GetGlyphHeight() + 3) * lineNumber);
		float xPos = 15.0f;
		float yPos = static_cast<float>(win.GetHeight()) - relPos - FontMap::GetGlyphHeight();
		RenderLine(line, xPos, yPos, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		line->SetLocation({xPos, yPos});
		++lineNumber;
    }
}
