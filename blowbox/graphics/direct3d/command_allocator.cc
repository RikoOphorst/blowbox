#include "command_allocator.h"

#include "../../graphics/direct3d/device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		CommandAllocator::CommandAllocator(const D3D12_COMMAND_LIST_TYPE& type, ID3D12Device* device) :
			command_allocator_(nullptr)
		{
			BB_CHECK(device->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator_)));
		}

		//------------------------------------------------------------------------------------------------------
		CommandAllocator::~CommandAllocator()
		{
			BB_GUARANTEE_RELEASE(command_allocator_);
		}

		//------------------------------------------------------------------------------------------------------
		CommandAllocator* CommandAllocator::Create(const D3D12_COMMAND_LIST_TYPE& type, Device* device)
		{
			return new CommandAllocator(type, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12CommandAllocator* CommandAllocator::Get()
		{
			return command_allocator_;
		}
	}
}