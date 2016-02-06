#include "memory_manager.h"

#include "../../../blowbox/core/memory/memory_pool.h"
#include "../../../blowbox/core/memory/heap_inspector.h"

namespace blowbox
{
	namespace memory
	{
		//------------------------------------------------------------------------------------------------------
		MemoryManager::MemoryManager(MemoryPool* memory_pool) :
			memory_pool_(memory_pool)
		{

		}

		//------------------------------------------------------------------------------------------------------
		MemoryManager::~MemoryManager()
		{

		}

		//------------------------------------------------------------------------------------------------------
		MemoryManager* MemoryManager::Create()
		{
			MemoryPool* pool = MemoryPool::Create(BB_MEMORY_SIZE);

			void* pool_start = pool->GetStartOfMemoryPool();

			BB_HEAP_BEGIN_ALLOC();
			MemoryManager* memory_manager = new (pool_start) MemoryManager(pool);
			BB_HEAP_END_ALLOC(pool_start, sizeof(memory_manager));
			
			pool->SetStartOffset(sizeof(MemoryPool) + sizeof(MemoryManager));

			return memory_manager;
		}
	}
}