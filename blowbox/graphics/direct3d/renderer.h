#pragma once

#include "../../graphics/direct3d/direct3d.h"

namespace blowbox
{
	class Window;
	
	namespace direct3d
	{
		class CommandAllocator;
		class CommandList;
		class CommandQueue;
		class DescriptorHeap;
		class Device;
		class PipelineState;
		class RootSignature;
		class SwapChain;
		class VertexBuffer;
		class Shader;
		
		/**
		* @class blowbox::direct3d::Renderer
		* @author Riko Ophorst
		* @brief A Direct3D renderer
		*/
		class Renderer
		{
		public:
			/**
			* @brief Default Renderer constructor
			*/
			Renderer();

			/**
			* @brief Default Renderer destructor
			*/
			~Renderer();

			/**
			* @brief Factory method for instancing of Renderer object
			*/
			static Renderer* Create();

			/**
			* @brief Initialises the renderer
			*/
			void Initialise();

			/**
			* @brief Set this renderer's window output target
			* @param[in] window (Window*) the window
			*/
			void SetWindow(Window* window);

			void Draw();

			void WaitForFrame();
		private:
			Window* window_; //<! The output window of this renderer

			D3D12_VIEWPORT viewport_;
			D3D12_RECT scissor_rect_;

			CommandAllocator* command_allocator_;
			CommandList* command_list_;
			CommandQueue* command_queue_;
			DescriptorHeap* frame_heap_;
			Device* device_;
			PipelineState* pipeline_state_;
			RootSignature* root_signature_;
			SwapChain* swap_chain_;
			ID3D12Resource* back_buffers_[2];
			Shader* shader_;

			ID3D12Fence* frame_fence_;
			HANDLE frame_event_;
			UINT64 frame_fence_value_;
			UINT frame_index_;

			VertexBuffer* triangle_;
		};
	}
}