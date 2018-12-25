#include "Window.h"

Window::Window(const char * name, int width, int height) :
	name(name), width(width), height(height) {}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::SetClearColor(Vec4 color) const
{
	glClearColor(color.x, color.y, color.z, color.w);
}

bool Window::Create()
{
	if (!glfwInit()) 
	{
		//TODO: Log Error
		return false;
	}
		
	window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (!window)
	{
		//TODO: Log Error
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);


	glewInit();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void Window::Update() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isClosed()
{
	return glfwWindowShouldClose(window) == 1;
}




//Callbacks
