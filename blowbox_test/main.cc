#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <comdef.h>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

int main(int argc, char** argv)
{
	Blowbox* blowbox = Blowbox::Create();
	blowbox->Initialise();

	blowbox->Run();

	MemoryManager::Deallocate(blowbox->GetSelfStorageAllocator(), blowbox);

	return 0;
}