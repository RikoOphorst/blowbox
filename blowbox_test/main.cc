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
		m1 = 'E';
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

	FreeListAllocator* allocator = MemoryManager::Instance()->ConstructAllocator<FreeListAllocator>(20000);

	util::LinkedList<Foo> list(allocator);

	std::cout << "List is empty: " << list.IsEmpty() << std::endl;

	std::cout << "Add an element" << std::endl;
	
	Foo* fighters[4];

	std::cout << "sizeof foo " << sizeof(Foo) << std::endl;

	for (int i = 0; i < 4; i++)
	{
		fighters[i] = MemoryManager::Allocate<Foo>(allocator);
		list.PushFront(*fighters[i]);
	}

	fighters[2]->m1 = 'R';
	
	for (auto i = list.Begin(); i != list.End(); i++)
	{
		std::cout << i->m1 << std::endl;
	}

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
