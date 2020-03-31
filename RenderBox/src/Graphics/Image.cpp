#include "Image.h"


namespace Rb {

	Image::Image(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		data = stbi_load(path.c_str(), &width, &height, &numChannels, 4);
	}

	Image::~Image()
	{
		stbi_image_free(data);
	}

	Vec4 Image::GetPixel(Vec2 pixel)
	{

		int x = pixel.x;
		int y = pixel.y;

		if (x > width - 1) 
			return Vec4(0, 0, 0, 255);
		
		if (x < 0) 
			return Vec4(0, 0, 0, 255);
		
		if (y > height - 1)
			return Vec4(0, 0, 0, 255);
		
		if (y < 0) 
			return Vec4(0, 0, 0, 255);
		
		unsigned char* xoffset = data + (x + height * y) * 4;

		Vec4 color;

		color.x = (int)xoffset[0];
		color.y = (int)xoffset[1];
		color.z = (int)xoffset[2];
		color.w = (int)xoffset[3];


		return color;
	}

	Vec2 Image::GetSize()
	{
		return Vec2(width,height);
	}

}
