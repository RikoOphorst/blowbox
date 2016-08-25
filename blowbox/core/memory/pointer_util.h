#pragma once

#include <memory>
#include <string>
#include <bitset>

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::PointerUtil
		* @author Riko Ophorst
		* @brief A utility for manipulating pointers
		*/
		class PointerUtil
		{
		public:
			/**
			* @brief Convert any object to binary text (i.e. 01110111011010000111100101100100011011110111010001101000011010010111001100111111)
			* @param[in]	val		The object to convert to binary
			* @tparam		T		The type of the object to be converted to binary
			*/
			template<typename T>
			static std::string ConvertToBinaryString(T val);

			/**
			* @brief Align the given address on given alignment in the forward direction (positive)
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			*/
			static void* AlignForward(void* address, const uint32_t& alignment);

			/**
			* @brief Align the given address on given alignment in the forward direction (positive)
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			*/
			static const void* AlignForward(const void* address, const uint32_t& alignment);
			
			/**
			* @brief Align the given address on given alignment in the backword direction (negative)
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			*/
			static void* AlignBackward(void* address, const uint32_t& alignment);
			
			/**
			* @brief Align the given address on given alignment in the backword direction (negative)
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			*/
			static const void* AlignBackward(const void* address, const uint32_t& alignment);

			/**
			* @brief Retrieve the adjustment that was used to achieve an forward (positive) alignment on an address
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			*/
			static uint32_t AlignForwardAdjustment(const void* address, const uint32_t& alignment);
			
			/**
			* @brief Retrieve the adjustment that was used to achieve an alignment on an address with a header
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			* @param[in]	header_size	The size of the header that should be used
			*/
			static uint32_t AlignForwardAdjustmentWithHeader(const void* address, const uint32_t& alignment, const uint32_t& header_size);
			
			/**
			* @brief Retrieve the adjustment that was used to achieve an backward (negative) alignment on an address
			* @param[in]	address		The address that should be aligned
			* @param[in]	alignment	The alignment that should be used
			*/
			static uint32_t AlignBackwardAdjustment(const void* address, const uint32_t& alignment);

			/**
			* @brief Add a value to a pointer
			* @param[in]	ptr		The pointer that should be added to
			* @param[in]	value	The value that should be added
			*/
			static void* Add(void* ptr, const uint32_t& value);
			
			/**
			* @brief Add a value to a pointer
			* @param[in]	ptr		The pointer that should be added to
			* @param[in]	value	The value that should be added
			*/
			static const void* Add(const void* ptr, const uint32_t& value);
			
			/**
			* @brief Subtract a value from a pointer
			* @param[in]	ptr		The pointer that should be subtracted from
			* @param[in]	value	The value that should be subtracted
			*/
			static void* Subtract(void* ptr, const uint32_t& value);
			
			/**
			* @brief Subtract a value from a pointer
			* @param[in]	ptr		The pointer that should be subtracted from
			* @param[in]	value	The value that should be subtracted
			*/
			static const void* Subtract(const void* ptr, const uint32_t& value);
		};

		//------------------------------------------------------------------------------------------------------
		template<typename T>
		inline std::string PointerUtil::ConvertToBinaryString(T val)
		{
			std::string result = "";

			const char* beg = reinterpret_cast<const char*>(&val);
			const char* end = beg + sizeof(val);
			while (beg != end)
			{
				result += std::bitset<8>(*beg++).to_string() + ' ';
			}

			return result;
		}
	}
}