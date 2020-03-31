#pragma once
#include <string>

namespace Rb {

	class Texture {
	public:
		Texture(std::string path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }

	private:
		unsigned int id;
		std::string path;

		int width, height, numChannels;
	};

}