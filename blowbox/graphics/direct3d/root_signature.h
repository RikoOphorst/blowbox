#pragma once

#include "../../graphics/direct3d/direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		class Device;

		/**
		* @class blowbox::direct3d::RootSignature
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class RootSignature
		{
		public:
			/**
			* @brief Default constructor
			*/
			RootSignature(D3D12_ROOT_SIGNATURE_DESC& desc, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~RootSignature();

			/**
			* @brief Creates an instance of this class
			*/
			static RootSignature* Create(D3D12_ROOT_SIGNATURE_DESC& desc, Device* device);

			ID3D12RootSignature* Get();
		private:
			ID3D12RootSignature* root_signature_;
		};
	}
}