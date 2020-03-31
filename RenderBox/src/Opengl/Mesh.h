#pragma once
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Math/Mat4.h"
#include <Vector>

namespace Rb {

	struct Vertex {

		Vertex(const Vec3& position, const Vec2& uv) : 
			position(position), uv(uv) {}

		Vec3 position;
		Vec2 uv;
	};

	class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		Mesh(std::vector<Vertex> vertices);

		int vertCount;

		~Mesh();

		void Bind() const;
		void Unbind() const;


	private:
		unsigned int vao, vbo, ebo;
		bool usesIndexBuffer;


	};

}