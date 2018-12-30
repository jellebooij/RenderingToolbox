#pragma once
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Utility/Time.h"
#include "Input.h"
#include "Core.h"
#include <memory>

namespace Rb {

	class RB_API Application {

	public:

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);


	private:
		bool OnWindowClose(OnWindowCloseEvent& e);


		std::unique_ptr<Window> window;
		std::shared_ptr<Input> input;
		std::shared_ptr<Time> time;

		bool running = true;

	};

	//Define in cl
	Application* CreateApplication();

}