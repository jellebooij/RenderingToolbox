#pragma once
#include <string>
#include <vector>
#include "Graphics/Image.h"

#include "Math/Vec2.h"
#include "Math/Vec4.h"

namespace Rb {

	enum Types { Empty, Normal };

	struct Node {

		bool walkable;
		Types type;

	};

	class World {
	public:
		World(const std::string& image, float nodeSize);

		int  GetSize() const;
		float GetNodeSize() const;
		Node GetNode(Vec2 position) const;
		Node GetNodeWorld(Vec3 position) const;
		bool IsPositionFree(Vec3 position) const;


	private:
		std::vector<std::vector<Node>> nodes;
		int size;
		float nodeSize;
	};

}