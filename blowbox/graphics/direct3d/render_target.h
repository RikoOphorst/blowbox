#pragma once

#include "../../graphics/direct3d/direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class DescriptorHeap;
		class Device;

		/**
		* @class blowbox::direct3d::RenderTarget
		* @author Riko Ophorst
		* @brief A render target
		*/
		class RenderTarget
		{
		public:
			/**
			* @brief Default constructor
			*/
			RenderTarget(ID3D12Resource* resource, D3D12_RENDER_TARGET_VIEW_DESC& desc, DescriptorHeap* descriptor_heap, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~RenderTarget();

			/**
			* @brief Creates an instance of this class
			*/
			static RenderTarget* Create(ID3D12Resource* resource, D3D12_RENDER_TARGET_VIEW_DESC& desc, DescriptorHeap* descriptor_heap, Device* device);

			ID3D12Resource* Get();
		private:
			ID3D12Resource* render_target_view_; //<! The view of the render target
		};
	}
}