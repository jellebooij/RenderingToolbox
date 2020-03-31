#pragma once
#include <gl\glew.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Math\Mat4.h"

namespace Rb {

	class Shader {

	public:
		Shader(std::string path);
		void Bind() const;

		unsigned int ID;
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setMat4(const std::string &name, const Mat4& value) const;

	};

}