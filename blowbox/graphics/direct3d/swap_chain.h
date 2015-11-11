#pragma once

#include "direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class CommandQueue;

		/**
		* @class blowbox::direct3d::SwapChain
		* @author Riko Ophorst
		* @brief The swapchains handles the switching of buffers which are outputted to the screen
		*/
		class SwapChain
		{
		public:
			/**
			* @brief Default constructor
			*/
			SwapChain(DXGI_SWAP_CHAIN_DESC& desc, ID3D12CommandQueue* command_queue);

			/**
			* @brief Default destructor
			*/
			~SwapChain();

			/**
			* @brief Creates an instance of this class
			* @param[in] desc (DXGI_SWAP_CHAIN_DESC&) the descriptor for the swap chain
			* @param[in] command_queue (CommandQueue*) the command queue
			*/
			static SwapChain* Create(DXGI_SWAP_CHAIN_DESC& desc, CommandQueue* command_queue);

			/**
			* @brief Get a pointer to the actual swapchain
			*/
			IDXGISwapChain3* Get();
		private:
			IDXGISwapChain3* swap_chain_; //<! The swapchain
		};
	}
}