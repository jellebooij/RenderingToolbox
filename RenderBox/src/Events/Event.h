#pragma once
#include "Application/Core.h"

namespace Rb {

	class RB_API Event {
	public:

		friend class EventDispatcher;

		enum EventTypes {
			WindowClose, KeyEvent, MouseMovementEvent, MouseButton
		};

		Event(EventTypes type) : type(type) {}

	protected:
		EventTypes type;

		EventTypes GetType() { return type; }
		bool handled;

	};

}