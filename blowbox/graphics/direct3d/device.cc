#include "device.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		Device::Device(const D3D_FEATURE_LEVEL& feature_level) :
			device_(nullptr)
		{
			BB_CHECK(D3D12CreateDevice(NULL, feature_level, IID_PPV_ARGS(&device_)));
		}
		
		//------------------------------------------------------------------------------------------------------
		Device::~Device()
		{
			BB_SAFE_RELEASE(device_);
		}

		//------------------------------------------------------------------------------------------------------
		Device* Device::Create(const D3D_FEATURE_LEVEL& feature_level)
		{
			return new Device(feature_level);
		}
		
		//------------------------------------------------------------------------------------------------------
		ID3D12Device* Device::Get()
		{
			return device_;
		}
	}
}