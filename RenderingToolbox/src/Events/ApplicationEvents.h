#pragma once
#include "Event.h"

class OnWindowCloseEvent : public Event {
public:
	OnWindowCloseEvent() : Event(EventTypes::WindowClose) {}

	static EventTypes GetStaticType() { return EventTypes::WindowClose; }
};