#include "LevelGeneration.h"
#include "Math/Vec4.h"
#include "Graphics/Image.h"
#include <iostream>


namespace Rb {

	LevelGenerator::LevelGenerator(int size) : levelSize(size)
	{
	}

	void LevelGenerator::AddPlane(std::vector<Vertex>* vertexBuffer, Side s, int x, int y, int z, int texX, int texY, float size)
	{
		const float t = 1.0f / 2.0f;

		float ux = x;
		float uy = y;
		float uz = z;

		float yMin = (16 - (texY + 1)) * t;
		float yMax = (16 - (texY)) * t;
		float xMin = texX * t;
		float xMax = (texX + 1) * t;

		size = size / 2.0f;

		if (s == Side::Left) {
			Vertex left[] = {
				//left							    	 
				Vertex(Vec3(ux - size,  uy + size,  uz + size), Vec2(xMin, yMax)),
				Vertex(Vec3(ux - size,  uy + size,  uz - size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux - size,  uy - size,  uz - size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux - size,  uy - size,  uz - size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux - size,  uy - size,  uz + size), Vec2(xMin, yMin)),
				Vertex(Vec3(ux - size,  uy + size,  uz + size), Vec2(xMin, yMax))
			};
			vertexBuffer->insert(vertexBuffer->end(), &left[0], &left[6]);
		}
		if (s == Side::Right) {
			Vertex right[] = {
				//right							    
				Vertex(Vec3(ux + size,  uy + size, uz + size), Vec2(xMin, yMax)),
				Vertex(Vec3(ux + size,  uy + size, uz - size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux + size,  uy - size, uz - size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux + size,  uy - size, uz - size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux + size,  uy - size, uz + size), Vec2(xMin, yMin)),
				Vertex(Vec3(ux + size,  uy + size, uz + size), Vec2(xMin, yMax))
			};
			vertexBuffer->insert(vertexBuffer->end(), &right[0], &right[6]);
		}
		if (s == Side::Down) {
			Vertex front[] = {
				//front									 
				Vertex(Vec3(ux - size, uy - size,  uz + size), Vec2(xMin, yMin)),
				Vertex(Vec3(ux + size, uy - size,  uz + size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux + size, uy + size,  uz + size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux + size, uy + size,  uz + size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux - size, uy + size,  uz + size), Vec2(xMin, yMax)),
				Vertex(Vec3(ux - size, uy - size,  uz + size), Vec2(xMin, yMin))
			};
			vertexBuffer->insert(vertexBuffer->end(), &front[0], &front[6]);
		}
		if (s == Side::Up) {
			Vertex back[] = {
				//back									 
				Vertex(Vec3(ux - size, uy - size, uz - size), Vec2(xMin, yMin)),
				Vertex(Vec3(ux + size, uy - size, uz - size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux + size, uy + size, uz - size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux + size, uy + size, uz - size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux - size, uy + size, uz - size), Vec2(xMin, yMax)),
				Vertex(Vec3(ux - size, uy - size, uz - size), Vec2(xMin, yMin))
			};
			vertexBuffer->insert(vertexBuffer->end(), &back[0], &back[6]);
		}
		if (s == Side::Roof) {
			Vertex top[] = {
				//top							    	 
				Vertex(Vec3(ux - size,  uy + size,  uz - size), Vec2(xMin, yMax)),
				Vertex(Vec3(ux + size,  uy + size,	uz - size), Vec2(xMax, yMax)),
				Vertex(Vec3(ux + size,  uy + size,	uz + size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux + size,  uy + size,	uz + size), Vec2(xMax, yMin)),
				Vertex(Vec3(ux - size,  uy + size,  uz + size), Vec2(xMin, yMin)),
				Vertex(Vec3(ux - size,  uy + size,  uz - size), Vec2(xMin, yMax))
			};
			vertexBuffer->insert(vertexBuffer->end(), &top[0], &top[6]);
		}
		if (s == Side::Floor) {
			Vertex bottom[] = {
				//bottom						    	 
				Vertex(Vec3(ux - size, uy - size,  uz - size),  Vec2(xMin, yMax)),
				Vertex(Vec3(ux + size, uy - size,  uz - size),  Vec2(xMax, yMax)),
				Vertex(Vec3(ux + size, uy - size,  uz + size),  Vec2(xMax, yMin)),
				Vertex(Vec3(ux + size, uy - size,  uz + size),  Vec2(xMax, yMin)),
				Vertex(Vec3(ux - size, uy - size,  uz + size),  Vec2(xMin, yMin)),
				Vertex(Vec3(ux - size, uy - size,  uz - size),  Vec2(xMin, yMax))
			};
			vertexBuffer->insert(vertexBuffer->end(), &bottom[0], &bottom[6]);
		}
	}
	

	void LevelGenerator::GenerateLevel(const World& world, std::vector<Vertex>* vertexBuffer)
	{

		int size = world.GetSize();
		float nodeSize = world.GetNodeSize();

		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				Node n = world.GetNode(Vec2(x, y));

				if (n.walkable) {

					AddPlane(vertexBuffer, Side::Floor, x * levelSize, 0, y * levelSize,  1, 0, nodeSize);
					AddPlane(vertexBuffer, Side::Roof,  x * levelSize, 0, y * levelSize,  0, 1, nodeSize);

					if (world.GetNode(Vec2(x + 1, y)).type == Types::Empty){
						AddPlane(vertexBuffer, Side::Right, x * levelSize , 0 , y * levelSize, 0, 0, nodeSize);
					}																		   
																							   
					if (world.GetNode(Vec2(x - 1, y)).type == Types::Empty) {
						AddPlane(vertexBuffer, Side::Left,  x * levelSize,  0 , y * levelSize, 0, 0, nodeSize);
					}																		   
																							   
					if (world.GetNode(Vec2(x, y + 1)).type == Types::Empty) {
						AddPlane(vertexBuffer, Side::Down,  x * levelSize, 0 ,  y * levelSize, 0, 0, nodeSize);
					}																		   
																							   
					if (world.GetNode(Vec2(x, y - 1)).type == Types::Empty) {
						AddPlane(vertexBuffer, Side::Up,    x * levelSize, 0,   y * levelSize, 0, 0, nodeSize);
					}

				}

			}
		}
	
	}


}

