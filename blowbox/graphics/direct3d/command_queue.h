#pragma once

#include "direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class Device;
		
		/**
		* @class blowbox::direct3d::CommandQueue
		* @author Riko Ophorst
		* @brief Queues up all commands
		*/
		class CommandQueue
		{
		public:
			/**
			* @brief Default constructor
			* @param[in] desc (const D3D12_COMMAND_QUEUE_DESC&) the descriptor for the command queue
			* @param[in] device (ID3D12Device*) the device that is going to use this command queue
			*/
			CommandQueue(D3D12_COMMAND_QUEUE_DESC& desc, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~CommandQueue();

			/**
			* @brief Creates an instance of this class
			* @param[in] desc (const D3D12_COMMAND_QUEUE_DESC&) the descriptor for the command queue
			* @param[in] device (Device*) the device that is going to use this command queue
			*/
			static CommandQueue* Create(D3D12_COMMAND_QUEUE_DESC& desc, Device* device);

			/**
			* @brief Get a pointer to the actual command queue
			*/
			ID3D12CommandQueue* Get();
		private:
			ID3D12CommandQueue* command_queue_; //<! The command queue
		};
	}
}