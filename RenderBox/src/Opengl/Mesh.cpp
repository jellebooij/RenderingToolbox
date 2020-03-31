#include "Mesh.h"
#include "GL/glew.h"
#include "Debug.h"

namespace Rb {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices) {

		vertCount = vertices.size();

		GLCALL(glGenVertexArrays(1, &vao));
		GLCALL(glCreateBuffers(1, &vbo));
		GLCALL(glGenBuffers(1, &ebo));
		
		GLCALL(glBindVertexArray(vao));
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	
		GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));
		
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() *  sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
	
		GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
		GLCALL(glEnableVertexAttribArray(0));
		
		GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))));
		GLCALL(glEnableVertexAttribArray(1));
	}

	Mesh::Mesh(std::vector<Vertex> vertices)
	{
		ebo = 0;

		vertCount = vertices.size();

		GLCALL(glGenVertexArrays(1, &vao));
		GLCALL(GLCALL(glCreateBuffers(1, &vbo)));

		GLCALL(glBindVertexArray(vao));
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

		GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));

		GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
		GLCALL(glEnableVertexAttribArray(0));

		GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))));
		GLCALL(glEnableVertexAttribArray(1));
	}

	Mesh::~Mesh()
	{
		GLCALL(glDeleteVertexArrays(1, &vao));
		GLCALL(glDeleteBuffers(1, &vbo));
		GLCALL(glDeleteBuffers(1, &ebo));
	}

	void Mesh::Bind() const
	{
		GLCALL(glBindVertexArray(vao));
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	}

}


