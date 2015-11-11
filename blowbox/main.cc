#include "../blowbox/core/blowbox.h"
#include "../blowbox/window/window.h"
#include "../blowbox/graphics/direct3d/renderer.h"
#include "../blowbox/graphics/direct3d/device.h"
#include "../blowbox/graphics/direct3d/swap_chain.h"
#include "../blowbox/graphics/direct3d/command_allocator.h"
#include "../blowbox/graphics/direct3d/command_list.h"
#include "../blowbox/graphics/direct3d/command_queue.h"
#include "../blowbox/graphics/direct3d/render_target.h"
#include "../blowbox/graphics/direct3d/descriptor_heap.h"
#include "../blowbox/graphics/direct3d/root_signature.h"
#include "../blowbox/graphics/direct3d/pipeline_state.h"
#include "../blowbox/graphics/direct3d/vertex.h"
#include "../blowbox/graphics/direct3d/vertex_buffer.h"
#include "../blowbox/core/threading/job_manager.h"
#include "../blowbox/core/threading/job.h"

#include "../blowbox/graphics/direct3d/direct3d.h"

#include <iostream>
#include <chrono>
#include <comdef.h>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace DirectX;

int main(int argc, char** argv)
{
	Blowbox* blowbox = new Blowbox();
	
	Renderer* renderer = Renderer::Create();
	blowbox->SetRenderer(renderer);

	Window* window = Window::MakeWindow("A blowbox game", 1280, 720);
	renderer->SetWindow(window);
	
	renderer->Initialise();

	blowbox->Run();



//	const int width = 1280;
//	const int height = 720;
//	const UINT frame_count = 2;
//
//	D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
//
//	Window* window = Window::MakeWindow("A blowbox game", 1280, 720);
//
//	D3D12_VIEWPORT viewport;
//	D3D12_RECT scissor_rect;
//	IDXGISwapChain3* swap_chain;
//	ID3D12Device* device;
//	ID3D12Resource* render_targets[frame_count];
//	ID3D12CommandAllocator* command_allocator;
//	ID3D12CommandQueue* command_queue;
//	ID3D12RootSignature* root_signature;
//	ID3D12DescriptorHeap* descriptor_heap;
//	ID3D12PipelineState* pipeline_state;
//	ID3D12GraphicsCommandList* command_list;
//	UINT rtv_descriptor_size;
//
//	ID3D12Resource* vertex_buffer;
//	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
//
//	bool use_warp_device = false;
//
//	UINT frame_index;
//	HANDLE fence_event;
//	ID3D12Fence* fence;
//	UINT64 fence_value;
//
//	scissor_rect.left = 0;
//	scissor_rect.top = 0;
//	scissor_rect.right = width;
//	scissor_rect.bottom = height;
//	viewport.TopLeftX = 0;
//	viewport.TopLeftY = 0;
//	viewport.MinDepth = 0.0f;
//	viewport.Width = width;
//	viewport.Height = height;
//	viewport.MaxDepth = 1.0f;
//
//#ifdef _DEBUG
//	ID3D12Debug* debug_controller;
//	if (D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)) == S_OK)
//	{
//		debug_controller->EnableDebugLayer();
//	}
//#endif
//
//	IDXGIFactory4* factory;
//	BB_CHECK(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));
//
//	if (use_warp_device)
//	{
//		IDXGIAdapter* adapter;
//		BB_CHECK(factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));
//
//		BB_CHECK(D3D12CreateDevice(
//			adapter,
//			feature_level,
//			IID_PPV_ARGS(&device)
//		));
//	}
//	else
//	{
//		IDXGIAdapter1* hardware_adapter;
//		GetHardwareAdapter(factory, &hardware_adapter);
//
//		BB_CHECK(D3D12CreateDevice(
//			hardware_adapter,
//			feature_level,
//			IID_PPV_ARGS(&device)
//		));
//	}
//
//	D3D12_COMMAND_QUEUE_DESC queue_desc = {};
//	queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//	queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
//
//	BB_CHECK(device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&command_queue)));
//
//	DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
//	swap_chain_desc.BufferCount = frame_count;
//	swap_chain_desc.BufferDesc.Width = width;
//	swap_chain_desc.BufferDesc.Height = height;
//	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//	swap_chain_desc.OutputWindow = window->GetWindowHandle();
//	swap_chain_desc.SampleDesc.Count = 1;
//	swap_chain_desc.Windowed = TRUE;
//
//	IDXGISwapChain* temp_swap_chain;
//	BB_CHECK(factory->CreateSwapChain(command_queue, &swap_chain_desc, &temp_swap_chain));
//	swap_chain = (IDXGISwapChain3*)temp_swap_chain;
//
//	BB_CHECK(factory->MakeWindowAssociation(window->GetWindowHandle(), DXGI_MWA_NO_ALT_ENTER));
//
//	frame_index = swap_chain->GetCurrentBackBufferIndex();
//
//	{
//		D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
//		rtv_heap_desc.NumDescriptors = frame_count;
//		rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
//		rtv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//		BB_CHECK(device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&descriptor_heap)));
//		
//		rtv_descriptor_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
//	}
//
//	{
//		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(descriptor_heap->GetCPUDescriptorHandleForHeapStart());
//
//		for (UINT n = 0; n < frame_count; n++)
//		{
//			BB_CHECK(swap_chain->GetBuffer(n, IID_PPV_ARGS(&render_targets[n])));
//			device->CreateRenderTargetView(render_targets[n], nullptr, rtv_handle);
//			rtv_handle.Offset(rtv_descriptor_size);
//		}
//	}
//
//	BB_CHECK(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator)));
//
//	{
//		CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc;
//		root_signature_desc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
//
//		ID3DBlob* signature;
//		ID3DBlob* error;
//		BB_CHECK(D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
//		BB_CHECK(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&root_signature)));
//	}
//
//	{
//		ID3DBlob* vertex_shader;
//		ID3DBlob* pixel_shader;
//
//#ifdef _DEBUG
//		UINT compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#else
//		UINT compile_flags = 0;
//#endif
//		
//		BB_CHECK(D3DCompileFromFile(L"E:\\Projects\\blowbox\\blowbox\\shaders\\shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compile_flags, 0, &vertex_shader, nullptr));
//		BB_CHECK(D3DCompileFromFile(L"E:\\Projects\\blowbox\\blowbox\\shaders\\shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compile_flags, 0, &pixel_shader, nullptr));
//
//		D3D12_INPUT_ELEMENT_DESC input_element_descs[] = 
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
//		};
//
//		D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
//		pso_desc.InputLayout = { input_element_descs, _countof(input_element_descs) };
//		pso_desc.pRootSignature = root_signature;
//		pso_desc.VS = { reinterpret_cast<UINT8*>(vertex_shader->GetBufferPointer()), vertex_shader->GetBufferSize() };
//		pso_desc.PS = { reinterpret_cast<UINT8*>(pixel_shader->GetBufferPointer()), pixel_shader->GetBufferSize() };
//		pso_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//		pso_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//		pso_desc.DepthStencilState.DepthEnable = FALSE;
//		pso_desc.DepthStencilState.StencilEnable = FALSE;
//		pso_desc.SampleMask = UINT_MAX;
//		pso_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//		pso_desc.NumRenderTargets = 1;
//		pso_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//		pso_desc.SampleDesc.Count = 1;
//		BB_CHECK(device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(&pipeline_state)));
//	}
//
//	BB_CHECK(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator, pipeline_state, IID_PPV_ARGS(&command_list)));
//
//	BB_CHECK(command_list->Close());
//
//	{
//		Vertex triangle_verts[] =
//		{
//			{ { 0.0f, 0.25f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
//			{ { 0.25f, -0.25f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
//			{ { -0.25f, -0.25f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
//		};
//
//		const UINT vertex_buffer_size = sizeof(triangle_verts);
//
//		BB_CHECK(device->CreateCommittedResource(
//			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//			D3D12_HEAP_FLAG_NONE,
//			&CD3DX12_RESOURCE_DESC::Buffer(vertex_buffer_size),
//			D3D12_RESOURCE_STATE_GENERIC_READ,
//			nullptr,
//			IID_PPV_ARGS(&vertex_buffer)
//		));
//
//		UINT8* vertex_data_begin;
//		CD3DX12_RANGE read_range(0, 0);
//		BB_CHECK(vertex_buffer->Map(0, &read_range, reinterpret_cast<void**>(&vertex_data_begin)));
//		memcpy(vertex_data_begin, triangle_verts, sizeof(triangle_verts));
//		vertex_buffer->Unmap(0, nullptr);
//
//		vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
//		vertex_buffer_view.StrideInBytes = sizeof(Vertex);
//		vertex_buffer_view.SizeInBytes = vertex_buffer_size;
//	}
//
//	{
//		BB_CHECK(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
//		fence_value = 1;
//
//		fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
//		if (fence_event == nullptr)
//		{
//			BB_CHECK(HRESULT_FROM_WIN32(GetLastError()));
//		}
//
//		const UINT64 fencet = fence_value;
//		BB_CHECK(command_queue->Signal(fence, fencet));
//		fence_value++;
//
//		// Wait until the previous frame is finished.
//		if (fence->GetCompletedValue() < fencet)
//		{
//			BB_CHECK(fence->SetEventOnCompletion(fencet, fence_event));
//			WaitForSingleObject(fence_event, INFINITE);
//		}
//
//		frame_index = swap_chain->GetCurrentBackBufferIndex();
//	}
//
//	while (true)
//	{
//		// update
//		printf("damn\n");
//
//		// render
//
//		// Command list allocators can only be reset when the associated 
//		// command lists have finished execution on the GPU; apps should use 
//		// fences to determine GPU execution progress.
//		BB_CHECK(command_allocator->Reset());
//
//		// However, when ExecuteCommandList() is called on a particular command 
//		// list, that command list can then be reset at any time and must be before 
//		// re-recording.
//		BB_CHECK(command_list->Reset(command_allocator, pipeline_state));
//
//		// Set necessary state.
//		command_list->SetGraphicsRootSignature(root_signature);
//		command_list->RSSetViewports(1, &viewport);
//		command_list->RSSetScissorRects(1, &scissor_rect);
//
//		// Indicate that the back buffer will be used as a render target.
//		command_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(render_targets[frame_index], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
//
//		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(descriptor_heap->GetCPUDescriptorHandleForHeapStart(), frame_index, rtv_descriptor_size);
//		command_list->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
//
//		// Record commands.
//		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
//		command_list->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
//		command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//		command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);
//		command_list->DrawInstanced(3, 1, 0, 0);
//
//		// Indicate that the back buffer will now be used to present.
//		command_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(render_targets[frame_index], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
//
//		BB_CHECK(command_list->Close());
//
//		// Execute the command list.
//		ID3D12CommandList* ppCommandLists[] = { command_list };
//		command_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
//
//		// Present the frame.
//		BB_CHECK(swap_chain->Present(1, 0));
//
//		const UINT64 fencet = fence_value;
//		BB_CHECK(command_queue->Signal(fence, fencet));
//		fence_value++;
//
//		// Wait until the previous frame is finished.
//		if (fence->GetCompletedValue() < fencet)
//		{
//			BB_CHECK(fence->SetEventOnCompletion(fencet, fence_event));
//			WaitForSingleObject(fence_event, INFINITE);
//		}
//
//		frame_index = swap_chain->GetCurrentBackBufferIndex();
//	}
//
//	return 0;
}