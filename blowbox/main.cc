#include "../blowbox/core/boot_manager.h"

#include "../blowbox/filesystem/file_system_manager.h"

#include <iostream>

using namespace blowbox;

int main(int argc, char** argv)
{
	BootManager* boot_manager = new BootManager();
	boot_manager->Boot(argc, argv);

	boot_manager->ShutDown();
	delete boot_manager;

	return 0;
}