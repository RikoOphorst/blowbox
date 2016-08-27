#pragma once

#define BB_MEMORY_SIZE 100000000

namespace blowbox
{
	namespace memory
	{
		class MemoryPool;
		class FreeListAllocator;
		class LinearAllocator;
		class StackAllocator;
		class PoolAllocator;
		class Allocator;
		
		/**
		* @class blowbox::memory::MemoryManager
		* @author Riko Ophorst
		* @brief Manages all things memory
		*/
		class MemoryManager
		{
		private:
			/**
			* @brief MemoryManager constructor
			* @param[in]	memory_pool		The memory pool that the memory manager will be able to use
			*/
			MemoryManager(MemoryPool* memory_pool);
		public:
			/**
			* @brief MemoryManager destructor
			*/
			~MemoryManager();

			/**
			* @brief Factory to create the MemoryManager
			*/
			static MemoryManager* Create();

			/**
			* @brief Get the instance of the MemoryManager
			*/
			static MemoryManager* Instance();

			/**
			* @brief Shorthand to creating a LinearAllocator
			* @param[in]	size	The size of the memory block the allocator should manage
			*/
			static LinearAllocator* LinearAllocator(const size_t& size);

			/**
			* @brief Shorthand to creating a StackAllocator
			* @param[in]	size	The size of the memory block the allocator should manage
			*/
			static StackAllocator* StackAllocator(const size_t& size);

			/**
			* @brief Shorthand to creating a FreeListAllocator
			* @param[in]	size	The size of the memory block the allocator should manage
			*/
			static FreeListAllocator* FreeListAllocator(const size_t& size);

			/**
			* @brief Shorthand to creating a LinearAllocator
			* @param[in]	size	The size of the memory block the allocator should manage
			* @tparam		T		The object that should be pooled
			*/
			template<typename T>
			static PoolAllocator* PoolAllocator(const size_t& size);

			/**
			* @brief Allocates an object using an allocator
			* @param[in]	allocator	The allocator that should be used to allocate the object
			* @param[in]	args		The arguments that should be sent to the object's constructor
			* @tparam		T			The object to be allocated
			* @tparam		Args		Types of all arguments that should be sent (this is optional)
			*/
			template<typename T, typename...Args>
			static T* Allocate(Allocator* allocator, Args...args);

			/**
			* @brief Allocates an array of objects using an allocator
			* @param[in]	allocator	The allocator that should be used to allocate the object
			* @param[in]	length		The length of the array that should be allocated
			* @param[in]	args		The arguments that should be sent to the object's constructor
			* @tparam		T			The object to be allocated
			* @tparam		Args		Types of all arguments that should be sent (this is optional)
			*/
			template<typename T, typename...Args>
			static T* AllocateArray(Allocator* allocator, const size_t& length, Args...args);

			/**
			* @brief Deallocates an object from an allocator
			* @param[in]	allocator	The allocator that should be used to deallocate the object
			* @param[in]	ptr			The object to be deallocated
			* @tparam		T			The type of object to be deallocated
			*/
			template<typename T>
			static void Deallocate(Allocator* allocator, T* ptr);

			/**
			* @brief Deallocates an array of objects from an allocator
			* @param[in]	allocator	The allocator from which the array should be deallocated
			* @param[in]	arr			The array that should be deallocated
			* @tparam		T			The object of which the array is built
			*/
			template<typename T>
			static void DeallocateArray(Allocator* allocator, T* arr);

			/**
			* @brief Constructs allocator of type T
			* @param[in]	size	The size of the memory block the allocator should manage
			* @tparam		T		The type of allocator to be constructed
			*/
			template<typename T>
			T* ConstructAllocator(const size_t& size);

			/**
			* @brief Constructs allocator of type T, with allocatable type B
			* @param[in]	size	The size of the memory block the allocator should manage
			* @tparam		T		The type of allocator to be constructed
			* @tparam		B		The type of object this allocator can allocate
			*/
			template<typename T, typename B>
			T* ConstructAllocator(const size_t& size);

			/**
			* @brief Destructs an allocator
			* @param[in]	allocator	The allocator that should be deallocated
			*/
			static void DestructAllocator(Allocator* allocator);
		private:
			memory::FreeListAllocator* all_allocators_; //!< An allocator that stores ALL allocators in this process
			memory::FreeListAllocator* memory_allocator_; //!< An allocator that stores ALL available memory in this process
			MemoryPool* memory_pool_; //!< The ENTIRE memory pool that is available in this process

			static MemoryManager* instance_; //!< Singleton instance of this MemoryManager
		};

		//------------------------------------------------------------------------------------------------------
		template<typename T>
		PoolAllocator* MemoryManager::PoolAllocator(const size_t& size)
		{
			return MemoryManager::Instance()->ConstructAllocator<memory::PoolAllocator, T>(size);
		}

		//------------------------------------------------------------------------------------------------------
		template<typename T, typename...Args>
		inline T* MemoryManager::Allocate(Allocator* allocator, Args...args)
		{
			return new (allocator->Allocate(sizeof(T), __alignof(T))) T(args...);
		}

		//------------------------------------------------------------------------------------------------------
		template<typename T, typename...Args>
		inline T* MemoryManager::AllocateArray(Allocator* allocator, const size_t& length, Args...args)
		{
			BB_ASSERT(length > 0, "Length of the array needs to be at least 1.");

			uint32_t header_size = sizeof(size_t) / sizeof(T); 
			
			if (sizeof(size_t) % sizeof(T) > 0)
				header_size += 1;

			T* ptr = ((T*) allocator->Allocate(sizeof(T) * (length + header_size), __alignof(T))) + header_size;

			*(((size_t*)ptr) - 1) = length;

			for (int i = 0; i < length; i++)
			{
				new (&ptr[i]) T(args...);
			}

			return ptr;
		}

		//------------------------------------------------------------------------------------------------------
		template<typename T>
		inline void MemoryManager::Deallocate(Allocator* allocator, T* ptr)
		{
			ptr->~T();
			allocator->Deallocate(ptr);
		}

		//------------------------------------------------------------------------------------------------------
		template<typename T>
		inline void MemoryManager::DeallocateArray(Allocator* allocator, T* arr)
		{
			size_t length = *(((size_t*)arr) - 1);

			for (int i = 0; i < length; i++)
			{
				arr[i].~T();
			}

			uint32_t header_size = sizeof(size_t) / sizeof(T);

			if (sizeof(size_t) % sizeof(T) > 0)
				header_size += 1;

			allocator->Deallocate(arr - header_size);
		}

		//------------------------------------------------------------------------------------------------------
		template<typename T>
		inline T* MemoryManager::ConstructAllocator(const size_t& size)
		{
			void* new_alloc = all_allocators_->Allocate(sizeof(T), __alignof(T));
			void* new_memory_zone = memory_allocator_->Allocate(size);

			return new (new_alloc)T(new_memory_zone, size);
		}

		//------------------------------------------------------------------------------------------------------
		template<typename T, typename B>
		inline T* MemoryManager::ConstructAllocator(const size_t& size)
		{
			void* new_alloc = all_allocators_->Allocate(sizeof(T), __alignof(T));
			void* new_memory_zone = memory_allocator_->Allocate(size);

			return new (new_alloc)T(new_memory_zone, size, sizeof(B), __alignof(B));
		}
	}
}