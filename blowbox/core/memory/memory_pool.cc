#include "memory_pool.h"

#include "../../../blowbox/core/memory/heap_inspector.h"

namespace blowbox
{
	namespace memory
	{
		//------------------------------------------------------------------------------------------------------
		MemoryPool::MemoryPool(void* start, const size_t& size) :
			memory_pool_(start),
			size_(size),
			start_offset_(sizeof(MemoryPool))
		{

		}

		//------------------------------------------------------------------------------------------------------
		MemoryPool::~MemoryPool()
		{
			
		}

		//------------------------------------------------------------------------------------------------------
		MemoryPool* MemoryPool::Create(const size_t& size)
		{
			BB_HEAP_BEGIN_ALLOC();
			void* memory = malloc(size);
			BB_HEAP_END_ALLOC(memory, size);

			MemoryPool* memory_pool = new (memory) MemoryPool(memory, size);

			return memory_pool;
		}

		//------------------------------------------------------------------------------------------------------
		void* MemoryPool::GetStartOfMemoryPool()
		{
			return (void*)((uintptr_t)memory_pool_ + start_offset_);
		}

		//------------------------------------------------------------------------------------------------------
		void* MemoryPool::GetActualStartOfMemoryPool()
		{
			return memory_pool_;
		}

		//------------------------------------------------------------------------------------------------------
		const size_t& MemoryPool::GetSizeOfMemoryPool()
		{
			return size_;
		}
		
		//------------------------------------------------------------------------------------------------------
		const size_t& MemoryPool::GetStartOffset()
		{
			return start_offset_;
		}
		
		//------------------------------------------------------------------------------------------------------
		void MemoryPool::SetStartOffset(const size_t& offset)
		{
			start_offset_ = offset;
		}
	}
}