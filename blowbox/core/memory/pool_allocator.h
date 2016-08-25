#pragma once

#include "../../../blowbox/core/memory/allocator.h"

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::PoolAllocator
		* @author Riko Ophorst
		* @brief Pool allocation, useful for allocating lots of objects of the same size
		*/
		class PoolAllocator : public Allocator
		{
		public:
			/**
			* @brief PoolAllocator constructor
			* @param[in]	start				The start of the memory block managed by this allocator
			* @param[in]	size				The size of the memory block managed by this allocator
			* @param[in]	object_size			The size of the pooled object
			* @param[in]	object_alignment	The alignment of the pooled object
			*/
			PoolAllocator(void* start, const size_t& size, const size_t& object_size, const uint32_t& object_alignment);

			~PoolAllocator(); //<! PoolAllocator destructor

			/**
			* @brief Allocates a new block of memory within this allocator
			* @param[in]	size		The size of the memory block we're allocating
			* @param[in]	alignment	The alignment of the memory block we're allocating
			*/
			void* Allocate(const size_t& size, const uint32_t& alignment = 4);

			/**
			* @brief Deallocates a block of memory
			* @param[in]	ptr		Pointer to the memory to be deallocated
			*/
			void Deallocate(void* ptr);
		private:
			size_t object_size_; //<! The size of the pooled object
			uint32_t object_alignment_; //<! The alignment of the pooled object

			void** free_list_; //<! Linked-list of unallocated free-nodes
		};
	}
}