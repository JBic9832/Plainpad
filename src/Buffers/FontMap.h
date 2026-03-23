#pragma once
#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

struct Character {
    unsigned int TextureId;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
	char Char;
};

class FontMap {
public:
	static void GenerateFontMapping(const std::string& fontFile, int glyphHeight);
	static std::map<char, Character> GetCharacterMapping();
	static int GetGlyphHeight();
	static float GetMinDescender();
	static float GetMaxAscender();

private:
	static std::map<char, Character> sCharacterMap;
	static int sGlyphHeight;
	static float sHeightMax, sHeightMin;
    
  
  
  
	
};
