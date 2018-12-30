#include "Input.h"

namespace Rb {

	bool keyState[1024];
	bool buttonState[32];

	Vec2 currentMousePos;
	Vec2 lastPos;

	Vec2 relativeMousePos;

	bool Input::OnKey(KeyEvent & e)
	{
		if (e.action == KeyEvent::KeyAction::KeyPress) {
			keyState[e.key] = true;
		}

		if (e.action == KeyEvent::KeyAction::KeyRelease) {
			keyState[e.key] = false;
		}

		return false;
	}

	bool Input::OnMouseMove(MouseMovementEvent & e)
	{
		lastPos = currentMousePos;
		currentMousePos = e.movement;
		return true;
	}

	bool Input::OnMouseButton(MouseButtonEvent & e)
	{
		if (e.action == MouseButtonEvent::Actions::ButtonPressed) {
			buttonState[e.button] = true;
		}

		if (e.action == MouseButtonEvent::Actions::ButtonReleased) {
			buttonState[e.button] = false;
		}

		return false;
	}

	bool Input::GetKey(unsigned int key)
	{
		if (key > 1023) {
			key = 1023;
		}

		return keyState[key];
	}

	bool Input::GetMouseButton(unsigned int button)
	{

		if (button > 31) {
			button = 31;
		}

		return buttonState[button];
	}

	Vec2 Input::GetMousePosition()
	{
		return currentMousePos;
	}

	Vec2 Input::GetMousePositionRelative()
	{
		return relativeMousePos;
	}

	float Input::GetHorizontal()
	{
		return (int)keyState[83] - (int)keyState[87];
	}

	float Input::GetVertical()
	{
		return (int)keyState[65] - (int)keyState[68];
	}

	void Input::Update()
	{
		relativeMousePos = currentMousePos - lastPos;
		lastPos = currentMousePos;
	}
}
