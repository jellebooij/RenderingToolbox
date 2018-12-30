#pragma once
#include "Event.h"

namespace Rb {

	class RB_API OnWindowCloseEvent : public Event {
	public:
		OnWindowCloseEvent() : Event(EventTypes::WindowClose) {}

		static EventTypes GetStaticType() { return EventTypes::WindowClose; }
	};
}