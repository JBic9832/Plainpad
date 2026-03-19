#pragma once

#include <list>

#include "FontMap.h"

class Line {
public:
	Line();
	Line(const std::string& content);

	std::list<Character> GetCharacters() const;

	void AddCharacter(Character c);
	void InsertCharacter(Character c, std::list<Character>::iterator position);
	std::list<Character>::iterator GetIteratorAtPosition(size_t position);

private:
	std::list<Character> mCharacters;

};
