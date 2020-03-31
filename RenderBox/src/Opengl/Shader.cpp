#include "Shader.h"
#include "Debug.h"

namespace Rb {

	enum shaderType { vertex, fragment };

	struct ShaderSources {
		std::string VertexSource;
		std::string FramentSource;
	};
	unsigned int compileShader(const char* source, shaderType type) {

		unsigned int ShaderType = (type == shaderType::vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

		unsigned int shader;
		shader = glCreateShader(ShaderType);
		GLCALL(glShaderSource(shader, 1, &source, NULL));
		GLCALL(glCompileShader(shader));


		/* Error handeling */
		int success;
		char infoLog[512];
		GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
		if (!success)
		{
			GLCALL(glGetShaderInfoLog(shader, 512, NULL, infoLog));
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return shader;
	}
	ShaderSources ParseShader(const std::string& filepath) {
		std::ifstream stream(filepath);


		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1

		};
		ShaderType type = ShaderType::NONE;


		std::string line;
		std::stringstream ss[2];
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
			else {
				ss[(int)type] << line << '\n';
			}
		}

		if (type != ShaderType::FRAGMENT) {
			std::cout << "COULD NOT FIND ALL SHADER TYPES" << std::endl << std::endl;
		}

		return { ss[0].str(), ss[1].str() };
	}


	Shader::Shader(std::string path)
	{

		ShaderSources sources = ParseShader(path);

		const char* vertexSource = sources.VertexSource.c_str();
		const char* fragmentSource = sources.FramentSource.c_str();

		unsigned int vertexShader = compileShader(vertexSource, shaderType::vertex);
		unsigned int fragmentShader = compileShader(fragmentSource, shaderType::fragment);


		ID = glCreateProgram();

		GLCALL(glAttachShader(ID, vertexShader));
		GLCALL(glAttachShader(ID, fragmentShader));
		GLCALL(glLinkProgram(ID));

		GLCALL(glUseProgram(ID));

		GLCALL(glDeleteShader(vertexShader));
		GLCALL(glDeleteShader(fragmentShader));

	}

	void Shader::Bind() const
	{
		glUseProgram(ID);
	}

	void Shader::setBool(const std::string & name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string & name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string & name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setMat4(const std::string & name, const Mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value.DataPointer());
	}

}