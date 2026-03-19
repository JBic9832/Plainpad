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
	std::unique_lock<std::mutex> ul {mMutex};
    *it = text;
	ul.unlock();
}

void TextFile::InsertLine(size_t position, const std::string& text) {
    if (position >= mLines.size()) {
        mLines.push_back(text);
        return;
    }

    auto it = GetLineIterator(position);
	++it;
	std::unique_lock<std::mutex> ul {mMutex};
    mLines.insert(it, text);
	ul.unlock(); 
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
	std::lock_guard<std::mutex> lock(mMutex);
	std::list<std::string> lines = mLines;
    return lines;
}

void TextFile::PullLineToEditBuffer(std::list<std::string>::iterator target) {
	// Flush before pulling a new line
	flushEditBuffer();

	mActiveLine = target;
	mEditBuffer = *mActiveLine;
	mEditBufferDirty = false;
}

void TextFile::flushEditBuffer() {
	if (mEditBufferDirty) {
		*mActiveLine = mEditBuffer;
		mEditBufferDirty = false;
	}

}























