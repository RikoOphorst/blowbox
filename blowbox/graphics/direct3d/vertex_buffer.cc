#include "vertex_buffer.h"

#include "../../graphics/direct3d/vertex.h"
#include "../../graphics/direct3d/device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		VertexBuffer::VertexBuffer(const std::vector<Vertex> verts, ID3D12Device* device) :
			vert_buffer_(nullptr),
			verts_(verts)
		{
			BB_CHECK(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(verts_.size()),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&vert_buffer_)
			));

			UINT8* pVertexDataBegin;
			CD3DX12_RANGE readRange(0, 0);
			BB_CHECK(vert_buffer_->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
			memcpy(pVertexDataBegin, &verts_[0], verts_.size() * sizeof(Vertex));
			vert_buffer_->Unmap(0, nullptr);
			
			vert_buffer_view_.BufferLocation = vert_buffer_->GetGPUVirtualAddress();
			vert_buffer_view_.StrideInBytes = sizeof(Vertex);
			vert_buffer_view_.SizeInBytes = static_cast<UINT>(verts_.size()) * sizeof(Vertex);
		}

		//------------------------------------------------------------------------------------------------------
		VertexBuffer::~VertexBuffer()
		{
			BB_SAFE_RELEASE(vert_buffer_);
		}

		//------------------------------------------------------------------------------------------------------
		VertexBuffer* VertexBuffer::Create(const std::vector<Vertex> verts, Device* device)
		{
			return new VertexBuffer(verts, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12Resource* VertexBuffer::Get()
		{
			return vert_buffer_;
		}
		
		//------------------------------------------------------------------------------------------------------
		const D3D12_VERTEX_BUFFER_VIEW & VertexBuffer::GetView()
		{
			return vert_buffer_view_;
		}
	}
}