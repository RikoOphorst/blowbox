#pragma once

#include "../core/memory/memory_object.h"
#include "../graphics/direct3d.h"

using namespace blowbox::memory;

namespace blowbox
{
	class Window;

	class Renderer : public MObject
	{
	public:
		static Renderer* Create(Allocator* allocator);

		Renderer(Allocator* allocator);
		~Renderer();

		void Startup(Window* output_window);
		
		void CreateDevice();
		void CreateFence();
		void FindDescriptorSizes();
		void CreateCommandObjects();
		void CheckMsaaLevels();
		void CreateSwapChain();
		void CreateRtvAndDsvHeaps();
		void CreateRenderTargetViews();
		void CreateDepthStencilView();
		void SetViewport();
		void SetScissorRect();

		void Update();

		void FlushCommandQueue();
		ID3D12Resource* GetCurrentBackBuffer() const;
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
		D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

	private:
		UINT rtv_descriptor_size_;
		UINT dsv_descriptor_size_;
		UINT cbv_srv_descriptor_size_;

		IDXGIFactory4* factory_;
		ID3D12Device* device_;

		ID3D12Fence* fence_;
		UINT fence_value_;

		ID3D12CommandQueue* command_queue_;
		ID3D12CommandAllocator* command_allocator_;
		ID3D12GraphicsCommandList* command_list_;

		UINT buffer_width_;
		UINT buffer_height_;
		DXGI_FORMAT buffer_format_;
		static const UINT buffer_count_ = 2;
		UINT current_back_buffer_;
		ID3D12Resource* buffers_[buffer_count_];

		HWND main_window_handle_;

		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS multisample_quality_levels_;

		IDXGISwapChain* swap_chain_;

		ID3D12DescriptorHeap* rtv_heap_;
		ID3D12DescriptorHeap* dsv_heap_;

		DXGI_FORMAT dsv_format_;
		ID3D12Resource* dsv_buffer_;
	};
}