#pragma once

#include "../../graphics/direct3d/direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class Device;
		
		/**
		* @class blowbox::direct3d::CommandAllocator
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class CommandAllocator
		{
		public:
			/**
			* @brief Default constructor
			*/
			CommandAllocator(const D3D12_COMMAND_LIST_TYPE& type, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~CommandAllocator();

			/**
			* @brief Creates an instance of this class
			*/
			static CommandAllocator* Create(const D3D12_COMMAND_LIST_TYPE& type, Device* device);

			ID3D12CommandAllocator* Get();
		private:
			ID3D12CommandAllocator* command_allocator_;
		};
	}
}