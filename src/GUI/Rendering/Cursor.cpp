#include "Cursor.h"

unsigned int vao, vbo;

Cursor::Cursor() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Cursor::Draw(glm::vec2 position) {
	float vertices[8] = {
		position.x,          position.y,
		position.x + mWidth, position.y,
		position.x + mWidth, position.y - mHeight,
		position.x,          position.y - mHeight
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 8);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cursor::SetCursorHeight(float cursorHeight) {
	mHeight = cursorHeight;
}
