#pragma once
#include <gl\glew.h>
#include "Application/Core.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

namespace Rb {

	class RB_API glShader {

	public:
		glShader(std::string path);
		void Bind();

		unsigned int ID;
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setMat4(const std::string &name, float value);

	};

}