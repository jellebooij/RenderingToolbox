#pragma once
#include <iostream>
#include "Events/Event.h"
#include "Events/InputEvents.h"

namespace Rb {

	class RB_API Input {

	public:

		friend class Application;

		bool OnKey(KeyEvent & e);
		bool OnMouseMove(MouseMovementEvent & e);
		bool OnMouseButton(MouseButtonEvent & e);

		static bool GetKey(unsigned int key);
		static bool GetMouseButton(unsigned int button);
		static Vec2 GetMousePosition();
		static Vec2 GetMousePositionRelative();

		static float GetHorizontal();
		static float GetVertical();

	private:
		void Update();

	};

}
