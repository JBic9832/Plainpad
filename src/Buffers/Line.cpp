#include "Line.h"

Line::Line() {}
Line::Line(const std::string& content) {
	for (char c : content) {
		mCharacters.push_back(FontMap::GetCharacterMapping()[c]);
	}
}

std::list<Character> Line::GetCharacters() const {
	return mCharacters;
}
