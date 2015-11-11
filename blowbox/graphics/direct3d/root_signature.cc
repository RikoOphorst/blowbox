#include "root_signature.h"

#include "../../graphics/direct3d/device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		RootSignature::RootSignature(D3D12_ROOT_SIGNATURE_DESC& desc, ID3D12Device* device) :
			root_signature_(nullptr)
		{
			ID3DBlob* signature_blob = nullptr;
			ID3DBlob* error_blob = nullptr;
			BB_CHECK(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION::D3D_ROOT_SIGNATURE_VERSION_1, &signature_blob, &error_blob));
			BB_CHECK(device->CreateRootSignature(0, signature_blob->GetBufferPointer(), signature_blob->GetBufferSize(), IID_PPV_ARGS(&root_signature_)));

			BB_SAFE_RELEASE(error_blob);
		}

		//------------------------------------------------------------------------------------------------------
		RootSignature::~RootSignature()
		{
			BB_GUARANTEE_RELEASE(root_signature_);
		}

		//------------------------------------------------------------------------------------------------------
		RootSignature* RootSignature::Create(D3D12_ROOT_SIGNATURE_DESC& desc, Device* device)
		{
			return new RootSignature(desc, device->Get());
		}

		//------------------------------------------------------------------------------------------------------
		ID3D12RootSignature* RootSignature::Get()
		{
			return root_signature_;
		}
	}
}