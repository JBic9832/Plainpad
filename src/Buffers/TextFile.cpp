#include "TextFile.h"
#include <stdexcept>
#include <iostream>

TextFile::TextFile() { }
TextFile::~TextFile() { }

void TextFile::EditLine(size_t position, const std::string& text) {
    if (position >= mLines.size()) {
        std::cout << "That line number DNE." << std::endl;
        return;
    }

    auto it = GetLineIterator(position);
    *it = text;
}

void TextFile::InsertLine(size_t position, const std::string& text) {
    if (position >= mLines.size()) {
        mLines.push_back(text);
        return;
    }

    auto it = GetLineIterator(position);
    mLines.insert(it, text);
}

std::list<std::string>::iterator TextFile::GetLineIterator(size_t position) {
    if (position >= mLines.size()) {
        throw std::out_of_range("Line index out of range!");
    }

    auto it = mLines.begin();
    std::advance(it, position);
    return it;
}

std::list<std::string> TextFile::GetLines() const {
    return mLines;
}