#pragma once
#include "Event.h"
#include "Math/Vec2.h"

namespace Rb {

	class RB_API KeyEvent : public Event {
	public:

		enum KeyAction {
			KeyRelease,
			KeyPress
		};


		KeyEvent(int key, KeyAction action) : Event(EventTypes::KeyEvent), action(action), key(key) {}

		KeyAction action;
		int key;

		static EventTypes GetStaticType() { return EventTypes::KeyEvent; }
	};
	class MouseMovementEvent : public Event {
	public:
		MouseMovementEvent(Vec2 movement) : movement(movement), Event(EventTypes::MouseMovementEvent) {}

		Vec2 movement;

		static EventTypes GetStaticType() { return EventTypes::MouseMovementEvent; }
	};
	class MouseButtonEvent : public Event {
	public:

		enum Actions {
			ButtonPressed, ButtonReleased
		};

		MouseButtonEvent(int button, Actions action) : button(button), action(action), Event(EventTypes::MouseButton) {}

		int button;
		Actions action;


		static EventTypes GetStaticType() { return EventTypes::MouseButton; }
	};

}