#include "swap_chain.h"

#include "../../graphics/direct3d/command_queue.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		SwapChain::SwapChain(DXGI_SWAP_CHAIN_DESC& desc, ID3D12CommandQueue* command_queue) :
			swap_chain_(nullptr)
		{
			IDXGIFactory* factory = nullptr;
			BB_CHECK(CreateDXGIFactory(IID_PPV_ARGS(&factory)));

			IDXGISwapChain* temp_swap_chain = nullptr;
			BB_CHECK(factory->CreateSwapChain(command_queue, &desc, &temp_swap_chain));
			swap_chain_ = static_cast<IDXGISwapChain3*>(temp_swap_chain);

			BB_GUARANTEE_RELEASE(factory);
		}

		//------------------------------------------------------------------------------------------------------
		SwapChain::~SwapChain()
		{
			BB_GUARANTEE_RELEASE(swap_chain_);
		}

		//------------------------------------------------------------------------------------------------------
		SwapChain* SwapChain::Create(DXGI_SWAP_CHAIN_DESC& desc, CommandQueue* command_queue)
		{
			return new SwapChain(desc, command_queue->Get());
		}

		//------------------------------------------------------------------------------------------------------
		IDXGISwapChain3* SwapChain::Get()
		{
			return swap_chain_;
		}
	}
}