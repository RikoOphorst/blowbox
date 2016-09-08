#pragma once

#include "../core/memory/memory_object.h"
#include "../graphics/direct3d.h"

using namespace blowbox::memory;

namespace blowbox
{
	class Window;

	/**
	* @class blowbox::Renderer
	* @author Riko Ophorst
	* @brief DirectX 12 renderer
	*/
	class Renderer : public MObject
	{
	public:
		/**
		* @brief Create an instance of a Renderer
		* @param[in]	allocator		The allocator to use to allocate this renderer
		*/
		static Renderer* Create(Allocator* allocator);

		/**
		* @brief Renderer constructor
		* @param[in]	allocator		The allocator to used to allocate this renderer
		*/
		Renderer(Allocator* allocator);

		/**
		* @brief Renderer destructor
		*/
		~Renderer();

		/**
		* @brief Starts up the renderer
		*/
		void Startup(Window* output_window);

		/**
		* @brief Updates the renderer
		*/
		void Update();

		/**
		* @brief Informs the renderer to flush the entire command queue
		*/
		void FlushCommandQueue();

		/**
		* @brief Gets the current back buffer resource
		*/
		ID3D12Resource* GetCurrentBackBuffer() const;

		/**
		* @brief Gets the current back buffer view
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;

		/**
		* @brief Gets the depth stencil view
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

	private:
		/**
		* @brief Creates the Direct3D device
		*/
		void CreateDevice();

		/**
		* @brief Creates fence for flushing command queue
		*/
		void CreateFence();

		/**
		* @brief Finds and caches the descriptor sizes of all types
		*/
		void FindDescriptorSizes();

		/**
		* @brief Creates the command objects (queue, allocator, list)
		*/
		void CreateCommandObjects();

		/**
		* @brief Checks for MSAA levels & support
		*/
		void CheckMsaaLevels();

		/**
		* @brief Creates the swap chain
		*/
		void CreateSwapChain();

		/**
		* @brief Creates the resource heaps for the render target views & depth/stencil views
		*/
		void CreateRtvAndDsvHeaps();

		/**
		* @brief Creates the actual render target views
		*/
		void CreateRenderTargetViews();

		/**
		* @brief Creates the depth/stencil view
		*/
		void CreateDepthStencilView();

		/**
		* @brief Sets the viewport
		*/
		void SetViewport();

		/**
		* @brief Sets the scissor rect
		*/
		void SetScissorRect();

	private:
		UINT rtv_descriptor_size_; //!< The size of a RTV descriptor
		UINT dsv_descriptor_size_; //!< The size of a DSV descriptor
		UINT cbv_srv_descriptor_size_; //!< The size of a CBV / SRV / UAV descriptor

		IDXGIFactory4* factory_; //!< The factory used to create DX objects
		ID3D12Device* device_; //!< The actual d3d12 device

		ID3D12Fence* fence_; //!< Fence used for flushing command queue
		UINT fence_value_; //!< Fence value used for flushing command queue

		ID3D12CommandQueue* command_queue_; //!< The command queue to the GPU
		ID3D12CommandAllocator* command_allocator_; //!< The allocator used to allocate commands for the GPU
		ID3D12GraphicsCommandList* command_list_; //!< The list of commands that gets put in the command queue

		UINT buffer_width_; //!< Width of the back buffer
		UINT buffer_height_; //!< Height of the back buffer
		DXGI_FORMAT buffer_format_; //!< Format of the back buffer
		static const UINT buffer_count_ = 2; //!< Amount of back buffer (2 for double buffering, 3 for triple buffering, etc)
		UINT current_back_buffer_; //!< The current in-use back buffer
		ID3D12Resource* buffers_[buffer_count_]; //!< All back buffers

		HWND main_window_handle_; //!< The main window used to render to

		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS multisample_quality_levels_; //!< The available multisample quality levels

		IDXGISwapChain* swap_chain_; //!< The swap chain used for page flipping

		ID3D12DescriptorHeap* rtv_heap_; //!< Heap to store descriptors of the render target views
		ID3D12DescriptorHeap* dsv_heap_; //!< Heap to store descriptors of the depth/stencil views

		DXGI_FORMAT dsv_format_; //!< Depth/stencil view format
		ID3D12Resource* dsv_buffer_; //!< Depth/stencil buffer
	};
}