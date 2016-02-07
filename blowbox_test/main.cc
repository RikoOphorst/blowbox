#include "blowbox/blowbox_include.h"

#include <iostream>

using namespace blowbox;
using namespace blowbox::direct3d;

struct SomeBullshitObject
{
	int abc[20];
	uint64_t lol;
};

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	memory::LinearAllocator* linear_allocator = new memory::LinearAllocator(malloc(100000), 100000);

	std::cout << "Size of object:\t\t" << sizeof(SomeBullshitObject) << std::endl;
	std::cout << "Align of object:\t" << __alignof(SomeBullshitObject) << std::endl;
	std::cout << "Start of alloc:\t\t" << (uintptr_t)linear_allocator->GetStart() << std::endl;

	for (int i = 0; i < 1136; i++)
	{
		std::cout << "New alloc on:\t\t" << (uintptr_t)linear_allocator->Allocate(sizeof(SomeBullshitObject), __alignof(SomeBullshitObject)) << std::endl;
	}

	std::cout << "Used memory:\t\t" << linear_allocator->GetUsedMemory() << std::endl;
	std::cout << "Num allocations:\t" << linear_allocator->GetNumAllocations() << std::endl;

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
