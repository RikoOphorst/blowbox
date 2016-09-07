#include "renderer.h"

#include "../util/macros.h"
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
			/*ID3D12Debug* debug_controller;
			BB_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)));
			debug_controller->EnableDebugLayer();
			debug_controller->Release();*/
		}
#endif
		
		BB_CHECK(CreateDXGIFactory2(NULL, IID_PPV_ARGS(&factory_)));

		UINT i = 0;
		IDXGIAdapter1* adapter = nullptr;
		while (factory_->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			//setup converter
			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;

			//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
			std::string converted_str = converter.to_bytes(desc.Description);

			Console::Instance()->Log(BB_LOGSTREAM << "Checking out GPU: " << converted_str);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// this adapter is a software adapter, skip it
				i++;
				continue;
			}
			
			break;
		}

		if (adapter == nullptr)
		{
			Console::Instance()->Log(BB_LOGSTREAM << "No valid adapter (GPU) was found with feature level 11_0");
			OutputDebugStringA("No valid adapter (GPU) was found with feature level 11_0");
			return;
		}

		BB_CHECK(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)));
	}
	
	//------------------------------------------------------------------------------------------------------
	void Renderer::Update()
	{
	}
}