#pragma once

#include "../../core/memory/memory_manager.h"
#include "../../core/memory/free_list_allocator.h"
#include "../../core/memory/pool_allocator.h"
#include "../../core/memory/stack_allocator.h"
#include "../../core/memory/linear_allocator.h"
#include "../../core/memory/stl_allocator.h"

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::MemoryObject
		* @author Riko Ophorst
		* @brief An inheritable object for objects that will be heap-allocated using the custom memory allocators
		*/
		class MemoryObject
		{
		public:
			/**
			* @brief MemoryObject constructor
			* @param[in]	allocator	The allocator that is used to allocate this object
			*/
			MemoryObject(memory::Allocator* allocator) : self_storage_allocator_(allocator) {} 

			memory::Allocator* GetSelfStorageAllocator() const; //<! Get the self storage allocator, useful if you want to deallocate this object without knowing who allocated it

		protected:
			memory::Allocator* self_storage_allocator_; //<! The allocator used to allocate this object
		};

		/**
		* @class blowbox::memory::MObject
		* @author Riko Ophorst
		* @brief Proxy of blowbox::memory::MemoryObject to ease the syntax a little bit
		*/
		class MObject : public MemoryObject
		{
		public:
			/**
			* @brief MObject constructor
			* @param[in]	allocator	The allocator that is used to allocate this object
			*/
			MObject(memory::Allocator* allocator) : MemoryObject(allocator) {}
		};
	}
}