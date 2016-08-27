#pragma once

#include "../../../blowbox/core/memory/allocator.h"

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::StlAllocator
		* @author Riko Ophorst
		* @brief Wrapper class around blowbox-allocators to make them STL compliant
		* @tparam T The object to be allocated in the allocator
		*/
		template <typename T>
		class StlAllocator : public std::allocator<T>
		{
		public:
			typedef size_t size_type; //!< The size type we use to define sizes
			typedef T* pointer; //!< Shorthand for this allocator's pointer type
			typedef const T* const_pointer; //!< Shorthand for this allocator's const pointer type

			/**
			* @struct blowbox::memory::StlAllocator::rebind
			* @author Riko Ophorst
			* @brief Allows for smart rebind of the StlAllocator
			* @tparam	_Tp1	The type to rebind to
			*/
			template<typename _Tp1>
			struct rebind
			{
				typedef StlAllocator<_Tp1> other; //!< New type will be available under this
			};

			/**
			* @brief Allocates N number of elements
			* @param[in]	n		The number of elements to allocate
			* @param[in]	hint	Hint
			*/
			pointer allocate(size_type n, const void *hint = 0)
			{
				return MemoryManager::AllocateArray<T>(allocator_, n);
			}

			/**
			* @brief Deallocates N number of elements
			* @param[in]	p	The object to deallocate
			* @param[in]	n	Number to deallocate
			*/
			void deallocate(pointer p, size_type n)
			{
				return MemoryManager::DeallocateArray<T>(allocator_, p);
			}

			/**
			* @brief Get the underlying allocator
			*/
			Allocator* GetAllocator()
			{
				return allocator_;
			}

			/**
			* @brief Get the underlying allocator
			*/
			Allocator* GetAllocator() const
			{
				return allocator_;
			}

			/**
			* @brief StlAllocator constructor
			* @param[in]	allocator	The underlying allocator the StlAllocator should utilise
			*/
			StlAllocator(Allocator* allocator) throw() : std::allocator<T>() 
			{ 
				allocator_ = allocator;
			}

			/**
			* @brief StlAllocator copy-constructor
			* @param[in]	allocator	The underlying StlAllocator the new StlAllocator should copy from
			*/
			StlAllocator(const StlAllocator& allocator) throw() : std::allocator<T>(a)
			{ 
				allocator_ = allocator.GetAllocator();
			}

			/**
			* @brief StlAllocator copy-constructor
			* @param[in]	allocator	The underlying StlAllocator the new StlAllocator should copy from
			*/
			template <class U>
			StlAllocator(const StlAllocator<U>& allocator) throw() : std::allocator<T>(a)
			{
				allocator_ = allocator.GetAllocator();
			}

			/**
			* @brief StlAllocator destructor
			*/
			~StlAllocator() throw() 
			{
				//MemoryManager::Instance()->DestructAllocator(allocator_);
			}
		private:
			Allocator* allocator_; //!< The underlying allocator this StlAllocator uses
		};
	}
}