#pragma once

#include <new>

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::MemoryPool
		* @author Riko Ophorst
		* @brief A pool of memory
		*/
		class MemoryPool
		{
		private:
			/**
			* @brief MemoryPool constructor
			* @param[in]	start	The start of the memory pool
			* @param[in]	size	The size of the memory pool
			*/
			MemoryPool(void* start, const size_t& size);

			~MemoryPool(); //<! MemoryPool destructor

		public:
			/**
			* @brief Factory for creating a memory pool
			* @param[in]	size	The size of the memory pool you wish to create
			*/
			static MemoryPool* Create(const size_t& size);

			void* GetStartOfMemoryPool(); //<! Get the start of the memory pool offsetted by the allocated memory
			void* GetActualStartOfMemoryPool(); //<! Get the ACTUAL start of the memory pool

			const size_t& GetSizeOfMemoryPool(); //<! Get the size of the memory pool

			const size_t& GetStartOffset(); //<! Get the start offset of the memory pool
			void SetStartOffset(const size_t& offset); //<! Set the start offset of the memory pool

		private:
			size_t start_offset_; //<! The start offset of the memory pool
			size_t size_; //<! The size of the memory pool
			void* memory_pool_; //<! The actual memory pool
		};
	}
}