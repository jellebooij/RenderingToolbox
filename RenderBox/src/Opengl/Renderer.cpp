#include "Renderer.h"


namespace Rb {

	Renderer::Renderer()
	{

	}

	void Renderer::Draw(const Mesh& mesh, const Shader& shader, const Texture& texture, const Mat4& transform)
	{
		mesh.Bind();
		texture.Bind();
		shader.Bind();

		shader.setMat4("transform", transform);

		glDrawArrays(GL_TRIANGLES, 0, mesh.vertCount);
	}

}
