#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <comdef.h>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 1

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;


int main(int argc, char** argv)
{
	Blowbox* blowbox = Blowbox::Create();

	blowbox->Initialise();

	blowbox->Run();

	std::cin.get();
	return 0;
}