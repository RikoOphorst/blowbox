#include "linear_allocator.h"

#include "../../../blowbox/util/macros.h"
#include "../../../blowbox/core/memory/pointer_util.h"
#include "../../../blowbox/core/memory/heap_inspector.h"

namespace blowbox
{
	namespace memory
	{
		LinearAllocator::LinearAllocator(void* start, const size_t& size) :
			Allocator(start, size),
			marker_(start)
		{

		}

		LinearAllocator::~LinearAllocator()
		{

		}

		void* LinearAllocator::Allocate(const size_t& size, const uint32_t& alignment)
		{
			BB_HEAP_BEGIN_ALLOC();
			BB_ASSERT(size > 0, "A block with no size cannot be allocated.");

			uint32_t adjustment = PointerUtil::AlignForwardAdjustment(marker_, alignment);

			if (used_memory_ + adjustment + size > size_)
			{
				BB_ASSERT(false, "Allocator ran out of space");
				return nullptr;
			}

			uintptr_t aligned_address = (uintptr_t)marker_ + adjustment;
			
			marker_ = PointerUtil::Add(marker_, size + adjustment);
			used_memory_ += adjustment + size;
			num_allocations_++;

			BB_HEAP_END_ALLOC((void*)aligned_address, size);
			return (void*)aligned_address;
		}

		void LinearAllocator::Deallocate(void* ptr)
		{
			BB_ASSERT(false, "Linear allocators cannot deallocate pointers. Once it's allocated, it stays allocated.");
		}
	}
}