#include "renderer.h"

#include "../util/macros.h"
#include "../window/window.h"
#include <comdef.h>
#include <codecvt>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Renderer* Renderer::Create(Allocator* allocator)
	{
		return MemoryManager::Allocate<Renderer>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	Renderer::Renderer(Allocator* allocator) :
		MObject(allocator),
		rtv_descriptor_size_(0),
		dsv_descriptor_size_(0),
		cbv_srv_descriptor_size_(0),
		factory_(nullptr),
		device_(nullptr),
		command_queue_(nullptr),
		command_allocator_(nullptr),
		command_list_(nullptr),
		buffer_width_(1280),
		buffer_height_(720),
		buffer_format_(DXGI_FORMAT_UNKNOWN),
		current_back_buffer_(0),
		swap_chain_(nullptr),
		rtv_heap_(nullptr),
		dsv_heap_(nullptr),
		dsv_format_(DXGI_FORMAT_UNKNOWN),
		dsv_buffer_(nullptr),
		fence_(nullptr),
		fence_value_(0)
	{
		for (int i = 0; i < buffer_count_; i++)
		{
			buffers_[i] = nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------------
	Renderer::~Renderer()
	{
		BB_SAFE_RELEASE(factory_);
		BB_SAFE_RELEASE(device_);
		BB_SAFE_RELEASE(command_queue_);
		BB_SAFE_RELEASE(command_allocator_);
		BB_SAFE_RELEASE(command_list_); 
		for (int i = 0; i < buffer_count_; i++)
		{
			BB_SAFE_RELEASE(buffers_[i]);
		}
		BB_SAFE_RELEASE(swap_chain_);
		BB_SAFE_RELEASE(rtv_heap_);
		BB_SAFE_RELEASE(dsv_heap_);
		BB_SAFE_RELEASE(dsv_buffer_);
		BB_SAFE_RELEASE(fence_);
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::Startup(Window* output_window)
	{
		main_window_handle_ = output_window->GetWindowHandle();
		buffer_width_ = output_window->GetWidth();
		buffer_height_ = output_window->GetHeight();
		buffer_format_ = DXGI_FORMAT_R8G8B8A8_UNORM;
		dsv_format_ = DXGI_FORMAT_D32_FLOAT;

		CreateDevice();

		CreateFence();

		FindDescriptorSizes();

		CreateCommandObjects();

		CheckMsaaLevels();

		CreateSwapChain();

		CreateRtvAndDsvHeaps();

		CreateRenderTargetViews();

		CreateDepthStencilView();

		SetViewport();

		SetScissorRect();
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateDevice()
	{
#if defined(DEBUG) || defined(_DEBUG)
		{
			ID3D12Debug* debug_controller;
			BB_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)));
			debug_controller->EnableDebugLayer();
			debug_controller->Release();
		}
#endif

		BB_CHECK(CreateDXGIFactory1(IID_PPV_ARGS(&factory_)));

		UINT i = 0;
		IDXGIAdapter1* adapter = nullptr;
		while (factory_->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;
			std::string converted_str = converter.to_bytes(desc.Description);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// this adapter is a software adapter, skip it
				i++;
				continue;
			}

			if (D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)) != S_OK)
			{
				i++;
				continue;
			}
			else
			{
				device_->Release();
				Console::Instance()->Log(BB_LOGSTREAM << "Using DirectX 12 compatible GPU: " << converted_str);
				break;
			}
		}

		if (adapter == nullptr)
		{
			Console::Instance()->Log(BB_LOGSTREAM << "No valid adapter (GPU) was found, creating WARP adapter..", BB_MESSAGE_TYPE_WARNING);
			factory_->EnumWarpAdapter(IID_PPV_ARGS(&adapter));
		}

		BB_CHECK(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)));
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateFence()
	{
		fence_value_ = 0;
		device_->CreateFence(fence_value_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::FindDescriptorSizes()
	{
		rtv_descriptor_size_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		dsv_descriptor_size_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
		cbv_srv_descriptor_size_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateCommandObjects()
	{
		D3D12_COMMAND_QUEUE_DESC queue_desc = {};
		queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		BB_CHECK(device_->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&command_queue_)));

		BB_CHECK(device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator_)));
		BB_CHECK(device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_, nullptr, IID_PPV_ARGS(&command_list_)));
		command_list_->Close();
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CheckMsaaLevels()
	{
		multisample_quality_levels_.Format = buffer_format_;
		multisample_quality_levels_.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
		multisample_quality_levels_.SampleCount = 4;
		multisample_quality_levels_.NumQualityLevels = 0;
		BB_CHECK(device_->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &multisample_quality_levels_, sizeof(multisample_quality_levels_)));
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateSwapChain()
	{
		BB_SAFE_RELEASE(swap_chain_);

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = buffer_width_;
		sd.BufferDesc.Height = buffer_height_;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = buffer_format_;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = buffer_count_;
		sd.OutputWindow = main_window_handle_;
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		BB_CHECK(factory_->CreateSwapChain(command_queue_, &sd, &swap_chain_));
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateRtvAndDsvHeaps()
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc;
		rtv_heap_desc.NumDescriptors = buffer_count_;
		rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		rtv_heap_desc.NodeMask = 0;

		device_->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&rtv_heap_));

		D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc;
		dsv_heap_desc.NumDescriptors = 1;
		dsv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		dsv_heap_desc.NodeMask = 0;

		device_->CreateDescriptorHeap(&dsv_heap_desc, IID_PPV_ARGS(&dsv_heap_));
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateRenderTargetViews()
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_heap_handle(rtv_heap_->GetCPUDescriptorHandleForHeapStart());
		for (UINT i = 0; i < buffer_count_; i++)
		{
			BB_CHECK(swap_chain_->GetBuffer(i, IID_PPV_ARGS(&buffers_[i])));

			// We can specify null for the rtv desc because we already specified the type of the buffers in the swap chain desc
			device_->CreateRenderTargetView(buffers_[i], nullptr, rtv_heap_handle);

			rtv_heap_handle.Offset(1, rtv_descriptor_size_);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::CreateDepthStencilView()
	{
		D3D12_RESOURCE_DESC depth_stencil_desc;
		depth_stencil_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		depth_stencil_desc.Alignment = 0;
		depth_stencil_desc.Width = buffer_width_;
		depth_stencil_desc.Height = buffer_height_;
		depth_stencil_desc.DepthOrArraySize = 1;
		depth_stencil_desc.MipLevels = 1;
		depth_stencil_desc.Format = dsv_format_;
		depth_stencil_desc.SampleDesc.Count = 1;
		depth_stencil_desc.SampleDesc.Quality = 0;
		depth_stencil_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depth_stencil_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		D3D12_CLEAR_VALUE opt_clear;
		opt_clear.Format = dsv_format_;
		opt_clear.DepthStencil.Depth = 1.0f;
		opt_clear.DepthStencil.Stencil = 0;
		
		BB_CHECK(device_->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &depth_stencil_desc, D3D12_RESOURCE_STATE_COMMON, &opt_clear, IID_PPV_ARGS(&dsv_buffer_)));

		// We can specify null for the dsv desc because we already specified the type of the buffers in the resource desc
		device_->CreateDepthStencilView(dsv_buffer_, nullptr, GetDepthStencilView());

		command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(dsv_buffer_, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::SetViewport()
	{
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(buffer_width_);
		viewport.Height = static_cast<float>(buffer_height_);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		command_list_->RSSetViewports(1, &viewport);
	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::SetScissorRect()
	{
		D3D12_RECT scissor_rect;
		scissor_rect.left = 0;
		scissor_rect.top = 0;
		scissor_rect.right = buffer_width_;
		scissor_rect.bottom = buffer_height_;

		command_list_->RSSetScissorRects(1, &scissor_rect);
	}
	
	//------------------------------------------------------------------------------------------------------
	void Renderer::Update()
	{
		BB_CHECK(command_allocator_->Reset());
		BB_CHECK(command_list_->Reset(command_allocator_, nullptr));

		command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		SetViewport();
		SetScissorRect();

		float clear_color[4];
		clear_color[0] = 0.1f;
		clear_color[1] = 0.1f;
		clear_color[2] = 0.4f;
		clear_color[3] = 1.0f;
		command_list_->ClearRenderTargetView(GetCurrentBackBufferView(), clear_color, 0, nullptr);

		command_list_->OMSetRenderTargets(1, &GetCurrentBackBufferView(), true, &GetDepthStencilView());

		command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		BB_CHECK(command_list_->Close());

		ID3D12CommandList* command_lists[] = { command_list_ };
		command_queue_->ExecuteCommandLists(_countof(command_lists), command_lists);

		BB_CHECK(swap_chain_->Present(0, 0));
		current_back_buffer_ = (current_back_buffer_ + 1) % buffer_count_;

		FlushCommandQueue();
	}
	
	//------------------------------------------------------------------------------------------------------
	void Renderer::FlushCommandQueue()
	{
		fence_value_++;

		BB_CHECK(command_queue_->Signal(fence_, fence_value_));

		if (fence_->GetCompletedValue() < fence_value_)
		{
			HANDLE event_handle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

			fence_->SetEventOnCompletion(fence_value_, event_handle);

			WaitForSingleObject(event_handle, INFINITE);
			CloseHandle(event_handle);
		}
	}

	//------------------------------------------------------------------------------------------------------
	ID3D12Resource* Renderer::GetCurrentBackBuffer() const
	{
		return buffers_[current_back_buffer_];
	}

	//------------------------------------------------------------------------------------------------------
	D3D12_CPU_DESCRIPTOR_HANDLE Renderer::GetCurrentBackBufferView() const
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(rtv_heap_->GetCPUDescriptorHandleForHeapStart(), current_back_buffer_, rtv_descriptor_size_);
	}
	
	//------------------------------------------------------------------------------------------------------
	D3D12_CPU_DESCRIPTOR_HANDLE Renderer::GetDepthStencilView() const
	{
		return dsv_heap_->GetCPUDescriptorHandleForHeapStart();
	}
}