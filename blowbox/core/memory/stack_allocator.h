#pragma once

#include "allocator.h"

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::StackAllocator
		* @author Riko Ophorst
		* @brief Stack allocation, useful for ordered allocations & deallocations, e.g. subsystem boot & shutdown
		*/
		class StackAllocator : public Allocator
		{
		public:
			/**
			* @brief StackAllocator constructor
			* @param[in]	start				The start of the memory block managed by this allocator
			* @param[in]	size				The size of the memory block managed by this allocator
			*/
			StackAllocator(void* start, const size_t& size);

			~StackAllocator(); //!< StackAllocator destructor

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
			/**
			* @struct blowbox::memory::StackAllocator::AllocationHeader
			* @author Riko Ophorst
			* @brief Allocation header prepended to each allocation
			*/
			struct AllocationHeader
			{
				uint32_t adjustment; //!< Adjustment used to achieve correct alignment of allocation
				void* prev_alloc; //!< Pointer to the previous allocation
			};

			void* top_; //!< Pointer to the top of the stack
			void* prev_alloc_; //!< Pointer to the previous (last) allocation
		};
	}
}