#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

struct Foo
{
	char m1;
	char m3;
	int m2;
};

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	MemoryManager::Create();
	
	Sleep(2000);
	FreeListAllocator* stack_allocator = MemoryManager::Instance()->ConstructAllocator<FreeListAllocator>(10000);
	StackAllocator* stack_allocator2 = MemoryManager::Instance()->ConstructAllocator<StackAllocator>(10000);
	
	void* p1 = stack_allocator->Allocate(1000, 16);
	void* p2 = stack_allocator->Allocate(1000, 8);
	void* p3 = stack_allocator->Allocate(1000, 8);

	stack_allocator->Deallocate(p3);
	stack_allocator->Deallocate(p2);
	stack_allocator->Deallocate(p1);

	p1 = stack_allocator->Allocate(1000, 8);

	p2 = stack_allocator2->Allocate(2000, 8);
	p3 = stack_allocator2->Allocate(2000, 8);

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
