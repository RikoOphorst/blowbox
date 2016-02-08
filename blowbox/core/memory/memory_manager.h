#pragma once

#define BB_MEMORY_SIZE 100000000

namespace blowbox
{
	namespace memory
	{
		class MemoryPool;
		class FreeListAllocator;
		class LinearAllocator;
		class Allocator;
		
		class MemoryManager
		{
		private:
			MemoryManager(MemoryPool* memory_pool);
		public:
			~MemoryManager();
			static MemoryManager* Create();
			static MemoryManager* Instance();

			template<typename T>
			T* ConstructAllocator(const size_t& size);

			void DestructAllocator(Allocator* allocator);
		private:
			FreeListAllocator* all_allocators_;
			FreeListAllocator* memory_allocator_;
			MemoryPool* memory_pool_;

			static MemoryManager* instance_;
		};

		template<typename T>
		inline T* MemoryManager::ConstructAllocator(const size_t& size)
		{
			void* new_alloc = all_allocators_->Allocate(sizeof(T), __alignof(T));
			void* new_memory_zone = memory_allocator_->Allocate(size);

			return new (new_alloc)T(new_memory_zone, size);
		}
	}
}