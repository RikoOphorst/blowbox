#include "indexed_vertex_buffer.h"

#include "../../graphics/direct3d/device.h"
#include "../../graphics/direct3d/vertex.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		IndexedVertexBuffer::IndexedVertexBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology, ID3D12Device* device) :
			VertexBuffer(vertices, device),
			index_buffer_(nullptr),
			indices_(indices),
			topology_(topology)
		{
			BB_CHECK(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(indices_.size()),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&index_buffer_)
				));

			UINT8* pVertexDataBegin;
			CD3DX12_RANGE readRange(0, 0);
			BB_CHECK(index_buffer_->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
			memcpy(pVertexDataBegin, &indices_[0], indices_.size() * sizeof(unsigned int));
			index_buffer_->Unmap(0, nullptr);

			index_buffer_view_.BufferLocation = index_buffer_->GetGPUVirtualAddress();
			index_buffer_view_.Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
			index_buffer_view_.SizeInBytes = static_cast<UINT>(indices_.size() * sizeof(unsigned int));
		}

		//------------------------------------------------------------------------------------------------------
		IndexedVertexBuffer::~IndexedVertexBuffer()
		{
			BB_GUARANTEE_RELEASE(index_buffer_);
		}

		//------------------------------------------------------------------------------------------------------
		IndexedVertexBuffer* IndexedVertexBuffer::Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology, Device* device)
		{
			return new IndexedVertexBuffer(vertices, indices, topology, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12Resource* IndexedVertexBuffer::GetIndexBuffer()
		{
			return index_buffer_;
		}

		//------------------------------------------------------------------------------------------------------
		const D3D12_INDEX_BUFFER_VIEW& IndexedVertexBuffer::GetIndexView()
		{
			return index_buffer_view_;
		}
		
		//------------------------------------------------------------------------------------------------------
		const D3D12_PRIMITIVE_TOPOLOGY& IndexedVertexBuffer::GetTopology()
		{
			return topology_;
		}
	}
}