#pragma once

#include "../../graphics/direct3d/direct3d.h"

using namespace DirectX;

namespace blowbox
{
	namespace direct3d
	{
		class Device;
		class DescriptorHeap;
		
		struct BB_CONSTANT_BUFFER_DATA
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX projection;
			float time;
		};

		class ConstantBuffer
		{
		public:
			ConstantBuffer(ID3D12DescriptorHeap* heap, ID3D12Device* device);
			~ConstantBuffer();

			static ConstantBuffer* Create(DescriptorHeap* heap, Device* device);

			ID3D12Resource* Get();

			const BB_CONSTANT_BUFFER_DATA& GetData() const;
			BB_CONSTANT_BUFFER_DATA& GetData();
			uint8_t* GetGPUDataPointer();
		private:
			ID3D12Resource* constant_buffer_;
			BB_CONSTANT_BUFFER_DATA constant_buffer_data_;
			uint8_t* gpu_data_pointer_;
		};
	}
}