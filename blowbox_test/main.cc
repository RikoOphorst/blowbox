#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

class Foo
{
public:
	Foo(){
		std::cout << "Foo constructed" << std::endl;
	}
	~Foo()
	{
		std::cout << "Foo destroyed" << std::endl;
	}
	char m1;
	char m3;
	int m2[500];
};

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	MemoryManager::Create();

	FreeListAllocator* allocator = MemoryManager::Instance()->ConstructAllocator<FreeListAllocator>(10000);
	
	Sleep(1000);
	void* foo_addr = allocator->Allocate(sizeof(Foo), __alignof(Foo));

	Sleep(2500);
	Foo* act_foo = new (foo_addr)Foo();

	{
		SharedPtr<Foo> foo_outside;
		{
			Sleep(2500);
			SharedPtr<Foo> foo = SharedPtr<Foo>(act_foo, allocator);
			foo_outside = foo;
			Sleep(2500);
		}
		std::cout << "outside first block" << std::endl;
		Sleep(2500);
	}
	std::cout << "outside all blocks" << std::endl;

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
