#include "Application.h"
#include "Buffers/FontMap.h"
#include "GUI/Rendering/TextRenderer.h"

#include <iostream>

Application::Application() : 
mAppMode {ApplicationMode::NORMAL}, 
mCursorPos {0, 0}, 
mRunning {false}, 
mAppWindow {"Plainpad", 800, 600}, 
mTextRenderer {glm::ortho(0.0f, 800.0f, 0.0f, 600.0f)},
mTextFile {std::make_shared<TextFile>()} { 
	std::cout << "Test" << std::endl;
	FontMap::GenerateFontMapping(RESOURCES_PATH "fonts/Arial.TTF", 24);
}

Application::~Application() {}

void Application::Run() {
	std::cout << "Test" << std::endl;
	mActiveLine = mTextFile->GetLineIterator(0);

    Shader cursorShader{RESOURCES_PATH "shaders/cursor.vs", RESOURCES_PATH "shaders/cursor.fs"};
	mCursor.SetCursorHeight(FontMap::GetGlyphHeight());
    cursorShader.Bind();
    cursorShader.setUniformMatrix4f("projection", mProjection);

	mRunning = true;
	while (!mAppWindow.ShouldClose()) {
		mAppWindow.BeginFrame();
		mRunning = !mAppWindow.ShouldClose();

		mTextRenderer.RenderFile(*mTextFile, {0.0f, 0.0f, 0.0f}, mAppWindow);

		mCursor.Draw(mCursorPos, mActiveLine, 800.0f);
		
		mAppWindow.EndFrame();
		mAppWindow.PollEvents();
	}

}
