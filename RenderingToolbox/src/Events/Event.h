#pragma once

class Event {
public:

	friend class EventDispatcher;
	
	enum EventTypes {
		WindowClose, KeyEvent, MouseMovementEvent, MouseButton
	};

	Event(EventTypes type) : type(type) {}

protected:				
	EventTypes type;

	EventTypes GetType(){ return type; }
	bool handled;

};