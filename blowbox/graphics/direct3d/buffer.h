#pragma once

#include "../../graphics/direct3d/direct3d.h"

#define BB_GPU_VIRTUAL_ADDRESS_NULL 0ull
#define BB_GPU_VIRTUAL_ADDRESS_UNKNOWN ~0ull

#include "../../graphics/direct3d/resource.h"
#include <string>

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::Buffer
		* @author Riko Ophorst
		* @brief A GPU buffer 
		*/
		class Buffer : Resource
		{
		public:
			static Buffer* Create(const std::string& name, const uint32_t& num_elements, const void* initial_data = nullptr);
		};
	}
}