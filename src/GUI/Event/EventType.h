#pragma once

#include "Event.h"

struct KeyPressedEvent : public Event {
	int _keyCode;
	KeyPressedEvent(int code) 
		: _keyCode(code) {}
	std::string GetName() const override { return "KeyPressed"; }
};

struct KeyReleasedEvent: public Event {
	int _keyCode;
	KeyReleasedEvent(int code) 
		: _keyCode(code) {}
	std::string GetName() const override { return "KeyReleased"; }
};

struct WindowResizedEvent : public Event {
	int _width, _height;
	WindowResizedEvent(int w, int h)
		: _width{ w }
		, _height { h } {}

	std::string GetName() const override { return "WindowResized"; }
};

struct MouseMovedEvent : public Event {
	int _x, _y;
	MouseMovedEvent(int x, int y)
		: _x { x }
		, _y { y } {}
	
	std::string GetName() const override { return "MouseMoved"; }
};
