#pragma once

#include "Opengl/Mesh.h"
#include "Opengl/Shader.h"
#include "Opengl/Texture.h"

namespace Rb {

	class Renderer {
	public:
		Renderer();

		void Draw(const Mesh& mesh, const Shader& shader, const Texture& texture, const Mat4& transform);

	private:

	};

}