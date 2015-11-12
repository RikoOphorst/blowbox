#pragma once

#include "../../graphics/direct3d/vertex_buffer.h"

#include <vector>

namespace blowbox
{
	namespace direct3d
	{
		struct Vertex;
		class Device;
		
		class IndexedVertexBuffer : public VertexBuffer
		{
		public:
			IndexedVertexBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology, ID3D12Device* device);
			~IndexedVertexBuffer();

			static IndexedVertexBuffer* Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology, Device* device);

			ID3D12Resource* GetIndexBuffer();
			const D3D12_INDEX_BUFFER_VIEW& GetIndexView();
			const D3D12_PRIMITIVE_TOPOLOGY& GetTopology();
		private:
			ID3D12Resource* index_buffer_;
			D3D12_INDEX_BUFFER_VIEW index_buffer_view_;
			std::vector<unsigned int> indices_;
			D3D12_PRIMITIVE_TOPOLOGY topology_;
		};
	}
}