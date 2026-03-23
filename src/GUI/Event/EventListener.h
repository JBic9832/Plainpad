#pragma once

#include <functional>
#include "Event.h"

class EventListener {
public:
	using Callback = std::function<void(const Event& e)>;

	EventListener(const Callback& callback);

	void OnEvent(const Event& event);

private:
	Callback m_Callback;
};
