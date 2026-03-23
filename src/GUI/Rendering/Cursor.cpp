#include "Cursor.h"
#include "Buffers/FontMap.h"
#include <glad/glad.h>
#include <iostream>

unsigned int vao, vbo, ebo;

Cursor::Cursor() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	//unsigned int indices[6] = {
	//	0, 1, 2,
	//	0, 2, 3
	//};

	unsigned int indices[6] = {
		3, 0, 1,
		3, 1, 2
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Cursor::Draw(glm::ivec2 iPos, LineStructure_t::iterator activeLine, float winOffset) {
	Line currentLine = **activeLine;
	glm::vec2 position = {currentLine.GetOffset(iPos.x) + currentLine.GetLocation().x, currentLine.GetLocation().y};
	std::cout << "Current Line Pos {" << (*activeLine)->GetLocation().x << " , " << (*activeLine)->GetLocation().y << "}\n";
	//std::cout << "Trying to draw cursor at: " << position.x << ", " << position.y << std::endl;
	float vertices[8] = {
		position.x,          position.y,
		position.x + mWidth, position.y,
		position.x + mWidth, position.y - mHeight,
		position.x,          position.y - mHeight
	};


	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cursor::SetCursorHeight(float cursorHeight) {
	mHeight = cursorHeight;
}
