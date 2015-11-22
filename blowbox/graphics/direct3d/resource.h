#pragma once

#include "../../graphics/direct3d/direct3d.h"

#define BB_GPU_VIRTUAL_ADDRESS_NULL 0ull
#define BB_GPU_VIRTUAL_ADDRESS_UNKNOWN ~0ull

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::Resource
		* @author Riko Ophorst
		* @brief A GPU resource, can be practically anything
		*/
		class Resource
		{
		public:
			Resource() :
				gpu_virtual_address_(BB_GPU_VIRTUAL_ADDRESS_NULL),
				usage_state_(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON),
				transitioning_state_((D3D12_RESOURCE_STATES)-1)
			{};

			Resource(ID3D12Resource* resource, D3D12_RESOURCE_STATES current_state) :
				resource_(resource),
				usage_state_(current_state),
				transitioning_state_((D3D12_RESOURCE_STATES)-1),
				gpu_virtual_address_(BB_GPU_VIRTUAL_ADDRESS_NULL)
			{};

			~Resource() 
			{
				Destroy();
			};

			static Resource* Create() 
			{ 
				return new Resource(); 
			};
			
			static Resource* Create(ID3D12Resource* resource, D3D12_RESOURCE_STATES current_state) 
			{ 
				return new Resource(); 
			}

			void Destroy() { BB_SAFE_RELEASE(resource_); };

			ID3D12Resource* operator->() { return resource_; };
			const ID3D12Resource* operator->() const { return resource_; };

			void SetResource(ID3D12Resource* resource) { resource_ = resource; };
			ID3D12Resource* GetResource() { return resource_; };
			const ID3D12Resource* GetResource() const { return resource_; };

			void SetGPUVirtualAddress(const D3D12_GPU_VIRTUAL_ADDRESS& gpu_virtual_address) { gpu_virtual_address_ = gpu_virtual_address; };
			D3D12_GPU_VIRTUAL_ADDRESS& GetGPUVirtualAddress() { return gpu_virtual_address_; }
			const D3D12_GPU_VIRTUAL_ADDRESS& GetGPUVirtualAddress() const { return gpu_virtual_address_; }

			void SetUsageState(const D3D12_RESOURCE_STATES& usage_state) { usage_state_ = usage_state; };
			D3D12_RESOURCE_STATES& GetUsageState() { return usage_state_; }
			const D3D12_RESOURCE_STATES& GetUsageState() const { return usage_state_; }

			void SetTransitioningState(const D3D12_RESOURCE_STATES& transitioning_state) { transitioning_state_ = transitioning_state; };
			D3D12_RESOURCE_STATES& GetTransitioningState() { return transitioning_state_; }
			const D3D12_RESOURCE_STATES& GetTransitioningState() const { return transitioning_state_; }
		private:
			ID3D12Resource* resource_;
			D3D12_RESOURCE_STATES usage_state_;
			D3D12_RESOURCE_STATES transitioning_state_;
			D3D12_GPU_VIRTUAL_ADDRESS gpu_virtual_address_;
		};
	}
}