#pragma once
#include <string>
#include <list>

// Use an edit buffer then when editing is done copy the contents into the lines buffer
class TextFile {
public:
    TextFile();
    ~TextFile();

    // Modify an existing line
    void EditLine(size_t position, const std::string& text);
    // Insert a new line 
    void InsertLine(size_t position, const std::string& text);
    std::list<std::string>::iterator GetLineIterator(size_t position);
    std::list<std::string> GetLines() const;

private:
    std::list<std::string> mLines;

};