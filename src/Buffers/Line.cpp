#include "Line.h"
#include <iterator>

Line::Line() {
	mOffsets = std::vector<float>(255);
	mOffsets[0] = 0.0f;
}

Line::Line(const std::string& content) {
	mOffsets = std::vector<float>(255);
	mOffsets[0] = 0.0f;
	for (char c : content) {
		mCharacters.push_back(FontMap::GetCharacterMapping()[c]);
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
