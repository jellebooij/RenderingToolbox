#include "World.h"
#include <cmath>
#include <iostream>



namespace Rb {

	Vec4 empty = Vec4(0, 0, 0, 255);

	World::World(const std::string& image, float nodeSize) : nodeSize(nodeSize)
	{
		Image img(image);
		Vec2 imgSize = img.GetSize();

		for (int x = 0; x < imgSize.x; x++)
		{

			std::vector<Node> temp;

			for (int y = 0; y < imgSize.y; y++)
			{
				Node n;

				if (img.GetPixel(Vec2(x, y)) == empty) {
					n.walkable = false;
					n.type = Types::Empty;
				}
				else {
					n.walkable = true;
					n.type = Types::Normal;
				}
				

				temp.push_back(n);
			}

			nodes.push_back(temp);

		}

		size = nodes.size();

	}

	Node World::GetNode(Vec2 position) const
	{
		int x = position.x;
		int y = position.y;

		Node n;

		n.walkable = false;
		n.type = Types::Empty;

		if (x < 0)
			return n;

		if (x > size - 1)
			return n;

		if (y < 0)
			return n;

		if (y > size - 1)
			return n;

		return nodes[x][y];
	}

	Node World::GetNodeWorld(Vec3 position) const
	{
		float x = std::floor((position.x / (float)nodeSize));
		float y = std::floor((position.z / (float)nodeSize));

		if (x > size - 1)
			x = size;
		if (x < 0)
			x = 0;
		if (y > size - 1)
			y = size;
		if (y < 0)
			y = 0;

		//std::cout << x << "  " << y  << "    "<< position.x << "  " << position.z << "Nodesize: " << nodeSize << std::endl;

		return nodes[x][y];
	}

	bool World::IsPositionFree(Vec3 position) const
	{
		return GetNodeWorld(position).walkable;
	}

	int World::GetSize() const
	{
		return size;
	}

	float World::GetNodeSize() const
	{
		return nodeSize;
	}

}
