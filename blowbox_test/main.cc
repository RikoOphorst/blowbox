#include "blowbox/blowbox_include.h"

#include <iostream>
#include <vector>

using namespace blowbox;
using namespace blowbox::direct3d;

int main(int argc, char** argv)
{
#ifdef _DEBUG
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	Sleep(250);

	memory::MemoryManager* mem_manager = memory::MemoryManager::Create();

	std::cout << sizeof(memory::MemoryManager) << std::endl;

	std::cin.get();

#ifdef _DEBUG
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
