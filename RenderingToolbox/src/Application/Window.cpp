#include "Window.h"
#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"

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
	glfwSwapInterval(0);
	glfwSetWindowUserPointer(window, &data);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action) {

			case(GLFW_PRESS):
			{
				KeyEvent e(key, KeyEvent::KeyAction::KeyPress);
				data.callback(e);
				break;
			}

			case(GLFW_RELEASE):
			{
				KeyEvent e(key, KeyEvent::KeyAction::KeyRelease);
				data.callback(e);
				break;
			}

			default: 
			{
				break;
			}
		}
		
	});
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		OnWindowCloseEvent e;
		data.callback(e);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		MouseMovementEvent e(Vec2((float)xpos,(float)ypos));
		data.callback(e);
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		switch (action) {

		case(GLFW_PRESS):
		{
			MouseButtonEvent e(button, MouseButtonEvent::Actions::ButtonPressed);
			data.callback(e);
			break;
		}

		case(GLFW_RELEASE):
		{
			MouseButtonEvent e(button, MouseButtonEvent::Actions::ButtonReleased);
			data.callback(e);
			break;
		}

		default:
		{
			break;
		}
		}
	});


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





