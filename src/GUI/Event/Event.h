#pragma once

#include <string>

class Event {
public:
	virtual ~Event() = default;
	virtual std::string GetName() const = 0;
};
