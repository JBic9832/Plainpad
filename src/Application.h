#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Buffers/TextFile.h"

enum ApplicationMode {
	NORMAL = 0,
	INSERT
};

class Application {
public:
    Application();
    ~Application();

    void Run();


private:
    glm::ivec2 mCursorPos;
    std::shared_ptr<TextFile> mTextFile;
	ApplicationMode mAppMode;

    void processInput();
	void drawCursor();
};
