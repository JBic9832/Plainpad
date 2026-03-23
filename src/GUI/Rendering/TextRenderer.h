#pragma once

#include "Buffers/TextFile.h"
#include "Shader.h"
#include "Buffers/Line.h"
#include "GUI/Window/Window.h"

class Line;

class TextRenderer {
public:
    TextRenderer(glm::mat4 projection);
    
    void RenderLine(std::shared_ptr<Line> line, float x, float y, float scale, glm::vec3 color);
    void RenderFile(TextFile& textFile, glm::vec3 color, const Window& win);
    int GetGlyphHeight() const;

private:
    unsigned int mVAO, mVBO;
    Shader mFontShader;
};
