#pragma once

#ifdef PLATFORM_WINDOWS

extern Rb::Application* Rb::CreateApplication();

int main(int argc, char* argb) {
	auto app = Rb::CreateApplication();
	app->Run();
	delete app;
}
#endif