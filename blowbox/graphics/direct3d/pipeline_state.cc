#include "pipeline_state.h"

#include "../../graphics/direct3d/device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		PipelineState::PipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, ID3D12Device* device) :
			pipeline_state_(nullptr)
		{
			BB_CHECK(device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pipeline_state_)));
		}

		//------------------------------------------------------------------------------------------------------
		PipelineState::~PipelineState()
		{
			BB_SAFE_RELEASE(pipeline_state_);
		}

		//------------------------------------------------------------------------------------------------------
		PipelineState* PipelineState::Create(D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, Device* device)
		{
			return new PipelineState(desc, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12PipelineState* PipelineState::Get()
		{
			return pipeline_state_;
		}
	}
}