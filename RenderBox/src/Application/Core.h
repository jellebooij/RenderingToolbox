#pragma once

#ifdef PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define RB_API __declspec(dllexport)
	#else
		#define RB_API __declspec(dllimport)
	#endif
#endif