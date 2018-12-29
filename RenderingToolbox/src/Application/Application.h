#pragma once
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Utility/Time.h"
#include "Input.h"
#include <memory>


class Application {

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