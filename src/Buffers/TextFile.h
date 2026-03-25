#pragma once
#include <string>
#include <list>
#include <mutex>
#include <memory>

#include "Line.h"
#include "Types.h"


// Use an edit buffer then when editing is done copy the contents into the lines buffer
class TextFile {
public:
    TextFile();
    ~TextFile();

    // Modify an existing line
    void EditLine(size_t position, const std::string& text);
    // Insert a new line 
    void InsertLine(size_t position, const std::string& text);
    LineStructure_t::iterator GetLineIterator(size_t position);
    LineStructure_t GetLines() const;
	size_t GetActiveLineBuffer();
	void PullLineToEditBuffer(size_t target);

private:
	void flushEditBuffer();

private:
	mutable std::mutex mMutex;
    LineStructure_t mLines;
	LineStructure_t::iterator mActiveLine;
	Line mEditBuffer;
	bool mEditBufferDirty = false;

};
