#pragma once

#include <glm/glm.hpp>

#include "GUI/Rendering/Cursor.h"
#include "GUI/Rendering/TextRenderer.h"
#include "GUI/Window/Window.h"
#include "GUI/Event/EventSystem.h"
#include "GUI/Event/InputManager.h"

#include <memory.h>
#include "Buffers/TextFile.h"

enum ApplicationMode {
	NORMAL = 0,
	INSERT
};

class Application {
public:
    Application(EventSystem& e);
    ~Application();

    void Run();


private:
    Window mAppWindow;
    glm::ivec2 mCursorPos;
	ApplicationMode mAppMode;
    Cursor mCursor;
    TextRenderer mTextRenderer;
    bool mRunning;
	InputManager mInputManager;
	std::shared_ptr<TextFile> mTextFile;
    
    glm::mat4 mProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    void processInput();
	void drawCursor();
};
