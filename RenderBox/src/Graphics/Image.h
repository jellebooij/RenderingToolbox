#pragma once
#include <string>
#include "vendor/stb_image.h"
#include "Math/Vec4.h"
#include "Math/Vec2.h"

namespace Rb {

	class Image {
	public:
		Image(const std::string& path);
		~Image();

		Vec4 GetPixel(Vec2 pixel);
		Vec2 GetSize();

	private:
		unsigned char* data;
		int width, height, numChannels;

	};

}