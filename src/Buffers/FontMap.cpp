#include "FontMap.h"
#include <glad/glad.h>
#include <iostream>

int FontMap::sGlyphHeight;
std::map<char, Character> FontMap::sCharacterMap;

void FontMap::GenerateFontMapping(const std::string& fontFile, int glyphHeight) {
	sGlyphHeight = glyphHeight;
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "Could not initialize FreeType library..." << std::endl;
        throw std::runtime_error("Failed to initialize FreeType!");
	}

	FT_Face face;
	if (FT_New_Face(ft, RESOURCES_PATH "fonts/Arial.TTF", 0, &face)) {
		std::cout << "Could not initialize font face..." << std::endl;
        throw std::runtime_error("Failed to initialize font face!");
	}

	FT_Set_Pixel_Sizes(face, 0, sGlyphHeight);

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

		sCharacterMap.insert(std::pair<char, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

std::map<char, Character> FontMap::GetCharacterMapping() {
	return sCharacterMap;
}

int FontMap::GetGlyphHeight() {
	return sGlyphHeight;
}

