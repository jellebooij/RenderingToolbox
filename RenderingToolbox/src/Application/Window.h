#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "Math/Vec4.h"
#include "Events/Event.h"
#include <functional>

class Window {

public:
	Window(const char *name, int width, int height);
	~Window();

	using EventCallback = std::function<void(Event&)>;

	bool Create();
	void Update() const;
	void Clear() const;

	bool isClosed();
	
	void SetClearColor(Vec4 color) const;
	void SetEventCallback(EventCallback callback) { data.callback = callback; }
	
	GLFWwindow* window;

	

private:

	const char* name;
	int width, height;

	struct WindowData{

		EventCallback callback;

	};

	WindowData data;
	
};