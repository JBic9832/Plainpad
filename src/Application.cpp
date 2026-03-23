#include <iostream> 

#include "Application.h"
#include "Buffers/FontMap.h"
#include "GUI/Rendering/TextRenderer.h"

Application::Application(EventSystem& e) : 
mAppWindow {"Plainpad", 800, 600, e}, 
mAppMode {ApplicationMode::NORMAL}, 
mCursorPos {0, 0}, 
mTextRenderer {glm::ortho(0.0f, 800.0f, 0.0f, 600.0f)},
mInputManager {e},
mTextFile {std::make_shared<TextFile>()} { 
	
}

Application::~Application() {}

void Application::Run() {
	FontMap::GenerateFontMapping(RESOURCES_PATH "fonts/Arial.TTF", 24);
    Shader cursorShader{RESOURCES_PATH "shaders/cursor.vs", RESOURCES_PATH "shaders/cursor.fs"};
	mCursor.SetCursorHeight(FontMap::GetGlyphHeight() + 4);
    cursorShader.Bind();
    cursorShader.setUniformMatrix4f("projection", mProjection);

	// Test lines
	mTextFile->InsertLine(0, "This is a test for cursor...");
    mTextFile->InsertLine(0, "This is a test for cursor...");
    mTextFile->InsertLine(0, "This is a test for cursor...");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!mAppWindow.ShouldClose()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		mAppWindow.BeginFrame();
		mAppWindow.DrawDecorations();

		mTextRenderer.RenderFile(*mTextFile, {0.0f, 0.0f, 0.0f}, mAppWindow);

		cursorShader.Bind();
		cursorShader.setUniformFloat("time", glfwGetTime());
		mCursor.Draw(mCursorPos, mTextFile->GetLineIterator(mCursorPos.y), mAppWindow.GetHeight());

		if(InputManager::GetKeyDown(GLFW_KEY_RIGHT)) {
			mCursorPos.x += 1;
		}

		if(InputManager::GetKeyDown(GLFW_KEY_LEFT)) {
			mCursorPos.x -= 1;
		}

		if(InputManager::GetKeyDown(GLFW_KEY_UP)) {
			if (!(mCursorPos.y - 1 < 0))
				mCursorPos.y -= 1;
		}

		if(InputManager::GetKeyDown(GLFW_KEY_DOWN)) {
			if(!(mCursorPos.y + 1 > mTextFile->GetLines().size() - 1))
				mCursorPos.y += 1;
		}

		mInputManager.EndFrame();

		mAppWindow.EndFrame();
		mAppWindow.PollEvents();
	}
}
