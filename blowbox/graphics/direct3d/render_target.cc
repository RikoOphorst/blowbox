#include "render_target.h"

#include "../../graphics/direct3d/device.h"
#include "../../graphics/direct3d/descriptor_heap.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		RenderTarget::RenderTarget(ID3D12Resource* resource, D3D12_RENDER_TARGET_VIEW_DESC& desc, DescriptorHeap* descriptor_heap, ID3D12Device* device) :
			render_target_view_(nullptr)
		{
			device->CreateRenderTargetView(resource, &desc, descriptor_heap->GetCPUHandle());
		}

		//------------------------------------------------------------------------------------------------------
		RenderTarget::~RenderTarget()
		{
			BB_GUARANTEE_RELEASE(render_target_view_);
		}

		//------------------------------------------------------------------------------------------------------
		RenderTarget* RenderTarget::Create(ID3D12Resource* resource, D3D12_RENDER_TARGET_VIEW_DESC& desc, DescriptorHeap* descriptor_heap, Device* device)
		{
			return new RenderTarget(resource, desc, descriptor_heap, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12Resource* RenderTarget::Get()
		{
			return render_target_view_;
		}
	}
}