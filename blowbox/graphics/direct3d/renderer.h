#pragma once

#include "../../graphics/direct3d/direct3d.h"

#include <vector>

namespace blowbox
{
	class Window;
	class GameObject;

	namespace direct3d
	{
		class Camera;
		class CommandAllocator;
		class CommandList;
		class CommandQueue;
		class DescriptorHeap;
		class Device;
		class PipelineState;
		class RootSignature;
		class SwapChain;
		class IndexedVertexBuffer;
		class Shader;
		class ConstantBuffer;
		
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
			* @param[in] window (Window*) the window the renderer should use
			*/
			void Initialise(Window* window);

			/**
			* @brief Set this renderer's window output target
			* @param[in] window (Window*) the window
			*/
			void SetWindow(Window* window);

			/**
			* @brief Set this renderer's camera
			* @param[in] camera (Camera*) the camera
			*/
			void SetCamera(Camera* camera);

			Device* GetDevice();

			void Draw(const std::vector<GameObject*>& game_objects);

			void WaitForFrame();
		private:
			Window* window_; //<! The output window of this renderer

			D3D12_VIEWPORT viewport_; //<! The viewport of the application
			D3D12_RECT scissor_rect_; //<! The scissor rect of the application

			Camera* camera_;
			CommandAllocator* command_allocator_; //<! The command allocator that is used to allocate lists
			CommandList* command_list_;
			CommandQueue* command_queue_;
			DescriptorHeap* frame_heap_;
			DescriptorHeap* constant_buffer_heap_;
			ConstantBuffer* constant_buffer_;
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
		};
	}
}