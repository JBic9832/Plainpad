#include "TextFile.h"
#include <stdexcept>
#include <iostream>

TextFile::TextFile() : mActiveLine {mLines.begin()} { }
TextFile::~TextFile() { }

void TextFile::EditLine(size_t position, const std::string& text) {
    if (position >= mLines.size()) {
        std::cout << "That line number DNE." << std::endl;
        return;
    }

    auto it = GetLineIterator(position);
	Line l{text};
	std::unique_lock<std::mutex> ul {mMutex};
    **it = l;
	ul.unlock();
}

void TextFile::InsertLine(size_t position, const std::string& text) {
	Line l {text};
    if (position >= mLines.size()) {
        mLines.push_back(std::make_shared<Line>(l));
        return;
    }

    auto it = GetLineIterator(position);
	++it;
	std::unique_lock<std::mutex> ul {mMutex};
    mLines.insert(it, std::make_shared<Line>(l));
	ul.unlock(); 
}

LineStructure_t::iterator TextFile::GetLineIterator(size_t position) {
    if (position >= mLines.size()) {
        throw std::out_of_range("Line index out of range!");
    }

    auto it = mLines.begin();
    std::advance(it, position);
    return it;
}

LineStructure_t TextFile::GetLines() const {
	std::lock_guard<std::mutex> lock(mMutex);
	std::list<std::shared_ptr<Line>> lines = mLines;
    return lines;
}






















