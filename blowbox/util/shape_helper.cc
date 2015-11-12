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
			std::vector<Vertex> vertices = { 
				{ { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
				{ { -0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
				{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
				{ { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } 
			};
			std::vector<unsigned int> indices = { 0, 1, 2, 3 };
			D3D12_PRIMITIVE_TOPOLOGY topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

			return Shape(vertices, indices, topology);
		}
	}
}