#pragma once
#include "Shader.h"

#include <map>

struct Character {
    unsigned int TextureId;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class TextRenderer {
public:
    TextRenderer(const std::string& font);
    
    void RenderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color);
    

private:
    Shader mFontShader;
    std::map<char, Character> mCharacters;

    void generateBitmap(const std::string& fontFile);
};