#include "Line.h"
#include <iterator>
#include <iostream>

Line::Line() {
	mOffsets = std::vector<float>(255);
	mOffsets[0] = 0.0f;
}

Line::Line(const std::string& content) {
	mOffsets = std::vector<float>(255);
	mOffsets[0] = 0.0f;
	for (char c : content) {
		Character ch = FontMap::GetCharacterMapping()[c];
		mCharacters.push_back(ch);

		float ascender = ch.Bearing.y;
		float descender = ch.Size.y - ch.Bearing.y;

		mMaxAscender = std::max(mMaxAscender, ascender);
		mMaxDescender = std::max(mMaxDescender, descender);
	}
}

float Line::GetOffset(int col) {
	float x = 0;

	for (int i = 0; i < col && i < mCharacters.size(); i++) {
		x += (GetIteratorAtPosition(i)->Advance >> 6);
	}

	return x;
}

std::list<Character> Line::GetCharacters() const {
	return mCharacters;
}

std::list<Character>::iterator Line::GetIteratorAtPosition(size_t position) {
	if (position >= mCharacters.size()) {
		return mCharacters.begin();
	}

	auto it = mCharacters.begin();
	std::advance(it, position);
	return it;
}

glm::vec2 Line::GetLocation() const {
	return mLocation;
}

void Line::SetLocation(glm::vec2 location) {
	mLocation = location;
}

float Line::GetMaxDescender() const {
	return mMaxDescender;
}

float Line::GetMaxAscender() const {
	return mMaxAscender;
}
