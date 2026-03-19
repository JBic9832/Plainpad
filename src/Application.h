#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Buffers/TextFile.h"

class Application {
public:
    Application();
    ~Application();

    void Run();


private:
    glm::ivec2 mCursorPos;
    std::shared_ptr<TextFile> mTextFile;

    void processInput();
};