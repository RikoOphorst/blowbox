#pragma once

#include "allocator.h"

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::FreeListAllocator
		* @author Riko Ophorst
		* @brief Free list allocation allows for unordered allocation & deallocation of objects with unconstrained size & alignment
		*/
		class FreeListAllocator : public Allocator
		{
		public:
			/**
			* @brief FreeListAllocator constructor
			* @param[in]	start	Pointer to the start of the memory block this allocator uses
			* @param[in]	size	Size of the memory block this allocator uses
			*/
			FreeListAllocator(void* start, const size_t& size);

			/**
			* @brief FreeListAllocator destructor
			*/
			~FreeListAllocator();
			
			/**
			* @brief Allocates a block of memory
			* @param[in]	size		The size of the memory block to be allocated
			* @param[in]	alignment	The alignment of the memory block to be allocated
			*/
			void* Allocate(const size_t& size, const uint32_t& alignment = 4);

			/**
			* @brief Deallocates a block of memory
			* @param[in]	ptr		Pointer to the memory to be deallocated
			*/
			void Deallocate(void* ptr);
		private:
			/**
			* @struct blowbox::memory::FreeListAllocator::AllocationHeader
			* @author Riko Ophorst
			* @brief Header placed in front of each allocation to store info about the allocation
			*/
			struct AllocationHeader
			{
				size_t size; //<! The size of the allocation that was made
				uint8_t adjustment; //<! The adjustment that was used to align the block correctly
			};

			/**
			* @struct blowbox::memory::FreeListAllocator::FreeBlock
			* @author Riko Ophorst
			* @brief A free block is a linked-list node in the allocator that functions as a block of unallocated memory
			*/
			struct FreeBlock
			{
				size_t size; //<! The size of the free block
				FreeBlock* next; //<! The next free block available in the allocator
			};

			FreeBlock* first_block_; //<! The first free block in the allocator
		};
	}
}