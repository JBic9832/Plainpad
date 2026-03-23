#pragma once

#include "EventListener.h"
#include "Event.h"
#include <vector>
#include <memory>
#include <unordered_map>

class EventSystem {
public:
	void Subscribe(const std::string& eventType, EventListener::Callback callback);
	void Notify(const Event& event);

private:
	std::unordered_map<std::string, std::vector<std::shared_ptr<EventListener>>> m_Subscribers;
};
