#include "allocator.h"

namespace blowbox
{
	namespace memory
	{
		Allocator::Allocator(void* start, const size_t& size) :
			start_(start),
			size_(size),
			used_memory_(0),
			num_allocations_(0)
		{

		}

		Allocator::~Allocator()
		{
			// Only doing this so that the memory is "clean"
			start_ = nullptr;
			size_ = 0;
			used_memory_ = 0;
			num_allocations_ = 0;
		}

		void* Allocator::GetStart()
		{
			return start_;
		}

		const size_t& Allocator::GetSize()
		{
			return size_;
		}

		const size_t& Allocator::GetUsedMemory()
		{
			return used_memory_;
		}

		const size_t& Allocator::GetNumAllocations()
		{
			return num_allocations_;
		}
	}
}