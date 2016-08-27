#pragma once

#include "allocator.h"

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::LinearAllocator
		* @author Riko Ophorst
		* @brief Allows for linear allocation, which is high-speed but has the drawback that memory cannot be deallocated
		*/
		class LinearAllocator : public Allocator
		{
		public:
			/**
			* @brief LinearAllocator constructor
			* @param[in]	start	Pointer to the start of the memory block that this allocator manages
			* @param[in]	size	The size of the memory block that this allocator manages
			*/
			LinearAllocator(void* start, const size_t& size);

			/**
			* @brief LinearAllocator destructor
			*/
			~LinearAllocator();

			/**
			* @brief Allocates a new block of memory within this allocator
			* @param[in]	size		The size of the memory block we're allocating
			* @param[in]	alignment	The alignment of the memory block we're allocating
			*/
			void* Allocate(const size_t& size, const uint32_t& alignment = 4);

			/**
			* @brief DOES NOT WORK ON THIS TYPE OF ALLOCATOR
			* @param[in]	ptr		The pointer to deallocate
			*/
			void Deallocate(void* ptr);

			/**
			* @brief Resets the allocator, essentially discarding all other objects that might be in the allocated block
			*/
			void Reset();
		private:
			void* marker_; //!< A marker to the current end of the currently allocated memory block in this allocator's memory zone
		};
	}
}