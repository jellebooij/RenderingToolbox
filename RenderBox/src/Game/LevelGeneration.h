#pragma once
#include <vector>
#include <Opengl\Mesh.h>
#include <string>
#include "World.h"


namespace Rb {

	class LevelGenerator {
	public:

		enum Side {
			Up, Down, Left, Right, Floor,Roof
		};

		LevelGenerator(int size);
		void AddPlane(std::vector<Vertex>* vertexBuffer, Side s, int x, int y, int z, int texX, int texY, float size);
		void GenerateLevel(const World& world, std::vector<Vertex>* vertexBuffer);

	private:
		int levelSize;

	};

}