#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	MemoryManager::Create();
	
	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
