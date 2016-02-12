#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

class Foo
{
public:
	Foo()
	{
		std::cout << "Foo constructed" << std::endl;
	}
	~Foo()
	{
		std::cout << "Foo destroyed" << std::endl;
	}
	char m1;
	char m3;
	int m2[10];
};

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	MemoryManager::Create();

	PoolAllocator* allocator = MemoryManager::Instance()->ConstructAllocator<PoolAllocator, Foo>(20000);

	Foo* f1 = MemoryManager::Allocate<Foo>(allocator);
	Foo* f2 = MemoryManager::Allocate<Foo>(allocator);
	Foo* f3 = MemoryManager::Allocate<Foo>(allocator);

	for (int i = 0; i < 416; i++)
	{
		Sleep(25);
		MemoryManager::Allocate<Foo>(allocator);
	}

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}