#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "Math/Vec4.h"

class Window {

public:
	Window(const char *name, int width, int height);
	~Window();

	bool Create();
	void Update() const;
	void Clear() const;

	bool isClosed();
	
	void SetClearColor(Vec4 color) const;
	
	GLFWwindow* window;

	

private:

	const char* name;
	int width, height;
	
};