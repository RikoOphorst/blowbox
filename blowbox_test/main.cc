#include "blowbox/blowbox_include.h"

#include <iostream>

using namespace blowbox;
using namespace blowbox::direct3d;

struct Header
{
	uintptr_t hallo;
	int bay;
	int bay2;
};

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	memory::MemoryManager::Create();
	memory::MemoryManager::Instance();

	uintptr_t address = 1240;

	std::vector<int> alignments;
	alignments.push_back(1024);
	alignments.push_back(512);
	alignments.push_back(256);
	alignments.push_back(128);
	alignments.push_back(64);
	alignments.push_back(32);
	alignments.push_back(16);

	for (int i = 0; i < alignments.size(); i++)
	{
		std::cout << "Address: " << address;
		std::cout << "\tAlignment: " << alignments[i];
		std::cout << "\tAligned address: " << (uintptr_t)memory::PointerUtil::AlignForward((void*)address, alignments[i]);
		std::cout << "\tAdjustment: " << (uintptr_t)memory::PointerUtil::AlignForwardAdjustment((void*)address, alignments[i]);
		std::cout << "\tHeader size: " << sizeof(Header);
		std::cout << "\tHeaded adjustment: " << (uintptr_t)memory::PointerUtil::AlignForwardAdjustmentWithHeader((void*)address, alignments[i], sizeof(Header)) << std::endl;
	}

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}
