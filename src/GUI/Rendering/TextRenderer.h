#pragma once

#include <map>

#include "Shader.h"
#include "Buffers/Line.h"

class Line;

class TextRenderer {
public:
    TextRenderer(glm::mat4 projection);
    
    void RenderText(const Line& line, float x, float y, float scale, glm::vec3 color);
    int GetGlyphHeight() const;

private:
    unsigned int mVAO, mVBO;
    Shader mFontShader;
};
