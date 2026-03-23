#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Buffers/Line.h"
#include "Buffers/Types.h"

class Cursor {
public:
	Cursor();

	void Draw(glm::ivec2 position, LineStructure_t::iterator activeLine, float winOffset);
	void SetCursorHeight(float cursorHeight);

private:
	float mHeight;
	float mWidth = 1.0f;
	float mHangOver = 1.0f;
};
