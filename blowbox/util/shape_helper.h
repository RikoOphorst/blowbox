#pragma once

#include "../graphics/direct3d/direct3d.h"

#include <vector>

namespace blowbox
{
	namespace direct3d
	{
		struct Vertex;
	}
	
	using namespace direct3d;

	namespace util
	{
		struct Shape
		{
			Shape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology) : vertices(vertices), indices(indices), topology(topology) {}
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			D3D12_PRIMITIVE_TOPOLOGY topology;
		};
		
		class ShapeHelper
		{
		public:
			static Shape CreateQuad();
			static Shape CreateTriangle();
			static Shape CreateCircle();
			static Shape CreateBox();
			static Shape CreatePyramid();
			static Shape CreateSphere();
			static Shape CreateCylinder();
		};
	}
}