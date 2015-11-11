#pragma once

#include "../../graphics/direct3d/direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class Device;
		
		/**
		* @class blowbox::direct3d::DescriptorHeap
		* @author Riko Ophorst
		* @brief A descriptor heap for describing resources to the GPU
		*/
		class DescriptorHeap
		{
		public:
			/**
			* @brief Default constructor
			*/
			DescriptorHeap(D3D12_DESCRIPTOR_HEAP_DESC& desc, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~DescriptorHeap();

			/**
			* @brief Creates an instance of this class
			* @param[in] desc (D3D12_DESCRIPTOR_HEAP_DESC&) the descriptor for the descriptor heap (dun dun duuuun..)
			* @param[in] device (Device*) the device this descriptor heap belongs to
			*/
			static DescriptorHeap* Create(D3D12_DESCRIPTOR_HEAP_DESC& desc, Device* device);
			
			/**
			* @brief Get a pointer to the actual descriptor heap
			*/
			ID3D12DescriptorHeap* Get();

			/**
			* @brief Get the size of each element in the heap
			*/
			const unsigned int& GetSize();

			CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCPUHandle();
		private:
			CD3DX12_CPU_DESCRIPTOR_HANDLE handle_;
			ID3D12DescriptorHeap* heap_; //<! The actual heap
			unsigned int size_; //<! The size of each element in the heap
		};
	}
}