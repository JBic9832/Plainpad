#include "Application.h"

Application::Application() : mAppMode {ApplicationMode::NORMAL}, mCursorPos {0, 0} {
	mTextFile = std::make_shared<TextFile>();
}
