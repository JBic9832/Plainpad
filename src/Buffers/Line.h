#pragma once

#include <list>
#include <vector>

#include "FontMap.h"

class Line {
public:
	Line();
	Line(const std::string& content);

	std::list<Character> GetCharacters() const;

	void AddCharacter(Character c);
	void InsertCharacter(Character c, std::list<Character>::iterator position);
	std::list<Character>::iterator GetIteratorAtPosition(size_t position);
	std::vector<float> mOffsets;
	float GetOffset(int col);
	glm::vec2 GetLocation() const;
	void SetLocation(glm::vec2 location);
	float GetMaxDescender() const;
	float GetMaxAscender() const;

private:
	std::list<Character> mCharacters;
	glm::vec2 mLocation{0};
	float mMaxDescender, mMaxAscender;

};
