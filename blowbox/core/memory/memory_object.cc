#include "memory_object.h"

blowbox::memory::Allocator* blowbox::memory::MemoryObject::GetSelfStorageAllocator() const
{
	return self_storage_allocator_;
}
