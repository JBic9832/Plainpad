#pragma once
#include <string>
#include <list>
#include <mutex>

#include "Line.h"

// Use an edit buffer then when editing is done copy the contents into the lines buffer
class TextFile {
public:
    TextFile();
    ~TextFile();

    // Modify an existing line
    void EditLine(size_t position, const std::string& text);
    // Insert a new line 
    void InsertLine(size_t position, const std::string& text);
    std::list<Line>::iterator GetLineIterator(size_t position);
    std::list<Line> GetLines() const;
	Line GetActiveLineBuffer() const;
	void PullLineToEditBuffer(std::list<Line>::iterator target);

private:
	void flushEditBuffer();

private:
	mutable std::mutex mMutex;
    std::list<Line> mLines;
	std::list<Line>::iterator mActiveLine;
	Line mEditBuffer;
	bool mEditBufferDirty = false;

};
