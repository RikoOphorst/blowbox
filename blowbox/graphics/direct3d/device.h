#pragma once

#include "direct3d.h"

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::Device
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class Device
		{
		public:
			/**
			* @brief Default constructor
			* @param[in] feature_level (const D3D_FEATURE_LEVEL&) The feature level the device should be created with
			*/
			Device(const D3D_FEATURE_LEVEL& feature_level);

			/**
			* @brief Default destructor
			*/
			~Device();

			/**
			* @brief Creates an instance of this class
			* @param[in] feature_level (const D3D_FEATURE_LEVEL&) The feature level the device should be created with
			*/
			static Device* Create(const D3D_FEATURE_LEVEL& feature_level);

			/**
			* @brief Get a pointer to the actual device
			*/
			ID3D12Device* Get();

		private:
			ID3D12Device* device_; //<! Direct3D 12 device
		};
	}
}