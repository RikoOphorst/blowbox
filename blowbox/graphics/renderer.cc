#include "renderer.h"

#include "../util/macros.h"
#include <comdef.h>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Renderer* Renderer::Create(Allocator* allocator)
	{
		return MemoryManager::Allocate<Renderer>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	Renderer::Renderer(Allocator* allocator) :
		MObject(allocator)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Renderer::~Renderer()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Renderer::Startup()
	{
#if defined(DEBUG) || defined(_DEBUG)
		{
			ID3D12Debug* debug_controller;
			BB_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)));
		}
#endif
		
		CreateDXGIFactory1(IID_PPV_ARGS(&factory_));

		UINT i = 0;
		IDXGIAdapter1* adapter = nullptr;
		while (factory_->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// this adapter is a software adapter, skip it
				i++;
				continue;
			}
			
			if (D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr) == S_OK)
			{
				Console::Instance()->Log(BB_LOGSTREAM << "Found compatible GPU: " << desc.Description);
				break;
			}
			else
			{
				i++;
			}
		}

		if (adapter == nullptr)
		{
			BB_BREAK(BB_LOGSTREAM << "No valid adapter (GPU) was found with feature level 11_0");
		}

		D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_));
	}
	
	//------------------------------------------------------------------------------------------------------
	void Renderer::Update()
	{
	}
}