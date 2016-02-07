#pragma once

#include <memory>
#include <string>

namespace blowbox
{
	namespace memory
	{
		class PointerUtil
		{
		public:
			static std::string ConvertToBinaryString(unsigned int val);

			static void* AlignForward(void* address, const uint32_t& alignment);
			static const void* AlignForward(const void* address, const uint32_t& alignment);
			
			static void* AlignBackward(void* address, const uint32_t& alignment);
			static const void* AlignBackward(const void* address, const uint32_t& alignment);

			static uint32_t AlignForwardAdjustment(const void* address, const uint32_t& alignment);
			static uint32_t AlignForwardAdjustmentWithHeader(const void* address, const uint32_t& alignment, const uint32_t& header_size);
			
			static uint32_t AlignBackwardAdjustment(const void* address, const uint32_t& alignment);

			static void* Add(void* ptr, const uint32_t& value);
			static const void* Add(const void* ptr, const uint32_t& value);
			static void* Subtract(void* ptr, const uint32_t& value);
			static const void* Subtract(const void* ptr, const uint32_t& value);
		};
	}
}