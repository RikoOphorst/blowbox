#include "descriptor_heap.h"

#include "../../graphics/direct3d/device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		DescriptorHeap::DescriptorHeap(D3D12_DESCRIPTOR_HEAP_DESC& desc, ID3D12Device* device) :
			heap_(nullptr)
		{
			BB_CHECK(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap_)));
			size_ = device->GetDescriptorHandleIncrementSize(desc.Type);
			handle_ = heap_->GetCPUDescriptorHandleForHeapStart();
		}

		//------------------------------------------------------------------------------------------------------
		DescriptorHeap::~DescriptorHeap()
		{
			BB_GUARANTEE_RELEASE(heap_);
		}

		//------------------------------------------------------------------------------------------------------
		DescriptorHeap* DescriptorHeap::Create(D3D12_DESCRIPTOR_HEAP_DESC& desc, Device* device)
		{
			return new DescriptorHeap(desc, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12DescriptorHeap* DescriptorHeap::Get()
		{
			return heap_;
		}

		//------------------------------------------------------------------------------------------------------
		const unsigned int& DescriptorHeap::GetSize()
		{
			return size_;
		}
		
		//------------------------------------------------------------------------------------------------------
		CD3DX12_CPU_DESCRIPTOR_HANDLE& DescriptorHeap::GetCPUHandle()
		{
			return handle_;
		}
	}
}