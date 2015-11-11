#include "renderer.h"

#include "../../util/macros.h"
#include "../../window/window.h"
#include "../../graphics/direct3d/device.h"
#include "../../graphics/direct3d/swap_chain.h"
#include "../../graphics/direct3d/command_allocator.h"
#include "../../graphics/direct3d/command_list.h"
#include "../../graphics/direct3d/command_queue.h"
#include "../../graphics/direct3d/render_target.h"
#include "../../graphics/direct3d/descriptor_heap.h"
#include "../../graphics/direct3d/root_signature.h"
#include "../../graphics/direct3d/vertex.h"
#include "../../graphics/direct3d/vertex_buffer.h"
#include "../../graphics/direct3d/pipeline_state.h"
#include "../../graphics/direct3d/shader.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		Renderer::Renderer() :
			window_(nullptr)
		{
			
		}

		//------------------------------------------------------------------------------------------------------
		Renderer::~Renderer()
		{
			BB_SAFE_DELETE(window_);
			BB_SAFE_DELETE(device_);
			BB_SAFE_DELETE(swap_chain_);
			BB_SAFE_DELETE(command_queue_);
			BB_SAFE_DELETE(command_allocator_);
			BB_SAFE_DELETE(command_list_);
			BB_SAFE_DELETE(frame_heap_);
			BB_SAFE_DELETE(pipeline_state_);
			BB_SAFE_DELETE(root_signature_);
			BB_SAFE_DELETE(shader_);
			BB_GUARANTEE_RELEASE(back_buffers_[0]);
			BB_GUARANTEE_RELEASE(back_buffers_[1]);
			BB_GUARANTEE_RELEASE(frame_fence_);
			BB_SAFE_DELETE(triangle_);
		}

		//------------------------------------------------------------------------------------------------------
		Renderer* Renderer::Create()
		{
			return new Renderer();
		}

		//------------------------------------------------------------------------------------------------------
		void Renderer::Initialise()
		{
			BB_ASSERT_NOTNULL(window_, "A window has to be set in order to initialise the renderer. Use Renderer::SetWindow() to set a window.");
			
			ID3D12Debug* debug_controller;
			if (D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)) == S_OK)
			{
				debug_controller->EnableDebugLayer();
			}
			
			device_ = Device::Create(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0);

			viewport_.TopLeftX = 0;
			viewport_.TopLeftY = 0;
			viewport_.Width = static_cast<float>(window_->GetWidth());
			viewport_.Height = static_cast<float>(window_->GetHeight());
			viewport_.MinDepth = 0.0f;
			viewport_.MaxDepth = 1.0f;

			scissor_rect_.left = 0;
			scissor_rect_.top = 0;
			scissor_rect_.right = window_->GetWidth();
			scissor_rect_.bottom = window_->GetHeight();

			D3D12_COMMAND_QUEUE_DESC cq_desc = {};
			cq_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cq_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			command_queue_ = CommandQueue::Create(cq_desc, device_);

			DXGI_SWAP_CHAIN_DESC sc_desc = {};
			sc_desc.BufferCount = 2;
			sc_desc.BufferDesc.Width = window_->GetWidth();
			sc_desc.BufferDesc.Height = window_->GetHeight();
			sc_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sc_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			sc_desc.OutputWindow = window_->GetWindowHandle();
			sc_desc.SampleDesc.Count = 1;
			sc_desc.Windowed = TRUE;
			swap_chain_ = SwapChain::Create(sc_desc, command_queue_);

			frame_index_ = swap_chain_->Get()->GetCurrentBackBufferIndex();

			D3D12_DESCRIPTOR_HEAP_DESC dh_desc = {};
			dh_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			dh_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			dh_desc.NumDescriptors = 2;
			frame_heap_ = DescriptorHeap::Create(dh_desc, device_);

			CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle = frame_heap_->GetCPUHandle();
			for (int i = 0; i < 2; i++)
			{
				BB_CHECK(swap_chain_->Get()->GetBuffer(i, IID_PPV_ARGS(&back_buffers_[i])));
				device_->Get()->CreateRenderTargetView(back_buffers_[i], nullptr, rtv_handle);
				rtv_handle.Offset(frame_heap_->GetSize());
			}

			command_allocator_ = CommandAllocator::Create(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT, device_);

			CD3DX12_DESCRIPTOR_RANGE ranges[1];
			ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

			CD3DX12_ROOT_PARAMETER root_parameters[1];
			root_parameters[0].InitAsDescriptorTable(1, &ranges[0], D3D12_SHADER_VISIBILITY_PIXEL);

			D3D12_STATIC_SAMPLER_DESC sampler_desc = {};
			sampler_desc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			sampler_desc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			sampler_desc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			sampler_desc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			sampler_desc.MipLODBias = 0;
			sampler_desc.MaxAnisotropy = 0;
			sampler_desc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			sampler_desc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			sampler_desc.MinLOD = 0.0f;
			sampler_desc.MaxLOD = D3D12_FLOAT32_MAX;
			sampler_desc.ShaderRegister = 0;
			sampler_desc.RegisterSpace = 0;
			sampler_desc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

			CD3DX12_ROOT_SIGNATURE_DESC rs_desc;
			rs_desc.Init(_countof(root_parameters), root_parameters, 1, &sampler_desc, D3D12_ROOT_SIGNATURE_FLAGS::D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

			root_signature_ = RootSignature::Create(rs_desc, device_);

			shader_ = Shader::Create("E:\\Projects\\blowbox\\blowbox\\shaders\\shaders.hlsl", BB_SHADER_TYPE_PIXEL_SHADER | BB_SHADER_TYPE_VERTEX_SHADER);

			D3D12_INPUT_ELEMENT_DESC input_element_descs[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};

			BB_CREATE_PSO_DESC(main_pso_desc, input_element_descs, root_signature_);
			main_pso_desc.VS = shader_->GetVertexShader();
			main_pso_desc.PS = shader_->GetPixelShader();
			pipeline_state_ = PipelineState::Create(main_pso_desc, device_);

			command_list_ = CommandList::Create(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_, pipeline_state_, device_);

			BB_CHECK(command_list_->Get()->Close());

			std::vector<Vertex> verts = {
				{ { 0.0f, 0.25f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
				{ { 0.25f, -0.25f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
				{ { -0.25f, -0.25f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
			};

			triangle_ = VertexBuffer::Create(verts, device_);

			device_->Get()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&frame_fence_));
			frame_fence_value_ = 1;

			frame_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (frame_event_ == nullptr)
			{
				BB_CHECK(HRESULT_FROM_WIN32(GetLastError()));
			}

			WaitForFrame();
		}
		
		//------------------------------------------------------------------------------------------------------
		void Renderer::SetWindow(Window* window)
		{
			window_ = window;
		}
		
		//------------------------------------------------------------------------------------------------------
		void Renderer::Draw()
		{
			command_allocator_->Get()->Reset();
			command_list_->Get()->Reset(command_allocator_->Get(), pipeline_state_->Get());

			command_list_->Get()->SetGraphicsRootSignature(root_signature_->Get());
			command_list_->Get()->RSSetViewports(1, &viewport_);
			command_list_->Get()->RSSetScissorRects(1, &scissor_rect_);

			command_list_->Get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(back_buffers_[frame_index_], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

			CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(frame_heap_->Get()->GetCPUDescriptorHandleForHeapStart(), frame_index_, frame_heap_->GetSize());
			command_list_->Get()->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

			// Record commands.
			const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
			command_list_->Get()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
			command_list_->Get()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			command_list_->Get()->IASetVertexBuffers(0, 1, &triangle_->GetView());
			command_list_->Get()->DrawInstanced(3, 1, 0, 0);

			// Indicate that the back buffer will now be used to present.
			command_list_->Get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(back_buffers_[frame_index_], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

			command_list_->Get()->Close();

			// Execute the command list.
			ID3D12CommandList* ppCommandLists[] = { command_list_->Get() };
			command_queue_->Get()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

			// Present the frame.
			BB_CHECK(swap_chain_->Get()->Present(1, 0));

			WaitForFrame();
		}
		
		//------------------------------------------------------------------------------------------------------
		void Renderer::WaitForFrame()
		{
			// WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
			// This is code implemented as such for simplicity. More advanced samples 
			// illustrate how to use fences for efficient resource usage.

			// Signal and increment the fence value.
			const UINT64 fence = frame_fence_value_;
			BB_CHECK(command_queue_->Get()->Signal(frame_fence_, fence));
			frame_fence_value_++;

			// Wait until the previous frame is finished.
			if (frame_fence_->GetCompletedValue() < fence)
			{
				BB_CHECK(frame_fence_->SetEventOnCompletion(fence, frame_event_));
				WaitForSingleObject(frame_event_, INFINITE);
			}

			frame_index_ = swap_chain_->Get()->GetCurrentBackBufferIndex();
		}
	}
}