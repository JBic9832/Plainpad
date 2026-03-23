#include "InputManager.h"
#include "EventType.h"

#include <iostream>

std::unordered_map<int, KeyState> InputManager::s_Keys;
MousePosition InputManager::s_MousePos;

InputManager::InputManager(EventSystem& eventSystem) : m_EventSystem { eventSystem } {
	m_EventSystem.Subscribe("KeyPressed", [this](const Event& e) {
		this->keyPressed(e);
	});

	m_EventSystem.Subscribe("KeyReleased", [this](const Event& e) {
		this->keyReleased(e);
	});

	m_EventSystem.Subscribe("MouseMoved", [this](const Event& e) {
		this->mouseMoved(e);
	});
}

void InputManager::keyPressed(const Event& e) {
	auto keyEvent = dynamic_cast<const KeyPressedEvent*>(&e);

	if (keyEvent) {
		auto& state = s_Keys[keyEvent->_keyCode];
		if (!state.held) {
			state.pressed = true;
		}
		state.held = true;
	}
}

void InputManager::keyReleased(const Event& e) {
	auto keyEvent = dynamic_cast<const KeyReleasedEvent*>(&e);

	if (keyEvent) {
		auto& state = s_Keys[keyEvent->_keyCode];
		state.held = false;
		state.released = true;
	}
}

void InputManager::mouseMoved(const Event& e) {
	auto mouseEvent = dynamic_cast<const MouseMovedEvent*>(&e);

	if (mouseEvent) {
		s_MousePos.x = mouseEvent->_x;
		s_MousePos.y = mouseEvent->_y;
	}
}

bool InputManager::GetKey(int key) {
	return s_Keys[key].held;
}

bool InputManager::GetKeyDown(int key) {
	return s_Keys[key].pressed;
}

bool InputManager::GetKeyUp(int key) {
	return s_Keys[key].released;
}

MousePosition InputManager::GetMousePosition() {
	return s_MousePos;
}

void InputManager::EndFrame() {
	for (auto& [key, state] : s_Keys) {
		state.pressed = false;
		state.released = false;
	}
}
