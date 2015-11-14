#include "constant_buffer.h"

#include "../../graphics/direct3d/device.h"
#include "../../graphics/direct3d/descriptor_heap.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		ConstantBuffer::ConstantBuffer(ID3D12DescriptorHeap* heap, ID3D12Device* device) :
			constant_buffer_(nullptr)
		{
			ZeroMemory(&constant_buffer_data_, sizeof(constant_buffer_data_));

			BB_CHECK(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(1024 * 64),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&constant_buffer_)
			));

			D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
			desc.BufferLocation = constant_buffer_->GetGPUVirtualAddress();
			desc.SizeInBytes = (sizeof(BB_CONSTANT_BUFFER_DATA) + 255) & ~255; // Constant buffer size MUST be 256 byte aligned
			device->CreateConstantBufferView(&desc, heap->GetCPUDescriptorHandleForHeapStart());

			CD3DX12_RANGE read_range(0, 0);
			BB_CHECK(constant_buffer_->Map(0, &read_range, reinterpret_cast<void**>(&gpu_data_pointer_)));
			memcpy(gpu_data_pointer_, &constant_buffer_data_, sizeof(constant_buffer_data_));
		}

		//------------------------------------------------------------------------------------------------------
		ConstantBuffer::~ConstantBuffer()
		{

		}

		//------------------------------------------------------------------------------------------------------
		ConstantBuffer* ConstantBuffer::Create(DescriptorHeap* heap, Device* device)
		{
			return new ConstantBuffer(heap->Get(), device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12Resource* ConstantBuffer::Get()
		{
			return constant_buffer_;
		}

		//------------------------------------------------------------------------------------------------------
		const BB_CONSTANT_BUFFER_DATA& ConstantBuffer::GetData() const
		{
			return constant_buffer_data_;
		}

		//------------------------------------------------------------------------------------------------------
		BB_CONSTANT_BUFFER_DATA& ConstantBuffer::GetData()
		{
			return constant_buffer_data_;
		}
		
		//------------------------------------------------------------------------------------------------------
		uint8_t* ConstantBuffer::GetGPUDataPointer()
		{
			return gpu_data_pointer_;
		}
	}
}