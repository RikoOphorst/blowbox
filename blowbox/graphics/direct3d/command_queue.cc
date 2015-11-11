#include "command_queue.h"

#include "../../graphics/direct3d/device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		CommandQueue::CommandQueue(D3D12_COMMAND_QUEUE_DESC& desc, ID3D12Device* device) :
			command_queue_(nullptr)
		{
			BB_CHECK(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue_)));
		}

		//------------------------------------------------------------------------------------------------------
		CommandQueue::~CommandQueue()
		{
			BB_SAFE_RELEASE(command_queue_);
		}

		//------------------------------------------------------------------------------------------------------
		CommandQueue* CommandQueue::Create(D3D12_COMMAND_QUEUE_DESC& desc, Device* device)
		{
			return new CommandQueue(desc, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12CommandQueue* CommandQueue::Get()
		{
			return command_queue_;
		}
	}
}