#pragma once

#include "../../graphics/direct3d/direct3d.h"

#define BB_CREATE_PSO_DESC(desc_name, input_element_descs, root_signature) D3D12_GRAPHICS_PIPELINE_STATE_DESC desc_name = {}; \
desc_name.InputLayout = { input_element_descs, _countof(input_element_descs) }; \
desc_name.pRootSignature = root_signature->Get(); \
desc_name.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT); \
desc_name.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT); \
desc_name.DepthStencilState.DepthEnable = FALSE; \
desc_name.DepthStencilState.StencilEnable = FALSE; \
desc_name.SampleMask = UINT_MAX; \
desc_name.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; \
desc_name.NumRenderTargets = 1; \
desc_name.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; \
desc_name.SampleDesc.Count = 1; 

namespace blowbox
{
	namespace direct3d
	{
		class Device;

		/**
		* @class blowbox::direct3d::PipelineState
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class PipelineState
		{
		public:
			/**
			* @brief Default constructor
			*/
			PipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~PipelineState();

			/**
			* @brief Creates an instance of this class
			*/
			static PipelineState* Create(D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, Device* device);

			ID3D12PipelineState* Get();
		private:
			ID3D12PipelineState* pipeline_state_;
		};
	}
}