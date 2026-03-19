#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Cursor {
public:
	Cursor();

	void Draw(glm::vec2 position);
	void SetCursorHeight(float cursorHeight);

private:
	float mHeight;
	float mWidth = 2.0f;
};
