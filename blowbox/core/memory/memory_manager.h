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

			template<typename T, typename...Args>
			static T* Allocate(Allocator* allocator, Args...args);

			template<typename T>
			static void Deallocate(Allocator* allocator, T* ptr);

			template<typename T>
			T* ConstructAllocator(const size_t& size);

			template<typename T, typename B>
			T* ConstructAllocator(const size_t& size);

			void DestructAllocator(Allocator* allocator);
		private:
			FreeListAllocator* all_allocators_;
			FreeListAllocator* memory_allocator_;
			MemoryPool* memory_pool_;

			static MemoryManager* instance_;
		};

		template<typename T, typename...Args>
		inline T* MemoryManager::Allocate(Allocator* allocator, Args...args)
		{
			return new (allocator->Allocate(sizeof(T), __alignof(T))) T(args...);
		}

		template<typename T>
		inline void MemoryManager::Deallocate(Allocator* allocator, T* ptr)
		{
			ptr->~T();
			allocator->Deallocate(ptr);
		}

		template<typename T>
		inline T* MemoryManager::ConstructAllocator(const size_t& size)
		{
			void* new_alloc = all_allocators_->Allocate(sizeof(T), __alignof(T));
			void* new_memory_zone = memory_allocator_->Allocate(size);

			return new (new_alloc)T(new_memory_zone, size);
		}

		template<typename T, typename B>
		inline T* MemoryManager::ConstructAllocator(const size_t& size)
		{
			void* new_alloc = all_allocators_->Allocate(sizeof(T), __alignof(T));
			void* new_memory_zone = memory_allocator_->Allocate(size);

			return new (new_alloc)T(new_memory_zone, size, sizeof(B), __alignof(B));
		}
	}
}