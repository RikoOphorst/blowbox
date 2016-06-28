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
		class MemoryObject
		{
		public:
			MemoryObject(memory::Allocator* allocator) : allocator_(allocator) {} 
			memory::Allocator* GetAllocator() const;

		protected:
			memory::Allocator* allocator_;
		};

		class MObject : public MemoryObject
		{
		public:
			MObject(memory::Allocator* allocator) : MemoryObject(allocator) {}
		};
	}
}