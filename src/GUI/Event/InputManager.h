#pragma once

#include "Event.h"
#include "EventSystem.h"

#include <unordered_map>

struct MousePosition {
	int x;
	int y;
};

struct KeyState {
	bool held = false;
	bool pressed = false;
	bool released = false;
};

class InputManager {
public:
	InputManager(EventSystem& eventSystem);

	// Was the key pressed
	static bool GetKeyDown(int key);
	// Is the key being held
	static bool GetKey(int key);
	static bool GetKeyUp(int key);
	static MousePosition GetMousePosition();

	void EndFrame();

private:
	void keyPressed(const Event& e);
	void keyReleased(const Event& e);
	void mouseMoved(const Event& e);

private:
	EventSystem& m_EventSystem;

private:
	static std::unordered_map<int, KeyState> s_Keys;
	static MousePosition s_MousePos;

};
