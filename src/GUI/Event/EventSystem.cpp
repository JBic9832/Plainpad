#include "EventSystem.h"

void EventSystem::Subscribe(const std::string& eventType, EventListener::Callback callback) {
	m_Subscribers[eventType].push_back(std::make_shared<EventListener>(callback));
}

void EventSystem::Notify(const Event& event) {
	auto it = m_Subscribers.find(event.GetName());
	if (it != m_Subscribers.end()) {
		for (auto& subscriber : it->second) {
			subscriber->OnEvent(event);
		}
	}
}
