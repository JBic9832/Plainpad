#pragma once
#include "Buffers/Line.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Cursor {
public:
	Cursor();

	void Draw(glm::ivec2 position, std::list<Line>::iterator activeLine, float winOffset);
	void SetCursorHeight(float cursorHeight);

private:
	float mHeight;
	float mWidth = 2.0f;
};
