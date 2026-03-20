#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Buffers/TextFile.h"
#include "GUI/Rendering/Cursor.h"
#include "GUI/Rendering/TextRenderer.h"
#include "GUI/Window/Window.h"

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
    std::list<Line>::iterator mActiveLine;
    Cursor mCursor;
    Window mAppWindow;
    TextRenderer mTextRenderer;
    bool mRunning;
    
    glm::mat4 mProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    void processInput();
	void drawCursor();
};
