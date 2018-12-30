#pragma once
#include "Application/Core.h"
#include <chrono>

namespace Rb {

	class RB_API Time {
	public:
		friend class Application;

		Time();
		static float GetDeltaTime();

	private:

		void Update();
	};

}