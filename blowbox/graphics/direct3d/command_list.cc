#include "command_list.h"

#include "../../graphics/direct3d/device.h"
#include "../../graphics/direct3d/command_allocator.h"
#include "../../graphics/direct3d/pipeline_state.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		CommandList::CommandList(const D3D12_COMMAND_LIST_TYPE& type, ID3D12CommandAllocator* allocator, ID3D12PipelineState* pipeline_state, ID3D12Device* device) :
			command_list_(nullptr)
		{
			BB_CHECK(device->CreateCommandList(0, type, allocator, pipeline_state, IID_PPV_ARGS(&command_list_)));
		}

		//------------------------------------------------------------------------------------------------------
		CommandList::~CommandList()
		{
			BB_GUARANTEE_RELEASE(command_list_);
		}

		//------------------------------------------------------------------------------------------------------
		CommandList* CommandList::Create(const D3D12_COMMAND_LIST_TYPE& type, CommandAllocator* allocator, PipelineState* pipeline_state, Device* device)
		{
			return new CommandList(type, allocator->Get(), pipeline_state == nullptr ? nullptr : pipeline_state->Get(), device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12GraphicsCommandList* CommandList::Get()
		{
			return command_list_;
		}
	}
}