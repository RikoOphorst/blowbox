#pragma once

#include "../../graphics/direct3d/direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class Device;
		class CommandAllocator;
		class PipelineState;

		/**
		* @class blowbox::direct3d::CommandList
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class CommandList
		{
		public:
			/**
			* @brief Default constructor
			*/
			CommandList(const D3D12_COMMAND_LIST_TYPE& type, ID3D12CommandAllocator* allocator, ID3D12PipelineState* pipeline_state, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~CommandList();

			/**
			* @brief Creates an instance of this class
			*/
			static CommandList* Create(const D3D12_COMMAND_LIST_TYPE& type, CommandAllocator* allocator, PipelineState* pipeline_state, Device* device);

			ID3D12GraphicsCommandList* Get();
		private:
			ID3D12GraphicsCommandList* command_list_;
		};
	}
}