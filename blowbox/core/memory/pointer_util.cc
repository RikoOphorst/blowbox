#include "pointer_util.h"

namespace blowbox
{
	namespace memory
	{
		//------------------------------------------------------------------------------------------------------
		std::string PointerUtil::ConvertToBinaryString(unsigned int val)
		{
			unsigned int mask = 1 << (sizeof(int) * 8 - 1);

			std::string result = "";

			for (int i = 0; i < sizeof(int) * 8; i++)
			{
				if ((val & mask) == 0)
					result += "0";
				else
					result += "1";

				mask >>= 1;
			}

			return result;
		}

		//------------------------------------------------------------------------------------------------------
		void* PointerUtil::AlignForward(void* address, const uint32_t& alignment)
		{
			return (void*)(((uintptr_t)(address)+(uintptr_t)(alignment - 1)) & (uintptr_t)(~(alignment - 1)));
		}

		//------------------------------------------------------------------------------------------------------
		const void* PointerUtil::AlignForward(const void* address, const uint32_t& alignment)
		{
			return (void*)(((uintptr_t)(address)+(uintptr_t)(alignment - 1)) & (uintptr_t)(~(alignment - 1)));
		}

		//------------------------------------------------------------------------------------------------------
		void* PointerUtil::AlignBackward(void* address, const uint32_t& alignment)
		{
			return (void*)(((uintptr_t)(address)) & (uintptr_t)(~(alignment - 1)));
		}

		//------------------------------------------------------------------------------------------------------
		const void* PointerUtil::AlignBackward(const void* address, const uint32_t& alignment)
		{
			return (void*)(((uintptr_t)(address)) & (uintptr_t)(~(alignment - 1)));
		}

		//------------------------------------------------------------------------------------------------------
		uint32_t PointerUtil::AlignForwardAdjustment(const void* address, const uint32_t& alignment)
		{
			uint32_t adjustment = alignment - ((uintptr_t)address & (uintptr_t)(alignment - 1));

			if (adjustment == alignment)
				return 0;

			return adjustment;
		}

		//------------------------------------------------------------------------------------------------------
		uint32_t PointerUtil::AlignForwardAdjustmentWithHeader(const void* address, const uint32_t& alignment, const uint32_t& header_size)
		{
			uint32_t adjustment = AlignForwardAdjustment(address, alignment);
			uint32_t needed_space = header_size;

			if (adjustment < needed_space)
			{
				needed_space -= adjustment;

				adjustment += alignment * (needed_space / alignment);

				if (needed_space % alignment > 0)
					adjustment += alignment;
			}

			return adjustment;
		}

		//------------------------------------------------------------------------------------------------------
		uint32_t PointerUtil::AlignBackwardAdjustment(const void* address, const uint32_t& alignment)
		{
			uint32_t adjustment = (uintptr_t)(address) & (uintptr_t)(alignment - 1);

			if (adjustment == alignment)
			{
				return 0;
			}

			return adjustment;
		}

		//------------------------------------------------------------------------------------------------------
		void* PointerUtil::Add(void* ptr, const uint32_t& value)
		{
			return (void*)((uintptr_t)ptr + value);
		}

		//------------------------------------------------------------------------------------------------------
		const void* PointerUtil::Add(const void* ptr, const uint32_t& value)
		{
			return (const void*)((uintptr_t)ptr + value);
		}

		//------------------------------------------------------------------------------------------------------
		void* PointerUtil::Subtract(void* ptr, const uint32_t& value)
		{
			return (void*)((uintptr_t)ptr - value);
		}

		//------------------------------------------------------------------------------------------------------
		const void* PointerUtil::Subtract(const void* ptr, const uint32_t& value)
		{
			return (const void*)((uintptr_t)ptr - value);
		}
	}
}