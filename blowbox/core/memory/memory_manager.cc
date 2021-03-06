#include "memory_manager.h"

#include "../../../blowbox/core/memory/free_list_allocator.h"
#include "../../../blowbox/core/memory/linear_allocator.h"
#include "../../../blowbox/core/memory/stack_allocator.h"
#include "../../../blowbox/core/memory/pool_allocator.h"
#include "../../../blowbox/core/memory/memory_pool.h"
#include "../../../blowbox/core/memory/heap_inspector.h"
#include "../../../blowbox/core/memory/pointer_util.h"
#include <iostream>

namespace blowbox
{
	namespace memory
	{
		MemoryManager* MemoryManager::instance_ = nullptr;

		//------------------------------------------------------------------------------------------------------
		MemoryManager::MemoryManager(MemoryPool* memory_pool) :
			memory_pool_(memory_pool)
		{
			void* pool_start = memory_pool_->GetStartOfMemoryPool();
			all_allocators_ = new (pool_start)memory::FreeListAllocator((void*)((uintptr_t)pool_start + sizeof(memory::FreeListAllocator)), 10000);
			memory_pool_->SetStartOffset(memory_pool_->GetStartOffset() + sizeof(memory::FreeListAllocator) + 10000);

			pool_start = memory_pool_->GetStartOfMemoryPool();
			memory_allocator_ = new (pool_start)memory::FreeListAllocator((void*)((uintptr_t)pool_start + sizeof(memory::FreeListAllocator)), memory_pool_->GetSizeOfMemoryPool() - memory_pool_->GetStartOffset());
			memory_pool_->SetStartOffset(memory_pool_->GetStartOffset() + sizeof(memory::FreeListAllocator) + (memory_pool_->GetSizeOfMemoryPool() - memory_pool_->GetStartOffset()));

			// Disable the heap inspector notifications for the memory allocator.
			// In the heap inspector client it causes a warning to popup for every
			// first allocation in a new allocator, because the start address of
			// that allocator (which is where that address puts its first allocation)
			// is the same as the memory that is allocated for it.
			memory_allocator_->SetHeapInspectorNotifications(false);
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
			void* aligned_address = PointerUtil::AlignForward(pool_start, __alignof(MemoryManager));
			uint32_t adjustment = PointerUtil::AlignForwardAdjustment(pool_start, __alignof(MemoryManager));

			pool->SetStartOffset(pool->GetStartOffset() + adjustment + sizeof(MemoryManager));
			MemoryManager* memory_manager = new (aligned_address)MemoryManager(pool);
			BB_HEAP_END_ALLOC(pool_start, sizeof(memory_manager));

			instance_ = memory_manager;

			return memory_manager;
		}

		//------------------------------------------------------------------------------------------------------
		MemoryManager* MemoryManager::Instance()
		{
			return instance_;
		}

		//------------------------------------------------------------------------------------------------------
		LinearAllocator* MemoryManager::LinearAllocator(const size_t& size)
		{
			return MemoryManager::Instance()->ConstructAllocator<memory::LinearAllocator>(size);
		}

		//------------------------------------------------------------------------------------------------------
		StackAllocator* MemoryManager::StackAllocator(const size_t& size)
		{
			return MemoryManager::Instance()->ConstructAllocator<memory::StackAllocator>(size);
		}

		//------------------------------------------------------------------------------------------------------
		FreeListAllocator* MemoryManager::FreeListAllocator(const size_t& size)
		{
			return MemoryManager::Instance()->ConstructAllocator<memory::FreeListAllocator>(size);
		}

		//------------------------------------------------------------------------------------------------------
		void MemoryManager::DestructAllocator(Allocator* allocator)
		{
			void* start = allocator->GetStart();
			Instance()->all_allocators_->Deallocate(allocator);
			Instance()->memory_allocator_->Deallocate(start);
		}
	}
}