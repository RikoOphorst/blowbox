#include "shape_helper.h"

#include "../graphics/direct3d/vertex.h"
#include "../graphics/direct3d/vertex_buffer.h"

namespace blowbox
{
	namespace util
	{
		//------------------------------------------------------------------------------------------------------
		Shape ShapeHelper::CreateQuad()
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			D3D12_PRIMITIVE_TOPOLOGY topology;

			return Shape(vertices, indices, topology);
		}
	}
}